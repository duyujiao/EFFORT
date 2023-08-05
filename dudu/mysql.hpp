#ifndef __MYSQL_H__
#define __MYSQL_H__
#include <mysql/mysql.h>
#include <string>
#include<iostream>

using namespace std;




class MySQL {
public:
    MySQL();
    ~MySQL();
    //连接mysql数据库
    bool connect(const string& host, const string& user, const string& password, const string& database);
    //断开mysql数据库连接
    void disconnect();
    //执行SQL查询语句
    bool execute(const string& sql);
    // 插入键值对，如果键已经存在，则更新对应的值，将键值对存储到MySQL数据库中的一个表中
    bool setValue(const string& key, const string& value);
    // 根据键获取对应的值，查询指定键在mytable表中对应的值
    string getValue(const string& key);
    // 根据键删除对应的键值对
    bool delKey(const string& key);


    // 将键值对插入到哈希表中，如果字段已经存在，则更新对应的值
    bool hsetValue(const string& key, const string& field, const string& value);
    // 根据键和字段从哈希表中删除对应的键值对
    bool hashdel(const string& key, const string& field);
    // 根据键和字段从哈希表中获取对应的值
    string gethash(const string& key, const string& field);
    // 返回哈希表中元素的个数
    int hlen(const string& key);

    // 将元素插入到 Set 集合中，如果元素已经存在，则什么也不做
    bool saddvalue(const string& key, const string& value);
    // 从 Set 集合中删除指定的元素
    bool sremvalue(const string& key, const string& value);
    // 返回 Set 集合中元素的个数
    int scard(const string& key);
     // 返回 Set 集合中所有的元素
    MYSQL_RES* smembers(const string& key);

    //查询数据是否存在
    bool isexist(const string& key,const string&value);
    //查询是否在线
    bool isClientOnline(const string& table, const string& field, const string& value);

    // 向列表的头部插入元素
    bool lpush(const string& key, const string& value);
    // 返回列表中元素的个数
    int llen(const string& key);
    // 返回列表中元素
    MYSQL_RES* lrange(const string& key);
    // 返回列表中指定范围内的元素
    MYSQL_RES* lrange(const string& key, int start, int end);
    // 保留列表中指定范围内的元素，其余的元素都删除
    bool ltrim(const string& key);

private:
    MYSQL* m_mysql;
};

MySQL::MySQL() {
    m_mysql = mysql_init(NULL);
}

MySQL::~MySQL() {
    mysql_close(m_mysql);
}

bool MySQL::connect(const string& host, const string& user, const string& password, const string& database) {
    if (m_mysql == NULL) {
        return false;
    }
    //if (mysql_real_connect(m_mysql, host.c_str(), user.c_str(), password.c_str(), database.c_str(), 0, NULL, 0) == NULL) 
    if(mysql_real_connect(m_mysql,"localhost","root","40111004","chatroom",0,NULL,0)==NULL)
    {
        return false;
    }
    return true;
}

void MySQL::disconnect() {
    mysql_close(m_mysql);
}

bool MySQL::execute(const string& sql) {
    if (mysql_query(m_mysql, sql.c_str()) != 0) {
        return false;
    }
    return true;
}

bool MySQL::setValue(const string& key, const string& value) {
    //INSERT INTO mytable (key, value) VALUES ('my_key', 'my_value')
    string sql = "INSERT INTO mytable(key, value) VALUES('" + key + "', '" + value + "') ON DUPLICATE KEY UPDATE value='" + value + "'";
    //将SQL语句传递给execute函数执行
    return execute(sql); 
}


//查询在mytable表中指定键对应的值，如果查询成功，则返回该值的字符串表示，否则返回空字符串。
string MySQL::getValue(const string& key) {
    //从mytable表中选择value列，条件是key列的值等于参数key的值
    string sql = "SELECT value FROM mytable WHERE key='" + key + "'";
    //发送查询请求
    if (mysql_query(m_mysql, sql.c_str()) != 0) {
        return "";
    }
    //获取查询结果
    MYSQL_RES* result = mysql_store_result(m_mysql);
    if (result == NULL) {
        return "";
    }
    //获取第一行查询结果的数据
    MYSQL_ROW row = mysql_fetch_row(result);
    if (row == NULL) {
        mysql_free_result(result);
        return "";
    }
    string value = row[0];
    //释放查询结果
    mysql_free_result(result);
    return value;
}

//删除mytable表中指定键对应的行数据
bool MySQL::delKey(const string& key) {
    string sql = "DELETE FROM mytable WHERE key='" + key + "'";
    return execute(sql);
}


bool MySQL::hsetValue(const string& key, const string& field, const string& value) {
    string sql = "INSERT INTO mytable(key, field, value) VALUES('" + key + "', '" + field + "', '" + value + "') ON DUPLICATE KEY UPDATE value='" + value + "'";
    return execute(sql);
}

bool MySQL::hashdel(const string& key, const string& field) {
    string sql = "DELETE FROM mytable WHERE key='" + key + "' AND field='" + field + "'";
    return execute(sql);
}

string MySQL::gethash(const string& key, const string& field) {
    string sql = "SELECT value FROM mytable WHERE key='" + key + "' AND field='" + field + "'";
    if (mysql_query(m_mysql, sql.c_str()) != 0) {
        return "";
    }
    MYSQL_RES* result = mysql_store_result(m_mysql);
    if (result == NULL) {
        return "";
    }
    MYSQL_ROW row = mysql_fetch_row(result);
    if (row == NULL) {
        mysql_free_result(result);
        return "";
    }
    string value = row[0];
    mysql_free_result(result);
    return value;
}

int MySQL::hlen(const string& key) {
    string sql = "SELECT COUNT(*) FROM mytable WHERE key='" + key + "'";
    if (mysql_query(m_mysql, sql.c_str()) != 0) {
        return -1;
    }
    MYSQL_RES* result = mysql_store_result(m_mysql);
    if (result == NULL) {
        return -1;
    }
    MYSQL_ROW row = mysql_fetch_row(result);
    if (row == NULL) {
        mysql_free_result(result);
        return -1;
    }
    //该数据解析为整数类型
    int count = stoi(row[0]);
    mysql_free_result(result);
    return count;
}

bool MySQL::saddvalue(const string& key, const string& value) {
    string sql = "INSERT INTO mytable(key, value) VALUES('" + key + "', '" + value + "') ON DUPLICATE KEY UPDATE value=value";
    return execute(sql);
}

bool MySQL::sremvalue(const string& key, const string& value) {
    string sql = "DELETE FROM mytable WHERE key='" + key + "' AND value='" + value + "'";
    return execute(sql);
}

int MySQL::scard(const string& key) {
    string sql = "SELECT COUNT(DISTINCT value) FROM mytable WHERE key='" + key + "'";
    if (mysql_query(m_mysql, sql.c_str()) != 0) {
        return -1;
    }
    MYSQL_RES* result = mysql_store_result(m_mysql);
    if (result == NULL) {
        return -1;
    }
    MYSQL_ROW row = mysql_fetch_row(result);
    if (row == NULL) {
        mysql_free_result(result);
        return -1;
    }
    int count = stoi(row[0]);
    mysql_free_result(result);
    return count;
}

MYSQL_RES* MySQL::smembers(const string& key) {
    string sql = "SELECT DISTINCT value FROM mytable WHERE key='" + key + "'";
    if (mysql_query(m_mysql, sql.c_str()) != 0) {
        return NULL;
    }
    MYSQL_RES* result = mysql_store_result(m_mysql);
    if (result == NULL) {
        return NULL;
    }
    return result;
}

bool MySQL::lpush(const string& key, const string& value) {
    string sql = "INSERT INTO mytable(key, value) VALUES('" + key + "', '" + value + "')";
    return execute(sql);
}

int MySQL::llen(const string& key) {
    string sql = "SELECT COUNT(*) FROM mytable WHERE key='" + key + "'";
    if (mysql_query(m_mysql, sql.c_str()) != 0) {
        return -1;
    }
    MYSQL_RES* result = mysql_store_result(m_mysql);
    if (result == NULL) {
        return -1;
    }
    MYSQL_ROW row = mysql_fetch_row(result);
    if (row == NULL) {
        mysql_free_result(result);
        return -1;
    }
    int count = stoi(row[0]);
    mysql_free_result(result);
    return count;
}

MYSQL_RES* MySQL::lrange(const string& key) {
    string sql = "SELECT value FROM mytable WHERE key='" + key + "'";
    if (mysql_query(m_mysql, sql.c_str()) != 0) {
        return NULL;
    }
    MYSQL_RES* result = mysql_store_result(m_mysql);
    if (result == NULL) {
        return NULL;
    }
    return result;
}

MYSQL_RES* MySQL::lrange(const string& key, int start, int end) {
    string sql = "SELECT value FROM mytable WHERE key='" + key + "' LIMIT " + to_string(start) + "," + to_string(end - start + 1);
    if (mysql_query(m_mysql, sql.c_str()) != 0) {
        return NULL;
    }
    MYSQL_RES* result = mysql_store_result(m_mysql);
    if (result == NULL) {
        return NULL;
    }
    return result;
}

bool MySQL::ltrim(const string& key) {
    string sql = "DELETE FROM mytable WHERE key='" + key + "' ORDER BY id LIMIT 1";
    return execute(sql);
}

bool MySQL::isexist(const string& key,const string&value)
{
    string sql = "SELECT value FROM mytable WHERE key='" + key + "' AND value='" + value + "'";
    //发送查询请求
    if (mysql_query(m_mysql, sql.c_str()) != 0) {
        return false;
    }
    //获取查询结果
    MYSQL_RES* result = mysql_store_result(m_mysql);
    if (result == NULL) {
        return false;
    }
    //获取第一行查询结果的数据
    MYSQL_ROW row = mysql_fetch_row(result);
    if (row == NULL) {
        mysql_free_result(result);
        return false;
    }
    //释放查询结果
    mysql_free_result(result);
    return true;
}

bool MySQL::isClientOnline(const string& table, const string& field, const string& value) {
    // 构造查询语句
    string sql = "SELECT COUNT(*) FROM " + table + " WHERE " + field + " = '" + value + "' AND online = 1";

    // 发送查询请求
    if (mysql_query(m_mysql, sql.c_str()) != 0) {
        cerr << "Error: " << mysql_error(m_mysql) << endl;
        return false;
    }

    // 获取查询结果
    MYSQL_RES* result = mysql_store_result(m_mysql);
    if (result == NULL) {
        cerr << "Error: " << mysql_error(m_mysql) << endl;
        return false;
    }

    // 获取第一行查询结果的数据
    MYSQL_ROW row = mysql_fetch_row(result);
    if (row == NULL) {
        cerr << "Error: " << mysql_error(m_mysql) << endl;
        mysql_free_result(result);
        return false;
    }

    // 获取结果值
    int count = atoi(row[0]);
    bool online = (count == 1);

    // 释放查询结果
    mysql_free_result(result);

    return online;
}


#endif
