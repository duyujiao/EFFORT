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

#include <sys/epoll.h>
#define OPEN_MAX 5000
class NetworkTestServer final : public NetworkTest::NT::Service
{
    friend void RunTestServer(std::shared_ptr<NetworkTestServer> service,
                              std::string addr);
    struct MessageInfo
    {
        std::string answer;
        std::string msg;
    };
    std::mutex mtx;
    TestStatus status = Success;
    std::unordered_map<uint32_t, MessageInfo *> info;
    uint32_t recv_seq = 0, seq = 0, cmp = 0;
    ::grpc::Status AnswerRegister(::grpc::ServerContext *context,
                                  const ::NetworkTest::Register *request,
                                  ::NetworkTest::Result *response) override
    {
        std::lock_guard<std::mutex> lk(mtx);
        if (status != Success)
        {
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
    void Update()
    {

        if (status != Success)
            return;

        auto avaliableMaxResult = std::min(recv_seq, seq);

        if (cmp > avaliableMaxResult)
        {
            status = TestError;
            return;
        }
        while (cmp < avaliableMaxResult)
        {
            auto *t = info[++cmp];
            if (t->answer == t->msg)
            {
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
                               ::NetworkTest::Result *response) override
    {
        std::lock_guard<std::mutex> lk(mtx);
        if (status != Success)
        {
            response->set_reason(static_cast<uint32_t>(status));
            response->set_id(cmp);
            return Status::OK;
        }
        auto queryIdx = request->id();
        if (queryIdx <= cmp)
        {
            response->set_reason(static_cast<uint32_t>(Success));
            response->set_id(cmp);
            return Status::OK;
        }
        Update();
        if (cmp >= queryIdx)
        {
            response->set_reason(static_cast<uint32_t>(Success));
            response->set_id(cmp);
            return Status::OK;
        }
        if (status != Success)
        {
            response->set_reason(static_cast<uint32_t>(status));
            response->set_id(cmp);
            return Status::OK;
        }
        if (cmp == recv_seq)
        {
            response->set_reason(static_cast<uint32_t>(Wait));
            response->set_id(cmp);
            return Status::OK;
        }
        if (cmp == seq)
        {
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
    void commit(std::string &&msg)
    {
        std::lock_guard<std::mutex> lk(mtx);
        if (status != Success)
        {
            return;
        }
        if (info[++recv_seq] == nullptr)
        {
            info[recv_seq] = new MessageInfo;
        }
        auto *t = info[recv_seq];
        t->msg = std::move(msg);
    }
};

void RunTestServer(std::shared_ptr<NetworkTestServer> service,
                   std::string addr)
{
    ServerBuilder builder;
    builder.AddListeningPort(addr, grpc::InsecureServerCredentials());
    builder.RegisterService(service.get());
    std::unique_ptr<Server> server(builder.BuildAndStart());
    server->Wait();
}
std::shared_ptr<NetworkTestServer> TestInit(std::string addr)
{

    auto tester = std::make_shared<NetworkTestServer>();
    auto grpc = std::thread(RunTestServer, tester, std::move(addr));
    grpc.detach();
    return tester;
}
class mess
{
public:
    int partid;
    int len;
};







void sys_err(const char *s) {
    perror(s);
    exit(-1);
}


//从文件描述符fd所代表的文件中读取n个字节的数据，并将数据存储到指定的buffer中
ssize_t Readn(int fd, void *buffer, size_t n)
{
    ssize_t numRead; 
    size_t sRead;  
    char *buf;

    buf = (char *)buffer; 
    for (sRead = 0; sRead < n;)
    {
        numRead = read(fd, buf, n - sRead);

        if (numRead == 0)   
            return sRead; 
        if (numRead == -1)
        {
            if (errno == EINTR || errno == EAGAIN)
                continue;
            else
                return -1; 
        }
        sRead += numRead;
        buf += numRead;
    }
    return sRead; 
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

int main()
{
    // Server 端的监听地址
    auto test = TestInit("0.0.0.0:1234");

    int lfd,cfd, sock;
    struct sockaddr_in serv_addr, clnt_addr;
    socklen_t clnt_addr_len;
    int i, n, num = 0;
    ssize_t nready, efd, ret;
    char str[INET_ADDRSTRLEN];

    lfd = socket(AF_INET, SOCK_STREAM, 0);


    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(9999);
    bind(lfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
    listen(lfd, 128);

    //创建epoll模型，efd指向红黑树根节点
    efd = epoll_create(OPEN_MAX);
    if (efd == -1)
    {
        sys_err("epoll_create error");
    }

    struct epoll_event tep, ep[OPEN_MAX];
    //指定lfd的监听时间为“读”
    tep.events = EPOLLIN;
    tep.data.fd = lfd;
    //将lfd及对应的结构体设置到树上，efd可找到该树
    ret = epoll_ctl(efd, EPOLL_CTL_ADD, lfd, &tep);
    if (ret == -1)
    {
        sys_err("epoll_ctr error");
    }

    while (1)
    {
        //epoll为server阻塞监听事件，ep为struct epoll_event类型数组，OPEN_MAX为数组容量，-1表示永久阻塞
        nready = epoll_wait(efd, ep, OPEN_MAX, -1);
        if (nready == -1)
        {
            sys_err("epoll_wait error");
        }

        for (i = 0; i < nready; ++i)
        {
            if (!(ep[i].events & EPOLLIN))
            {
                continue;
            }

            if (ep[i].data.fd == lfd)
            {
                clnt_addr_len = sizeof(clnt_addr);
                cfd = accept(lfd, (struct sockaddr *)&clnt_addr, &clnt_addr_len);
                tep.events = EPOLLIN;
                tep.data.fd =cfd;
                ret = epoll_ctl(efd, EPOLL_CTL_ADD,cfd, &tep);
                printf("client opend connection\n");
                if (ret == -1)
                {
                    sys_err("epoll_ctl error");
                }
            }
            else
            {
                sock = ep[i].data.fd;
                int len;
                n = Readn(sock, &len, sizeof(len));
                if (n == 0)
                {
                    ret = epoll_ctl(efd, EPOLL_CTL_DEL, sock, NULL);                   
                    close(sock);
                    printf("client closed connection\n");
                    continue;
                }

                len = ntohl(len);
                char *buf = (char *)malloc(len);
                n = Readn(sock, buf, len);
                //将len字节写到标准输出流
                Writen(STDOUT_FILENO, buf, len);
                Writen(STDOUT_FILENO, "\n", 1);

                if (n == 0)
                {
                    ret = epoll_ctl(efd, EPOLL_CTL_DEL, sock, NULL);                  
                    close(sock);
                    printf("client closed connection\n");
                }
                else if (n < 0)
                {
                    perror("read n < 0 error: ");
                    ret = epoll_ctl(efd, EPOLL_CTL_DEL, sock, NULL);
                    close(sock);
                }
                else
                {
                    std::string str(buf, len);
                    test->commit(std::move(str));
                }
                free(buf);
            }
        }
    }

    close(lfd);
    close(efd);
    // Put your code Here!
}
