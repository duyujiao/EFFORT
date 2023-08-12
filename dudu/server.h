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
    static unordered_map<string,int>name_sock_map;//名字和套接字描述符
    static pthread_mutex_t name_sock_mutx;//互斥锁，锁住需要修改name_sock_map的临界区
    static unordered_map<int,set<int>>group_map;//记录群号和套接字描述符集合
    static pthread_mutex_t group_mutx;//互斥锁，锁住需要修改group_map的临界区
    public:
    //构造函数
    server(int port,string ip);
    //析构函数
    ~server();
    //服务器开始服务
    void run();
    //子线程工作的静态函数
    static void RecvMsg(int conn);
    static void HandleRequest(int conn,string str,tuple<bool,string,string,int,int> &info);
    //static void HandleRequest(int conn,string str);
   static void signalHandler(int signum) ;


};



#endif