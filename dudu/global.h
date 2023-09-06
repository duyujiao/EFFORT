#ifndef _GLOBAL_H
#define _GLOBAL_H

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
#include <thread>
#include <vector>
#include <mysql/mysql.h>  
#include <unordered_map> 
#include <unordered_set>  
#include <pthread.h> 
#include <signal.h>   
#include <cstdlib>
#include <csignal>  // 包含信号处理相关的头文件
#include <set>//将处于同一群聊的套接字描述符放入同一个 set 中
#include<sys/epoll.h>
#include<errno.h>
#include<filesystem>
#include <fstream>
#include<mutex>

// #include<boost/bind.hpp>
// #include<boost/asio.hpp>
#include<errno.h>


// #include<boost/bind.hpp>
// #include<boost/asio.hpp>
// #include <hiredis/hiredis.h>
#include <fstream>  
using namespace std;


#endif