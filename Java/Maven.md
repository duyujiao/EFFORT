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

### 2.依赖传递和冲突

**依赖传递**：导入依赖，会自动导入依赖的依赖！（compile dependenices)

简化依赖的导入 确保依赖的版本五冲突

**依赖冲突**：发现已经存在依赖（重复依赖）会终止依赖传递，避免循环依赖和重复依赖的问题

依赖冲突发生场景：重复依赖！

​	A -  B 1.0

​	C - B 2.0

A

C依赖传递B

依赖冲突的解决原则：

第一原则：谁短谁优先！引用的路径的长度

A-C -B 1.0

F-B 2.0

A C F B 2.0

第二原则：谁上谁优先！dependencies声明的先后顺序

A-B 1.0

F-B 2.0

A-F-B 1.0

练习：

前提：

A 1.1->B 1.1 ->C 1.1

F 2.2->B 2.2

pom声明：

F 2.2

A 1.1

B 2.2

请问最终拿到哪些依赖版本

F 2.2

A 1.1

B 2.2（最短）

注意：不会引入C 1.1 只要发生冲突，后续的依赖传递全部终止



  **依赖传递**指的是当一个模块或库 A 依赖于另一个模块或库 B，而 B 又依赖于模块或库 C，那么 A 会间接依赖于 C。这种依赖传递结构可以形成一个依赖树。当我们引入一个库或框架时，构建工具（如 Maven、Gradle）会自动解析和加载其所有的直接和间接依赖，确保这些依赖都可用。

  依赖传递的**作用**是：

  1. 减少重复依赖：当多个项目依赖同一个库时，Maven 可以自动下载并且只下载一次该库。这样可以减少项目的构建时间和磁盘空间。
  2. 自动管理依赖: Maven 可以自动管理依赖项，使用依赖传递，简化了依赖项的管理，使项目构建更加可靠和一致。
  3. 确保依赖版本正确性：通过依赖传递的依赖，之间都不会存在版本兼容性问题，确实依赖的版本正确性！

  依赖传递演示：

项目中，需要导入jackson相关的依赖，通过之前导入经验，jackson需要导入三个依赖，分别为：

![img](https://secure2.wostatic.cn/static/463a23mzkd1mo97Fm1rhpS/image.png?auth_key=1698306063-aBNrcfRChxChMqBpcc9Q5X-0-192117870f4d6fd2e084fbb1974d10a0&image_process=resize,w_750&file_size=183752&timestamp=1698306070111)

通过查看网站介绍的依赖传递特性：data-bind中，依赖其他两个依赖(只有Compile Dependencies)

![img](https://secure2.wostatic.cn/static/m8TKvDS5fj34z334a6jPxz/image.png?auth_key=1698306062-29GFTVgKmfHp49Uamf1zzQ-0-324e84a8c942633d9ac29ddaf49297b4&image_process=resize,w_1023&file_size=92298&timestamp=1698306070020)

最佳导入：直接可以导入data-bind，自动依赖传递需要的依赖

```XML
<!-- https://mvnrepository.com/artifact/com.fasterxml.jackson.core/jackson-databind -->
<dependency>
    <groupId>com.fasterxml.jackson.core</groupId>
    <artifactId>jackson-databind</artifactId>
    <version>2.15.0</version>
</dependency>
```

  依赖冲突演示：

  当直接引用或者间接引用出现了相同的jar包! 这时呢，一个项目就会出现相同的重复jar包，这就算作冲突！依赖冲突避免出现重复依赖，并且终止依赖传递！

  ![](https://secure2.wostatic.cn/static/4C2G8BJGLJ4pzmWoGs1Woi/image.png?auth_key=1698306062-9pZZimejXEuYKkEUbGCeUr-0-e7578c1cdf46a8c36480263378daca4a)

  maven自动解决依赖冲突问题能力，会按照自己的原则，进行重复依赖选择。同时也提供了手动解决的冲突的方式，不过不推荐！

  解决依赖冲突（如何选择重复依赖）方式：
    1. 自动选择原则
        - 短路优先原则（第一原则）

            A—>B—>C—>D—>E—>X(version 0.0.1)
    
            A—>F—>X(version 0.0.2)
    
            则A依赖于X(version 0.0.2)。
        - 依赖路径长度相同情况下，则“先声明优先”（第二原则）
    
            A—>E—>X(version 0.0.1)
    
            A—>F—>X(version 0.0.2)
    
            在<depencies></depencies>中，先声明的，路径相同，会优先选择！

### 3依赖导入失败场景和解决方案

  在使用 Maven 构建项目时，可能会发生依赖项下载错误的情况，主要原因有以下几种：

  1. 下载依赖时出现网络故障或仓库服务器宕机等原因，导致无法连接至 Maven 仓库，从而无法下载依赖。
  2. 依赖项的版本号或配置文件中的版本号错误，或者依赖项没有正确定义，导致 Maven 下载的依赖项与实际需要的不一致，从而引发错误。
  3. 本地 Maven 仓库或缓存被污染或损坏，导致 Maven 无法正确地使用现有的依赖项，并且也无法重新下载！

  解决方案：

  1. 检查网络连接和 Maven 仓库服务器状态。
  2. 确保依赖项的版本号与项目对应的版本号匹配，并检查 POM 文件中的依赖项是否正确。
  3. 清除本地 Maven 仓库缓存（lastUpdated 文件），因为只要存在lastupdated缓存文件，刷新也不会重新下载。本地仓库中，根据依赖的gav属性依次向下查找文件夹，最终删除内部的文件，刷新重新下载即可！

      例如： pom.xml依赖

```XML
<dependency>
  <groupId>com.alibaba</groupId>
  <artifactId>druid</artifactId>
  <version>1.2.8</version>
</dependency>
```

文件：

![img](https://secure2.wostatic.cn/static/6mSDgf4nkaRLAu16dqSJk7/image.png?auth_key=1698306064-dNsTwyUmPTY19cPXhpm4G7-0-ba015c96f3ca8059690a6a383e391e61&image_process=resize,w_1001&file_size=31454)

​      脚本使用：清理maven错误缓存.bat

脚本下载的文件所在位置：C:\Users\dyj\Downloads

```XML
使用记事本打开
set REPOSITORY_PATH=D:\repository  改成你本地仓库地址即可！
点击运行脚本，即可自动清理本地错误缓存文件！！
```



### 4.扩展构建管理和插件配置

**构建概念**：

项目构建是指将<font color=red>源代码，依赖库和资源文件等转换成可执行或可部署的应用程序</font>的过程,在这个过程中包括编译源代码，链接依赖库，打包和部署等多个步骤

清理--》编译--》测试--》报告--》打包--》部署

部署的目的是将开发完成的应用程序或系统交付给最终用户或客户，使其能够在目标环境中运行，并提供所需的功能和服务。部署通常涉及到配置服务器、安装依赖项、设置环境变量、启动应用程序等步骤，以确保应用程序能够顺利运行。

**主动触发场景**：

重新编译：编译不充分，部分文件没有被编译！

打包：独立部署到外部服务器软件，打包部署

部署本地或者私服仓库：maven工程加入到本地或者私服仓库，供其他工程使用

**命令方式构建**：

语法：mvn 构建命令 构建命令...

| 命令        | 描述                                        |
| ----------- | ------------------------------------------- |
| mvn clean   | 清理编译或打包后的项目结构,删除target文件夹 |
| mvn compile | 编译项目，生成target文件                    |
| mvn test    | 执行测试源码 (测试)                         |
| mvn site    | 生成一个项目依赖信息的展示页面              |
| mvn package | 打包项目，生成war / jar 文件                |
| mvn install | 打包后上传到maven本地仓库(本地部署)         |
| mvn deploy  | 只打包，上传到maven私服仓库(私服部署)       |

可视化方式构建：在idea的右边

**构建命令周期**：

构建生命周期可以理解成一组固定构建命令的有序集合，<font color=red>触发周期后的命令，会自动触发周期前的命令！</font>

- 清理周期：主要是对项目编译生成文件进行清理

    包含命令：clean
- 默认周期：定义了真正构件时所需要执行的所有步骤，它是生命周期中最核心的部分

    包含命令：compile - test - package - install / deploy
- 报告周期

    包含命令：site

    打包: mvn clean package 本地仓库: mvn clean install

**最佳使用方案**：

```纯文本
打包：mvn clean package
重新编译：mvn clean compile
本地部署:mvn clean install
```

**周期，命令和插件:**

周期→包含若干命令→包含若干插件!

使用周期命令构建，简化构建过程！

最终进行构建的是插件！

插件配置：

```xml
<build>
   <!-- jdk17 和 war包版本插件不匹配 -->
    <plugins>
        <plugin>
            <groupId>org.apache.maven.plugins</groupId>
            <artifactId>maven-war-plugin</artifactId>
            <version>3.2.2</version>
        </plugin>
    </plugins>
</build>
```

## Maven继承和聚合特性

### 1.Maven工程继承关系

**继承概念**：

Maven 继承是指在 Maven 的项目中，让一个项目从另一个项目中继承配置信息的机制。继承可以让我们在多个项目中共享同一配置信息，简化项目的管理和维护工作。

**继承作用：**

<font color=red>作用：在父工程中统一管理项目中的依赖信息，进行同一版本管理</font>

它的背景是：

- 对一个比较大型的项目进行了模块拆分。
- 一个 project 下面，创建了很多个 module。
- 每一个 module 都需要配置自己的依赖信息。

它背后的需求是：

- 多个模块要使用同一个框架，它们应该是同一个版本，所以整个项目中使用的框架版本需要统一管理。
- 使用框架时所需要的 jar 包组合（或者说依赖信息组合）需要经过长期摸索和反复调试，最终确定一个可用组合。这个耗费很大精力总结出来的方案不应该在新的项目中重新摸索。

通过在父工程中为整个项目维护依赖信息的组合既保证了整个项目使用规范、准确的 jar 包；又能够将以往的经验沉淀下来，节约时间和精力。

**继承语法：**

父工程

```xml
<groupId>com.atguigu.maven</groupId>
<artifactId>pro03-maven-parent</artifactId>
<version>1.0-SNAPSHOT</version>
<!-- 当前工程作为父工程，它要去管理子工程，所以打包方式必须是 pom -->
<packaging>pom</packaging>

```

子工程

```xml
<!-- 使用parent标签指定当前工程的父工程 -->
<parent>
  <!-- 父工程的坐标 -->
  <groupId>com.atguigu.maven</groupId>
  <artifactId>pro03-maven-parent</artifactId>
  <version>1.0-SNAPSHOT</version>
</parent>

<!-- 子工程的坐标 -->
<!-- 如果子工程坐标中的groupId和version与父工程一致，那么可以省略 -->
<!-- <groupId>com.atguigu.maven</groupId> -->
<artifactId>pro04-maven-module</artifactId>
<!-- <version>1.0-SNAPSHOT</version> -->
```

maven-pom-parent-02

pom.xml

```xml
<?xml version="1.0" encoding="UTF-8"?>
<project xmlns="http://maven.apache.org/POM/4.0.0"
         xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
         xsi:schemaLocation="http://maven.apache.org/POM/4.0.0 http://maven.apache.org/xsd/maven-4.0.0.xsd">
    <modelVersion>4.0.0</modelVersion>

    <groupId>org.example</groupId>
    <artifactId>maven-pom-parent-02</artifactId>
    <version>1.0-SNAPSHOT</version>
    <!-- 父工程不打包，也不写代码-->
    <packaging>pom</packaging>
    <modules>
        <module>shop-order</module>
    </modules>

    <!--声明版本信息-->
    <!--导入依赖！此处导入，所有子工程都有相应的依赖-->
    <dependencies></dependencies>
    <!--声明依赖，不会下载依赖！可以被子工程继承版本号-->
    <dependencyManagement>
        <dependencies>
            <dependency>
                <groupId>com.fasterxml.jackson.core</groupId>
                <artifactId>jackson-core</artifactId>
                <version>2.15.2</version>
            </dependency>
            <dependency>
                <groupId>mysql</groupId>
                <artifactId>mysql-connector-java</artifactId>
                <version>8.0.28</version>
            </dependency>
        </dependencies>
    </dependencyManagement>


</project>
```

shop-user

pom.xml

```xml
<?xml version="1.0" encoding="UTF-8"?>
<project xmlns="http://maven.apache.org/POM/4.0.0"
         xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
         xsi:schemaLocation="http://maven.apache.org/POM/4.0.0 http://maven.apache.org/xsd/maven-4.0.0.xsd">
    <modelVersion>4.0.0</modelVersion>
    <parent>
        <groupId>org.example</groupId>
        <artifactId>maven-pom-parent-02</artifactId>
        <version>1.0-SNAPSHOT</version>
    </parent>

    <artifactId>shop-order</artifactId>

    <dependencies>
        <dependency>
            <groupId>com.fasterxml.jackson.core</groupId>
            <artifactId>jackson-core</artifactId>
        </dependency>
    </dependencies>




</project>
```

**父工程依赖统一管理**

父工程声明版本

```xml
<!-- 使用dependencyManagement标签配置对依赖的管理 -->
<!-- 被管理的依赖并没有真正被引入到工程 -->
<dependencyManagement>
  <dependencies>
    <dependency>
      <groupId>org.springframework</groupId>
      <artifactId>spring-core</artifactId>
      <version>4.0.0.RELEASE</version>
    </dependency>
    <dependency>
      <groupId>org.springframework</groupId>
      <artifactId>spring-beans</artifactId>
      <version>4.0.0.RELEASE</version>
    </dependency>
    <dependency>
      <groupId>org.springframework</groupId>
      <artifactId>spring-context</artifactId>
      <version>4.0.0.RELEASE</version>
    </dependency>
    <dependency>
      <groupId>org.springframework</groupId>
      <artifactId>spring-expression</artifactId>
      <version>4.0.0.RELEASE</version>
    </dependency>
    <dependency>
      <groupId>org.springframework</groupId>
      <artifactId>spring-aop</artifactId>
      <version>4.0.0.RELEASE</version>
    </dependency>
  </dependencies>
</dependencyManagement>
```

子工程引用版本

```xml
<!-- 子工程引用父工程中的依赖信息时，可以把版本号去掉。  -->
<!-- 把版本号去掉就表示子工程中这个依赖的版本由父工程决定。 -->
<!-- 具体来说是由父工程的dependencyManagement来决定。 -->
<dependencies>
  <dependency>
    <groupId>org.springframework</groupId>
    <artifactId>spring-core</artifactId>
  </dependency>
  <dependency>
    <groupId>org.springframework</groupId>
    <artifactId>spring-beans</artifactId>
  </dependency>
  <dependency>
    <groupId>org.springframework</groupId>
    <artifactId>spring-context</artifactId>
  </dependency>
  <dependency>
    <groupId>org.springframework</groupId>
    <artifactId>spring-expression</artifactId>
  </dependency>
  <dependency>
    <groupId>org.springframework</groupId>
    <artifactId>spring-aop</artifactId>
  </dependency>
</dependencies>
```

### 2.Maven工程聚合关系

1. 聚合概念

    Maven 聚合是指将多个项目组织到一个父级项目中，通过触发父工程的构建,统一按顺序触发子工程构建的过程!!
2. 聚合作用
    1. 统一管理子项目构建：通过聚合，可以将多个子项目组织在一起，方便管理和维护。
    2. 优化构建顺序：通过聚合，可以对多个项目进行顺序控制，避免出现构建依赖混乱导致构建失败的情况。
3. 聚合语法

    父项目中包含的子项目列表。

```XML
<project>
  <groupId>com.example</groupId>
  <artifactId>parent-project</artifactId>
  <packaging>pom</packaging>
  <version>1.0.0</version>
        <!--要统一管理哪些子工程的artifactId-->
  <modules>
    <module>child-project1</module>
    <module>child-project2</module>
  </modules>
</project>
```
4. 聚合演示

    通过触发父工程构建命令、引发所有子模块构建！产生反应堆！

    ![](https://secure2.wostatic.cn/static/weyQ7odFa3amf3NTtCgyjQ/image.png?auth_key=1698323078-rBXBe3y9b5BKk55CPgzeuw-0-7da560e74f008e2d0ef2273429a018d0)

## Maven实战案例：搭建微服务Maven工程架构

### 1.项目需求和结构分析

![](https://secure2.wostatic.cn/static/55JDMJtqJgk1V39q31237Q/image.png?auth_key=1698323859-hBTegC1yuQ3Y1oLV4bSxSs-0-eac5a7027355b2da0284190676300ce1)

需求案例：搭建一个电商平台项目，该平台包括用户服务、订单服务、通用工具模块等。

项目架构：

1. 用户服务：负责处理用户相关的逻辑，例如用户信息的管理、用户注册、登录等。
2. 订单服务：负责处理订单相关的逻辑，例如订单的创建、订单支付、退货、订单查看等。
3. 通用模块：负责存储其他服务需要通用工具类，其他服务依赖此模块。

服务依赖：

1. 用户服务 (1.0.1)
    - spring-context 6.0.6 
    - spring-core 6.0.6
    - spring-beans 6.0.6
    - jackson-databind /  jackson-core / jackson-annotations 2.15.0 
2. 订单服务 (1.0.1)
    1. shiro-core 1.10.1 
    2. spring-context 6.0.6 
    3. spring-core 6.0.6
    4. spring-beans 6.0.6
3. 通用模块 (1.0.1)
    1. commons-io 2.11.0

### 2.项目搭建和统一管理

![image-20231026213712334](C:\Users\dyj\AppData\Roaming\Typora\typora-user-images\image-20231026213712334.png)

1. 父模块搭建 (micro-shop)
    1. 创建父工程

        ![](https://secure2.wostatic.cn/static/q4ub49tpGULm7q2tLaTu1J/image.png?auth_key=1698325009-oHRwkWVxoobTMKwAkYdKQL-0-362d1fab5616b83ce95776d1d4d0e048)
    2. pom.xml配置

```XML
<?xml version="1.0" encoding="UTF-8"?>
<project xmlns="http://maven.apache.org/POM/4.0.0"
         xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
         xsi:schemaLocation="http://maven.apache.org/POM/4.0.0 http://maven.apache.org/xsd/maven-4.0.0.xsd">
    <modelVersion>4.0.0</modelVersion>

    <groupId>com.atguigu</groupId>
    <artifactId>micro-shop</artifactId>
    <version>1.0.1</version>
    <!-- 父工程不打包，所以选择pom值-->
    <packaging>pom</packaging>

    <properties>
        <spring.version>6.0.6</spring.version>
        <jackson.version>2.15.0</jackson.version>
        <shiro.version>1.10.1</shiro.version>
        <commons.version>2.11.0</commons.version>
        <maven.compiler.source>17</maven.compiler.source>
        <maven.compiler.target>17</maven.compiler.target>
        <project.build.sourceEncoding>UTF-8</project.build.sourceEncoding>
    </properties>

    <!-- 依赖管理 -->
    <dependencyManagement>
        <dependencies>
            <!-- spring-context会依赖传递core/beans -->
            <dependency>
                <groupId>org.springframework</groupId>
                <artifactId>spring-context</artifactId>
                <version>${spring.version}</version>
            </dependency>

            <!-- jackson-databind会依赖传递core/annotations -->
            <dependency>
                <groupId>com.fasterxml.jackson.core</groupId>
                <artifactId>jackson-databind</artifactId>
                <version>${jackson.version}</version>
            </dependency>

            <!-- shiro-core -->
            <dependency>
                <groupId>org.apache.shiro</groupId>
                <artifactId>shiro-core</artifactId>
                <version>${shiro.version}</version>
            </dependency>
            <!-- commons-io -->
            <dependency>
                <groupId>commons-io</groupId>
                <artifactId>commons-io</artifactId>
                <version>${commons.version}</version>
            </dependency>
            
            
            
              <!--把这个粘贴到父工程里，可以在父工程中管理版本-->
            <!--自己的工程-->
            <dependency>
                <groupId>org.example</groupId>
                <artifactId>common-service</artifactId>
                <version>1.0.1</version>
            </dependency>
            
            

        </dependencies>

    </dependencyManagement>

    <dependencies>
        <!-- 父工程添加依赖，会自动传递给所有子工程，不推荐！ -->
    </dependencies>

    <!-- 统一更新子工程打包插件-->
    <build>
        <!-- jdk17 和 war包版本插件不匹配 -->
        <plugins>
            <plugin>
                <groupId>org.apache.maven.plugins</groupId>
                <artifactId>maven-war-plugin</artifactId>
                <version>3.2.2</version>
            </plugin>
        </plugins>
    </build>

</project>
```
2. 通用模块 (common-service)
    1. 创建模块

        ![](https://secure2.wostatic.cn/static/s29BZ1jzoRgncf5dY8Zecx/image.png?auth_key=1698325009-2SP5igY1tqBFiBGEEFs4jJ-0-b0bf7cb312a5a3c3dfc37541c388f09e)

        ![](https://secure2.wostatic.cn/static/uJF4JRuQqi7GxHtSPEq8Mi/image.png?auth_key=1698325009-oMVc9jM4ZkRKPvjQ6yC5KA-0-cb99e43f11f51a5139abbb154679e536)
    2. pom.xml配置

```XML
<?xml version="1.0" encoding="UTF-8"?>
<project xmlns="http://maven.apache.org/POM/4.0.0"
         xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
         xsi:schemaLocation="http://maven.apache.org/POM/4.0.0 http://maven.apache.org/xsd/maven-4.0.0.xsd">
    <modelVersion>4.0.0</modelVersion>
    <parent>
        <groupId>com.atguigu</groupId>
        <artifactId>micro-shop</artifactId>
        <version>1.0.1</version>
    </parent>
    <artifactId>common-service</artifactId>
    <!-- 打包方式默认就是jar！ -->
    <packaging>jar</packaging>

    <properties>
        <maven.compiler.source>17</maven.compiler.source>
        <maven.compiler.target>17</maven.compiler.target>
        <project.build.sourceEncoding>UTF-8</project.build.sourceEncoding>
    </properties>

    <dependencies>
        <!-- 声明commons-io，继承父工程版本 -->
        <dependency>
            <groupId>commons-io</groupId>
            <artifactId>commons-io</artifactId>
        </dependency>
    </dependencies>

</project>
```
3. 用户模块 (user-service)
    1. 创建模块

        ![](https://secure2.wostatic.cn/static/feDvXd6JWZWLf3MiP1GbQC/image.png?auth_key=1698325009-dEpF8jcTCahoq6ooZzuX8U-0-031d1aad8351d7c29cd549892dd461a4)

        ![](https://secure2.wostatic.cn/static/qxywuU1jKc2rpyn68nGtfU/image.png?auth_key=1698325009-u8f8o7sFXE5PSmLeww6bfS-0-dbbc53b4edc4727b6888cc298a524fa6)
    2. pom.xml配置

```XML
<?xml version="1.0" encoding="UTF-8"?>

<project xmlns="http://maven.apache.org/POM/4.0.0" xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance" xsi:schemaLocation="http://maven.apache.org/POM/4.0.0 http://maven.apache.org/xsd/maven-4.0.0.xsd">  
  <modelVersion>4.0.0</modelVersion>  
  <parent> 
    <groupId>com.atguigu</groupId>  
    <artifactId>micro-shop</artifactId>  
    <version>1.0.1</version> 
  </parent>  
  <artifactId>user-service</artifactId>  
  <packaging>war</packaging>

  <properties> 
    <maven.compiler.source>17</maven.compiler.source>  
    <maven.compiler.target>17</maven.compiler.target>  
    <project.build.sourceEncoding>UTF-8</project.build.sourceEncoding> 
  </properties>

  <dependencies>
    <!-- 添加spring-context 自动传递 core / beans -->
    <dependency>
      <groupId>org.springframework</groupId>
      <artifactId>spring-context</artifactId>
    </dependency>

    <!-- 添加jackson-databind 自动传递 core / annotations -->
    <dependency>
      <groupId>com.fasterxml.jackson.core</groupId>
      <artifactId>jackson-databind</artifactId>
    </dependency>
      
      <!--自己的工程-->
    <dependency>
      <groupId>org.example</groupId>
      <artifactId>common-service</artifactId>
    </dependency>
      
  </dependencies>
</project>

```
4. 订单模块 (order-service)
    1. 创建模块

        ![](https://secure2.wostatic.cn/static/gRxngf1p153nByr6Fpp46T/image.png?auth_key=1698325009-mkWfn6VMSDc7DWFQ2pfcRo-0-8aac30bb4b9f82f53e506b3a947a0179)

        ![](https://secure2.wostatic.cn/static/qxywuU1jKc2rpyn68nGtfU/image.png?auth_key=1698325009-riG6UG2rVxE52aMzQAdKeT-0-3797971a140086f95339ba4980e8d8a0)
    2. pom.xml

```XML
<?xml version="1.0" encoding="UTF-8"?>
<project xmlns="http://maven.apache.org/POM/4.0.0"
         xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
         xsi:schemaLocation="http://maven.apache.org/POM/4.0.0 http://maven.apache.org/xsd/maven-4.0.0.xsd">
    <modelVersion>4.0.0</modelVersion>
    <parent>
        <groupId>com.atguigu</groupId>
        <artifactId>micro-shop</artifactId>
        <version>1.0.1</version>
    </parent>

    <artifactId>order-service</artifactId>
    <packaging>war</packaging>

    <properties>
        <maven.compiler.source>17</maven.compiler.source>
        <maven.compiler.target>17</maven.compiler.target>
        <project.build.sourceEncoding>UTF-8</project.build.sourceEncoding>
    </properties>

    <dependencies>
        <!-- 继承父工程依赖版本 -->
        <dependency>
            <groupId>org.springframework</groupId>
            <artifactId>spring-context</artifactId>
        </dependency>

        <!-- 继承父工程依赖版本 -->
        <dependency>
            <groupId>org.apache.shiro</groupId>
            <artifactId>shiro-core</artifactId>
        </dependency>
        
        
        <!--自己的工程-->
    <dependency>
      <groupId>org.example</groupId>
      <artifactId>common-service</artifactId>
    </dependency>
        
        
    </dependencies>

</project>
```

