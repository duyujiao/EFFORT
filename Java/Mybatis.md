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

#### 1.1.数据输入-简单类型传入

传入的单个简单类型 key随便写 一般情况下推荐使用参数名！！！

![image-20231113222128954](C:\Users\dyj\AppData\Roaming\Typora\typora-user-images\image-20231113222128954.png)

![image-20231113222145623](C:\Users\dyj\AppData\Roaming\Typora\typora-user-images\image-20231113222145623.png)

#### 1.2.单个实体对象传入

传入的是一个实体对象key写法    key=属性名即可！！！

![image-20231113222458480](C:\Users\dyj\AppData\Roaming\Typora\typora-user-images\image-20231113222458480.png)

![image-20231113222508511](C:\Users\dyj\AppData\Roaming\Typora\typora-user-images\image-20231113222508511.png)

#### 1.3.多个简单类型传入

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

#### 1.4map类型传入

传入map 如何指定key的值

key=map的key即可

![image-20231113223908160](C:\Users\dyj\AppData\Roaming\Typora\typora-user-images\image-20231113223908160.png)

![image-20231113223918217](C:\Users\dyj\AppData\Roaming\Typora\typora-user-images\image-20231113223918217.png)

### 2.数据输出

#### 2.1单个简单类型和定义别名

返回i单个简单类型如何指定？ resultType的写法！返回值的数据类型！！

resultType语法：

1.类的全限定符号

2.别名简称  mybatis给我们提供了72种默认的别名！

这些都是我们常用的Java数据类型！【java的常用数据类型】

基本数据类型 int double --> _int _double

包装数据类型 Integer Double-->int integer   double        

 集合容器类型 Map List HashMap-->小写即可 map list hashmap

  扩展：如果没有提供的需要自己定义或者写类的全限定符号，给自己声明的类如何定义别名

mybatis-config.xml文件中，①给类单独定义别名！！！.

注意这部分要写在<settings></settings>下面！！！

```xml
 <typeAliases>
        <typeAlias type="org.example.pojo.Employee" alias="ergouzi"
    </typeAliases>
```

   ②批量设置

批量将报下的类给与别名，别名就是类的首字母小写

扩展：如果不想使用批量的别名，可以使用注解给与名字。也就是在自己定义的类前面加上@Alias("ergouzi")

```xml
 <typeAliases>
        <package name="org.example.pojo"/>
    </typeAliases>
```

​         

 ![image-20231114150011725](C:\Users\dyj\AppData\Roaming\Typora\typora-user-images\image-20231114150011725.png)

![image-20231114150043689](C:\Users\dyj\AppData\Roaming\Typora\typora-user-images\image-20231114150043689.png)

#### 2.2单个实体类型输出

默认要求：查询，返回单个实体类型，要求列名和属性名要一致！这样才可以进行实体类的属性映射

但是也可以进行设置，设置支持驼峰式自动映射！

emp_id--->empId===empId

mybatis-config.xml文件

| **mapUnderscoreToCamelCase** | 是否开启驼峰命名自动映射，即从经典数据库列名 A_COLUMN 映射到经典 Java 属性名 aColumn。 | true \| false | False |
| ---------------------------- | ------------------------------------------------------------ | ------------- | ----- |
|                              |                                                              |               |       |

```xml
<setting name"mapUnderscoreToCamelCase" value="true"/>
```

#### 2.3返回Map类型

适用于SQL查询返回的各个字段综合起来并不和任何一个现有的实体类对应，没法封装到实体类对象中。能够封装成实体类类型的，就不使用Map类型。

当没有实体类可以使用接值的时候，我们可以使用map接受数据

key->查询的列  value->查询的值

```xml
<!-- Map<String,Object> selectEmpNameAndMaxSalary(); -->
<!-- 返回工资最高的员工的姓名和他的工资 -->
<select id="selectEmpNameAndMaxSalary" resultType="map">
  SELECT
    emp_name 员工姓名,
    emp_salary 员工工资,
    (SELECT AVG(emp_salary) FROM t_emp) 部门平均工资
  FROM t_emp WHERE emp_salary=(
    SELECT MAX(emp_salary) FROM t_emp
  )
</select>
```

#### 2.4返回集合类型

返回值试剂盒，resultType不需要指定结合类型，只需要指定泛型即可！！！

![image-20231114153749992](C:\Users\dyj\AppData\Roaming\Typora\typora-user-images\image-20231114153749992.png)

#### 2.5自动提交事务和自增长主键回显

主键回显 获取插入数据的主键

自增长主键回显 mysql auto_increment

```
//员工插入

int insertEmp(Employee employee)

usGeneratedKeys="true" 我们想要数据库自动增强的主键值
keyColumn="emp_id" 主键列的值
keyProperty="empId"接受主键列值的属性！！！


```

![image-20231114155948808](C:\Users\dyj\AppData\Roaming\Typora\typora-user-images\image-20231114155948808.png)

![image-20231114160052340](C:\Users\dyj\AppData\Roaming\Typora\typora-user-images\image-20231114160052340.png)

#### 2.6非自增长类型主键维护

自己维护主键是在test中写

```
String id=UUID.randomUUID().toString().replaceAll("-","")
teacher.settId(id);
```

期望，非自增长的主键，交给mybatis帮助我们维护

插入之前，先指定一段sql语句，生成一个主键值！

```
order="before|after"sql语句实在插入之前还是之后执行！

resultType=返回值类型

keyProperty=查询结果给哪个属性赋值
<selectKey order="BEFORE" resultType="string" keyProperty="tId">
SELECT REPLACE(UUID(),'-,');
<selectKey>

```

#### 2.7列名和属性名不一致-自定义映射关系和resultMap初体验

方案一：别名

方案二：开启驼峰式映射

方案三：resultMap自定义映射（resultType和resultMap二选一）

resultType按照规则自动映射 按照是否开启驼峰式映射，自己映射属性和列名！只能映射一层结构！

深层次的对象结构无法映射，多表查询的时候结果无法映射！

resultMap标签，自定义映射关系，可以深层次可以单层次！！

声明resultMap标签，自己定义映射规则

id标识：select resultMap="标识"

type:具体的返回值类型 全限定符和别名|集合只写泛型即可

<id 主键映射关系

<result 普通列的映射关系

![image-20231114191805215](C:\Users\dyj\AppData\Roaming\Typora\typora-user-images\image-20231114191805215.png)

## 3.Mybatis多表映射

#### 3.1多表映射需要我们做什么

要做三件事情：

1.多表查询的sql语句需要我们编写 连接查询

2.自己设计存储数据的实体类 承接多个表查询的结果

3.自己定义结果集映射 resultMap

![image-20231115124545554](C:\Users\dyj\AppData\Roaming\Typora\typora-user-images\image-20231115124545554.png)

#### 3.2多表实体类存储设计

多表结果实体类设计小技巧：

对一，属性中包含对方对象

对多，属性中包含对方对象的集合