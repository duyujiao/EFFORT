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