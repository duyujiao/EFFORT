#ifndef __LOGIN_HANDLER_H__
#define __LOGIN_HANDLER_H__
#include <iostream>
#include <string>
#include <sys/epoll.h>

#include "myredis.hpp"
#include "readwrite.hpp"
#include "loginmessage.hpp"
#include "class.hpp"
enum
{
    QUIT,       //退出
    LOGIN,      //登录
    REGISTERED, //注册
    DEL         //删除账号
};
using namespace std;

void menulogin()
{
    cout << "--------------------------------------" << endl;
    cout << "-------------聊天室--------------------" << endl;
    cout << "-------------0.退出--------------------" << endl;
    cout << "-------------1.登录--------------------" << endl;
    cout << "-------------2.注册--------------------" << endl;
    cout << "-------------3.注销--------------------" << endl;
}

void messagemenu()
{
    cout << "-----------------------------------------" << endl;
    cout << "----------------1.发消息------------------" << endl;
    cout << "----------------2.加好友------------------" << endl;
    cout << "----------------2.查看所有好友-------------" << endl;
}

string regclier() //注册账号(客户端)
{
    User peope;
    string p;
    string temp;
    cout << "请输入邮箱:";
    cin >> p;
    peope.settele(p);
    cout << "请输入昵称: ";
    cin >> p;
    peope.
setname(p);
flag:
    cout << "请输入密码:";
    cin >> p;
    cout << "请再次输入密码:";
    cin >> temp;
    if (temp != p)
    {
        cout << "两次密码输入不一致" << endl;
        goto flag;
    }
    peope.setpassword(temp);
    return peope.tojson();
}

string regser(void *ffd) //注册账号(服务器)
{
    int fd = *(int *)ffd;
    string buf;
    recvMsg(fd, buf);
    User people;
    people.jsonparse(buf);
    string UID = people.getUID();
    Redis r;
    r.connect();
    r.hsetValue("peopleinfo", UID, buf);
    r.saddvalue("info", UID);
    return UID;
}

void logincli(int fd, User &people) //登录(客户端)
{
    string UID;
    string password;
flag:
    cout << "请输入你的账号: ";
    cin >> UID;
    cout << "请输入你的密码: ";
    cin >> password;
    loginmessage p(UID, password);
    string buf = p.tojson();
    cout << buf << endl;
    sendMsg(fd, buf);
    recvMsg(fd, buf);
    if (buf == "-2")
    {
        cout << "账号错误,请重新输入" << endl;
        goto flag;
    }
    else
    {
        if (buf == "-1")
        {
            cout << "密码错误,请重新输入" << endl;
            goto flag;
        }
        else
        {
            cout << "登录成功" << endl;
            recvMsg(fd, buf);
            people.jsonparse(buf);
        }
    }
}

void loginser(void *arg) //登录(服务器)
{
    struct epoll_event temp;
    int *arr = (int *)arg;
    int fd = arr[0];
    int efd = arr[1];
    temp.data.fd = fd;
    temp.events = EPOLLIN;
    epoll_ctl(efd, EPOLL_CTL_DEL, fd, &temp);
    User people;
    Redis r;
    r.connect();
    string buf;
flag:
    recvMsg(fd, buf);
    cout << buf << endl;
    loginmessage p;
    p.jsonparse(buf);
    string UID = p.getUID();
    string password = p.getpassword();
    if (!r.sismember("info", UID)) //如果该账号不存在
    {
        sendMsg(fd, "-2");
        // goto flag;
    }
    else //账号存在，下面进行密码匹配
    {
        string json;
        json = r.gethash("peopleinfo", UID);
        people.jsonparse(json);
        if (people.getpassword() != password) //密码错误
        {
            sendMsg(fd, "-1");
            // goto flag;
        }
        else
        {
            sendMsg(fd, "1");
            //改变用户状态
            people.setislog(fd);
            sendMsg(fd, json);
        }
    }
    epoll_ctl(efd, EPOLL_CTL_ADD, fd, &temp);
}


#endif