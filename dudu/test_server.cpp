#include"server.h"
// 信号处理函数
void signalHandler(int signum) {
    //连接MYSQL数据库
    MYSQL *con=mysql_init(NULL);
    mysql_real_connect(con,"127.0.0.1","root","40111004","chatroom",0,NULL,CLIENT_MULTI_STATEMENTS);
    if (signum == SIGINT) {
        // 将所有在线用户设置为离线
        string updateQuery = "UPDATE USER SET online_status = 'offline'";
        mysql_query(con, updateQuery.c_str());

        // 关闭数据库连接
        mysql_close(con);

        // 退出进程
        exit(0);
    }
}
int main(){
    server serv(8023,"127.0.0.1");//创建实例，传入端口号和ip作为构造函数参数
    signal(SIGINT, signalHandler);

    serv.run();//启动服务
}