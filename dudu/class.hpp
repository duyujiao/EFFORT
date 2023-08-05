#include<iostream>
#include<string>
#include<jsoncpp/json/json.h>

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
        return user;
    }
};