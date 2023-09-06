#include<iostream>
#include<string>
#include<jsoncpp/json/json.h>
#include<set>

using namespace std;
using namespace Json;


class User
{
    public:
    string name;
    string pass;


    //序列化为json字符串
    string tojson() const
    {
        Value user;
        user["name"]=name;
        user["pass"]=pass;
        
        StreamWriterBuilder writerBuilder;
        string jsonStr=writeString(writerBuilder,user);
        return jsonStr;

    }
    static User fromjson(const string& jsonStr)
    {
        User user;

        CharReaderBuilder readerBuilder;

        Value root;
        //>>运算符将输入流中的数据解析并存储到root对象中，从而实现了字符串到 JSON 对象的反序列化
        istringstream(jsonStr)>>root;

        user.name=root["name"].asString();
        user.pass=root["pass"].asString();

        //去除前缀
        if(user.name.find("name:")==0)
        {
            user.name=user.name.substr(5);
        }
        if(user.pass.find("pass:")==0)
        {
            user.pass=user.pass.substr(5);
        }
        if(user.name.find("login")==0)
        {
            user.name=user.name.substr(5);
        }
        return user;
    }
};



class Friend
{
    public:
    string target_name;
    string logiin_name;
    string nameadd;
    string nameblock;
    
    string tojson() const
    {
        Value f;
        f["target_name"]=target_name;
        f["logiin_name"]=logiin_name;
        f["nameadd"]=nameadd;
        f["nameblock"]=nameblock;

        StreamWriterBuilder writerBuilder;
        string jsonStr=writeString(writerBuilder,f);
        return jsonStr;
    }
    static Friend fromjson(const string& jsonStr)
    {
        Friend f;

        CharReaderBuilder readerBuilder;

        Value root;
        //>>运算符将输入流中的数据解析并存储到root对象中，从而实现了字符串到 JSON 对象的反序列化
        istringstream(jsonStr)>>root;

        f.target_name=root["target_name"].asString();
        f.logiin_name=root["logiin_name"].asString();
        f.nameadd=root["nameadd"].asString();
        f.nameblock=root["nameblock"].asString();

        //去除前缀
        if(f.nameadd.find("add:")==0)
        {
            f.nameadd=f.nameadd.substr(4);
        }
        if(f.nameadd.find("delete:")==0)
        {
            f.nameadd=f.nameadd.substr(7);
        }
        if(f.nameadd.find("querry")==0)
        {
            f.nameadd=f.nameadd.substr(6);
        }
        if(f.nameblock.find("blocck:")==0)
        {
            f.nameblock=f.nameblock.substr(7);
        }
        if(f.nameblock.find("unlock:")==0)
        {
            f.nameblock=f.nameblock.substr(7);
        }

        return f;
    }

};

class Group
{
    public:
    string group_num;
    string logiin_name;
    string group_type;
    string group_admin;
    string group_kick;
    string tojson() const
    {
        Value f;
        f["group_num"]=group_num;
        f["logiin_name"]=logiin_name;
        f["group_type"]=group_type;
        f["group_admin"]=group_admin;
        f["group_kick"]=group_kick;

        StreamWriterBuilder writerBuilder;
        string jsonStr=writeString(writerBuilder,f);
        return jsonStr;
    }
    static Group fromjson(const string& jsonStr)
    {
        Group f;

        CharReaderBuilder readerBuilder;

        Value root;
        //>>运算符将输入流中的数据解析并存储到root对象中，从而实现了字符串到 JSON 对象的反序列化
        istringstream(jsonStr)>>root;

        f.group_num=root["group_num"].asString();
        f.logiin_name=root["logiin_name"].asString();
        f.group_type=root["group_type"].asString();
        f.group_admin=root["group_admin"].asString();
        f.group_kick=root["group_kick"].asString();

        if(f.group_num.find("create:")==0)
        {
            f.group_num=f.group_num.substr(7);
        }
        if(f.group_num.find("dismiss:")==0)
        {
            f.group_num=f.group_num.substr(8);
        }
         if(f.group_num.find("join:")==0)
        {
            f.group_num=f.group_num.substr(5);
        }
         if(f.group_num.find("quit:")==0)
        {
            f.group_num=f.group_num.substr(5);
        }
        if(f.group_num.find("gmem:")==0)
        {
            f.group_num=f.group_num.substr(5);
        }
        if(f.group_admin.find("increase:")==0)
        {
            f.group_admin=f.group_admin.substr(9);
        }
        if(f.group_admin.find("decrease:")==0)
        {
            f.group_admin=f.group_admin.substr(9);
        }
        if(f.group_num.find("view")==0)
        {
            f.group_num=f.group_num.substr(4);
        }
        if(f.group_kick.find("kicck:")==0)
        {
            f.group_kick=f.group_kick.substr(6);
        }
        if(f.group_num.find("approve:")==0)
        {
            f.group_num=f.group_num.substr(8);
        }
        return f;
    }

};