## 基于IDEA的Maven工程的创建

### 1.梳理Maven工程GAVP属性

> Maven工程相对之前的工程，多出一组gavp属性，gav需要我们在创建项目的时指定，p有默认值，后期通过配置文件修改。既然要填写的属性，我们先行了解下这组属性的含义!

Maven 中的 GAVP 是指 GroupId、ArtifactId、Version、Packaging 等四个属性的缩写，其中前三个是必要的，而 Packaging 属性为可选项。这四个属性主要为每个项目在maven仓库总做一个标识，类似人的《姓-名》。有了具体标识，方便maven软件对项目进行管理和互相引用！

**GAV遵循一下规则：**

  1） **GroupID 格式**：com.{公司/BU }.业务线.[子业务线]，最多 4 级。

    说明：{公司/BU} 例如：alibaba/taobao/tmall/aliexpress 等 BU 一级；子业务线可选。
    
    正例：com.taobao.tddl 或 com.alibaba.sourcing.multilang  com.atguigu.java

  2） **ArtifactID 格式**：产品线名-模块名。语义不重复不遗漏，先到仓库中心去查证一下。

    正例：tc-client / uic-api / tair-tool / bookstore

  3） **Version版本号格式推荐**：主版本号.次版本号.修订号 1.0.0

    1） 主版本号：当做了不兼容的 API 修改，或者增加了能改变产品方向的新功能。
    
    2） 次版本号：当做了向下兼容的功能性新增（新增类、接口等）。
    
    3） 修订号：修复 bug，没有修改方法签名的功能加强，保持 API 兼容性。
    
    例如： 初始→1.0.0  修改bug → 1.0.1  功能调整 → 1.1.1等

**Packaging定义规则：**

  指示将项目打包为什么类型的文件，idea根据packaging值，识别maven项目类型！

  packaging 属性为 jar（默认值），代表普通的Java工程，打包以后是.jar结尾的文件。

  packaging 属性为 war，代表Java的web工程，打包以后.war结尾的文件。

  packaging 属性为 pom，代表不会打包，用来做继承的父工程。

### 2.Idea构建Maven JavaSE工程

![img](https://secure2.wostatic.cn/static/oDo2HDrVXHoKqfqRdqLKuV/image.png?auth_key=1698152692-2Wak1oNEB3A99rWmcB5TYq-0-b014caaec455afe1b73a58b859b66e05&image_process=resize,w_501&file_size=54036)

### 3.Idea构建Maven JavaEE工程

1.手动创建

a.创建一个javasemaven工程

b.手动添加web项目结构文件

注意：结构和命名固定

![](https://secure2.wostatic.cn/static/2iYsG44sjYayNqY7t9WtrZ/image.png?auth_key=1698152764-r12Tp7wsYzNibJRfUtAnmq-0-2a81207438ce5652ac41036aaab95d1b)

c.修改pom.xml文件打包方式

修改位置：项目下/pom.xml

```XML
<groupId>com.atguigu</groupId>
<artifactId>maven_parent</artifactId>
<version>1.0-SNAPSHOT</version>
<!-- 新增一列打包方式packaging -->
<packaging>war</packaging>
```

d.刷新和校验

![img](https://secure2.wostatic.cn/static/CEhMC5eswYp2GhyYQwnry/image.png?auth_key=1698152764-3J7JcwegGMQVhpPR2r7kBZ-0-006c2759cfb33e117d33604f713d5c17&image_process=resize,w_401&file_size=29714)

![img](https://secure2.wostatic.cn/static/haCWoNhTmZaQEzd3T8GmRu/image.png?auth_key=1698152764-sCswEnUmETKMiftYZKddS7-0-dd18ed09efdb893d0b2d22623ab86155&image_process=resize,w_172&file_size=1208)

项目中webapp文件夹出现小蓝点，代表成功！

2.插件方式创建

a.安装插件JBLJAVAToWeb

file-setting-plugins-marketplace

![img](https://secure2.wostatic.cn/static/dfWTRgLdpDLHj7triTW9nM/image.png?auth_key=1698152764-u46yiUgt39ovBeQd2jVxps-0-c6cb9796bdb9c8614620d03aa4a5707d&image_process=resize,w_508&file_size=85118)

b.创建一个javasemaven工程

c.右键，使用插件快速补全web项目

![img](https://secure2.wostatic.cn/static/vdNw6jnGT7r7CXUji3j7ah/image.png?auth_key=1698152764-raaaMrNDS1GXhhtGHArutS-0-5559fd72e84eb3fcea57148d5a57072a&image_process=resize,w_507&file_size=53861)

### 4.Maven工程项目架构说明

Maven 是一个强大的构建工具，它提供一种标准化的项目结构，可以帮助开发者更容易地管理项目的依赖、构建、测试和发布等任务。以下是 Maven Web 程序的文件结构及每个文件的作用：

```XML
|-- pom.xml                               # Maven 项目管理文件 
|-- src
    |-- main                              # 项目主要代码
    |   |-- java                          # Java 源代码目录
    |   |   `-- com/example/myapp         # 开发者代码主目录
    |   |       |-- controller            # 存放 Controller 层代码的目录
    |   |       |-- service               # 存放 Service 层代码的目录
    |   |       |-- dao                   # 存放 DAO 层代码的目录
    |   |       `-- model                 # 存放数据模型的目录
    |   |-- resources                     # 资源目录，存放配置文件、静态资源等
    |   |   |-- log4j.properties          # 日志配置文件
    |   |   |-- spring-mybatis.xml        # Spring Mybatis 配置文件
    |   |   `-- static                    # 存放静态资源的目录
    |   |       |-- css                   # 存放 CSS 文件的目录
    |   |       |-- js                    # 存放 JavaScript 文件的目录
    |   |       `-- images                # 存放图片资源的目录
    |   `-- webapp                        # 存放 WEB 相关配置和资源
    |       |-- WEB-INF                   # 存放 WEB 应用配置文件
    |       |   |-- web.xml               # Web 应用的部署描述文件
    |       |   `-- classes               # 存放编译后的 class 文件
    |       `-- index.html                # Web 应用入口页面
    `-- test                              # 项目测试代码
        |-- java                          # 单元测试目录
        `-- resources                     # 测试资源目录
```

- pom.xml：Maven 项目管理文件，用于描述项目的依赖和构建配置等信息。
- src/main/java：存放项目的 Java 源代码。
- src/main/resources：存放项目的资源文件，如配置文件、静态资源等。
- src/main/webapp/WEB-INF：存放 Web 应用的配置文件。
- src/main/webapp/index.html：Web 应用的入口页面。
- src/test/java：存放项目的测试代码。
- src/test/resources：存放测试相关的资源文件，如测试配置文件等。

## Maven核心功能依赖和构建管理

### 1.依赖管理和配置

Maven 依赖管理是 Maven 软件中最重要的功能之一。Maven 的依赖管理能够帮助开发人员自动解决软件包依赖问题，使得开发人员能够轻松地将其他开发人员开发的模块或第三方框架集成到自己的应用程序或模块中，避免出现版本冲突和依赖缺失等问题。

我们通过定义 POM 文件，Maven 能够自动解析项目的依赖关系，并通过 Maven **仓库自动**下载和管理依赖，从而避免了手动下载和管理依赖的繁琐工作和可能引发的版本冲突问题。

<font color=red>重点: 编写pom.xml文件!</font>

maven项目信息属性配置和读取

```xml
<!-- 模型版本 -->
<modelVersion>4.0.0</modelVersion>
<!-- 公司或者组织的唯一标志，并且配置时生成的路径也是由此生成， 如com.companyname.project-group，maven会将该项目打成的jar包放本地路径：/com/companyname/project-group -->
<groupId>com.companyname.project-group</groupId>
<!-- 项目的唯一ID，一个groupId下面可能多个项目，就是靠artifactId来区分的 -->
<artifactId>project</artifactId>
<!-- 版本号 -->
<version>1.0.0</version>

<!--打包方式
    默认：jar
    jar指的是普通的java项目打包方式！ 项目打成jar包！
    war指的是web项目打包方式！项目打成war包！
    pom不会讲项目打包！这个项目作为父工程，被其他工程聚合或者继承！后面会讲解两个概念
-->
<packaging>jar/pom/war</packaging>
```

依赖管理和添加

```xml
<!-- 
   通过编写依赖jar包的gav必要属性，引入第三方依赖！
   scope属性是可选的，可以指定依赖生效范围！
   依赖信息查询方式：
      1. maven仓库信息官网 https://mvnrepository.com/
      2. mavensearch插件搜索
 -->
<dependencies>
    <!-- 引入具体的依赖包 -->
    <dependency>
        <groupId>log4j</groupId>
        <artifactId>log4j</artifactId>
        <version>1.2.17</version>
        <!--
            生效范围
            - compile ：main目录 test目录  打包打包 [默认]
            - provided：main目录 test目录  Servlet
            - runtime： 打包运行           MySQL
            - test:    test目录           junit
         -->
        <scope>runtime</scope>
    </dependency>

</dependencies>
```

以来版本提取和维护

```xml
<!--声明版本-->
<properties>
  <!--命名随便,内部制定版本号即可！-->
  <junit.version>4.11</junit.version>
  <!-- 也可以通过 maven规定的固定的key，配置maven的参数！如下配置编码格式！-->
  <project.build.sourceEncoding>UTF-8</project.build.sourceEncoding>
  <project.reporting.outputEncoding>UTF-8</project.reporting.outputEncoding>
</properties>

<dependencies>
  <dependency>
    <groupId>junit</groupId>
    <artifactId>junit</artifactId>
    <!--引用properties声明版本 -->
    <version>${junit.version}</version>
  </dependency>
</dependencies>
```

pom.xml

```xml
<?xml version="1.0" encoding="UTF-8"?>
<project xmlns="http://maven.apache.org/POM/4.0.0"
         xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
         xsi:schemaLocation="http://maven.apache.org/POM/4.0.0 http://maven.apache.org/xsd/maven-4.0.0.xsd">
    <modelVersion>4.0.0</modelVersion>

    <groupId>org.example</groupId>
    <artifactId>maven-javase-project-01</artifactId>
    <version>1.0-SNAPSHOT</version>


    <!--声明版本-->
    <properties>
        <!--声明一个变量！声明完变量以后，在其他位置可以引用${junit.version}
        注意：声明的标签建议两层以上命名！ version 4.11 推荐：技术名：version
        -->

        <!--命名随便,内部制定版本号即可！-->
        <junit.version>4.13.1</junit.version>
        <!-- 也可以通过 maven规定的固定的key，配置maven的参数！如下配置编码格式！-->
        <project.build.sourceEncoding>UTF-8</project.build.sourceEncoding>
        <project.reporting.outputEncoding>UTF-8</project.reporting.outputEncoding>
    </properties>

    <!--第三方依赖信息说明
        dependencise-项目依赖信息的集合
        dependency-每个依赖项
        gav- 依赖的信息，就是其他maven的工程[jar]

        第三方依赖信息怎么知道？
        依赖信息查询方式：
      1. maven仓库信息官网 https://mvnrepository.com/
      2. mavensearch插件搜索

      扩展：
      1.提取版本号，统一管理
      2.可选属性scope
        scope引入依赖的作用域
        默认：compile main test 打包和运行

            生效范围
            - compile ：main目录 test目录                  打包和运行 [默认]
            - provided：main目录 test目录                     Servlet
            - runtime： 打包运行 main不会有 test 不会用          MySQL
            - test:    test目录                               junit
    总结:他是一种锦上添花的手段，如果你掌握不好，那你就默认值，全部生效，你就一定不会错！

    -->

    <dependencies>
        <dependency>
            <groupId>junit</groupId>
            <artifactId>junit</artifactId>
            <!--引用properties声明版本 -->
            <version>${junit.version}</version>
            <!--只能在test里用-->
            <scope>test</scope>
        </dependency>
    </dependencies>



</project>
```

