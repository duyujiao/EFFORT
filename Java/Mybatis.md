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

#### 3.3对一查询实现

根据ID拆线呢订单，以及订单关联的用户的信息

创建resultMap实现对一关联关系映射

<!-- 创建resultMap实现“对一”关联关系映射 -->
<!-- id属性：通常设置为这个resultMap所服务的那条SQL语句的id加上“ResultMap” -->
<!-- type属性：要设置为这个resultMap所服务的那条SQL语句最终要返回的类型 -->
<resultMap id="selectOrderWithCustomerResultMap" type="order">

第一层属性 order对象 

order的主键 id标签  然后是普通列result标签    column数据库中的名字，property对应的属性名

第二层：对象属性赋值 <association>

property对象属性名  javaType对象类型

![image-20231119132357746](C:\Users\dyj\AppData\Roaming\Typora\typora-user-images\image-20231119132357746.png)

#### 3.4对多查询

 <association>换成<collection>

给集合属性赋值：property 集合属性名，ofType结合的泛型类型

#### 3.5多表查询优化

resultMap标签 有没有嵌套都会自动帮我们映射result标签的属性和列,就不用写result啦！！！

<setting name="autoMappingBehavior" value="FULL"/>

## 4.Mbatis动态语句

### 4.1where if标签

*案例：根据员工的姓名和工资查询员工的信息*

sql语句有多个条件时，如果传入属性，就判断相等；如果不传入，不加对应的条件

if 判断传入的参数，最终是否添加语句   <if test="name!=null"></if>

test属性：内部做比较运算，最终true将标签内的sql语句进行拼接 false不拼接标签内部语句

判断语句 ：key 比较符号 值 and | or key 比较符号 值

大于和小于 不推荐直接写符号！实体符号  html 

```
 ">"==&gt;    "<"==&lt;
```

问题：会有多余的where和and出现

那么就用到了where标签：自动添加where关键字，where内部有任何一个if满足，自动添加where不满足去掉where;自动去掉多余的and和or关键字

![image-20231119141654344](C:\Users\dyj\AppData\Roaming\Typora\typora-user-images\image-20231119141654344.png)

### 4.2set标签

案例：根据员工id更新员工数据，我们要求 传入的name和salary不为null的才更新

又会面临差不多的问题：多了一个逗号或者语法错误多set

set作用：自动去掉多余的逗号，自动添加set关键字

### 4.3trim标签-替代where和set

prefix属性：指定要动态添加的前缀

suffix属性：指定要动态添加的后缀

prefixOverrides属性：指定要动态去掉的前缀，使用"|"分割有可能多个值

suffixOverrides属性：指定要动态去掉的后缀，使用"|"分割有可能多个值

**替代where**

![image-20231119160658976](C:\Users\dyj\AppData\Roaming\Typora\typora-user-images\image-20231119160658976.png)

**替代set**

![image-20231119160735924](C:\Users\dyj\AppData\Roaming\Typora\typora-user-images\image-20231119160735924.png)

### 4.4choose/when/otherwise标签

案例：根据两个条件拆线呢，如果姓名不为null使用姓名查询，如果姓名为null,薪水不为空就使用薪水查询！都为null查询全部

在多个分支条件中，仅执行一个，只有一个满足，从上到下依次执行条件判断，碰到的第一个满足条件的分支会被采纳，被采纳分支后面的分支都将不被考虑，如果所有的when分支都不满足，那么就执行otherwise分支

![image-20231119161652880](C:\Users\dyj\AppData\Roaming\Typora\typora-user-images\image-20231119161652880.png)

### 4.5foreach标签

案例：根据id的批量查询，删除，插入，修改

 collection:遍历的数据collection="ids"，如果没有起别名就写成collection="ids|arg0|list"

open:遍历之前要追加的字符串

close:遍历结束需要添加的字符串

separator:每次遍历的分隔符号！如果时最后一次，不会追加

item：获取每个遍历项  

遍历的内容：#{遍历项 item指定的key}

 ![image-20231119164603004](C:\Users\dyj\AppData\Roaming\Typora\typora-user-images\image-20231119164603004.png)

![image-20231119164930482](C:\Users\dyj\AppData\Roaming\Typora\typora-user-images\image-20231119164930482.png)

 ![image-20231119165407104](C:\Users\dyj\AppData\Roaming\Typora\typora-user-images\image-20231119165407104.png)

如果一个标签设计多个语句！需要设置允许指定多语句！

```properties
atguigu.dev.url=jdbc:mysql:///mybatis-example?allowMultiQueries=true
```

### 4.6sql片段

抽取重复事务SQL片段，引用已抽取的SQL片段

![image-20231119165722454](C:\Users\dyj\AppData\Roaming\Typora\typora-user-images\image-20231119165722454.png)

![image-20231119165745059](C:\Users\dyj\AppData\Roaming\Typora\typora-user-images\image-20231119165745059.png)

## 5.Mybatis高级扩展

### 5.1批量mapper指定

1.要求Mapperxml文件和mapper接口的命名必须相同

2.最终打包后的位置要一致 都是指定的包地址下

方案一：xml文件也加入到接口所在的包即可和修改maven的pom.xml最终把这下面的配置都打包（不推荐）

方案二：在resources文件夹创建对应的文件夹结构即可，直接一口气创建多个文件夹不能用com.atiguigu.mapper,必须使用com/atiguigu/mapper

![image-20231119172152085](C:\Users\dyj\AppData\Roaming\Typora\typora-user-images\image-20231119172152085.png)

### 5.2插件机制和分页插件使用

正常编写sql语句，不要使用;结尾

调用mapper.queryList()；之前，先设置分页数据（当前是第几页，每页显示几个），这里前端会传过来

将查询数据封装到一个PageInfo的分页实体类（一共有多少页，一共有多少条等等）

![image-20231119174005631](C:\Users\dyj\AppData\Roaming\Typora\typora-user-images\image-20231119174005631.png)

```java
@Test
public void testTeacherRelationshipToMulti() {

    TeacherMapper teacherMapper = session.getMapper(TeacherMapper.class);
	//先设置分页数据（当前是第几页，每页显示几个），这里前端会传过来
    PageHelper.startPage(1,2);
    // 查询Customer对象同时将关联的Order集合查询出来
    //TODO:注意不能将两条查询装到一个分区页
    List<Teacher> allTeachers = teacherMapper.findAllTeachers();
	//将查询数据封装到一个PageInfo的分页实体类（一共有多少页，一共有多少条等等）
    PageInfo<Teacher> pageInfo = new PageInfo<>(allTeachers);

    System.out.println("pageInfo = " + pageInfo);
    long total = pageInfo.getTotal(); // 获取总记录数
    System.out.println("total = " + total);
    int pages = pageInfo.getPages();  // 获取总页数
    System.out.println("pages = " + pages);
    int pageNum = pageInfo.getPageNum(); // 获取当前页码
    System.out.println("pageNum = " + pageNum);
    int pageSize = pageInfo.getPageSize(); // 获取每页显示记录数
    System.out.println("pageSize = " + pageSize);
    List<Teacher> teachers = pageInfo.getList(); //获取查询页的数据集合
    System.out.println("teachers = " + teachers);
    teachers.forEach(System.out::println);

}
```

### 5.3ORM介绍和逆向工程 

ORM介绍：ORM思维应用在持久层框架上，使用面向对象思维进行数据库操作

![image-20231119181111614](C:\Users\dyj\AppData\Roaming\Typora\typora-user-images\image-20231119181111614.png)

 期望半自动的orm框架，也能实现单表的curd自动生成

**逆向工程**：半自动orm---->全自动orm迈进，插件MybatisX实现自动生成单表的增删改查

## 6.Mybatis总结

|                 |                                               |
| --------------- | --------------------------------------------- |
| 核心点          | 掌握目标                                      |
| mybatis基础     | 使用流程, 参数输入,#{} ${},参数输出           |
| mybatis多表     | 实体类设计,resultMap多表结果映射              |
| mybatis动态语句 | Mybatis动态语句概念, where , if , foreach标签 |
| mybatis扩展     | Mapper批量处理,分页插件,逆向工程              |