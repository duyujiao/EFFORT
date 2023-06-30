# 目录和文件操作

cd .. 跳到上一级目录

pwd 查看的当前目录

sudo su切换当根用户

exit 切换回来

which查看指定命令所在路径

mkdir 创建目录

rmdir 删除空目录

tree 这个命令下载安装 sudo apt-get install tree  按树形状显示目录文件

##  **linux系统目录**

bin 存放二进制可执行文件

./data 就是自己运行data文件

boot 存放的开机启动程序

dev 存放设备文件

cat 读一个文件内容

linux系统中“所见皆文件”

etc 存放当前系统的用户相关配置信息

home 存放用户的目录

lib  库文件

root 管理员宿主目录（主目录）

usr 用户资源管理目录

## **linux系统文件类型**

普通文件：-

目录文件：d

字符设备文件：c

块设备文件:b

软连接:l

管道文件：p

套接字:s

## **相对路径和绝对路径**

绝对路径：从/目录开始描述的路径

cd /home

cd /usr

相对路径：从当前位置开始描述的路径

cd ../../

ls abc/def



**shell家族**

shell命令解释器，根据输入的命令执行相应的命令

查看当前系统下有哪些shell:

cat /etc/shells

查看当前系统正在使用的shell:

echo $SHELL

/bin/sh(已经被/bin/bash所取代)

/bin/bash(就是linux默认的shell)

/bin/ksh(Kornshell由AT&T Bell lab.发展出来的，兼容与bash)

/bin/tcsh(整合C Shell,提供更多的功能)

/bin/csh(已经被/bin/tcsh所取代)

/bin/zsh(基于ksh发展出来的，功能更强大的shell)

**创建修改用户和用户组**

创建用户  sudo adduser 新用户名

修改文件所属用户 sudo chown 新用户名 待修改文件名

sudo chown wangwu a.c

创建用户组 sudo addgroup 新组名

修改文件所属用户组  sudo chgrp 新用户组名 待修改文件名

sudo chgrp g88 a.c

删除用户 sudo deluser wangwu

删除用户组 sudo delgroup g88

**find命令**

-type按文件类型搜索

-name按文件名搜索

-maxdepth 指定搜索深度,应作为第一个参数出现

eg:   find -maxdepth 2 -name '*.jpg'

-size 按文件大小搜索  eg:find ./ -size +20M -size -50M

​                                              ls -l -h ./.vscode/extensions/ms-vscode.cpptools-1.14.4-linux-x64/bin/cpptools

-exec               find ./ -maxdepth 1 -type f -exec ls -l {} \;会执行ls -l操作    将find搜索的结果集执行某一命令

-ok         以交互式的方式将find搜索的结果集执行某一命令









