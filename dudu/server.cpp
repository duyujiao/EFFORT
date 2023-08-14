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

unordered_map<int,set<int> > server::group_map;//记录群号和套接字描述符集合
pthread_mutex_t server::group_mutx;//互斥锁，锁住需要修改group_map的临界区
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
    cout << "您有 " << num_rows << " 条待接收的消息：" << endl;
    // 遍历查询结果并输出消息内容
    MYSQL_ROW row;
    while ((row = mysql_fetch_row(query_result))) {
      string sender = row[1];
      string message = row[3];
     string output_message = "[" + sender + "]: " + message + "\n";

  // 发送消息给客户端
  send(conn, output_message.c_str(), output_message.length(), 0);
    }
  } else {
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
string store_message_query = "INSERT INTO messages (sender, receiver, message) VALUES ('" + login_name + "', '" + target_name + "', '" + str.substr(7) + "');";
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

    else if(str.find("create:")!=str.npos)
    {
        Group groupobj=Group::fromjson(str);
        string groupnum=groupobj.group_num;
        string leader=groupobj.logiin_name.substr(5);
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
                string create="INSERT INTO MYGROUP (num,member,leader) VALUES ('"+groupnum+"','"+leader+"','"+leader+"')";
                cout<<"sql语句"<<create<<endl;
                mysql_query(con, create.c_str());
                cout << "创建群组成功，群账号：" << groupnum << endl;
                // 发送响应到客户端
                // send(conn, "success", 7, 0);
            }

        }

    }
    else if(str.find("dismiss")!=str.npos)
    {
        Group groupobj=Group::fromjson(str);
        string groupnum=groupobj.group_num;
        string leader=groupobj.logiin_name.substr(5);
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