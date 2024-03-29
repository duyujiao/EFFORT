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
#include"readnwriten.hpp"
// ANSI转义码
#define ANSI_COLOR_GREEN  "\033[32m"
#define ANSI_COLOR_RESET  "\033[0m"
int g_fileSize;
char* g_fileBuf;

pthread_mutex_t client::m_mutex;

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




    // //创建发送线程和接收线程
    // thread send_t(SendMsg,sock),recv_t(RecvMsg,sock);
    // send_t.join();
    // cout<<"发送线程已结束\n";
    // recv_t.join();
    // cout<<"接收线程已结束\n";
    return;
}
//读取文件
 bool readFile(const char* fileName)
 {
    FILE*read=fopen(fileName,"rb");
    if(!read)
    {
        perror("文件打开失败：\n");
        return false;
    }
    //获取文件大小
    fseek(read,0,SEEK_END);//将文件位置指针移动到最后
    g_fileSize=ftell(read);//保存文件大小
    fseek(read,0,SEEK_SET);//移动到开头
    cout<<g_fileSize<<endl;

    //分配内存
    //char* g_fileBuf;//保存文件数据
    g_fileBuf = new char[g_fileSize]();
    //把文件读到内存中来
    fread(g_fileBuf,sizeof(char),g_fileSize,read);

    delete[] g_fileBuf;
    
    fclose(read);
    return true;

 }
 bool saveFile(const char*fileName)
 {
    FILE*write=fopen(fileName,"wb");
    if(!write)
    {
        perror("文件打开失败：\n");
        return false;
    }
    fwrite(g_fileBuf,sizeof(char),g_fileSize,write);
    fclose(write);
    return true;
 }
 bool sendFile(int conn,const char*fileName)
 {
    readFile(fileName);

     send(conn,g_fileBuf,g_fileSize,0);
    cout<<"发送成功"<<g_fileSize<<"Bytes"<<endl;
    return true;

 }
 bool recvFile(int conn,const char*fileName)
 {
    if(g_fileBuf==NULL)
    {
        g_fileBuf = new char[g_fileSize]();
    }
    int ret=recv(conn,g_fileBuf,g_fileSize,0);
    if(ret==0)
    {
        cout<<"服务器发完"<<endl;
    }
    else if(ret<0)
    {
        perror("recv");
    }
    saveFile(fileName);
    //delete[] g_fileBuf;
    return 0;

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
        //私聊消息
        if(conn>0)
        {
        str="content:"+str;
        }
        //群聊消息
        if(conn<0)
        {
            str="gr_message:"+str;
        }
        int ret=send(abs(conn),str.c_str(),str.length(),0);
 

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
void recvv(int conn){
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
        else
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
        cout<<"|              2:查看好友历史消息记录         |\n";
        cout<<"|              3:请求添加好友                   |\n";
        cout<<"|              4:删除好友                   |\n";
        cout<<"|              5:查询好友                    |\n";
        cout<<"|              6:注销                        |\n";
        cout<<"|              7:屏蔽好友                     |\n";
        cout<<"|              8:解除屏蔽                     |\n";        
        cout<<"|              9:发起群聊                     |\n";
        cout<<"|              10:群组创建                    |\n";
        cout<<"|              11:群组解散                    |\n";
        cout<<"|              12:加入某个群组                |\n";
        cout<<"|              13:查看已加入的群组             |\n";
        cout<<"|              14:退出某个群组                |\n";
        cout<<"|              15:查看群成员列表              |\n";
        cout<<"|              16:添加管理员                 |\n";
        cout<<"|              17:取消管理员                 |\n";
        cout<<"|              18:查看是否有人申请加入群聊     |\n";
        cout<<"|              19:踢人                       |\n";
        cout<<"|              20:发送文件                    |\n";
        cout<<"|              21:发起群聊                    |\n";
        cout<<"|              22:好友申请列表                 |\n";
        cout<<"|              23:好友在线状态                 |\n";
        cout<<"|              24:接收文件                    |\n";
        cout<<"|                                            |\n";
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

                    char buf[1000];
                memset(buf,0,sizeof(buf));
                recv(sock,buf,sizeof(buf),0);//接受响应
                string recv_str(buf);
        
                     
                if(recv_str=="1")
                {
                //     char bu[1000];
                // memset(bu,0,sizeof(bu));
                // recv(sock,bu,sizeof(bu),0);//接受响应
                // cout<<bu<<endl;
                // int b = std::atoi(bu);
                //  while(b>0)
                //       {
                    cout<<"你有新消息"<<endl;
                   char buff[1000];
                memset(buff,0,sizeof(buff));
                recv(sock,buff,sizeof(buff),0);
                cout<<buff<<endl;
                // b--;//接受响应
                // }
               sleep(10);
                break;
                }               
            else
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
        string l=login_name.substr(5);   
        // pthread_mutex_lock(&m_mutex);//上锁
        // thread t(recvv,conn);//消息实时通知
        // pthread_mutex_unlock(&m_mutex);//解锁
        if(if_login){
        //system("clear");//清空终端d
        cout<<"        欢迎回来,"<<login_name.substr(5)<<endl;
        client::Menu();
        cin>>choice;
    }

            
        if(choice==0)
        break;

        else if(choice==20)
        {
            cout<<"请输入要发送文件对方的用户名：";
            string target_name,content;
            cin>>target_name;
            Friend friendobj;
            friendobj.target_name="file:"+target_name;
            friendobj.logiin_name="from:"+login_name.substr(5);
            string login=login_name.substr(5);
            string sendstr=friendobj.tojson();
            send(sock,sendstr.c_str(),sendstr.length(),0);
            sendFile(conn,"../../文档/typora/111.md");
           // recvFile(conn,"1.md");
        }
        else if(choice==24)
        {
            
            string targetname;
            cout<<"请输入要查看接收谁的文件"<<endl;
            cin>>targetname;
            string str="wwww"+targetname;
            send(conn,str.c_str(),str.length(),0);
            recvFile(sock,"1.md");
            cout<<"接收文件成功"<<endl;
        }

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
         else if(choice==22)
        {
            Friend friendobj;
            friendobj.nameadd="apply";
            friendobj.logiin_name="from:"+login_name.substr(5);
            string str=friendobj.tojson();
            send(conn,str.c_str(),str.length(),0);
            char buffer[1000];
            memset(buffer, 0, sizeof(buffer));
            recv(sock, buffer, sizeof(buffer), 0);
            string response(buffer);
            cout << "查询结果：" << response << endl;
            if(response.empty())
            {
                cout<<"没有要添加的好友"<<endl;
            }
            string addname;
            cout<<"请输入要添加的好友的名字"<<endl;
            cin>>addname;
            send(conn,addname.c_str(),addname.length(),0);
            cout<<"是否同意将该用户添加到群组?(y/n):";
            char c;
            cin>>c;
            if(response!="No addfriendsrequest found")
            {
            if(c=='y'||c=='Y')
            { 
                    string approveRequest="agree:";
                    send(conn,approveRequest.c_str(),approveRequest.length(),0);
                    cout<<"已发送同意请求\n"; 
            }
            else if(c=='n')
            {
                string rejectRequest = "unagree:" ;
                send(conn, rejectRequest.c_str(), rejectRequest.length(), 0);
                cout << "已发送拒绝请求\n";
            }
            }
            
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
        else if(choice==5)
        {
            Friend friendobj;
            friendobj.logiin_name="from:"+login_name.substr(5);
            friendobj.nameadd = "querry:";
            string str = friendobj.tojson();
            send(conn, str.c_str(), str.length(), 0);
            cout << "已发送查询好友请求\n\n";
            // 接收并打印查询结果
            char buffer[1000];
            memset(buffer,0,sizeof(buffer));
            recv(sock,buffer,sizeof(buffer),0);//接受响应
            //将接收到的数据缓冲区buffer转换为string类型的对象response
            string reponse(buffer);
            cout << "查询结果："<<reponse << endl;
            sleep(10);
        }
        else if(choice==23)
        {
            Friend friendobj;
            friendobj.logiin_name="from:"+login_name.substr(5);
            friendobj.nameadd="online";
            string str = friendobj.tojson();
            send(conn, str.c_str(), str.length(), 0);
            cout << "已发送查询好友在线状态请求\n\n";
            // 接收并打印查询结果
            char buffer[1000];
            memset(buffer,0,sizeof(buffer));
            recv(sock,buffer,sizeof(buffer),0);//接受响应
            //将接收到的数据缓冲区buffer转换为string类型的对象response
            string reponse(buffer);
            cout << "查询在线结果："<< endl;
            std::cout <<reponse<< std::endl;
        }

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
        else if(choice==7)
        {
            string blockedFriendName;
            cout<<"请输入要屏蔽的好友的名字：";
            cin>>blockedFriendName;
            //发送屏蔽好友请求到服务器
            Friend friendobj;
            friendobj.nameblock="blocck:"+blockedFriendName;
            friendobj.logiin_name="from:"+login_name.substr(5);
            string request=friendobj.tojson();
            send(conn,request.c_str(),request.length(),0);
            cout<<"已发送屏蔽好友的请求\n\n";
            client::Menu();

        }
        //解除屏蔽
        else if(choice==8)
        {
            string blockedFriendName;
            cout<<"请输入要解除屏蔽的好友的名字：";
            cin>>blockedFriendName;
            //发送屏蔽好友请求到服务器
            Friend friendobj;
            friendobj.logiin_name="from:"+login_name.substr(5);
            friendobj.nameblock="unlock:"+blockedFriendName;
            string request=friendobj.tojson();
            send(conn,request.c_str(),request.length(),0);
            cout<<"已发送屏蔽好友的请求\n\n";
        }
        //群聊
        else if(choice==9)
        {
            cout<<"请输入群号：";
            int num;
            cin>>num;
            string sendstr("group:"+to_string(num));
            send(sock,sendstr.c_str(),sendstr.length(),0);
            cout<<"请输入你想说的话(输入exit退出):\n";
            
            thread t1(client::SendMsg,-conn);//创建发送线程，传入负数，和私聊区分开
            thread t2(client::RecvMsg,conn);//创建接收线程
            t1.join();
            t2.join();


        }
        //私聊
        else if(choice==1)
        {
            cout<<"请输入对方的用户名：";
            string target_name,content;
            cin>>target_name;
            Friend friendobj;
            friendobj.target_name="target:"+target_name;
            friendobj.logiin_name="from:"+login_name.substr(5);
            string login=login_name.substr(5);
            string sendstr=friendobj.tojson();
           // string sendstr("target:"+target_name+"from:"+login_name);//标识目标用户+源用户
            send(sock,sendstr.c_str(),sendstr.length(),0);//先向服务器发送目标用户和源用户
            cout<<"请输入你想说的话(输入exit退出):\n";
            thread t1(client::SendMsg,conn); //创建发送线程
            thread t2(client::RecvMsg,conn);//创建接收线程

            t1.join();
            t2.join();

        }
        else if(choice==10)
        {
            string groupNum;
            cout<<"请输入要创建的群组账号：";
            cin>>groupNum;
            string agree;
            bool validInput = false;

            while (!validInput) {
            cout << "请输入要创建的群组成员加入是否需要你的同意 (y or n): ";
            cin >> agree;

            if (agree == "y" || agree == "n") {
            validInput = true;
            } else {
            cout << "输入无效，请重新输入。\n";
            }
            } 
            //发送创建群组的请求
            Group groupobj;
            groupobj.group_num="create:"+groupNum;
            groupobj.logiin_name="from:"+login_name.substr(5);
            groupobj.group_type=agree;
            string str=groupobj.tojson();
            send(conn,str.c_str(),str.length(),0);
            cout<<"已发送创建群组的请求\n\n";
            //接收服务器的响应并处理
            // char buffer[10000];
            //  memset(buffer, 0, sizeof(buffer));
            // recv(conn, buffer, sizeof(buffer), 0);
            // string response = buffer;

            // if (response == "success") {
            // cout << "创建群组成功" << endl;
            // // 处理创建群组成功的情况
            // } else {
            // cout << "创建群组失败" << endl;
            // // 处理创建群组失败的情况
            // }

            client::Menu();
      
        }
        else if(choice==11)
        {
            string groupNum;
            cout<<"请输入要解散的群组账号：";
            cin>>groupNum;
            //发送创建群组的请求
            Group groupobj;
            groupobj.logiin_name="from:"+login_name.substr(5);
            groupobj.group_num="dismiss:"+groupNum;
            string str=groupobj.tojson();
            send(conn,str.c_str(),str.length(),0);
            cout<<"已发送解散群组的请求\n\n";
            //接收服务器的响应并处理
            // char buffer[10000];
            //  memset(buffer, 0, sizeof(buffer));
            // recv(conn, buffer, sizeof(buffer), 0);
            // string response = buffer;

            // if (response == "success") {
            // cout << "解散群组成功" << endl;
            // // 处理解散群组成功的情况
            // } else {
            // cout << "解散群组失败" << endl;
            // // 处理解散群组失败的情况
            // }
            client::Menu();
        }
        else if(choice==12)
        {  
            string groupNum;
            cout<<"请输入要加入的群组的账号：";
            cin>>groupNum;
            //发送加入群组的请求
            Group groupobj;
            groupobj.logiin_name="from:"+login_name.substr(5);
            groupobj.group_num="join:"+groupNum;
            string str=groupobj.tojson();
            send(conn,str.c_str(),str.length(),0);
            cout<<"已发送加入群组的请求\n\n";
        }
        else if(choice==14)
        {
            string groupNum;
            cout<<"请输入要退出的群组账号：";
            cin>>groupNum;
            //发送退出群组的请求
            Group groupobj;
            groupobj.logiin_name="from:"+login_name.substr(5);
            groupobj.group_num="quit:"+groupNum;
            string str=groupobj.tojson();
            send(conn,str.c_str(),str.length(),0);
            cout<<"已发送退出群组的请求\n\n";
        }
        else if(choice==15)
        {
            string groupNum;
            cout<<"请输入要查询群成员的群组的账号：";
            cin>>groupNum;
            //发送加入群组的请求
            Group groupobj;
            groupobj.logiin_name="from:"+login_name.substr(5);
            groupobj.group_num="gmem:"+groupNum;
            string str=groupobj.tojson();
            send(conn,str.c_str(),str.length(),0);
            cout<<"已发送查询群成员的请求\n\n";
            char buffer[1000];
            memset(buffer, 0, sizeof(buffer));
            recv(sock, buffer, sizeof(buffer), 0);
            string response(buffer);
            cout << "查询结果：" << response << endl;
           

        }
        else if(choice==18)
        {
            string groupNum;
            cout<<"请输入要查看申请的群组的账号：";
            cin>>groupNum;
            Group groupobj;
            groupobj.logiin_name="from:"+login_name.substr(5);
            groupobj.group_num="view"+groupNum;
            string str=groupobj.tojson();
            send(conn,str.c_str(),str.length(),0);
            cout<<"已发送查看申请的请求\n\n";
            char buffer[1000];
            memset(buffer, 0, sizeof(buffer));
            recv(sock, buffer, sizeof(buffer), 0);
            string response(buffer);
            cout << "查询结果：" << response << endl;

            if(response!="No addgrouprequest found")
            {
                cout<<"是否同意将该用户添加到群组?(y/n):";
                char c;
                cin>>c;
                if(c=='y'||c=='Y')
                {
                    string approveRequest="approve:"+groupNum;
                    send(conn,approveRequest.c_str(),approveRequest.length(),0);
                    cout<<"已发送同意请求\n"; 
                }
                else if(c=='n')
                {
                    string rejectRequest = "reject:" + groupNum;
                    send(conn, rejectRequest.c_str(), rejectRequest.length(), 0);
                    cout << "已发送拒绝请求\n";
                }
            }

        }
        else if(choice==16)
        {
            string groupNum;
            cout<<"请输入要添加管理员的群组的账号：";
            cin>>groupNum;
            string adminName;
            cout<<"请输入要添加的管理员的名字：";
            cin>>adminName;
            Group groupobj;
            groupobj.group_num=groupNum;
            groupobj.group_admin="increase:"+adminName;
            groupobj.logiin_name="from:"+login_name.substr(5);
            string str=groupobj.tojson();
            send(conn,str.c_str(),str.length(),0);
            cout<<"已发送添加管理员的请求\n\n";
            client::Menu();

        }
        else if(choice==17)
        {
            string groupNum;
            cout<<"请输入要取消管理员的群组的账号：";
            cin>>groupNum;
            string adminName;
            cout<<"请输入要取消的管理员的名字：";
            cin>>adminName;
            Group groupobj;
            groupobj.group_num=groupNum;
            groupobj.group_admin="decrease:"+adminName;
            groupobj.logiin_name="from:"+login_name.substr(5);
            string str=groupobj.tojson();
            send(conn,str.c_str(),str.length(),0);
            cout<<"已发送取消管理员的请求\n\n";
            client::Menu();
        }
        else if(choice==19)
        {
            string groupNum;
            cout<<"请输入要踢人的群组的账号：";
            cin>>groupNum;
            string kickName;
            cout<<"请输入要踢的名字：";
            cin>>kickName;
            Group groupobj;
            groupobj.group_num=groupNum;
            groupobj.group_kick="kicck:"+kickName;
            groupobj.logiin_name="from:"+login_name.substr(5);
            string str=groupobj.tojson();
            send(conn,str.c_str(),str.length(),0);
            cout<<"已发送踢出的请求\n\n";
        }
        else if(choice==13)
        {
            Group groupobj;
            groupobj.logiin_name="from:"+login_name.substr(5);
            groupobj.group_num="groupzu";
            string query=groupobj.tojson();
            send(conn,query.c_str(),query.length(),0);
            cout<<"已发送群组查询请求\n\n";
             // 接收并打印查询结果
            char buffer[1000];
            memset(buffer, 0, sizeof(buffer));
            recv(sock, buffer, sizeof(buffer), 0);
            string response(buffer);
            cout << "查询结果：" << response << endl;
           
        }
        else if(choice==2)
        {
            
            MYSQL *co=mysql_init(NULL);
            mysql_real_connect(co,"127.0.0.1","root","40111004","chatroom",0,NULL,CLIENT_MULTI_STATEMENTS);
            // 查询数据库中的待接收消息
            string retrieve_messages_query = "SELECT * FROM message WHERE receiver = '" + login_name.substr(5) + "';";
            int result = mysql_query(co, retrieve_messages_query.c_str());
            if (result != 0) {
            cout << "检索消息失败: " << mysql_error(co) << endl;
            // 处理检索失败的情况
            } else {
            MYSQL_RES* query_result = mysql_store_result(co);
            int num_rows = mysql_num_rows(query_result);
            if (num_rows > 0) {
             cout << "您有 " << num_rows << " 条历史消息：" << endl;
            // 遍历查询结果并输出消息内容
            MYSQL_ROW row;
            while ((row = mysql_fetch_row(query_result))) {
            string sender = row[1];
            string message = row[3];
            string output_message = message + "\n";
            cout<<output_message<<endl;
        }

  } else {
    send(conn,"2",10,0);
    cout << "没有待接收的消息。" << endl;
  }
  mysql_free_result(query_result);
}
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