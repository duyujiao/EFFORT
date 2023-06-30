```c
void printname()//打印提示符
{
  char *name1 = "emo@dyj";
  printf("\033[1m\033[32m%s\033[0m", name1);
  printf(":");
  getcwd(arr,sizeof(arr));
  printf("\033[1m\033[34m%s\033[0m", arr);
  printf("$ ");
  fflush(stdout); //清空缓冲区,默认为行缓冲，提示符不是以\n结尾的
}

```

```c
int main()//参数输入
{
  read_history(NULL);
  signal(SIGINT, SIG_IGN);
  signal(SIGHUP, SIG_IGN);
  // char commod[MAX];
  while (1)
  {
    char *argv[MAX] = {NULL};
    //打印提示符
    printname();
    // commod[0]=0;
    // fgets(commod,MAX,stdin);
    //fflush(stdout);
    char *commod = readline(" ");
    if (commod == NULL) //屏蔽掉ctrl d 出现死循环的情况
    {
      printf("\n");
      continue;
    }
    add_history(commod);
    write_history(NULL);
    // commod[strlen(commod)-1]=0;
    if (strlen(commod) == 0) //屏蔽掉ctrl d 出现死循环的情况
    {
      // printf("\n");
      continue;
    }

    const char *mark = " "; //分割标识符,用strtok函数以空格为分割标识对字符串commod进行分割,将每个指令取出来.
    int i = 1;
    argv[0] = strtok(commod, mark);
    while (argv[i] = strtok(NULL, mark))
    {
      i++;
    }
    // free(commod);
    commodAnalsy(argv, i);//解析参数的函数
     free(commod);
  }
}

```

```c
int isdo(char *argv[], int count)//解析参数
{
  int flag = 10, i;
  if (argv[0] == NULL)
    return 0;
  if (strcmp(argv[0], "cd") == 0)
  {
    flag = 1;
  }
  for (i = 0; i < count; i++)
  {
    if (strcmp(argv[i], ">") == 0)
      flag = 2;
    if (strcmp(argv[i], "|") == 0)
      flag = 3;
    if (strcmp(argv[i], ">>") == 0)
      flag = 4;
    if (strcmp(argv[i], "<") == 0)
      flag = 5;
    if (strcmp(argv[i], "<<") == 0)
      flag = 6;
    if (strcmp(argv[i], "&") == 0)
    {
        pass = 1;
        argv[i]=NULL;
    }
  }
  return flag;
}
void commodAnalsy(char *argv[], int number)
{
  int flag = isdo(argv, number);
  if(pass==1)
  {
    number--;
  }
  if (flag == 1)
  {
    mycd(argv);
  }
  else if (strcmp(argv[0], "history") == 0)
  {
    ShowHistory();
  }
  else if (strcmp(argv[0], "exit") == 0)
  {
    printf("exit\n");
    printf("有停止的任务\n");
    exit(0);
  }
  else if (flag == 2) //输出重定向'>'
  {
    mydup(argv);
  }
  else if (flag == 3) //管道'|'
  {
    callCommandWithPipe(argv, number);
  }
  else if (flag == 4) //输出重定向'>>'
  {
    mydup2(argv);
  }
  else if (flag == 5)//输入重定向'<'
  {
    mydup3(argv);
  }
  else if (flag == 10) //需要子进程进行执行的第三方函数
  {
    if (strcmp(argv[0], "ll") == 0)
    {
      strcpy(argv[0], "ls");
      argv[number++] = "-l";
    }
    if (strcmp(argv[0], "ls") == 0)
      argv[number++] = "--color=auto";
    pid_t pid = fork();
    if (pid < 0)
    {
      perror("fork");
      exit(1);
    }
    else if (pid == 0) //子进程
    {
      execvp(argv[0], argv); //执行命令
      perror("commod");
      exit(1);
    }
    else if (pid > 0) //父进程
    {
      if(pass==1)
      {
        pass=0;
        printf("%d\n",pid);
        return;
      }
      waitpid(pid, NULL, 0);
    }
  }
}

```

```c
char strpwd[MAX]; //用来存放上一次的路径 实现 cd -
void mycd(char *argv[])
{
  if (argv[1] == NULL)
  {
    getcwd(strpwd, sizeof(strpwd));
    chdir("/home");
  }
  else if (strcmp(argv[1], "-") == 0)
  {
    char strpwd1[MAX];
    getcwd(strpwd1, sizeof(strpwd));
    chdir(strpwd);
    printf("%s\n", strpwd);
    strcpy(strpwd, strpwd1);
  }
  else if (strcmp(argv[1], "~") == 0)
  {
    getcwd(strpwd, sizeof(strpwd));
    chdir("/home/gty");
  }
  else
  {
    getcwd(strpwd, sizeof(strpwd));
    chdir(argv[1]);
  }
}

```

```c
void mydup(char *argv[])//>
{
  char *strc[MAX] = {NULL};
  int i = 0;
  while (strcmp(argv[i], ">"))
  {
    strc[i] = argv[i];
    i++;
  }
  int number=i;//重定向前面参数的个数
  int flag =isdo(argv, number);
  i++;
  //出现 echo "adcbe" > test.c  这种情况
  int fdout = dup(1);                                   //让标准输出获取一个新的文件描述符
  int fd = open(argv[i], O_WRONLY | O_CREAT | O_TRUNC,0666); //只写模式|表示如果指定文件不存在，则创建这个文件|表示截断，如果文件存在，并且以只写、读写方式打开，则将其长度截断为0。
  dup2(fd, 1);
  pid_t pid = fork();
  if (pid < 0)
  {
    perror("fork");
    exit(1);
  }
  else if (pid == 0) //子进程
  {
    // dup2(fd, 1);
      if (flag == 3) //管道'|'含有管道
      {
        callCommandWithPipe(strc, number);
      }
      else
       execvp(strc[0], strc);
  }
  else if (pid > 0)
  {
     if(pass==1)
      {
        pass=0;
        printf("%d\n",pid);
        return;
      }
    waitpid(pid, NULL, 0);
  }
  dup2(fdout, 1); //
}
void mydup2(char *argv[])//>>
{
  char *strc[MAX] = {NULL};
  int i = 0;
  
  while (strcmp(argv[i], ">>"))
  {
    strc[i] = argv[i];
    i++;
  }
  int number=i;//重定向前面参数的个数
  int flag =isdo(argv, number);
  i++;
  int fdout = dup(1);                                    //让标准输出获取一个新的文件描述符
  int fd = open(argv[i], O_WRONLY | O_CREAT | O_APPEND,0666); //只写模式|表示如果指定文件不存在，则创建这个文件|表示追加，如果原来文件里面有内容，则这次写入会写在文件的最末尾。
  pid_t pid = fork();
   dup2(fd, 1);
  if (pid < 0)
  {
    perror("fork");
    exit(1);
  }
  else if (pid == 0) //子进程
  {
    if (flag == 3)  //管道'|'含有管道
      {
        callCommandWithPipe(strc, number);
      }
      else
       execvp(strc[0], strc);
  }
  else if (pid > 0)
  {
     if(pass==1)
      {
        pass=0;
        printf("%d\n",pid);
        return;
      }
    waitpid(pid, NULL, 0);
  }
  dup2(fdout, 1); //
}
void mydup3(char *argv[])//<
{
  char *strc[MAX] = {NULL};
  int i = 0;
  while (strcmp(argv[i], "<"))
  {
    strc[i] = argv[i];
    i++;
  }
  i++;
  int number=i;//重定向前面参数的个数
  int flag =isdo(argv, number);
  int fdin = dup(0);                //让标准输出获取一个新的文件描述符
  int fd = open(argv[i], O_RDONLY,0666); //只读模式
   dup2(fd, 0);
  pid_t pid = fork();
  if (pid < 0)
  {
     if(pass==1)
      {
        pass=0;
        printf("%d\n",pid);
        return;
      }
    perror("fork");
    exit(1);
  }
  else if (pid == 0) //子进程
  {
     if (flag == 3)  //管道'|'含有管道
      {
        callCommandWithPipe(strc, number);
      }
      else
       execvp(strc[0], strc);
  }
  else if (pid > 0)
  {
    waitpid(pid, NULL, 0);
  }
  dup2(fdin, 0);
}

```

```c
void ShowHistory()
{
  int i = 0;
  HIST_ENTRY **his;
  his = history_list();
  while (his[i] != NULL)
    printf("%-3d   %s\n", i, his[i++]->line);
}

```

