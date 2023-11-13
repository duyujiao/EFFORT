# 一、Mybatis简介

之前：xxxDao 是接口 规定方法

xxxDaoImpl是实现类 方法的具体实现（数据库的动作）

mybatis:xxxMapper 接口 规定方法

xxxMapper.xml xml 接口对应方法的sql语句，只写sql语句

## mybatis快速入门步骤

1.导入依赖

2.创建实体类

3.创建Mapper接口和Mapper.xml文件

4准备mybatis的配置文件Mybatis-config.xml    链接数据库信息和mapper.xml位置和sql语句

5.使用mybatisapi进行数据库查找即可

SqlSeesionFactory SqlSeesion getMapper(接口.class) 代理对象.方法

## mybatis前沿ibatis

ibatis方式进行数据库操作
1.不要求你写接口

2.直接创建mapper.xmL文件内部编写sqL语句

3.namespace 没有任何要求，随意声明一个字符串即可<mapper namespace="xx.jj">

4.内部通过crud标签声明sqL语句即可

### ibatis

![image-20231113210613853](C:\Users\dyj\AppData\Roaming\Typora\typora-user-images\image-20231113210613853.png)

### mybatis

![image-20231113211710444](C:\Users\dyj\AppData\Roaming\Typora\typora-user-images\image-20231113211710444.png)

# 二、Mybatis基本使用

### 1.向sql语句传参

#{key}：占位符+赋值  emp_id=?   ?=赋值

${key}: 字符串拼接  ”emp_id="+id

推荐使用#{key} 防止【注入攻击】的问题！！！

总结：动态值  使用#{key}

​	   动态的列名 容器名 关键字${key}

？只能替代值的位置，不能替代 容器名（标签，列名，sql关键字）emp_id=? 不能写？=？

xxx(columnName,columnValue)

sql select * from 表 where 列名是动态的${columnName}=动态的值#{columnValue}

### 2.简单类型传入

传入的单个简单类型 key随便写 一般情况下推荐使用参数名！！！

![image-20231113222128954](C:\Users\dyj\AppData\Roaming\Typora\typora-user-images\image-20231113222128954.png)

![image-20231113222145623](C:\Users\dyj\AppData\Roaming\Typora\typora-user-images\image-20231113222145623.png)

### 3.单个实体对象传入

传入的是一个实体对象key写法    key=属性名即可！！！

![image-20231113222458480](C:\Users\dyj\AppData\Roaming\Typora\typora-user-images\image-20231113222458480.png)

![image-20231113222508511](C:\Users\dyj\AppData\Roaming\Typora\typora-user-images\image-20231113222508511.png)

### 4.多个简单类型传入

传入多个简单类型数据如何取值key!  不可以随便写，按照形参名称也不可以

方案一：注解指定 @Param注解 指定多个简单参数的key  key=@Param("value值")

方案二：mybatis默认机制 

  arg0 arg1.....形参从左到右依次对应arg0 arg1  例如：(name,salary) name->arg0  salary->arg1

param1 param2...       (name,salary) name->param1    salary->param2

①

![image-20231113223153856](C:\Users\dyj\AppData\Roaming\Typora\typora-user-images\image-20231113223153856.png)

![image-20231113223203789](C:\Users\dyj\AppData\Roaming\Typora\typora-user-images\image-20231113223203789.png)

②

![image-20231113223230831](C:\Users\dyj\AppData\Roaming\Typora\typora-user-images\image-20231113223230831.png)

③![image-20231113223504729](C:\Users\dyj\AppData\Roaming\Typora\typora-user-images\image-20231113223504729.png)

### 5.map类型传入

传入map 如何指定key的值

key=map的key即可

![image-20231113223908160](C:\Users\dyj\AppData\Roaming\Typora\typora-user-images\image-20231113223908160.png)

![image-20231113223918217](C:\Users\dyj\AppData\Roaming\Typora\typora-user-images\image-20231113223918217.png)