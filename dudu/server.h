#ifndef SERVER_H
#define SERVER_H

#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <iostream>
#include <thread>
#include <vector>
using namespace std;

#include"global.h"
class server
{
    private:
    //服务器端口号
    int server_port;
    //设为listen状态的套接字描述符
    int server_sockfd;
    //服务器ip
    string server_ip;
    //保存所有的套接字描述符
    //vector<int> sock_arr;
      static vector<bool> sock_arr;//改为了静态成员变量，且类型变为vector<bool>
    public:
    //构造函数
    server(int port,string ip);
    //析构函数
    ~server();
    //服务器开始服务
    void run();
    //子线程工作的静态函数
    static void RecvMsg(int conn);
    static void HandleRequest(int conn,string str);
};



#endif