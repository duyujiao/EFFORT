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

