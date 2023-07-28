#ifndef __RW_HANDLER_H__
#define __RW_HANDLER_H__
#include<iostream>
#include<string>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<cstring>
#include<arpa/inet.h>
using namespace std;
int writen(int fd, char*msg,int size)
{
  char*buf=msg;
  int count =size;
  while(count>0)
  {
    int len=send(fd,buf,count,0);
    if(len==-1)
    {
      return -1;
    }
    else if(len==0)
    {
      continue;
    }
    buf+=len;
    count-=len;
  }
  return size;
}
int sendMsg(int fd,string msg)
{
  if(fd<0||msg.c_str()==NULL||msg.size()<=0)
  {
    return -1;
  }
  char*data=(char*)malloc(sizeof(char)*(msg.size()+4));
  int biglen=htonl(msg.size());
  memcpy(data,&biglen,4);
  memcpy(data+4,msg.c_str(),msg.size());
  int ret;
  ret=writen(fd,data,msg.size()+4);
  if(ret==-1)
  {
    perror("send error");
    close(fd);
  }
  return ret;
}
int readn(int fd,char*buf,int size)
{
  char*pt=buf;
  int count =size;
  while(count>0)
  {
    int len=recv(fd,pt,count,0);
    if(len==-1)
    {
      return -1;
    }
    else if(len==0)
    {
      return size-count;
    }
    pt+=len;
    count-=len;
  }
  return size-count;
}
int recvMsg(int fd,string&msg)
{
  int len=0;
  readn(fd,(char*)&len,4);
  len=ntohl(len);
  printf("接收到的 数据块大小 %d\n",len);
  char * data=(char*)malloc(len+1);
  int Len=readn(fd,data,len);
  if(Len==0)
  { 
      printf("对方断开链接\n");
      close(fd);    
  }
  else if(len!=Len)
  {
    printf("数据接收失败\n");
  }
  data[len]='\0';
  msg=data;
  return Len;
}
#endif