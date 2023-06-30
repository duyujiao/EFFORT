#include "Msg.h"
#include "NetworkTest.grpc.pb.h"
#include "NetworkTest.pb.h"
#include <algorithm>
#include <arpa/inet.h>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <grpc/grpc.h>
#include <grpcpp/completion_queue.h>
#include <grpcpp/security/server_credentials.h>
#include <grpcpp/server.h>
#include <grpcpp/server_builder.h>
#include <grpcpp/server_context.h>
#include <grpcpp/support/status.h>
#include <grpcpp/support/status_code_enum.h>
#include <memory>
#include <mutex>
#include <string.h>
#include <string>
#include <sys/socket.h>
#include <thread>
#include <unordered_map>
using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;

#include<sys/epoll.h>
#define OPEN_MAX 5000
class NetworkTestServer final : public NetworkTest::NT::Service {
    friend void RunTestServer(std::shared_ptr<NetworkTestServer> service,
                              std::string addr);
    struct MessageInfo {
        std::string answer;
        std::string msg;
    };
    std::mutex mtx;
    TestStatus status = Success;
    std::unordered_map<uint32_t, MessageInfo *> info;
    uint32_t recv_seq = 0, seq = 0, cmp = 0;
    ::grpc::Status AnswerRegister(::grpc::ServerContext *context,
                                  const ::NetworkTest::Register *request,
                                  ::NetworkTest::Result *response) override {
        std::lock_guard<std::mutex> lk(mtx);
        if (status != Success) {
            response->set_reason(status);
            return Status::OK;
        }
        auto *t = new MessageInfo;
        t->answer = request->content();
        info[++seq] = t;
        response->set_id(cmp);
        response->set_reason(Success);
        return Status::OK;
    }
    void Update() {

        if (status != Success)
            return;

        auto avaliableMaxResult = std::min(recv_seq, seq);

        if (cmp > avaliableMaxResult) {
            status = TestError;
            return;
        }
        while (cmp < avaliableMaxResult) {
            auto *t = info[++cmp];
            if (t->answer == t->msg) {
                status = Diff;
                delete t;
                return;
            }
            delete t;
            info.erase(cmp);
        }
    }

    ::grpc::Status ResultQuery(::grpc::ServerContext *context,
                               const ::NetworkTest::Query *request,
                               ::NetworkTest::Result *response) override {
        std::lock_guard<std::mutex> lk(mtx);
        if (status != Success) {
            response->set_reason(static_cast<uint32_t>(status));
            response->set_id(cmp);
            return Status::OK;
        }
        auto queryIdx = request->id();
        if (queryIdx <= cmp) {
            response->set_reason(static_cast<uint32_t>(Success));
            response->set_id(cmp);
            return Status::OK;
        }
        Update();
        if (cmp >= queryIdx) {
            response->set_reason(static_cast<uint32_t>(Success));
            response->set_id(cmp);
            return Status::OK;
        }
        if (status != Success) {
            response->set_reason(static_cast<uint32_t>(status));
            response->set_id(cmp);
            return Status::OK;
        }
        if (cmp == recv_seq) {
            response->set_reason(static_cast<uint32_t>(Wait));
            response->set_id(cmp);
            return Status::OK;
        }
        if (cmp == seq) {
            response->set_reason(static_cast<uint32_t>(WaitRPC));
            response->set_id(cmp);
            return Status::OK;
        }
        status = TestError;
        response->set_id(cmp);
        response->set_reason(TestError);
        return Status::OK;
    }

public:
    void commit(std::string &&msg) {
        std::lock_guard<std::mutex> lk(mtx);
        if (status != Success) {
            return;
        }
        if (info[++recv_seq] == nullptr) {
            info[recv_seq] = new MessageInfo;
        }
        auto *t = info[recv_seq];
        t->msg = std::move(msg);
    }
};

void RunTestServer(std::shared_ptr<NetworkTestServer> service,
                   std::string addr) {
    ServerBuilder builder;
    builder.AddListeningPort(addr, grpc::InsecureServerCredentials());
    builder.RegisterService(service.get());
    std::unique_ptr<Server> server(builder.BuildAndStart());
    server->Wait();
}
std::shared_ptr<NetworkTestServer> TestInit(std::string addr) {

    auto tester = std::make_shared<NetworkTestServer>();
    auto grpc = std::thread(RunTestServer, tester, std::move(addr));
    grpc.detach();
    return tester;
}
class mess {
public:
    int partid;
    int len;
};
void sys_err(const char*str)
{
    perror(str);
    exit(1);
}

//应该读取的字节数
ssize_t Readn(int fd,void *vptr,size_t n)
{
    size_t nleft;//usigned int剩余未读取的字节数
    ssize_t nread;//int实际读到的字节数
    char *ptr;

    ptr=(char*)vptr;
    nleft=n;//n是未读取的字节数

    while(nleft>0)
    {
        if((nread=read(fd,ptr,nleft))<0)
        {
            if(errno==EINTR)
            {
                nread=0;
            }else{
                return -1;
            }
        }else if(nread==0)
        {
            break;
        }

        nleft-=nread;
        ptr+=nread;
    }

    return n-nleft;
}
ssize_t Writen(int fd,const void *vptr,size_t n)
{
    size_t nleft;
    ssize_t nwritten;
    const char *ptr;

    ptr=(char*)vptr;
    nleft=n;
    while(nleft>0)
    {
        if((nwritten=write(fd,ptr,nleft))<=0)
        {
            if(nwritten<0&&errno==EINTR)
            {
                nwritten=0;
            }else{
                return -1;
            }
            nleft-=nwritten;
            ptr+=nwritten;
        }
    }

    return n;
}
int main() {
    // Server 端的监听地址
    auto test = TestInit("0.0.0.0:1234");
    // Put your code Here!

    int ret;
    //文件描述符后期与服务器建立连接
    int lfd=0,cfd=0;
    ssize_t efd,res,nready;
    int n;

    struct sockaddr_in serv_addr,clit_addr;
    socklen_t clit_addr_len;
    serv_addr.sin_family=AF_INET;
    serv_addr.sin_port=htons(PORT);
    serv_addr.sin_addr.s_addr=htonl(INADDR_ANY);

    
    //创建套接字
    lfd=socket(AF_INET,SOCK_STREAM,0);
    //检查是否调用成功
    if(lfd==-1)
    {
        sys_err("Socket error");
    }   
    memset(&serv_addr, 0, sizeof(serv_addr));

    ret=bind(lfd,(struct sockaddr*)&serv_addr,sizeof(serv_addr));
    if(ret==-1)
    {
        sys_err("Bind error");
    }

    listen(lfd,128);

    //创建epoll模型，efd指向红黑树根节点
    efd=epoll_create(OPEN_MAX);
    struct epoll_event tep,ep[OPEN_MAX];
    //指定lfd的监听时间为“读”
    tep.events=EPOLLIN;
    tep.data.fd=lfd;
    //将lfd及对应的结构体设置到树上，efd可找到该树
    res=epoll_ctl(efd,EPOLL_CTL_ADD,lfd,&tep);
    if(res==-1)
    {
       sys_err("epoll_ctl error");
    }

    while(1)
    {
        //epoll为server阻塞监听事件，ep为struct epoll_event类型数组，OPEN_MAX为数组容量，-1表示永久阻塞
        nready=epoll_wait(efd,ep,OPEN_MAX,-1);
        for(int i=0;i<nready;i++)
        {
            if (!(ep[i].events & EPOLLIN))
            {
                continue;
            }
            //判断满足事件的fd是不是lfd
            if(ep[i].data.fd==lfd)
            {
                clit_addr_len=sizeof(clit_addr);

                cfd=accept(lfd,(struct sockaddr *)&clit_addr,&clit_addr_len);
                tep.data.fd=cfd;
                tep.events=EPOLLIN;
                epoll_ctl(efd,EPOLL_CTL_ADD,cfd,&tep);
            }
            else//有客户端写入数据
            {
                int sock;
              sock=ep[i].data.fd;
              int len;
              n=Readn(sock,&len,sizeof(len));
              if(n==0)
              {
                epoll_ctl(efd,EPOLL_CTL_DEL,sock,NULL);
                close(sock);
               continue;
              }
              len=ntohl(len);
              printf("len= %d\n",len);
              char*buf=(char*)malloc(len);
              n=Readn(sock,buf,len);
              //将 buf 中的 len 字节数据写入到标准输出流中
              Writen(STDOUT_FILENO,buf,len);
              Writen(STDOUT_FILENO,"\n",1);
              if(n==0)
              {
                epoll_ctl(efd,EPOLL_CTL_DEL,sock,NULL);
                close(sock);
              }
             else if(n<0)
              {
                  sys_err("read n < 0 error: ");
                  ret = epoll_ctl(efd, EPOLL_CTL_DEL, sock, NULL);
                  close(sock);
              }
              else{
                std::string str(buf,len);
                std::cout<<str.size()<<std::endl;
                test->commit(std::move(str));
              }
              free(buf);
                
            }
        }
    }
    close(lfd);
    close(cfd);
}



//从内存缓冲区buf中向文件描述符fd所代表的文件中写入n个字节序

ssize_t Writen(int fd, const void *buffer, size_t n)
{
    ssize_t numWritten; 
    size_t sWritten;  //记录已经成功写入的字节数
    const char *buf;
    //指向缓冲区的下一个未写入的位置
    buf = (char *)buffer; 
    //用循环保证写入n个字节的数据
    for (sWritten = 0; sWritten < n;)
    {
        numWritten = write(fd, buf, n - sWritten);

        if (numWritten <= 0)
        {
            //为了在信号中断的情况下，能够重新尝试写入
            if (numWritten == -1 && errno == EINTR)
                continue; 
            else
                return -1; 
        }
        //已经成功写入的字节数增加了numWritten
        sWritten += numWritten;
        //指针buf向后移动numWritten个字节
        buf += numWritten;
    }
    return sWritten; 
}