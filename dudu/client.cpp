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
        // memset(sendbuf, 0, sizeof(sendbuf));
        // cin>>sendbuf;
        // int ret=send(conn, sendbuf, strlen(sendbuf),0); //发送
        string str;
        cin>>str;
        //发送消息
        str="content:"+str;
        int ret=send(conn,str.c_str(),str.length(),0);

        //输入exit或者对端关闭时结束
        //if(strcmp(sendbuf,"exit")==0||ret<=0)
        if(str=="content:exit"||ret<=0)
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
        cout<<buffer<<endl;
    }
}


void client::Menu()
{
cout<<" -------------------------------------------\n";
        cout<<"|                                           |\n";
        cout<<"|          请选择你要的选项：               |\n";
        cout<<"|              0:退出                       |\n";
        cout<<"|              1:发起单独聊天                |\n";
        cout<<"|              2:发起群聊                   |\n";
        cout<<"|              3:添加好友                   |\n";
        cout<<"|              4:删除好友                   |\n";
        cout<<"|              5:查询好友                    |\n";
        cout<<"|                 6:注销                          |\n";
        cout<<" ------------------------------------------- \n\n";
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
        client::Menu();
        cin>>choice;
    }
        if(choice==0)
        break;
         else if(choice==3)
        {
            printf("uuu");
            string friendName;
            cout<<"请输入要添加的好友名字：";
            cin>>friendName;
            Friend friendobj;
            friendobj.nameadd="add:"+friendName;
            friendobj.logiin_name="from:"+login_name.substr(5);
            string str2=friendobj.tojson();
            send(conn,str2.c_str(),str2.length(),0);
            cout<<"已发送添加好友的请求\n\n";
            cout<<"添加成功"<<endl;
            client::Menu();

        }
        else if(choice==4)
        {
            string friendName;
            cout<<"请输入要删除的好友名字：";
            cin >> friendName;
            Friend friendobj;
            friendobj.nameadd = "delete:" + friendName;
            friendobj.logiin_name="from:"+login_name.substr(5);
            string str = friendobj.tojson();
            
            send(conn, str.c_str(), str.length(), 0);
            cout << "已发送删除好友请求\n\n";
            cout<<"删除成功"<<endl;
            client::Menu();
        }
        // else if(choice==5)
        // {
        //     Friend friendobj;
        //     friendobj.logiin_name="from:"+login_name.substr(5);
        //     friendobj.nameadd = "querry:";
        //     string str = friendobj.tojson();
        //     send(conn, str.c_str(), str.length(), 0);
        //     cout << "已发送查询好友请求\n\n";
        // }
         else if(choice==6)
        {
        // 发送注销请求
        string logoutMsg = "logout";
        send(sock, logoutMsg.c_str(), logoutMsg.length(), 0);

        // 接收响应
        char buffer[1000];
        memset(buffer, 0, sizeof(buffer));
        recv(sock, buffer, sizeof(buffer), 0);
        string response(buffer);

        // 注销成功
        if (response == "logout_success") {
            cout << "注销成功\n\n";
        }
        // 未登录
        else if (response == "not_logged_in") {
            cout << "您尚未登录\n\n";
        }
        }
        //私聊
        else if(choice==1)
        {
            cout<<"请输入对方的用户名：";
            string target_name,content;
            cin>>target_name;
            // //检查好友关系
            // string from_user = login_name.substr(5);
            // string check_friendship_query = "SELECT * FROM FRIENDS WHERE NAME = '" + from_user + "' AND FIND_IN_SET('" + target_name + "', FRIENDS);";
            // int result = mysql_query(con, check_friendship_query.c_str());


            Friend friendobj;
            friendobj.target_name="target:"+target_name;
            friendobj.logiin_name="from:"+login_name.substr(5);
            string sendstr=friendobj.tojson();
           // string sendstr("target:"+target_name+"from:"+login_name);//标识目标用户+源用户
            send(sock,sendstr.c_str(),sendstr.length(),0);//先向服务器发送目标用户和源用户
            cout<<"请输入你想说的话(输入exit退出):\n";
            thread t1(client::SendMsg,conn); //创建发送线程
            thread t2(client::RecvMsg,conn);//创建接收线程
            t1.join();
            t2.join();
            break;

        }
      
    }

    
    close(sock);
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