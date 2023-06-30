```c
void ls_l(struct stat buf,char *name,int color)
{
       char colorname[PATH_MAX+1];
       struct passwd *uid;
       struct group *gid;
       char mtime[100];
          //文档类别
         if(S_ISLNK(buf.st_mode))//判断是否为符号连接
          printf("l");
          else if(S_ISREG(buf.st_mode))//判断是否为一般文件
          printf("-");
          else if(S_ISDIR(buf.st_mode))//是否为目录文件
          printf("d");
          else if(S_ISCHR(buf.st_mode))//是否为字符设备文件
          printf("c");
          else if(S_ISBLK(buf.st_mode))//是否为快设备文件
          printf("b");
          else if(S_ISFIFO(buf.st_mode))//是否为先进先出FIFO
          printf("f");
          else if(S_ISSOCK(buf.st_mode))//是否为socketP
          printf("s");
          
          //user 权限
          if(buf.st_mode&S_IRUSR)
          {
            printf("r");
          }
          else 
          {
            printf("-");
          }
          if(buf.st_mode&S_IWUSR)
          printf("w");
          else 
          printf("-");
          if(buf.st_mode&S_IXUSR)
          printf("x");
          else
          printf("-");
          //逻辑与
          /*
            S_IRUSR:用户读权限
            S_IWUSR:用户写权限
            S_IRGRP:用户组读权限
            S_IWGRP:用户组写权限
            S_IROTH:其他组读权限
            S_IWOTH:其他组写权限
          */
 
          //group 权限
          if(buf.st_mode&S_IRGRP)
          printf("r");
          else
          printf("-");
          if(buf.st_mode&S_IWGRP)
          printf("w");
           else
          printf("-");
          if(buf.st_mode&S_IXGRP)
          printf("x");
          else
          printf("-");
 
          //other 权限
          if(buf.st_mode&S_IROTH)
          printf("r");
           else
          printf("-");
          if(buf.st_mode&S_IWOTH)
          printf("w");
           else
          printf("-");
          if(buf.st_mode&S_IXOTH)
          printf("x");
           else
          printf("-");
    //链接数
          printf("%4lu ",buf.st_nlink);
          //uid和gid
          uid=getpwuid(buf.st_uid);//获得用户名
          gid=getgrgid(buf.st_uid);//获得用户组名
          if(uid==NULL||gid==NULL)
           {
               printf("error,can't get id");
               return ; // __LINE__正在编译的行号
           }
          printf("%-8s  ",uid->pw_name);
          printf("%-8s",gid->gr_name);
           
           //文档容量大小
          printf("%8ld  ",buf.st_size);
          //最后修改时间
          strcpy(mtime,ctime(&buf.st_mtime));
          mtime[strlen(mtime)-1]='\0';  //不然会换行
          printf("%s",mtime);
          /*
          int sprintf(char*str,char*format,agrument,...)
          char*str要写入的字符串
          char*format为格式化字符串
           agrument,...为变量
          */
          sprintf(colorname,"\033[%dm%s\033[0m",color,name);
          printf(" %-s\n",colorname);
 
 
 
}
```

