#include <iostream>
#include <mysql/mysql.h>
#include <string>

using namespace std;

class MySQL {
public:
    MySQL();
    ~MySQL();
    //连接mysql数据库
    bool connect(const string& host, const string& user, const string& password, const string& database);
    //断开mysql数据库连接
    void disconnect();
    bool execute(const string& sql);
    bool setValue(const string& key, const string& value);
    string getValue(const string& key);
    bool delKey(const string& key);

    bool hsetValue(const string& key, const string& field, const string& value);
    bool hashdel(const string& key, const string& field);
    string gethash(const string& key, const string& field);
    int hlen(const string& key);

    bool saddvalue(const string& key, const string& value);
    bool sremvalue(const string& key, const string& value);
    int scard(const string& key);
    MYSQL_RES* smembers(const string& key);

    bool lpush(const string& key, const string& value);
    int llen(const string& key);
    MYSQL_RES* lrange(const string& key);
    MYSQL_RES* lrange(const string& key, int start, int end);
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
    if (mysql_real_connect(m_mysql, host.c_str(), user.c_str(), password.c_str(), database.c_str(), 0, NULL, 0) == NULL) {
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
    string sql = "INSERT INTO mytable(key, value) VALUES('" + key + "', '" + value + "') ON DUPLICATE KEY UPDATE value='" + value + "'";
    return execute(sql);
}

string MySQL::getValue(const string& key) {
    string sql = "SELECT value FROM mytable WHERE key='" + key + "'";
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
