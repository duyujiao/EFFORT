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
#include"class.hpp"

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
    bool if_login=false;//记录是否登录成功
    string login_name;//记录成功登陆的用户名

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
        if(if_login)
        break;
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
            // string str=name+pass;
            User user;
            user.name=name;
            user.pass=pass;
            string str=user.tojson();
         

            send(conn,str.c_str(),str.length(),0);
            cout<<"注册成功\n";
            cout<<"\n请继续输入你需要的选项:";
        }
        else if(choice==1&&!if_login)
        {
            while(1)
            {
                cout<<"用户名：";
                cin>>name;
                cout<<"密码：";
                cin>>pass;
                // //格式化
                // string str="login"+name;
                // str+="pass:";
                // str+=pass;
                User user;
                user.name="login"+name;
                user.pass="pass:"+pass;
                string str=user.tojson();

                send(sock,str.c_str(),str.length(),0);//发送登录信息
                char buffer[1000];
                memset(buffer,0,sizeof(buffer));
                recv(sock,buffer,sizeof(buffer),0);//接受响应
                string recv_str(buffer);
                //登陆成功
                if(recv_str.substr(0,2)=="ok")
                {
                    if_login=true;
                    login_name=user.name;
                    cout<<"登陆成功\n\n";
                    break;
                }
                //登陆失败
                else
                cout<<"密码或用户名错误!\n\n";
            }
        }
    }
    //登录成功
    while(if_login&&1)
    {
    if(if_login){
        system("clear");//清空终端d
        cout<<"        欢迎回来,"<<login_name.substr(5)<<endl;
        int choice;
    string friendName;

    
    cout << " ------------------\n";
    cout << "|                  |\n";
    cout << "| 请选择好友管理选项： |\n";
    cout << "|    0:返回主菜单     |\n";
    cout << "|    1:添加好友       |\n";
    cout << "|    2:删除好友       |\n";
    cout << "|    3:查询好友       |\n";
    cout << "|                  |\n";
    cout << " ------------------ \n\n";

    while(1)
    {
        cin>>choice;
        if(choice==0)
        {
            break;
        }
        else if(choice==1)
        {
            cout<<"请输入要添加的好友名字：";
            cin>>friendName;
            Friend friendobj;
            friendobj.nameuser=login_name;
            friendobj.nameadd="add:"+friendName;
            string str=friendobj.tojson();
            send(conn,str.c_str(),str.length(),0);
            cout<<"已发送添加好友的请求\n\n";
        }
        else if(choice==2)
        {
            cout<<"请输入要删除的好友名字：";
            cin >> friendName;
            Friend friendobj;
            friendobj.nameuser=login_name;
            friendobj.nameadd = "delete:" + friendName;
            string str = friendobj.tojson();
            send(conn, str.c_str(), str.length(), 0);
            cout << "已发送删除好友请求\n\n";
        }
        else if(choice==3)
        {
            Friend friendobj;
            friendobj.nameuser=login_name;
            friendobj.nameadd = "query";
            string str = friendobj.tojson();
            send(conn, str.c_str(), str.length(), 0);
            cout << "已发送查询好友请求\n\n";
        }
    }
       // ManageFriends(conn);
        // cout<<" -------------------------------------------\n";
        // cout<<"|                                           |\n";
        // cout<<"|          请选择你要的选项：               |\n";
        // cout<<"|              0:退出                       |\n";
        // cout<<"|              1:发起单独聊天               |\n";
        // cout<<"|              2:发起群聊                   |\n";
        // cout<<"|                                           |\n";
        // cout<<" ------------------------------------------- \n\n";
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