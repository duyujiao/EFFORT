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

//一般可以使用一个网络地址宏INADDR_ANY,代表取出系统中有效的任意ip地址,默认取出的是二进制类型
addr.sin_addr.s_addr=htonl(INADDR_ANY);
bind(fd,(struct sockaddr*)&addr,size);
```

## 网络套接字函数

有三个套接字

### socket模型创建流程图

！！！这个流程图最好可以写出来

![image-20230611201026121](/home/oem/.config/Typora/typora-user-images/image-20230611201026121.png)

### socket函数

```
#include <sys/socket.h>

int socket(int domain, int type, int protocol);		创建一个 套接字

	domain所选用的地址协议：AF_INET、AF_INET6、AF_UNIX--本地套接字

	type创建套接字选的数据传输协议：SOCK_STREAM（代表协议TCP)、SOCK_DGRAM(代表协议UDP)

	protocol选的代表协议: 0 

	返回值：

		成功： 新套接字所对应文件描述符

		失败: -1 errno

```

###  bind()函数

```
#include<sys/socket.h>
#include<arpa/inet.h>

int bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen);		给socket绑定一个 地址结构 (IP+port端口号)

	sockfd: socket 函数返回值
	
		//初始化
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
#include<sys/socket.h>
int listen(int sockfd, int backlog); 设置同时与服务器建立连接的上限数。（同时进行3次握手的客户端数量）
	sockfd: socket 函数返回值
	backlog：上限数值。最大值 128.
	
	返回值：
		成功：0
		失败：-1 errno	

```

### accept()函数

```
#include<sys/socket.h>
int accept(int socket,struct sockaddr*addr,sockelen_t &addrlen);  阻塞等待客户端建立连接，成功的话，返回一个与客户端成功连接的socket文件描述符。

	sockfd: socket 函数返回值
	addr：传出参数。成功与服务器建立连接的那个客户端的地址结构（IP+port）

	第三个参数赋值方法:socklen_t clit_addr_len = sizeof(addr);
    addrlen：传入传出。 &clit_addr_len
		 入：addr的大小。 出：客户端addr实际大小。


	返回值：
		成功：能与客户端进行数据通信的 socket 对应的文件描述符   。
		失败： -1 ， errno

```

### connect()函数

```
int connect(int sockfd,const struct sockadr*addr,socklen_t addrlen);使用现有的socket与服务器建立连接
	sockfd： socket 函数返回值

		struct sockaddr_in srv_addr;		// 服务器地址结
		srv_addr.sin_family = AF_INET;
		srv_addr.sin_port = 9527 	跟服务器bind时设定的 port 完全一致。

		inet_pton(AF_INET, "服务器的IP地址"，&srv_adrr.sin_addr.s_addr);

	addr：传入参数。服务器的地址结构

	addrlen：服务器的地址结构的大小

	返回值：

		成功：0
		失败：-1 errno

	如果不使用bind绑定客户端地址结构, 采用"隐式绑定".

```

## C/S模型-TCP

### TCP通信流程分析-server

> 1.socket()----创建socket
>
> 2.bind()----绑定服务器地址结构
>
> 3.listen()----设置监听上限
>
> 4.accept()----阻塞监听客户端连接
>
> 5.read()----读socket获取客户端数据
>
> 6.小写转大写-----toupper()
>
> 7.write(fd)
>
> 8.close()

### client

> 1.socket()----创建socket
>
> 2.connect()----与服务器建立连接
>
> 3.write()----写数据到socket
>
> 4.read()----读转换后的数据
>
> 5.显示读取结果
>
> 6.close()

### server的实现

> STDOUT_FILENO是一个常量，通常在C语言中使用，表示标准输出流的文件描述符。在Unix和Linux系统中，每个进程都有三个默认打开的文件描述符：标准输入（stdin）、标准输出（stdout）和标准错误（stderr）。其中，STDOUT_FILENO指向标准输出流的文件描述符，通常被用于向终端或文件中输出数据。在C语言中，可以使用printf函数将数据输出到标准输出流中，也可以使用write函数通过STDOUT_FILENO将数据输出到标准输出流中。



> ```c
> #include<stdio.h>
> #include<stdlib.h>
> #include<ctype.h>
> #include<string.h>
> #include<unistd.h>
> #include<errno.h>
> #include<pthread.h>
> 
> #include<sys/socket.h>
> #include<arpa/inet.h>
> 
> #define SERV_PORT 9527
> 
> void sys_err(const char*str)
> {
>     perror(str);
>     exit(1);
> }
> int main()
> {
>     
>     int lfd=0,cfd=0;//文件描述符后期与服务器建立连接
>     int ret;//read返回实际读到的字节数
>     char buf[BUFSIZ];
> 
>     struct sockaddr_in serv_addr,clit_addr;
>     socklen_t clit_addr_len;
> 
>     serv_addr.sin_family=AF_INET;//和socket的第一个参数一样
>     serv_addr.sin_port=htons(SERV_PORT);
>     serv_addr.sin_addr.s_addr=htonl(INADDR_ANY);
>     
>     lfd=socket(AF_INET,SOCK_STREAM,0);//创建socket
>     if(lfd==-1)//要检查函数是否调用成功
>     {
>         sys_err("socket error");
>     }
>     bind(lfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr));
>     
>     listen(lfd,128);
> 
>     clit_addr_len=sizeof(clit_addr);
>     cfd=accept(lfd,(struct sockaddr *)&clit_addr,&clit_addr_len);//第三个参数客户端地址结构长度
>     if(cfd==-1)//要检查函数是否调用成功
>     {
>         sys_err("accept error");
>     }
> 
>     while(1){
>     ret=read(cfd,buf,sizeof(buf));
>     write(STDOUT_FILENO,buf,ret);
>     for(int i=0;i<ret;i++)
>     {
>         buf[i]=toupper(buf[i]);
>     }
>     write(cfd,buf,ret);
>     }
>     close(lfd);
>     close(cfd);
>     return 0;
> }
> ```
>
> ![image-20230615212206941](/home/oem/.config/Typora/typora-user-images/image-20230615212206941.png)
>
> ![image-20230615212250545](/home/oem/.config/Typora/typora-user-images/image-20230615212250545.png)
>
> 借助nc命令+主机IP地址+你指定的服务器端口号，就是在与你的服务器连接

### client实现

```c
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<errno.h>
#include<pthread.h>

#include<sys/socket.h>
#include<arpa/inet.h>

#define SERV_PORT 9527

void sys_err(const char *str)
{
    perror(str);
    exit(1);
}

int main(int argc,char *argv[])
{
    int cfd;
    int count=10;
    char buf[BUFSIZ];
    struct sockaddr_in serv_addr;//服务器地址结构
    serv_addr.sin_family=AF_INET;
    serv_addr.sin_port=htons(SERV_PORT);//服务器端口
    inet_pton(AF_INET,"127.0.0.1",&serv_addr.sin_addr.s_addr);//将ip地址转换成网络字节序
    //serv_addr.sin_addr.s_addr=htonl(INADDR_ANY);

    cfd=socket(AF_INET,SOCK_STREAM,0);
    if(cfd==-1)
    {
        sys_err("socket error");
    }

    int ret=connect(cfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr));
    if(ret!=0)
    {
        sys_err("connect error");
    }

    while(--count)
    {
        write(cfd,"hello\n",6);
        ret=read(cfd,buf,sizeof(buf));
        write(STDOUT_FILENO,buf,ret);
        sleep(1);
    }
    close(cfd);
    return 0;
}
```

## 错误处理函数的封装

这里原函数和包裹函数的函数名差异只有首字母大写，这是因为man page对字母大小写不敏感，同名的包裹函数一样可以跳转至man page

**错误处理函数封装：**就是重新包裹需要检查返回值的函数，让代码不那么肥胖。

### 封装思想总结和readn、readline封装思想说明

封装目的： 在 server.c 编程过程中突出逻辑，将出错处理与逻辑分开，可以直接跳转man手册。


【wrap.c】								【wrap.h】


存放网络通信相关常用 自定义函数						存放 网络通信相关常用 自定义函数原型(声明)。

命名方式：系统调用函数首字符大写, 方便查看man手册

 如：Listen()、Accept();



函数功能：调用系统调用函数，处理出错场景。

在 server.c 和 client.c 中调用 自定义函数

联合编译 server.c 和 wrap.c 生成 server

client.c 和 wrap.c 生成 client