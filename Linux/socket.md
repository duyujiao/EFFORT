# Socket编程

## 套接字概念

在通信过程中，套接字一定是成对出现的

使用同一个文件描述符指向一个套接字，该套接字内部由内核借助两个缓冲区实现，发送缓冲区和接收缓冲区

## 预备知识

### 网络字节序

小端法（**计算机存储）**：	高位存高地址，低位存低地址。	int a=0x12345678

大端法：（**网络存储）**	高位存低地址，低位存高地址。

> htonl --> 本地-->网络 （IP）	在套接字中，IP地址通常以字符串形式表示的，例如：192.168.1.11 --> string --> atoi() --> int -->htonl --> 网络字节序
>
> 在网络设备中，IP地址通常以**二进制**形式存储和传输的
>
> htons --> 本地-->网络 (port)
>
> ntohl --> 网络--> 本地（IP）
>
> ntohs --> 网络--> 本地（Port）

调用以下库函数做网络字节和主机字节序的转换

```c
#include<arpa/inet.h>

//本地转网络
//htonl()函数将主机字节序的32位IP地址转换为网络字节序的32位IP地址
uint32_t htonl(uint32_t hostlong);//无符号32位整型数
uint32_t ntohl(uint32_t netlong);

//针对port端口
uint16_t htons(uint16_t hostshort);
uint16_t ntohs(uint16_t netshort);
//h表示host,n表示network,l表示32位长整数,s表示16位短整数
```

### IP地址转换函数

```c
//本地字节序（string IP） ---> 网络字节序（二进制）
int inet_pton(int af, const char *src, void *dst);		

	//af：AF_INET（IPv4)、AF_INET6(IPv6)
	//src：传入参数，IP地址（点分十进制）
	//dst：传出，转换后的 网络字节序的 IP地址。 

	//返回值：
		//成功： 1
		//异常： 0， 说明src指向的不是一个有效的ip地址。
		//失败：-1

//网络字节序 ---> 本地字节序（string IP）
   const char *inet_ntop(int af, const void *src, char *dst, socklen_t size);	

	//af：AF_INET、AF_INET6
	//src: 网络字节序IP地址
    //dst：本地字节序（string IP）
	//size： dst 的大小

	//返回值： 
    	//成功：dst。 	
		//失败：NULL

```

### socketaddr()地址结构

```
可查看>man 7 zip
```

```c
struct sockaddr_in addr;
//初始化addr
addr.sin_family=AF_INET/AF_INET6//指明使用的IP协议
addr.sin_port=htons(9527);//端口号
//int dst;
//inet_pton(AF_INET,"192.157.22.45",(void*)&dst);//这里因为结构体嵌套结构,所以必须这样初始化
//addr.sin_addr.s_addr=dst;

//一般可以使用一个宏INADDR_ANY,代表取出系统中有效的ip地址,默认取出的是二进制类型
addr.sin_addr.s_addr=htonl(INADDR_ANY);
bind(fd,(struct sockaddr*)&addr,size);
```

## 网络套接字函数

有三个套接字

### socket模型创建流程图

![image-20230611201026121](/home/oem/.config/Typora/typora-user-images/image-20230611201026121.png)

### socket函数

```
#include <sys/socket.h>

int socket(int domain, int type, int protocol);		创建一个 套接字

	domain所选用的地址协议：AF_INET、AF_INET6、AF_UNIX--本地套接字

	type创建套接字选的数据传输协议：SOCK_STREAM（TCP)、SOCK_DGRAM(UDP)

	protocol选的代表协议: 0 

	返回值：

		成功： 新套接字所对应文件描述符

		失败: -1 errno

```

###  bind()函数

```
#include<sys/socket.h>

int bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen);		给socket绑定一个 地址结构 (IP+port端口号)

	sockfd: socket 函数返回值
		/初始化
		struct sockaddr_in addr;

		addr.sin_family = AF_INET;

		addr.sin_port = htons(8888);

		addr.sin_addr.s_addr = htonl(INADDR_ANY);

	addr: 传入参数(struct sockaddr *)&addr

	addrlen: sizeof(addr) 地址结构的大小。

	返回值：

		成功：0

		失败：-1 errno

```

### listen()函数

```
#include<
```

