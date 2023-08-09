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
// using namespace std;
#include"server.h"
#include"mysql.hpp"
#include"class.hpp"

unordered_map<string,int> server::name_sock_map;//名字和套接字描述符
pthread_mutex_t server::name_sock_mutx;//互斥锁，锁住需要修改name_sock_map的临界区
vector<bool> server::sock_arr(10000,false);//将10000个位置都设为false，sock_arr[i]=false表示套接字描述符i未打开（因此不能关闭）
//构造函数
server::server(int port,string ip):server_port(port),server_ip(ip){}

//析构函数
server::~server()
{
    // for(auto conn:sock_arr)
    // close(conn);
    // close(server_sockfd);
    for(int i=0;i<sock_arr.size();i++){
        if(sock_arr[i])
            close(i);
    }
    close(server_sockfd);
}

//服务器开始服务
void server::run()
{
     //定义sockfd
    server_sockfd = socket(AF_INET,SOCK_STREAM, 0);

    //定义sockaddr_in
    struct sockaddr_in server_sockaddr;
    server_sockaddr.sin_family = AF_INET;//TCP/IP协议族
    server_sockaddr.sin_port = htons(server_port);//server_port;//端口号
    server_sockaddr.sin_addr.s_addr = inet_addr(server_ip.c_str());//ip地址，127.0.0.1是环回地址，相当于本机ip

    //bind，成功返回0，出错返回-1
    if(bind(server_sockfd,(struct sockaddr *)&server_sockaddr,sizeof(server_sockaddr))==-1)
    {
        perror("bind");//输出错误原因
        exit(1);//结束程序
    }

    //listen，成功返回0，出错返回-1
    if(listen(server_sockfd,20) == -1)
    {
        perror("listen");//输出错误原因
        exit(1);//结束程序
    }

    //客户端套接字
    struct sockaddr_in client_addr;
    socklen_t length = sizeof(client_addr);

     //不断取出新连接并创建子线程为其服务
    while(1){
        int conn = accept(server_sockfd, (struct sockaddr*)&client_addr, &length);
        if(conn<0)
        {
            perror("connect");//输出错误原因
            exit(1);//结束程序
        }
        std::cout<<"文件描述符为"<<conn<<"的客户端成功连接\n";
        sock_arr.push_back(conn);
        //创建线程
        thread t(server::RecvMsg,conn);
        t.detach();//置为分离状态，不能用join，join会导致主线程阻塞
    }
}

//子线程工作的静态函数
//注意，前面不用加static，否则会编译报错
// void server::RecvMsg(int conn){
//     //接收缓冲区
//     char buffer[1000];
//     //不断接收数据
//     while(1)
//     {
//         memset(buffer,0,sizeof(buffer));
//         int len = recv(conn, buffer, sizeof(buffer),0);
//         //客户端发送exit或者异常结束时，退出
//         if(strcmp(buffer,"exit")==0 || len<=0){
//             close(conn);
//             sock_arr[conn]=false;
//             break;
//         }
//         std::cout<<"收到套接字描述符为"<<conn<<"发来的信息："<<buffer<<endl;
                                  
//          string str(buffer);
//         HandleRequest(conn,str);
//         //回复客户端
//         string ans="收到";
//         int ret = send(conn,ans.c_str(),ans.length(),0);
//         //服务器收到exit或者异常关闭套接字描述符
//         if(ret<=0){
//             close(conn);
//             sock_arr[conn]=false;
//             break;
//         }
//     }
// }


void server::RecvMsg(int conn)
{
    //元组类型，四个成员分别为if_login,login_name,target_name,target_conn
    tuple<bool,string,string,int> info;
    /*
        bool if_login;//记录当前服务对象是否成功登录
        string login_name;//记录当前服务对象的名字
        string target_name;//记录目标对象的名字
        int target_conn;//目标对象的套接字描述符
    */
   get<0>(info)=false;//把if_login置为false
   get<3>(info)=-1;//target_conn置为-1

   //接收缓冲区
    char buffer[1000];
    //不断接收数据
    while(1)
    {
        memset(buffer,0,sizeof(buffer));
        int len = recv(conn, buffer, sizeof(buffer),0);
        //客户端发送exit或者异常结束时，退出
        if(strcmp(buffer,"content:exit")==0 || len<=0){
            close(conn);
            sock_arr[conn]=false;
            break;
        }
        std::cout<<"收到套接字描述符为"<<conn<<"发来的信息："<<buffer<<endl;
        string str(buffer);
        HandleRequest(conn,str,info);
    }

}


void server::HandleRequest(int conn,string str,tuple<bool,string,string,int> &info)
{
    char buffer[1000];
    string name,pass;
    //把参数提出来，方便操作
    bool if_login=get<0>(info);//记录当前服务对象是否成功登录
    string login_name=get<1>(info);//记录当前服务对象的名字
    string target_name=get<2>(info);//记录目标对象的名字
    int target_conn=get<3>(info);//目标对象的套接字描述符

    //连接MYSQL数据库
    MYSQL *con=mysql_init(NULL);
    mysql_real_connect(con,"127.0.0.1","root","40111004","chatroom",0,NULL,CLIENT_MULTI_STATEMENTS);


    // MySQL sql;
    // sql.connect("localhost","root","40111004","chatroom");

     //注册
     //str.npos是std::string类的一个静态常量，表示一个无效的位置或未找到的位置
     //不等于说明找到了"name:"
    if(str.find("name:")!=str.npos){
        // int p1=str.find("name:"),p2=str.find("pass:");
        // name=str.substr(p1+5,p2-5);
        // pass=str.substr(p2+5,str.length()-p2-4);

        // string search="INSERT INTO USER VALUES (\"";
        // search+=name;
        // search+="\",\"";
        // search+=pass;
        // search+="\");";

        User user = User::fromjson(str);
        string search = "INSERT INTO USER VALUES (";
        search += "'" + user.name + "', ";
        search += "'" + user.pass + "');";
        std::cout<<"sql语句:"<<search<<endl<<endl;
        mysql_query(con,search.c_str());
    }
   //登录

    else if(str.find("login")!=str.npos){
        // int p1=str.find("login"),p2=str.find("pass:");
        // name=str.substr(p1+5,p2-5);
        // pass=str.substr(p2+5,str.length()-p2-4);
        // string search="SELECT * FROM USER WHERE NAME=\"";
        // search+=name;
        // search+="\";";
        User user = User::fromjson(str);
        string search="SELECT * FROM USER WHERE name='" + user.name + "'";
        std::cout<<"sql语句:"<<search<<endl;
        auto search_res=mysql_query(con,search.c_str());
        auto result=mysql_store_result(con);
        int col=mysql_num_fields(result);//获取列数
        int row=mysql_num_rows(result);//获取行数
        
        //查询到用户名
        if(search_res==0&&row!=0){
            std::cout<<"查询成功\n";
            auto info=mysql_fetch_row(result);//获取一行的信息
            std::cout<<"查询到用户名:"<<info[0]<<" 密码:"<<info[1]<<endl;
            //密码正确
            if(info[1]==user.pass){
                std::cout<<"登录密码正确\n\n";
                string sear="UPDATE USER SET online_status = 'online' WHERE name = '" +user.name+"'";
                mysql_query(con, sear.c_str()) ;
                string str1="ok";
                if_login=true;
                login_name=user.name;//记录下当前登录的用户名

                pthread_mutex_lock(&name_sock_mutx);//上锁
                name_sock_map[login_name]=conn;//记录下名字和文件描述符的对应关系
                pthread_mutex_unlock(&name_sock_mutx);//解锁
                send(conn,str1.c_str(),str1.length()+1,0);
              
            }
            //密码错误
            else{
                std::cout<<"登录密码错误\n\n";
                char str1[100]="wrong";
                send(conn,str1,strlen(str1),0);
            }
        }
        //没找到用户名
        else{
            std::cout<<"查询失败\n\n";
            char str1[100]="wrong";
            send(conn,str1,strlen(str1),0);
        }
        mysql_free_result(result);
    }
    else if (str == "logout") 
    {
        if (if_login) {
            // 更新当前用户的在线状态为离线
            string updateQuery = "UPDATE USER SET online_status = 'offline' WHERE name = '" + login_name + "'";
            mysql_query(con, updateQuery.c_str());

            if_login = false;
            login_name = "";
            cout << "注销成功\n\n";
            char response[100] = "logout_success";
            send(conn, response, strlen(response), 0);
        } else {
            char response[100] = "not_logged_in";
            send(conn, response, strlen(response), 0);
        }
    }


    else if(str.find("add:")!=str.npos)
    {
        Friend friendobj = Friend::fromjson(str);
        // 处理添加好友逻辑
        cout << "收到添加好友请求，好友名字：" << friendobj.nameadd << endl;
        string add=friendobj.nameadd;
        string from=friendobj.logiin_name.substr(5);
        string search = "INSERT INTO FRIENDS (NAME,FRIENDS) VALUES ('" +from+ "','" +add+ "');";
        search="UPDATE FRIENDS SET friends = CONCAT(friends, '," +add+ "') WHERE name = '" +from+ "';";
        std::cout<<"sql语句:"<<search<<endl<<endl;
        mysql_query(con, search.c_str());
        cout << "已添加好友：" << friendobj.nameadd  << endl << endl;

    }
    else if (str.find("delete:") != str.npos) 
    {
        Friend friendobj=Friend::fromjson(str);
        //处理好友逻辑
        cout<<"收到删除好友的请求，好友名字："<<friendobj.nameadd<<endl;
        string deletee=friendobj.nameadd;
        string from=friendobj.logiin_name.substr(5);
        string search = "UPDATE FRIENDS SET friends=TRIM(TRAILING '," +deletee+ "' FROM SUBSTRING_INDEX (CONCAT(friends,','),'," +deletee+ "',1))WHERE name='" +from+ "';";
        cout << "SQL语句:" << search << endl;
        mysql_query(con, search.c_str());
        cout << "已删除好友：" << friendobj.nameadd << endl << endl;

    }
    else if(str=="query"!=str.npos)
    {
      
        
        Friend friendobj = Friend::fromjson(str);
        // 处理查询好友逻辑
        cout << "收到查询好友请求" << endl;
        string from=friendobj.logiin_name.substr(5);
        string search="SELECT friends FROM FRIENDS WHERE name='" +from+ "';";
        cout << "SQL语句:" << search << endl;
        mysql_query(con, search.c_str());
        auto result = mysql_store_result(con);
        int numFriends = mysql_num_rows(result);
        if (numFriends > 0) {
        cout << "已查询到以下好友：" << endl;
        for (int i = 0; i < numFriends; i++) {
            auto row = mysql_fetch_row(result);
            string friendName = row[0];
            cout << friendName << endl;
            // 将好友信息发送给客户端
            send(conn, friendName.c_str(), friendName.length(), 0);
        }
        }
        else{
             cout << "未查询到好友" << endl;
             // 发送未查询到好友的信息给客户端
            string message = "No friends found";
            send(conn, message.c_str(), message.length(), 0);
        }

    }

    //设定目标的文件描述符
    else if(str.find("target:")!=str.npos)
    {
         Friend friendobj = Friend::fromjson(str);
         string target=friendobj.target_name.substr(7);
         string from=friendobj.logiin_name.substr(5);
        // int pos1=str.find("from");
        // string target=str.substr(7,pos1-7),from=str.substr(pos1+4);
        target_name=target;
        //找不到这个目标
        if(name_sock_map.find(target)==name_sock_map.end())
        {

            cout<<"源用户为"<<login_name<<",目标用户"<<target_name<<"仍未登录，无法发起私聊\n";
        }
        //找到了目标
        else
        {
             cout<<"源用户"<<login_name<<"向目标用户"<<target_name<<"发起的私聊即将建立";
            cout<<",目标用户的套接字描述符为"<<name_sock_map[target]<<endl;
            target_conn=name_sock_map[target];
        }

    }
    //接收到消息，转发
    else if(str.find("content:")!=str.npos)
    {
        if(target_conn==-1)
        {
            cout<<"找不到目标用户"<<target_name<<"的套接字,将尝试重新寻找目标用户的套接字\n";
        }
        if(name_sock_map.find(target_name)!=name_sock_map.end())
        {
                target_conn=name_sock_map[target_name];
                cout<<"重新查找目标用户套接字成功\n";
        }
        else
        {
                cout<<"查找仍然失败，转发失败！\n";
        }
        string recv_str(str);
        string send_str=recv_str.substr(8);
        cout<<"用户"<<login_name<<"向"<<target_name<<"发送"<<send_str;
        send_str="["+login_name+"]:"+send_str;
        send(target_conn,send_str.c_str(),send_str.length(),0);
    }
     //更新实参
    get<0>(info)=if_login;//记录当前服务对象是否成功登录
    get<1>(info)=login_name;//记录当前服务对象的名字
    get<2>(info)=target_name;//记录目标对象的名字
    get<3>(info)=target_conn;//目标对象的套接字描述符

}

    



// int main()
// {
//     //定义sockfd
//     int server_sockfd=socket(AF_INET,SOCK_STREAM,0);

//     //定义sockaddr_in
//     struct sockaddr_in server_sockaddr;
//     server_sockaddr.sin_family=AF_INET;//TCP/IP协议族
//     server_sockaddr.sin_port=htons(8023);//端口号
//     server_sockaddr.sin_addr.s_addr=inet_addr("127.0.0.1");//ip地址

//     //bind,成功返回0,出错返回-1
//     if(bind(server_sockfd,(struct sockaddr *)&server_sockaddr,sizeof(server_sockaddr))==-1)
//     {
//         perror("bind");//输出错误原因
//         exit(1);//结束程序
//     }

//      //listen，成功返回0，出错返回-1
//     if(listen(server_sockfd,20) == -1)
//     {
//         perror("listen");//输出错误原因
//         exit(1);//结束程序
//     }

//     //客户端套接字
//     struct sockaddr_in client_addr;
//     socklen_t length = sizeof(client_addr);

//     //成功返回非负描述字，出错返回-1
//     int conn = accept(server_sockfd, (struct sockaddr*)&client_addr, &length);
//     if(conn<0)
//     {
//         perror("connect");//输出错误原因
//         exit(1);//结束程序
//     }
//     cout<<"客户端成功连接"<<endl;

//     //接收缓冲区
//     char buffer[1000];

//      //不断接收数据
//     while(1)
//     {
//         memset(buffer,0,sizeof(buffer));
//         int len = recv(conn, buffer, sizeof(buffer),0);
//         //客户端发送exit或者异常结束时，退出
//         if(strcmp(buffer,"exit")==0 || len<=0)
//             break;
//         cout<<"收到客户端信息："<<buffer<<endl;
//     }
//     close(conn);
//     close(server_sockfd);
//     return 0;

// }