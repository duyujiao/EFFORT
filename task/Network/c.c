#include "Msg.h"
#include "NetworkTest.grpc.pb.h"
#include "NetworkTest.pb.h"
#include <algorithm>
#include <arpa/inet.h>
#include <asm-generic/socket.h>
#include <bits/types/FILE.h>
#include <chrono>
#include <climits>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstring>
#include <deque>
#include <exception>
#include <fcntl.h>
#include <grpc/grpc.h>
#include <grpcpp/channel.h>
#include <grpcpp/client_context.h>
#include <grpcpp/create_channel.h>
#include <grpcpp/security/credentials.h>
#include <grpcpp/support/status.h>
#include <memory>
#include <mutex>
#include <ostream>
#include <random>
#include <stdexcept>
#include <string>
#include <sys/socket.h>
#include <sys/stat.h>
#include <thread>
#include <unistd.h>
#include <vector>

class ClientTester {
    friend void RunClientTest(std::shared_ptr<ClientTester> tester);
    using NT = NetworkTest::NT;
    using Stub = NetworkTest::NT::Stub;
    using Result = NetworkTest::Result;
    using runtime_error = std::runtime_error;
    using Context = ::grpc::ClientContext;

    std::unique_ptr<Stub> stub;
    std::default_random_engine re;
    std::uniform_int_distribution<char> AsciiStringGenerator;
    std::uniform_int_distribution<char> BinStringGenerator;
    std::uniform_int_distribution<uint32_t> LenGenerator;
    int fd;
    void QueryStatus(uint64_t idx, Result &response) {
        if (idx < 0)
            runtime_error("No Exist msg Idx<0\n");
        if (idx <= SuccessMaxIdx) {
            response.set_id(SuccessMaxIdx);
            response.set_reason(Success);
            return;
        }
        Context context;
        NetworkTest::Query query;
        query.set_id(idx);
        auto res = stub->ResultQuery(&context, query, &response);
        if (!res.ok())
            runtime_error("Test Error,Please Retry!\n");
        if (response.reason() >= ErrorLevel)
            throw std::runtime_error(
                    ErrorCode2Msg(static_cast<TestStatus>(response.reason())));
        if (response.reason() == Success)
            SuccessMaxIdx = std::max(SuccessMaxIdx, response.id());
    }
    void SendAnswer(const std::string &s) {
        SendSeq++;
        Context context;
        Result response;
        ::NetworkTest::Register answer;
        answer.set_content(s);
        auto res = stub->AnswerRegister(&context, answer, &response);
        if (!res.ok())
            runtime_error("Test Error,Please Retry!\n");
        if (response.reason() >= ErrorLevel)
            throw std::runtime_error(
                    ErrorCode2Msg(static_cast<TestStatus>(response.reason())));
        if (response.reason() == Success)
            SuccessMaxIdx = std::max(SuccessMaxIdx, response.id());
    }
    uint32_t SendSeq = -1;
    uint32_t SuccessMaxIdx = -1;
    static const char *ErrorCode2Msg(TestStatus s) noexcept {
        switch (s) {
            case Success:
                return "Success";
            case Wait:
                return "Wait For Msg";
            case WaitRPC:
                return "Wait For Test";
            case Diff:
                return "Msg is Error";
            case Unknow:
                return "Unknow Error";
            case ErrorLevel:
            case TestError:;
        }
        return "Tester is Error";
    }

    TestStatus Check() {
        using namespace std::chrono_literals;
        Result response;
        QueryStatus(SendSeq, response);
        if (response.id() == SendSeq && response.reason() == Success)
            return Success;
        std::this_thread::sleep_for(3s);
        return (response.id() == SendSeq && response.reason() == Success)
                       ? Success
                       : static_cast<TestStatus>(response.reason());
    }

    void genAsciiMsg(uint64_t size) {
        for (uint64_t i = 0; i < size; i++) {
            auto len = LenGenerator(re);
            auto ch = AsciiStringGenerator(re);
            std::string s(len, ch);
            SendAnswer(s);
            msgs->push(std::move(s));
        }
    }

    void genBinMsg(uint64_t size) {
        for (uint64_t i = 0; i < size; i++) {
            auto len = LenGenerator(re);
            std::string s;
            for (auto t = 0; t < len; t++)
                s.push_back(BinStringGenerator(re));
            SendAnswer(s);
            msgs->push(std::move(s));
        }
    }
    uint64_t getSeed() {
        fd = open("/dev/urandom", O_RDONLY);
        uint64_t seed;
        auto rc = read(fd, &seed, sizeof(seed));
        if (rc != sizeof(seed))
            throw runtime_error("read /dev/random failed");
        return seed;
    }

public:
    ClientTester(std::string addr)
        : stub(NT::NewStub(
                  grpc::CreateChannel(addr, grpc::InsecureChannelCredentials()))),
          re(getSeed()), msgs(std::make_shared<MsgBuf>()),
          AsciiStringGenerator(' ', '~'), BinStringGenerator(CHAR_MIN, CHAR_MAX),
          LenGenerator(0, 4096) {}
    std::shared_ptr<MsgBuf> msgs;
    void FinishCheck() {
        auto res = Check();
        if (res == Success) {
            puts("Congratulations! You Pass The Test!");
            _exit(0);
        }
        printf("Sorry! You did not pass all Test. Reason:%s  :(\n",
               ErrorCode2Msg(res));
    }
};
void RunClientTest(std::shared_ptr<ClientTester> tester) {
    try {
        using namespace std::chrono_literals;
        tester->genAsciiMsg(1);
        std::this_thread::sleep_for(2s);
        auto reslut = tester->Check();
        if (reslut != Success) {
            printf("QAQ: Failed at 1\n");
        }
        tester->genAsciiMsg(1);
        reslut = tester->Check();
        if (reslut != Success) {
            printf("QAQ: Failed at 2\n");
        }
        tester->genAsciiMsg(1);
        reslut = tester->Check();
        if (reslut != Success) {
            printf("QAQ: Failed at 3\n");
        }
        tester->genBinMsg(1);
        reslut = tester->Check();
        if (reslut != Success) {
            printf("QAQ: Failed at 4\n");
        }
        tester->genBinMsg(1);
        reslut = tester->Check();
        if (reslut != Success) {
            printf("QAQ: Failed at 5\n");
        }
        tester->genBinMsg(1);
        reslut = tester->Check();
        if (reslut != Success) {
            printf("QAQ: Failed at 6\n");
        }
        tester->genAsciiMsg(1024);
        reslut = tester->Check();
        if (reslut != Success) {
            printf("QAQ: Failed at 7\n");
        }
        tester->genBinMsg(1024);
        reslut = tester->Check();
        if (reslut != Success) {
            printf("QAQ: Failed at 8\n");
        }
        tester->genAsciiMsg(1024);
        reslut = tester->Check();
        if (reslut != Success) {
            printf("QAQ: Failed at 9\n");
        }
        tester->genBinMsg(1024);
        reslut = tester->Check();
        if (reslut != Success) {
            printf("QAQ: Failed at 10\n");
        }
        printf("Success Pass All Test\n");
        _exit(0);
    } catch (...) {
        printf("Exception:\n");
    }
}
std::shared_ptr<MsgBuf> InitTestClient(std::string addr) {
    try {
        auto tester = std::make_shared<ClientTester>(addr);
        auto test_thread = std::thread(RunClientTest, tester);
        test_thread.detach();
        return tester->msgs;
    } catch (std::exception &e) {

        printf("Exception: %s\n", e.what());
    }
    return nullptr;
}

struct Message {
    int msgID;
    int partID;
    std::string data;
};
class mess {
    int partid;
    int len;
};
void sys_err(const char *str)
{
    perror(str);
    exit(1);
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
    auto msg = InitTestClient("127.0.0.1:1234");
    // Put your code Here!

    int cfd;
    int len;
    struct sockaddr_in serv_addr;
    serv_addr.sin_family=AF_INET;
    serv_addr.sin_port=htons(PORT);
    inet_pton(AF_INET,"127.0.0.1",&serv_addr.sin_addr.s_addr);

    cfd=socket(AF_INET,SOCK_STREAM,0);
    if(cfd==-1)
    {
        sys_err("socket error");
    }

    int ret=connect(cfd,(struct sockaddr*)&serv_addr,sizeof(serv_addr));
    if(ret!=0)
    {
        sys_err("connect error");
    }

    for(;;)
    {
        auto str=msg->pop();
        const char*data=str.data();

        len=str.size();
        if(len==0)
        {
            continue;
        }
         printf("len = %d\n", len);
        char buf[len];
        int length=htonl(len);

        strncpy(buf,data,len);
        Writen(cfd,&length,sizeof(len));
        int ret = Writen(cfd, buf, len);
        if (ret == -1) 
        {
            sys_err("Write error");
        } 
        else if (ret == 0)
        {
            break;
        }
        Writen(STDOUT_FILENO, buf, len);
        Writen(STDOUT_FILENO, "\n", 1);
    }
    close(cfd);
    return 0;

}


//从文件描述符fd中读取n个字节的数据
ssize_t readn(int fd,void*buffer,size_t n)
{
    ssize_t numRead;//本次读取的数据
    ssize_t totRead;//已经读取的数据
    char* buf;//缓冲区指针

    buf=(char*)buffer;
    //循环读取数据，直到读取到n个字节的数据
    for(totRead=0;totRead<n;)
    {
        numRead=read(fd,buf,n-totRead);//从fd中读取数据
        if(numRead==0)//如果读取到文件末尾，返回已读取的字节数
        {
            return totRead;
        }
        if(numRead==-1)//如果读取出错
        {
            if(errno==EINTR)//如果是由于中断导致的错误，继续读取
            {
                continue;
            }
            else//其他错误。返回-1
            return -1;
        }
        totRead+=numRead;//更新已读取的字节数
        buf+=numRead;//更新缓冲区指针
    }
    return totRead;//返回已读取的字节数
}