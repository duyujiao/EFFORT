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
#include"readnwriten.hpp"

vector<bool> server::sock_arr(10000,false);
unordered_map<string,int> server::name_sock_map;//名字和套接字描述符
unordered_map<string,string> server::from_to_map;//记录用户xx要向用户yy发送信息
unordered_map<int,set<int> > server::group_map;//记录群号和套接字描述符集合
pthread_mutex_t server::name_sock_mutx;//互斥锁，锁住需要修改name_sock_map的临界区
pthread_mutex_t server::group_mutx;//互斥锁，锁住需要修改group_map的临界区
pthread_mutex_t server::from_mutex;//自旋锁，锁住修改from_to_map的临界区
//构造函数
server::server(int port,string ip):server_port(port),server_ip(ip){
    pthread_mutex_init(&name_sock_mutx, NULL); //创建互斥锁
    pthread_mutex_init(&group_mutx, NULL); //创建互斥锁
    pthread_mutex_init(&from_mutex, NULL); //创建互斥锁
}

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
// //将参数的文件描述符设置为非阻塞
// void server::setnonblocking(int sock)
// {
//     int opts;
//     opts=fcntl(sock,F_GETFL);
//     if(opts<0)
//     {
//         perror("fcntl(sock,GETSL)");
//         exit(1);
//     }
//     opts=opts|O_NONBLOCK;
//     if(fcntl(sock,F_SETFL,opts)<0)
//     {
//         perror("fcntl(sock,SETFL,opts)");
//         exit(1);
//     }

// }
void SetNonBlocking(int sockfd) {
        int flags = fcntl(sockfd, F_GETFL, 0);
        if (flags == -1) {
            perror("fcntl");
            exit(1);
        }

        if (fcntl(sockfd, F_SETFL, flags | O_NONBLOCK) == -1) {
            perror("fcntl");
            exit(1);
        }
    }


//服务器开始服务
void server::run()
 {
    // //listen的backlog大小
    // int LISTENQ=200;
    // int i,maxi,listenfd,connfd,sockfd,epfd,nfds;
    // ssize_t n;
    // //char line[MAXLINE];
    // socklen_t clilen;
    // //声明epoll_event结构体变量，ev用于注册事件，数组用于回传要处理的事件
    // struct epoll_event ev,events[10000];
    // //生成用于处理accept的epoll专用的文件描述符
    // epfd=epoll_create(10000);
    // struct sockaddr_in clientaddr;
    // struct sockaddr_in serveraddr;
    // listenfd=socket(PF_INET,SOCK_STREAM,0);
    // //把socket设置为非阻塞方式
    // setnonblocking(listenfd);
    // //设置与要处理的事件相关的文件描述符
    // ev.data.fd=listenfd;
    // //设置要处理的事件类型
    // ev.events=EPOLLIN|EPOLLET;
    // //注册epoll事件
    // epoll_ctl(epfd,EPOLL_CTL_ADD,listenfd,&ev);
    // //设置serveraddr
    // bzero(&serveraddr,sizeof(serveraddr));



    //  //定义sockfd
    // server_sockfd = socket(AF_INET,SOCK_STREAM, 0);
    // serveraddr.sin_family = AF_INET;//TCP/IP协议族
    // serveraddr.sin_port = htons(server_port);//server_port;//端口号
    // serveraddr.sin_addr.s_addr = inet_addr("127.0.0.1");//ip地址，127.0.0.1是环回地址，相当于本机ip
    // bind(listenfd,(sockaddr*)&serveraddr,sizeof(serveraddr));
    // listen(listenfd,LISTENQ);
    // clilen=sizeof(clientaddr);
    // maxi=0;
    // //定义一个10线程的线程池
    // boost::asio::thread_pool tp(10);
    // while(1)
    // {
    //             cout<<"--------------------------"<<endl;
    //     cout<<"epoll_wait阻塞中"<<endl;
    //     //等待epoll事件的发生
    //     nfds=epoll_wait(epfd,events,10000,-1);//最后一个参数是timeout，0:立即返回，-1:一直阻塞直到有事件，x:等待x毫秒
    //     cout<<"epoll_wait返回，有事件发生"<<endl;
    //     //处理所发生的所有事件
    //     for(i=0;i<nfds;++i)
    //     {
    //         //有新客户端连接服务器
    //         if(events[i].data.fd==listenfd)
    //         {
    //             connfd = accept(listenfd,(sockaddr *)&clientaddr, &clilen);
    //             if(connfd<0){
    //                  perror("connfd<0");
    //                  exit(1);
    //             }
    //             else{
    //                 cout<<"用户"<<inet_ntoa(clientaddr.sin_addr)<<"正在连接\n";
    //             }
    //             //设置用于读操作的文件描述符
    //             ev.data.fd=connfd;
    //             //设置用于注册的读操作事件，采用ET边缘触发，为防止多个线程处理同一socket而使用EPOLLONESHOT
    //             ev.events=EPOLLIN|EPOLLET|EPOLLONESHOT;
    //             //边缘触发要将套接字设为非阻塞
    //             setnonblocking(connfd);
    //             //注册ev
    //             epoll_ctl(epfd,EPOLL_CTL_ADD,connfd,&ev);
    //         }
    //         //接收到读事件
    //         else if(events[i].events&EPOLLIN)
    //         {
    //             sockfd = events[i].data.fd;
    //             events[i].data.fd=-1;
    //             cout<<"接收到读事件"<<endl;

    //             string recv_str;
    //             boost::asio::post(boost::bind(RecvMsg,epfd,sockfd)); //加入任务队列，处理事件
    //         }
    //     }
    // }
    // close(listenfd);




   //定义sockfd
    int server_sockfd = socket(AF_INET,SOCK_STREAM, 0);

    //定义sockaddr_in
    struct sockaddr_in server_sockaddr;
    server_sockaddr.sin_family = AF_INET;//TCP/IP协议族
    server_sockaddr.sin_port = htons(8023);//端口号
    server_sockaddr.sin_addr.s_addr = inet_addr("127.0.0.1");//ip地址，127.0.0.1是环回地址，相当于本机ip

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
    //元组类型，五个成员分别为if_login,login_name,target_name,target_conn，group_num
    tuple<bool,string,string,int,int> info;
    /*
        bool if_login;//记录当前服务对象是否成功登录
        string login_name;//记录当前服务对象的名字
        string target_name;//记录目标对象的名字
        int target_conn;//目标对象的套接字描述符
        int group_num;//记录所处的群号
    */
   get<0>(info)=false;//把if_login置为false
   get<3>(info)=-1;//target_conn置为-1

    // string recv_str;
    // while(1){
    //     char buf[1000];
    //     memset(buf, 0, sizeof(buf));
    //     int ret  = recv(conn, buf, sizeof(buf), 0);
    //     if(ret < 0){
    //         cout<<"recv返回值小于0"<<endl;
    //         //对于非阻塞IO，下面的事件成立标识数据已经全部读取完毕
    //         if((errno == EAGAIN) || (errno == EWOULDBLOCK)){
    //                 printf("数据读取完毕\n");
    //             cout<<"接收到的完整内容为："<<recv_str<<endl;
    //             cout<<"开始处理事件"<<endl;
    //             break;
    //         }
    //         cout<<"errno:"<<errno<<endl;
    //         return;
    //     }
    //     else if(ret == 0){
    //         cout<<"recv返回值为0"<<endl;
    //         return;
    //     }
    //     else{
    //         printf("接收到内容如下: %s\n",buf);
    //         string tmp(buf);
    //         recv_str+=tmp;
    //     }
    // }
    // string str=recv_str;
    // HandleRequest(epollfd,conn,str,info);

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


void server::HandleRequest(int conn,string str,tuple<bool,string,string,int,int> &info)
{
    char buffer[1000];
    string name,pass;
    //把参数提出来，方便操作
    bool if_login=get<0>(info);//记录当前服务对象是否成功登录
    string login_name=get<1>(info);//记录当前服务对象的名字
    string target_name=get<2>(info);//记录目标对象的名字
    int target_conn=get<3>(info);//目标对象的套接字描述符
    int group_num=get<4>(info);//记录所处的群号

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
                send(conn,str1.c_str(),str1.length()+1,0);

                // 查询数据库中的待接收消息
string retrieve_messages_query = "SELECT * FROM messages WHERE receiver = '" + login_name + "';";
int result = mysql_query(con, retrieve_messages_query.c_str());
if (result != 0) {
  cout << "检索消息失败: " << mysql_error(con) << endl;
  // 处理检索失败的情况
} else {
  MYSQL_RES* query_result = mysql_store_result(con);
  int num_rows = mysql_num_rows(query_result);
  if (num_rows > 0) {
    send(conn,"1",10,0);
    cout << "您有 " << num_rows << " 条待接收的消息：" << endl;
    //send(conn,to_string(num_rows).c_str(),to_string(num_rows).length(),0);
    // 遍历查询结果并输出消息内容
    MYSQL_ROW row;
    while ((row = mysql_fetch_row(query_result))) {
      string sender = row[1];
      string message = row[3];
     string output_message = "[" + sender + "]: " + message + "\n";
cout<<output_message<<endl;
  // 发送消息给客户端
  send(conn, output_message.c_str(), output_message.length(), 0);
    }


  } else {
    send(conn,"2",10,0);
    cout << "没有待接收的消息。" << endl;
  }
  mysql_free_result(query_result);
}

// 清空数据库中的待接收消息
string clear_messages_query = "DELETE FROM messages WHERE receiver = '" + login_name + "';";
result = mysql_query(con, clear_messages_query.c_str());
if (result != 0) {
  cout << "清空消息失败: " << mysql_error(con) << endl;
}

                pthread_mutex_lock(&name_sock_mutx);//上锁
                name_sock_map[login_name]=conn;//记录下名字和文件描述符的对应关系
                pthread_mutex_unlock(&name_sock_mutx);//解锁
            
                         
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

        string search_from = "INSERT INTO FRIENDS (NAME,FRIENDS) VALUES ('" +from+ "','" +add+ "');";
        mysql_query(con, search_from.c_str()); // 执行from添加add的SQL语句
        
        string search_add = "INSERT INTO FRIENDS (NAME,FRIENDS) VALUES ('" +add+ "','" +from+ "');";
        mysql_query(con, search_add.c_str());  // 执行add添加from的SQL语句

        string check_friendship_query = "SELECT * FROM FRIENDS WHERE name='" +from+ "' AND FIND_IN_SET('" +add+ "', friends);";
        string checkk_friendship_query = "SELECT * FROM FRIENDS WHERE name='" +add+ "' AND FIND_IN_SET('" +from+ "', friends);";

        // 执行查询语句
        int result = mysql_query(con, check_friendship_query.c_str());
        if (result != 0)
        {
        cout << "查询错误: " << mysql_error(con) << endl;
        // 处理查询错误的情况
        } 
        else 
        {
            MYSQL_RES* query_result = mysql_store_result(con);
            int num_rows = mysql_num_rows(query_result);
            if (num_rows > 0)
            {
                cout << "好友关系已存在，无需重复添加" << endl;
                // 处理好友关系已存在的情况       
            }
             else 
            {
                search_from="UPDATE FRIENDS SET friends = CONCAT(friends, '," +add+ "') WHERE name = '" +from+ "';";
                mysql_query(con, search_from.c_str()); // 执行from添加add的SQL语句
                std::cout << "sql语句(from添加add):" << search_from << endl;
            }
           mysql_free_result(query_result); // 释放查询结果集  
        }
        int resullt = mysql_query(con, checkk_friendship_query.c_str());
        if (resullt != 0) 
        {
            cout << "查询错误: " << mysql_error(con) << endl;
            // 处理查询错误的情况
        } 
        else
        {
            MYSQL_RES* query_result = mysql_store_result(con);
            int num_rows = mysql_num_rows(query_result);
            if (num_rows > 0)
            {
            cout << "好友关系已存在，无需重复添加" << endl;
            // 处理好友关系已存在的情况
            } 
        else 
        {
        search_add="UPDATE FRIENDS SET friends = CONCAT(friends, '," +from+ "') WHERE name = '" +add+ "';";
        std::cout << "sql语句(add添加from):" << search_add << endl;
        mysql_query(con, search_add.c_str());  // 执行add添加from的SQL语句
        }
           mysql_free_result(query_result); // 释放查询结果集 
        }
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
    else if(str.find("increase:")!=str.npos)
    {
        Group groupobj=Group::fromjson(str);
        string leader=groupobj.logiin_name.substr(5);
        string admin=groupobj.group_admin;
        string groupnum=groupobj.group_num;
        string typ="SELECT leader FROM MYGROUP WHERE num='" +groupnum+ "'";
        int result = mysql_query(con, typ.c_str());
        if (result != 0) {
            cout << "查询错误：" << mysql_error(con) << endl;
            } 
        else
        {
            MYSQL_RES* join_type_result = mysql_store_result(con);
            if (join_type_result != nullptr) {
            MYSQL_ROW row = mysql_fetch_row(join_type_result);
            if (row != nullptr) {
            string joinType = row[0]; 
            if(joinType==leader)
            {
                string search="UPDATE MYGROUP SET manager=CONCAT(IFNULL(manager,''),',"+admin+"')WHERE leader='"+leader+"' AND num='"+groupnum+"';";
                cout<<"SQL语句:"<<search<<endl;
                cout<<"已取消群号为"<<groupnum<<"管理员"<<admin<<endl<<endl;
            }
            else
            {
                cout<<"你不是群主无法执行取消管理员操作"<<endl;
            }
            }
            }
            mysql_free_result(join_type_result);
        }
    }
    else if(str.find("decrease:")!=str.npos)
    {
        Group groupobj=Group::fromjson(str);
        string leader=groupobj.logiin_name.substr(5);
        string admin=groupobj.group_admin;
        string groupnum=groupobj.group_num;
        //群组存在，检查是否需要群主同意加入
        string typ="SELECT leader FROM MYGROUP WHERE num='" +groupnum+ "'";
        int result = mysql_query(con, typ.c_str());
        if (result != 0) {
            cout << "查询错误：" << mysql_error(con) << endl;
            } 
        else
        {
            MYSQL_RES* join_type_result = mysql_store_result(con);
            if (join_type_result != nullptr) {
            MYSQL_ROW row = mysql_fetch_row(join_type_result);
            if (row != nullptr) {
            string joinType = row[0]; 
            if(joinType==leader)
            {
                string search="UPDATE MYGROUP SET manager=TRIM(TRAILING',"+admin+"' FROM SUBSTRING_INDEX (CONCAT(manager,','),',"+admin+"',1)) WHERE leader='"+leader+"' AND num='"+groupnum+"';";
                cout<<"SQL语句:"<<search<<endl;
                cout<<"已取消群号为"<<groupnum<<"管理员"<<admin<<endl<<endl;
            }
            else
            {
                 cout<<"你不是群主无法执行取消管理员操作"<<endl;
            }
            }
            }
            mysql_free_result(join_type_result);
            }
    }

    else if(str.find("querry")!=str.npos)
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
        string friendList;
        for (int i = 0; i < numFriends; i++) {
            auto row = mysql_fetch_row(result);
            string friendName = row[0];
            cout << friendName << endl;
            friendList+=friendName+",";
        }
         // 将好友信息发送给客户端
         send(conn, friendList.c_str(), friendList.length(), 0);
        }
        else{
             cout << "未查询到好友" << endl;
             // 发送未查询到好友的信息给客户端
            string message = "No friends found";
            send(conn, message.c_str(), message.length(), 0);
        }

    }
    //屏蔽
    else if(str.find("block:")!=str.npos)
    {
         Friend friendobj = Friend::fromjson(str);
         cout<<"收到屏蔽好友的请求"<<endl;
         string blockedFriendName=friendobj.nameblock;
         string from=friendobj.logiin_name.substr(5);
         string search = "INSERT INTO BLOCK (NAME,BLOCKFRIENDS) VALUES ('" +from+ "','" +blockedFriendName+ "');";
         mysql_query(con, search.c_str()); 
        string check_friendship_query = "SELECT * FROM BLOCK WHERE name='" +from+ "' AND FIND_IN_SET('" +blockedFriendName+ "',blockfriends);";
        
        // 执行查询语句
        int result = mysql_query(con, check_friendship_query.c_str());
        if (result != 0)
        {
        cout << "查询错误: " << mysql_error(con) << endl;
        // 处理查询错误的情况
        } 
        else 
        {
            MYSQL_RES* query_result = mysql_store_result(con);
            int num_rows = mysql_num_rows(query_result);
            if (num_rows > 0)
            {
                cout << "已屏蔽该好友，无需重复屏蔽" << endl;
            }
             else 
            {
                search="UPDATE BLOCK SET blockfriends = CONCAT(blockfriends, '," +blockedFriendName+ "') WHERE name = '" +from+ "';";
                mysql_query(con, search.c_str()); 
                std::cout << "sql语句:" << search << endl;
            }
           mysql_free_result(query_result); // 释放查询结果集  
        
        }
         cout<<"已屏蔽好友："<<blockedFriendName<<endl;
    }
    //解除屏蔽
    else if(str.find("unlock:")!=str.npos)
    {

         Friend friendobj=Friend::fromjson(str);
        //处理好友逻辑
       cout<<"收到解除屏蔽好友的请求"<<endl;
         string blockedFriendName=friendobj.nameblock;
        string from=friendobj.logiin_name.substr(5);
        string search = "UPDATE BLOCK SET blockfriends=TRIM(TRAILING '," +blockedFriendName+ "' FROM SUBSTRING_INDEX (CONCAT(blockfriends,','),'," +blockedFriendName+ "',1))WHERE name='" +from+ "';";
        cout << "SQL语句:" << search << endl;
        mysql_query(con, search.c_str());
       
        cout<<"已解除屏蔽好友："<<blockedFriendName<<endl;
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
              // 存储消息到数据库
string store_message_query = "INSERT INTO messages (sender, receiver, message) VALUES ('" + login_name + "', '" + target_name + "', '" + str.substr(8) + "');";
int result = mysql_query(con, store_message_query.c_str());
if (result != 0) {
  cout << "存储消息失败: " << mysql_error(con) << endl;
  // 处理存储失败的情况
}
          
        }
        if(name_sock_map.find(target_name)!=name_sock_map.end())
        {
                target_conn=name_sock_map[target_name];
                cout<<"重新查找目标用户套接字成功\n";

                string from_user=login_name;
                string to_user=target_name;
                //检查好友关系
                string check_friendship_query="SELECT * FROM FRIENDS WHERE name='" +from_user+ "'AND FIND_IN_SET('" +to_user+ "',friends);";
                int result=mysql_query(con,check_friendship_query.c_str());
                if (result != 0) 
                {
                cout << "查询错误: " << mysql_error(con) << endl;
                 // 处理查询错误
                } else
                {
                MYSQL_RES* query_result = mysql_store_result(con);
                int num_rows = mysql_num_rows(query_result);
                if (num_rows == 0) {
                cout << "用户 " << from_user << " 和 " << to_user << " 不是好友，禁止私聊" << endl;
                // 处理非好友关系的情况，禁止私聊逻辑
                } else {
                    //检查是否屏蔽了好友发送的消息
                    string check_friendship_queryy="SELECT * FROM BLOCK WHERE name='" +to_user+ "'AND FIND_IN_SET('" +from_user+ "',blockfriends);";
                    int result=mysql_query(con,check_friendship_queryy.c_str());
                if (result != 0) 
                {
                cout << "查询错误: " << mysql_error(con) << endl;
                 // 处理查询错误
                } 
                else{
                    MYSQL_RES* query_result = mysql_store_result(con);
                int num_rows = mysql_num_rows(query_result);
                if (num_rows == 0)
                {
          
                string recv_str(str);
                string send_str = recv_str.substr(8);
                cout << "用户 " << login_name << " 向 " << target_name << " 发送 " << send_str << endl;
                send_str = "[" + login_name + "]: " + send_str;
              
                send(target_conn, send_str.c_str(), send_str.length(), 0);
                 // 处理好友关系的情况，执行私聊逻辑
                    
                }
                    else
                    {
                        cout << "用户 " << to_user << " 屏蔽了用户 " << from_user << " 的消息，不转发" << endl;
                    }
                }
                mysql_free_result(query_result); // 释放结果集
                }
        }
        }
        else
        {
                cout<<"查找仍然失败，转发失败！\n";
        }
       
    }
    //创建群聊
    else if(str.find("create:")!=str.npos)
    {
        Group groupobj=Group::fromjson(str);
        string groupnum=groupobj.group_num;
        string leader=groupobj.logiin_name.substr(5);
        string type=groupobj.group_type;
        //检查群组是否已经存在
        string check="SELECT *FROM MYGROUP WHERE num='" +groupnum+ "'";
        int result=mysql_query(con,check.c_str());
        if(result!=0)
        {
            cout<<"查询错误："<<mysql_error(con)<<endl;
        }
        else
        {
            MYSQL_RES* query_result = mysql_store_result(con);
            int num_rows = mysql_num_rows(query_result);
            if (num_rows > 0)
            {
                //群组存在
                cout << "群组已存在，无法创建" << endl;
                //send(conn,"failed",9,0);
            }
            else
            {
                if(type=="y"){
                string create1="INSERT INTO MYGROUP (num,member,leader,type) VALUES ('"+groupnum+"','"+leader+"','"+leader+"','y')";
                cout<<"sql语句"<<create1<<endl;
                mysql_query(con, create1.c_str());
                cout << "创建群组成功，群账号：" << groupnum << endl;
                }
                else
                {
                string create="INSERT INTO MYGROUP (num,member,leader,type) VALUES ('"+groupnum+"','"+leader+"','"+leader+"','n')";
                cout<<"sql语句"<<create<<endl;
                mysql_query(con, create.c_str());
                cout << "创建群组成功，群账号：" << groupnum << endl;
                }
                // 发送响应到客户端
                // send(conn, "success", 7, 0);
            }
        mysql_free_result(query_result);
        }

    }
    //解散群聊
    else if(str.find("dismiss")!=str.npos)
    {
        Group groupobj=Group::fromjson(str);
        string groupnum=groupobj.group_num;
        string leader=groupobj.logiin_name.substr(5);
        string sqll="SELECT leader FROM MYGROUP WHERE num='" +groupnum+ "'";
        cout<<"sql语句"<<sqll<<endl;
        int resultt=mysql_query(con,sqll.c_str());
        if(resultt!=0)
        {
            cout<<"查询错误"<<mysql_error(con)<<endl;
        }
        else
        {
            MYSQL_RES* query_result = mysql_store_result(con);
            if (query_result != nullptr) 
            {
            MYSQL_ROW row = mysql_fetch_row(query_result);
            if (row != nullptr) 
            {
                string master=row[0];
                cout<<"群号"<<groupnum<<"的群主是"<<master<<endl;
                if(master==leader)
                {
                    string sql="DELETE FROM MYGROUP WHERE num='" +groupnum+ "'";
                    cout<<"sql语句"<<sql<<endl;
                    int result=mysql_query(con,sql.c_str());
                    if(result!=0)
                    {
                        cout<<"解散群聊失败"<<mysql_error(con)<<endl;
                        //send(conn,"failed",7,0);
                    }
                    else
                    {
                        cout<<"解散群组"<<groupnum<<"成功"<<endl;
                        //send(conn,"success",8,0);
                    }
                }
                else
                {
                     cout << "你不是群主，无法解散群聊" << endl;
                     // send(conn, "failed", 7, 0);
                }
            }
            else{
                cout<<"找不到群号为2的群组"<<endl;
            }
            mysql_free_result(query_result);
            }
        }
        

    }
    //申请加入某个群组
    else if(str.find("join:")!=str.npos)
    {
        Group groupobj=Group::fromjson(str);
        string groupnum=groupobj.group_num;
        string from=groupobj.logiin_name.substr(5);
        //检查群组是否存在
        string check="SELECT * FROM MYGROUP WHERE num='" +groupnum+ "'";
        int result=mysql_query(con,check.c_str());
        if(result!=0)
        {
            cout<<"查询错误"<<mysql_error(con)<<endl;
        }
        else
        {
            MYSQL_RES* query_resultt=mysql_store_result(con);
            int num_rows=mysql_num_rows(query_resultt);
            if(num_rows>0)
            {
                //群组存在，检查是否需要群主同意加入
                string typ="SELECT type FROM MYGROUP WHERE num='" +groupnum+ "'";
                result = mysql_query(con, typ.c_str());
                if (result != 0) {
                cout << "查询错误：" << mysql_error(con) << endl;
                } 
                else{
                    MYSQL_RES* join_type_result = mysql_store_result(con);
                    if (join_type_result != nullptr) {
                    MYSQL_ROW row = mysql_fetch_row(join_type_result);
                    if (row != nullptr) {
                        string joinType = row[0]; //获取加入方式
                        if(joinType=="y")
                        {
                            //怎么实现对群主发送加群申请，群主并且同意
                        }
                        else
                        {
                            string sqll = "SELECT member FROM MYGROUP WHERE num = '" + groupnum + "' AND FIND_IN_SET('"+from+"', member) > 0";
                            //string sqll="SELECT member FROM MYGROUP WHERE num='" +groupnum+ "'";
                            cout<<"sql语句"<<sqll<<endl;
                            int resultt=mysql_query(con,sqll.c_str());
                            if(resultt!=0)
                            {
                             cout<<"查询错误"<<mysql_error(con)<<endl;
                            }
                            else
                            {
                                MYSQL_RES* query_result = mysql_store_result(con);
                                if (query_result != nullptr) 
                                {
                                    MYSQL_ROW row = mysql_fetch_row(query_result);
                                    if (row != nullptr) 
                                    {
                                        //string mem = row[0];
                                        cout<<"你已经是该群的成员"<<endl;
                                    }
                                    else
                                    {
                                        string search="UPDATE MYGROUP SET member = CONCAT(member, '," +from+ "') WHERE num = '" +groupnum+ "';";
                                        mysql_query(con, search.c_str());
                                        std::cout << "sql语句:" << search << endl;
                                        cout<<"已加入该群"<<endl;
                                       
                                    }
                                }
                                mysql_free_result(query_result);
                            }

                        }
                    }
                    else{
                        cout << "找不到群号为" << groupnum << "的群组" << endl;
                        // 发送响应到客户端
                        // send(conn, "failed", 7, 0);
                    }
                     mysql_free_result(join_type_result);
   

                }

            }
            }
             else {
            // 群组不存在
            cout << "群组不存在，无法加入" << endl;
            // 发送响应到客户端
            // send(conn, "failed", 7, 0);
                    }
             mysql_free_result(query_resultt);

        }
    }
    //退出某个群组
    else if(str.find("quit")!=str.npos)
    {
        Group groupobj=Group::fromjson(str);
        string groupnum=groupobj.group_num;
        string from=groupobj.logiin_name.substr(5);
        //检查群组是否存在
        string check="SELECT * FROM MYGROUP WHERE num='" +groupnum+ "'";
        int result=mysql_query(con,check.c_str());
        if(result!=0)
        {
            cout<<"查询错误"<<mysql_error(con)<<endl;
        }
        else
        {
            MYSQL_RES* query_resultt=mysql_store_result(con);
            int num_rows=mysql_num_rows(query_resultt);
            if(num_rows>0)
            {
                    string search="UPDATE MYGROUP SET member=TRIM(TRAILING '," +from+ "' FROM SUBSTRING_INDEX (CONCAT(member,','),'," +from+ "',1))WHERE num = '" + groupnum + "';";
                    mysql_query(con, search.c_str());
                    std::cout << "sql语句:" << search << endl;
                    cout<<"已退出该群"<<endl;

            }
            else {
            // 群组不存在
            cout << "群组不存在" << endl;
            // 发送响应到客户端
            // send(conn, "failed", 7, 0);
                    }
            mysql_free_result(query_resultt);
        }
    }
    //绑定群聊号
    else if(str.find("group:")!=str.npos)
    {
        string recv_str(str);
        string num_str=recv_str.substr(6);
        group_num=stoi(num_str);
        cout<<"用户"<<login_name<<"绑定的群聊号是:"<<num_str<<endl;
        pthread_mutex_lock(&group_mutx);//上锁
        group_map[group_num].insert(conn);
        pthread_mutex_unlock(&group_mutx);//解锁
    }
    //广播群聊信息
    else if(str.find("gr_message:")!=str.npos)
    {
        string send_str(str);
        send_str=send_str.substr(11);
        send_str="["+login_name+"]:"+send_str;
        cout<<"群聊消息:"<<send_str<<endl;
        for(auto i:group_map[group_num])
        {
            if(i!=conn)
            {
                send(i,send_str.c_str(),send_str.length(),0);
            }
        }
    }
    //查询群组
    else if(str.find("groupzu")!=str.npos)
    {
        Group groupobj=Group::fromjson(str);
        string from=groupobj.logiin_name.substr(5);
        string search="SELECT num FROM MYGROUP WHERE FIND_IN_SET('" +from+ "',member)>0";
        cout << "SQL语句:" << search << endl;
        mysql_query(con, search.c_str());
        auto result = mysql_store_result(con);
        int numGroups = mysql_num_rows(result);

    if (numGroups > 0) {
        cout << "Found the following groups:" << endl;
        string groupList;
        for (int i = 0; i < numGroups; i++) {
            auto row = mysql_fetch_row(result);
            string groupName = row[0];
            cout << groupName << endl;
            groupList += groupName + ",";
        }

        // Send group information to the client
        send(conn, groupList.c_str(), groupList.length(), 0);
    } else {
        cout << "No groups found" << endl;
        // Send "no groups found" message to the client
        string message = "No groups found";
        send(conn, message.c_str(), message.length(), 0);
    }
    }
    else if(str.find("gmem:")!=str.npos)
    {
        Group groupobj=Group::fromjson(str);
        string from=groupobj.logiin_name.substr(5);
        string groupnum=groupobj.group_num;
        string search="SELECT member FROM MYGROUP WHERE num='"+groupnum+"'";
        cout << "SQL语句:" << search << endl;
        mysql_query(con, search.c_str());
        auto result = mysql_store_result(con);
        int numGroups = mysql_num_rows(result);

        if (numGroups > 0) {
        cout << "Found the following groupmembers:" << endl;
        string groupList;
        for (int i = 0; i < numGroups; i++) {
            auto row = mysql_fetch_row(result);
            string groupName = row[0];
            cout << groupName << endl;
            groupList += groupName + ",";
        }

        // Send group information to the client
        send(conn, groupList.c_str(), groupList.length(), 0);
    } else {
        cout << "No groupsmember found" << endl;
        // Send "no groups found" message to the client
        string message = "No groupsmember found";
        send(conn, message.c_str(), message.length(), 0);
    }
    }

   

    mysql_close(con);
     //更新实参
    get<0>(info)=if_login;//记录当前服务对象是否成功登录
    get<1>(info)=login_name;//记录当前服务对象的名字
    get<2>(info)=target_name;//记录目标对象的名字
    get<3>(info)=target_conn;//目标对象的套接字描述符
    get<4>(info)=group_num;//记录所处的群号

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