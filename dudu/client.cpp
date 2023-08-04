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
using namespace std;
#include"client.h"
client::client(int port,string ip):server_port(port),server_ip(ip){}
client::~client()
{
    close(sock);
}

void client::run(){

    //定义sockfd
    sock = socket(AF_INET,SOCK_STREAM, 0);

    //定义sockaddr_in
    struct sockaddr_in servaddr;
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(server_port);  //服务器端口
    servaddr.sin_addr.s_addr = inet_addr(server_ip.c_str());  //服务器ip

    //连接服务器，成功返回0，错误返回-1
    if (connect(sock, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0)
    {
        perror("connect");
        exit(1);
    }
    cout<<"连接服务器成功\n";

    HandleClient(sock);

    //创建发送线程和接收线程
    thread send_t(SendMsg,sock),recv_t(RecvMsg,sock);
    send_t.join();
    cout<<"发送线程已结束\n";
    recv_t.join();
    cout<<"接收线程已结束\n";
    return;
}
void client::SendMsg(int conn){
    char sendbuf[100];
    while (1)
    {
        memset(sendbuf, 0, sizeof(sendbuf));
        cin>>sendbuf;
        int ret=send(conn, sendbuf, strlen(sendbuf),0); //发送
        //输入exit或者对端关闭时结束
        if(strcmp(sendbuf,"exit")==0||ret<=0)
            break;
    }
}
void client::RecvMsg(int conn){
    //接收缓冲区
    char buffer[1000];
    //不断接收数据
    while(1)
    {
        memset(buffer,0,sizeof(buffer));
        int len = recv(conn, buffer, sizeof(buffer),0);
        //recv返回值小于等于0，退出
        if(len<=0)
            break;
        cout<<"收到服务器发来的信息："<<buffer<<endl;
    }
}


void client::HandleClient(int conn)
{
    int choice;
    string name,pass,pass1;
    //bool if_login=false;//记录是否登录成功

    cout<<" ------------------\n";
    cout<<"|                  |\n";
    cout<<"| 请输入你要的选项:   |\n";
    cout<<"|    0:退出         |\n";
    cout<<"|    1:登录         |\n";
    cout<<"|    2:注册         |\n";
    cout<<"|                  |\n";
    cout<<" ------------------ \n\n";

    //开始处理事物
    while(1)
    {
        //if(if_login)
        //break;
        cin>>choice;
        if(choice==0)
        {
            break;
        }
        //注册
        else if(choice==2)
        {
            cout<<"注册的用户名：";
            cin>>name;
            while(1)
            {
                cout<<"密码:";
                cin>>pass;
                cout<<"确认密码:";
                cin>>pass1;
                if(pass==pass1)
                break;
                else
                cout<<"两次密码不一致！\n\n";
            }
            name="name:"+name;
            pass="pass:"+pass;
            string str=name+pass;
            send(conn,str.c_str(),str.length(),0);
            cout<<"注册成功\n";
            cout<<"\n请继续输入你需要的选项:";
        }
    }
}

// int main()
// {
//     //定义sockfd
//     int sock_cli = socket(AF_INET,SOCK_STREAM, 0);

//     //定义sockaddr_in
//     struct sockaddr_in servaddr;
//     memset(&servaddr, 0, sizeof(servaddr));
//     servaddr.sin_family = AF_INET;//TCP/IP协议族
//     servaddr.sin_port = htons(8023);  //服务器端口
//     servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");  //服务器ip

//     //连接服务器，成功返回0，错误返回-1
//     if (connect(sock_cli, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0)
//     {
//         perror("connect");
//         exit(1);
//     }
//     cout<<"连接服务器成功！\n";

//     char sendbuf[100];
//     char recvbuf[100];
//     while (1)
//     {
//         memset(sendbuf, 0, sizeof(sendbuf));
//         cin>>sendbuf;
//         send(sock_cli, sendbuf, strlen(sendbuf),0); //发送
//         if(strcmp(sendbuf,"exit")==0)
//             break;
//     }
//     close(sock_cli);
//     return 0;
// }