#ifndef __LOGINMESSAGE_HANDLER_H__
#define __LOGINMESSAGE_HANDLER_H__

#include <iostream>
#include <string>
#include <json/json.h>
using namespace std;
using namespace Json;
class loginmessage
{
private:
    string UID;
    string password;
public:
    loginmessage(string a="",string b="")
    {
        UID=a;
        password=b;
    }
    string getUID()
    {
        return UID;
    }
    string getpassword()
    {
        return password;
    }
    string tojson()
    {
        Value root;
        root.append(UID);
        root.append(password);
        FastWriter f;
        return f.write(root);
    }
    void jsonparse(string json)
    {
        Reader r;
        Value root;
        r.parse(json,root);
        int i=0;
        UID=root[i++].asString();
        password=root[i++].asString();
    }
};
#endif