#pragma once
#include <iostream>
#include <string>
#include <cstdlib>
#include <json/json.h>
#include <ctime>
#include <cstdio>
#include <chrono>
using namespace std;
using namespace Json;
string gettime()
{
    time_t rawtime;
    struct tm *ptm;
    time(&rawtime);
    ptm = localtime(&rawtime);
    char data[60];
    sprintf(data, "%d-%02d-%02d %02d:%02d:%02d", (int)ptm->tm_year + 1900, (int)ptm->tm_mon + 1, (int)ptm->tm_mday, (int)ptm->tm_hour, (int)ptm->tm_min, (int)ptm->tm_sec);
    string(move(data));
    return data;
}
class User
{
private:
    string UID;      //由系统分配，不唯一
    string password; //密码
    string name;     //昵称
    string my_time;  //该用户创建时间
    string my_friend;   //一个set的索引
    string tele;      //手机号，用于密码找回
    int islog;//是否咋在线;false代表不在线，非0代表在fd

public:
    User(); //初始化
    void setUID(string uid)
    {
        UID = uid;
    }
    string getUID()
    {
        return UID;
    }
    void setpassword(string pass)
    {
        password = pass;
    }
    void setname(string na)
    {
        name = na;
    }
    void settele(string temp)
    {
        tele=temp;
    }
    string getpassword()
    {
        return password;
    }
    void setislog(int fd)
    {
        islog=fd;
    }
    int getlog()
    {
        return islog;
    }
    string tojson();
    void jsonparse(string &json);
};
User::User()
{
    time_t timestamp;
    time(&timestamp);
    UID = to_string(timestamp);
    my_time=gettime();
    my_friend=my_time;
    password="";
    name="";
    islog=0;
}
string User::tojson()
{
    Value root;
    root.append(UID);
    root.append(password);
    root.append(name);
    root.append(my_time);
    root.append(my_friend);
    root.append(tele);
    FastWriter f;
    string json=f.write(root);
    return json;
}
void User::jsonparse(string &json)
{
    Value root;
    Reader r;
    r.parse(json,root);
    int i=0;
    UID=root[i++].asString();
    password=root[i++].asString();
    name=root[i++].asString();
    my_time=root[i++].asString();
    my_friend=root[i++].asString();
    tele=root[i++].asString();

}