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


void sys_err(const char *s) {
    perror(s);
    exit(-1);
}
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

int main() {
    // Server 端的监听地址
    auto msg = InitTestClient("192.168.30.170:1234");
    // Put your code Here!

    int len;
    int lfd;
    

    struct sockaddr_in serv_addr;
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(9999);
    inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr);

    lfd = socket(AF_INET, SOCK_STREAM, 0);
    if (lfd == -1) {
        sys_err("socket error");
    }

    int ret = connect(lfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr));
    if (ret != 0) {
        sys_err("connect err");
    }

    for (;;) {
        auto str = msg->pop();
        const char *data = str.data();

        len = str.size();
        if (len == 0) {
            continue;
        }

        char buf[len];
        int length = htonl(len);

        strncpy(buf, data, len);
        Writen(lfd, &length, sizeof(len));
        int ret = Writen(lfd, buf, len);
        if (ret == -1) {
            sys_err("write error");
        } else if (ret == 0) {
            break;
        }
        Writen(STDOUT_FILENO, buf, len);
        Writen(STDOUT_FILENO, "\n", 1);
    }

    close(lfd);

    return 0;
}
