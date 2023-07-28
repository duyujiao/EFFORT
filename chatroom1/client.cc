#include "Sock.hpp"
#include "login.hpp"
int main()
{
    int socket = Sock::Socket();
    Sock::Connect(socket, "127.0.0.1", 9997);
    menulogin();
    int p;
    User people;//存放该用户的所有信息
    string temp;
    cin >> p;
    switch (p)
    {
    case 1:
        temp = "1";
        sendMsg(socket, temp);
        logincli(socket,people);
        messagemenu();
        break;
    case 2:
        temp = "2";
        sendMsg(socket, temp);
        temp=regclier();
        sendMsg(socket, temp);
        recvMsg(socket,temp);
        cout<<"账号注册成功"<<endl;
        cout<<"你的账号为:"<<temp<<endl;
        sendMsg(socket, temp);
        break;
    case 3:
        temp = "3";
        sendMsg(socket, temp);
        break;
    }
}