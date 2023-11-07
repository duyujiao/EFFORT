## 一、技术体系结构

### 1.总体技术体系

**单一架构**：

一个项目，一个工程，导出为一个war包，在一个Tomcat上运行。也叫all in one

![img](https://secure2.wostatic.cn/static/bnm9zUQo34z7FgXA9vAmfm/image.png?auth_key=1698385357-cNtT8VuLBziaipxWSxYgHG-0-90583fdaefba4737177181db4540f3d2&image_process=resize,w_1195&file_size=85984)

单一架构，项目主要应用技术框架：Spring,SpringMVC,Mybatis

**分布式架构**：

一个项目（对应IDEA中的一个project),拆分成很多个模块，每个模块是一个IDEA中的一个module。每个工程都是运行在自己的Tomat上，模块之间可以互相调用。每个模块内部 可以看成是一个单一架构的应用。

![img](https://secure2.wostatic.cn/static/9NxDdZATsg76FfXNgskTFE/image.png?auth_key=1698385357-ehjRawzqoHsgKm89itVWD4-0-57804e9c5650d0b645c13e631a3a2d00&image_process=resize,w_1195&file_size=55677)

分布式架构，项目主要应用技术框架：SpringBoot(SSM),SpringCloud,中间件等

### 2.框架概念和理解

框架( Framework )是一个集成了基本结构、规范、设计模式、编程语言和程序库等基础组件的软件系统，它可以用来构建更高级别的应用程序。框架的设计和实现旨在解决特定领域中的常见问题，帮助开发人员更高效、更稳定地实现软件开发目标。

框架的**优点**包括以下几点：

1. **提高开发效率**：框架提供了许多预先设计好了的组件和工具，能够帮助开发人员快速进行开发。相较于传统手写代码，在框架提供的规范化环境中，开发者可以更快地实现项目的各种要求。
2. **降低开发成本**：框架的提供标准化的编程语言、数据操作等代码片段，避免了重复开发的问题，降低了开发成本，提供深度优化的系统，降低了维护成本，增强了系统的可靠性。
3. **提高应用程序的稳定性**：框架通常经过了很长时间的开发和测试，其中的许多组件、代码片段和设计模式都得到了验证。重复利用这些组件有助于减少bug的出现，从而提高了应用程序的稳定性。
4. **提供标准化的解决方案**：框架通常是针对某个特定领域的，通过提供标准化的解决方案，可以为开发人员提供一种共同的语言和思想基础，有助于更好地沟通和协作。

框架的**缺点**包括以下几个方面：

1. **学习成本高**：框架通常具有特定的语言和编程范式。对于开发人员而言，需要花费时间学习其背后的架构、模式和逻辑，这对于新手而言可能会耗费较长时间。

2. **可能存在局限性**：虽然框架提高了开发效率并可以帮助开发人员解决常见问题，但是在某些情况下，特定的应用需求可能超出框架的范围，从而导致应用程序无法满足要求。开发人员可能需要更多的控制权和自由度，同时需要在框架和应用程序之间进行权衡取舍。

3. **版本变更和兼容性问题**：框架的版本发布和迭代通常会导致代码库的大规模变更，进而导致应用程序出现兼容性问题和漏洞。当框架变更时，需要考虑框架是否向下兼容，以及如何进行适当的测试、迁移和升级。

4. **架构风险**：框架涉及到很多抽象和概念，如果开发者没有足够的理解和掌握其架构，可能会导致系统出现设计和架构缺陷，从而影响系统的健康性和安全性。

   

站在文件架构的角度理解框架，可以将框架总结：<font color=red>框架=jar包+配置文件</font>

![img](https://secure2.wostatic.cn/static/mVVMygbUkcQx9Loxs21XdC/image.png?auth_key=1698385894-ecwkXp8PoPmDZtKRwNoYhK-0-ff9a44fcec91001f1004067c654ad533&image_process=resize,w_1275&file_size=69925)

采用一种框架其实就是限制用户必须使用其规定的方案来实现，可以降低程序员之间沟通以及日后维护的成本！

常用的单一架构JavaEE项目框架演进，从SSH、SSH2过渡到了SSM：SpringMVC、Spring、MyBatis。

总之，框架已经对基础的代码进行了封装并提供相应的API，开发者在使用框架是直接调用封装好的API可以省去很多代码编写，从而提高工作效率和开发速度。

## 二、SpringFramework介绍

### 1.Spring和SpringFramework概念

**<font color=yellow>广义的Spring:Spring 技术栈</font>**（全家桶）

广义上的 Spring 泛指以 Spring Framework 为基础的 Spring 技术栈。

经过十多年的发展，Spring 已经不再是一个单纯的应用框架，而是逐渐发展成为一个由多个不同子项目（模块）组成的成熟技术，例如 Spring Framework、Spring MVC、SpringBoot、Spring Cloud、Spring Data、Spring Security 等，其中 Spring Framework 是其他子项目的基础。

这些子项目涵盖了从企业级应用开发到云计算等各方面的内容，能够帮助开发人员解决软件发展过程中不断产生的各种实际问题，给开发人员带来了更好的开发体验。

**<font color=yellow>狭义的Spring:Spring Framework</font>**(基础框架)

狭义的 Spring 特指 Spring Framework，通常我们将它称为 Spring 框架。

Spring Framework（Spring框架）是一个开源的应用程序框架，由SpringSource公司开发，最初是为了解决企业级开发中各种常见问题而创建的。它提供了很多功能，例如：依赖注入（Dependency Injection）、面向切面编程（AOP）、声明式事务管理（TX）等。其主要目标是使企业级应用程序的开发变得更加简单和快速，并且Spring框架被广泛应用于Java企业开发领域。

Spring全家桶的其他框架都是以SpringFramework框架为基础！

**对比理解：**

QQ 和 腾讯(腾讯最终发展了很多游戏，视频，音乐等等)

腾讯 = Spring

QQ = SpringFramework

### 2.SpringFramework主要功能模块

SpringFramework框架结构图：

![img](https://secure-bigfile.wostatic.cn/static/5D6E8yWCFE2pUa3koBp4ra/image.png?auth_key=1698386516-coSvQr1GPmXGYxeFuqEhWA-0-f82fc7db3fc542f973197c913c1796a0&image_process=resize,w_1271&file_size=8793951)



| 功能模块       | 功能介绍                                                    |
| -------------- | ----------------------------------------------------------- |
| Core Container | 核心容器，在 Spring 环境下使用任何功能都必须基于 IOC 容器。 |
| AOP&Aspects    | 面向切面编程                                                |
| TX             | 声明式事务管理。                                            |
| Spring MVC     | 提供了面向Web应用程序的集成功能。                           |

### 3.SpringFramework主要优势

1. 丰富的生态系统：Spring 生态系统非常丰富，支持许多模块和库，如 Spring Boot、Spring Security、Spring Cloud 等等，可以帮助开发人员快速构建高可靠性的企业应用程序。
2. 模块化的设计：框架组件之间的松散耦合和模块化设计使得 Spring Framework 具有良好的可重用性、可扩展性和可维护性。开发人员可以轻松地选择自己需要的模块，根据自己的需求进行开发。
3. 简化 Java 开发：Spring Framework 简化了 Java 开发，提供了各种工具和 API，可以降低开发复杂度和学习成本。同时，Spring Framework 支持各种应用场景，包括 Web 应用程序、RESTful API、消息传递、批处理等等。
4. 不断创新和发展：Spring Framework 开发团队一直在不断创新和发展，保持与最新技术的接轨，为开发人员提供更加先进和优秀的工具和框架。

因此，这些优点使得 Spring Framework 成为了一个稳定、可靠、且创新的框架，为企业级 Java 开发提供了一站式的解决方案。

Spring 使创建 Java 企业应用程序变得容易。它提供了在企业环境中采用 Java 语言所需的一切，支持 Groovy 和 Kotlin 作为 JVM 上的替代语言，并且可以根据应用程序的需求灵活地创建多种架构。**从Spring Framework 6.0.6开始，Spring 需要 Java 17+。**

## 三、Spring IoC容器和核心概念

### 1.组件和组件管理概念

#### 1.1什么是组件？

回顾常规的三层架构处理请求流程：

![img](https://secure2.wostatic.cn/static/i5cYp4uqLG3mVEKEv2qofF/image.png?auth_key=1698385357-9BnZfBnCk5Lmi269ESuu5S-0-3629dfb28bbb1e77be51ebc0c70d78db&image_process=resize,w_1199&file_size=19814)

整个项目就是由各种组件搭建而成的：

![img](https://secure2.wostatic.cn/static/8LSuy5YWXmufYmPWM894rN/image.png?auth_key=1698385357-qnHXTdx9pmDnhaYc8DB37M-0-ffe2e53f53a42091cf1745a2c8357ab2&image_process=resize,w_1199&file_size=31162)

#### 1.2我们的期待

- 有人替我们创建组件的对象
- 有人帮我们保存组件的对象
- 有人帮助我们自动组装
- 有人替我们管理事务
- 有人协助我们整合其他框架
- ......

#### 1.3Spring充当组件管理角色(Ioc)

那么谁帮我们完成我们的期待，帮我们管理组件呢？

当然是Spring 框架了！

组件可以完全交给Spring 框架进行管理，Spring框架替代了程序员原有的new对象和对象属性赋值动作等！

Spring具体的组件管理动作包含：

- 组件对象实例化
- 组件属性属性赋值
- 组件对象之间引用
- 组件对象存活周期管理
- ......

我们只需要编写元数据（配置文件）告知Spring 管理哪些类组件和他们的关系即可！

注意：<font color=red>组件</font>是映射到应用程序中所有可重用组件的Java对象，应该是<font color=red>可复用的</font>功能组件

<font color=red>组件一定是对象，对象不一定是组件</font>

综上所述，Spring 充当一个组件容器，创建、管理、存储组件，减少了我们的编码压力，让我们更加专注进行业务编写！

#### 1.4组件交给Spring管理优势

1. 降低了组件之间的耦合性：Spring IoC容器通过依赖注入机制，将组件之间的依赖关系削弱，减少了程序组件之间的耦合性，使得组件更加松散地耦合。
2. 提高了代码的可重用性和可维护性：将组件的实例化过程、依赖关系的管理等功能交给Spring IoC容器处理，使得组件代码更加模块化、可重用、更易于维护。
3. 方便了配置和管理：Spring IoC容器通过XML文件或者注解，轻松的对组件进行配置和管理，使得组件的切换、替换等操作更加的方便和快捷。
4. 交给Spring管理的对象（组件），方可享受Spring框架的其他功能（AOP,声明事务管理）等

### 2.Spring Ioc容器和容器实现

#### 2.1普通容器和复杂容器

**普通容器**：

生活中的普通容器：水杯，> 普通容器只能用来存储，没有更多功能。

程序中的普通容器：数组，集合List,集合Set

**复杂容器：**

生活中的复杂容器：政府管理我们的一生，生老病死都和政府有关。![img](https://api.wolai.com/v1/proxy/image?src=http%3A%2F%2Fheavy_code_industry.gitee.io%2Fcode_heavy_industry%2Fassets%2Fimg%2Fimg003.6f9c041c.png&spaceId=fqkGyHKKxSnzkhVZnoSxhC&userId=&image_process=resize,w_944)

程序中的复杂容器：Servlet 容器，能够管理 Servlet(init,service,destroy)、Filter、Listener 这样的组件的一生，所以它是一个复杂容器。

| 名称       | 时机                                                         | 次数 |
| ---------- | ------------------------------------------------------------ | ---- |
| 创建对象   | 默认情况：接收到第一次请求  修改启动顺序后：Web应用启动过程中 | 一次 |
| 初始化操作 | 创建对象之后                                                 | 一次 |
| 处理请求   | 接收到请求                                                   | 多次 |
| 销毁操作   | Web应用卸载之前                                              | 一次 |

我们即将要学习的 SpringIoC 容器也是一个复杂容器。它们不仅要负责创建组件的对象、存储组件的对象，还要负责调用组件的方法让它们工作，最终在特定情况下销毁组件。

总结：Spring管理组件的容器，就是一个复杂容器，不仅存储组件，也可以管理组件之间依赖关系，并且创建和销毁组件等！

#### 2.2SpringIoc容器介绍

Spring Ioc容器，负责实例化，配置和组装bean(组件)。容器通过读取配置元数据来获取有关要实例化、配置和组装组件的指令。<font color=red>配置元数据以XML、Java注解或Java代码形式表现</font>

它允许表达组成应用程序的组件以及这些组件之间丰富的相互依赖关系。

![img](https://secure2.wostatic.cn/static/mFt9PQ2ggCqB193CC57AKi/image.png?auth_key=1698387314-cn3bzM6mw5371Ugreoggbg-0-0d2c44787ea22bd03259edb294c7b4f9&image_process=resize,w_1004&file_size=11514)

上图显示了 Spring 容器工作原理的高级视图。应用程序类与配置元数据相结合，您拥有完全配置且可执行的系统或应用程序。

#### 2.3SpringIoc容器具体接口和实现类

SpringFactory接口提供了一种高级配置机制，能够管理任何类型的对象，它是SpringIoc容器标准化超接口！

ApplicationContext是BeanFactory的子接口，它扩展了以下功能：

- 更容易与 Spring 的 AOP 功能集成
- 消息资源处理（用于国际化）
- 特定于应用程序给予此接口实现，例如Web 应用程序的 `WebApplicationContext`

简而言之， BeanFactory 提供了配置框架和基本功能，而 ApplicationContext 添加了更多特定于企业的功能。 ApplicationContext 是 BeanFactory 的完整超集！

**ApplicationContext容器实现类：**

![img](https://api.wolai.com/v1/proxy/image?src=http%3A%2F%2Fheavy_code_industry.gitee.io%2Fcode_heavy_industry%2Fassets%2Fimg%2Fimg004.f6680aef.png&spaceId=fqkGyHKKxSnzkhVZnoSxhC&userId=&image_process=resize,w_1004)

| 类型名                             | 简介                                                         |
| ---------------------------------- | ------------------------------------------------------------ |
| ClassPathXmlApplicationContext     | 通过读取类路径下的 XML 格式的配置文件创建 IOC 容器对象       |
| FileSystemXmlApplicationContext    | 通过文件系统路径读取 XML 格式的配置文件创建 IOC 容器对象     |
| AnnotationConfigApplicationContext | 通过读取Java配置类创建 IOC 容器对象                          |
| WebApplicationContext              | 专门为 Web 应用准备，基于 Web 环境创建 IOC 容器对象，并将对象引入存入 ServletContext 域中。 |

#### 2.4SpringIoc容器管理配置方式

Spring IoC 容器使用多种形式的配置元数据。此配置元数据表示您作为应用程序开发人员如何告诉 Spring 容器实例化、配置和组装应用程序中的对象。

![img](https://secure2.wostatic.cn/static/mFt9PQ2ggCqB193CC57AKi/image.png?auth_key=1698396605-qFqv3MptDcmshEf5UrfrNH-0-b50dd86c50a150fedd88c607e70763bb&image_process=resize,w_936&file_size=11514)



Spring框架提供了多种配置方式：**XML配置方式、注解方式和Java配置类方式**

1. XML配置方式：是Spring框架最早的配置方式之一，通过在XML文件中定义Bean及其依赖关系、Bean的作用域等信息，让Spring IoC容器来管理Bean之间的依赖关系。该方式从Spring框架的第一版开始提供支持。
2. 注解方式：从Spring 2.5版本开始提供支持，可以通过在Bean类上使用注解来代替XML配置文件中的配置信息。通过在Bean类上加上相应的注解（如@Component, @Service, @Autowired等），将Bean注册到Spring IoC容器中，这样Spring IoC容器就可以管理这些Bean之间的依赖关系。
3. <font color=red>**Java配置类**</font>方式：从Spring 3.0版本开始提供支持，通过Java类来定义Bean、Bean之间的依赖关系和配置信息，从而代替XML配置文件的方式。Java配置类是一种使用Java编写配置信息的方式，通过@Configuration、@Bean等注解来实现Bean和依赖关系的配置。

为了迎合当下开发环境，我们将以<font color=red>**配置类+注解方式**</font>为主进行讲解！

### 3.Spring IoC/DI概念总结

Sping的核心容器就两个功能：IoC和DI

类<--------------Java代码（new 类()------------------->权力交给程序员）

类<--------------spring核心容器（ioc容器中完成实例化反射---------------->权力交给核心容器spring)

这就是**IoC控制反转**

Java代码（把对象2赋值给对象1，有构造方法，set方法等等）

Spring核心容器（把对象2赋值给对象1，只需要写个配置文件告诉它）

这就是**DI依赖注入**

## 四、Spring IoC实践和应用

### 1.Spring IoC/DI实现步骤

第一步：编写配置信息，配置文件（xml,注解，配置):（组件类信息，组件之间的引用关系）

配置元数据，既是编写交给SpringIoC容器管理组件的信息，配置方式有三种。

基于 XML 的配置元数据的基本结构：

<bean id="..." [1] class="..." [2]>  
    <!-- collaborators and configuration for this bean go here -->
  </bean>

```XML
<?xml version="1.0" encoding="UTF-8"?>
<!-- 此处要添加一些约束，配置文件的标签并不是随意命名 -->
<beans xmlns="http://www.springframework.org/schema/beans"
  xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
  xsi:schemaLocation="http://www.springframework.org/schema/beans
    https://www.springframework.org/schema/beans/spring-beans.xsd">

  <bean id="..." [1] class="..." [2]>  
    <!-- collaborators and configuration for this bean go here -->
  </bean>

  <bean id="..." class="...">
    <!-- collaborators and configuration for this bean go here -->
  </bean>
  <!-- more bean definitions go here -->
</beans>
```

Spring IoC 容器管理一个或多个组件。这些 组件是使用你提供给容器的配置元数据（例如，以 XML `<bean/>` 定义的形式）创建的。

<bean /> 标签 == 组件信息声明

- `id` 属性是标识单个 Bean 定义的字符串。
- `class` 属性定义 Bean 的类型并使用完全限定的类名。

第二步：要指定配置信息，实例化ioc容器对象：（(IoC/DI）组件 组件 组件)

提供给 `ApplicationContext` 构造函数的位置路径是资源字符串地址，允许容器从各种外部资源（如本地文件系统、Java `CLASSPATH` 等）加载配置元数据。

我们应该选择一个合适的容器实现类，进行IoC容器的实例化工作：

```Java
//实例化ioc容器,读取外部配置文件,最终会在容器内进行ioc和di动作
ApplicationContext context = 
           new ClassPathXmlApplicationContext("services.xml", "daos.xml");
```

第三步：如何在Java代码中获取组件（Bean）  使用组件

`ApplicationContext` 是一个高级工厂的接口，能够维护不同 bean 及其依赖项的注册表。通过使用方法 `T getBean(String name, Class<T> requiredType)` ，您可以检索 bean 的实例。

允许读取 Bean 定义并访问它们，如以下示例所示：

```Java
//创建ioc容器对象，指定配置文件，ioc也开始实例组件对象
ApplicationContext context = new ClassPathXmlApplicationContext("services.xml", "daos.xml");
//获取ioc容器的组件对象
PetStoreService service = context.getBean("petStore", PetStoreService.class);
//使用组件对象
List<String> userList = service.getUsernameList();
```

### 2.基于XML配置方式组件管理

自己如何实例化对象？不考虑反射！！

**类**

构造函数实例化（无参数构造函数和有参数构造函数实例化)

工厂模式实例化(静态工厂和非静态工厂)

不同的实例化方式对象和组件，ioc的配置方式也不同

#### 2.1实验一：组件(Bean)信息声明配置(IoC)

1. 目标

    Spring IoC 容器管理一个或多个 bean。这些 Bean 是使用您提供给容器的配置元数据创建的（例如，以 XML `<bean/>` 定义的形式）。

    我们学习，如何通过定义XML配置文件，声明组件类信息，交给 Spring 的 IoC 容器进行组件管理！
2. 思路

    ![](http://heavy_code_industry.gitee.io/code_heavy_industry/assets/img/img006.c8bae859.png)
3. 准备项目
    1. 创建maven工程（spring-ioc-xml-01）
    2. 导入SpringIoC相关依赖

        pom.xml

```XML
<dependencies>
    <!--spring context依赖-->
    <!--当你引入Spring Context依赖之后，表示将Spring的基础依赖引入了-->
    <dependency>
        <groupId>org.springframework</groupId>
        <artifactId>spring-context</artifactId>
        <version>6.0.6</version>
    </dependency>
    <!--junit5测试-->
    <dependency>
        <groupId>org.junit.jupiter</groupId>
        <artifactId>junit-jupiter-api</artifactId>
        <version>5.3.1</version>
    </dependency>
</dependencies>

```

4.基于无参数构造函数

> 当通过构造函数方法创建一个bean(组件对象)时，所有普通类都可以由Spring使用并与之兼容。也就是说，正在开发的类不需要实现特定的接口或以特定的方式进行编码。只需要指定Bean类信息就足够了。但是，默认情况下，我们需要一个默认(空)构造函数



a.准备组件类

```java
package org.example.ioc_01;

public class HappyComponent {
    //默认包含无参数构造函数
    public void doWork(){
        System.out.println("HappyComponent.doWork");
    }
}

```

b.xml配置文件编写

创建携带spring约束的xml配置文件：resouces右键--new--XML配置文件

![img](https://secure2.wostatic.cn/static/7eC1WeTyXz1oLaGkPfJBfh/image.png?auth_key=1698406116-7jyY7i6amYbPC1V62vD9dN-0-d6444aa60269a4126188f433604001c3&image_process=resize,w_940&file_size=69946)

编写配置文件：文件：resources/spring-bean-01.xml

```java
<?xml version="1.0" encoding="UTF-8"?>
<beans xmlns="http://www.springframework.org/schema/beans"
       xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
       xsi:schemaLocation="http://www.springframework.org/schema/beans http://www.springframework.org/schema/beans/spring-beans.xsd">

    <!-- 1.可以使用无参数构造函数实例化的组件，如何进行ioc配置呢
    <bean  -  一个组件信息  - 一个组件对象
            id :组件的标识 唯一 方便后期读取
            class :组件的类的权限定符
            将一个组件类 - 声明两个组件信息 - [默认是单例模式] - 会实例化两个组件对象
            new
            new
      -->
    <bean id="happyComponent1" class="org.example.ioc_01.HappyComponent"/>
    <bean id="happyComponent2" class="org.example.ioc_01.HappyComponent"/>

</beans>
```



bean标签：通过配置bean标签告诉IOC容器需要创建对象的组件信息

id属性：bean的唯一标识，方便后期获取Bean

class属性：组件类的全限定符

<font color=red>注意：要求当前组件类必须包含无参数构造函数</font>,构造函数私有也没关系

5.基于静态工厂方法实例化

> 除了使用构造函数实例化对象，还有一类是通过工厂模式实例化对象。接下来我们讲解如何定义使用静态工厂方法创建Bean的配置 ！

a.准备组件类

```java
package org.example.ioc_01;

public class ClientService {
    private static ClientService clientService = new ClientService();
    private ClientService() {}

    public static ClientService createInstance() {

        return clientService;
    }
}

```



b.xml配置文件编写

文件：resources/spring-bean-01.xml

```java
<?xml version="1.0" encoding="UTF-8"?>
<beans xmlns="http://www.springframework.org/schema/beans"
       xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
       xsi:schemaLocation="http://www.springframework.org/schema/beans http://www.springframework.org/schema/beans/spring-beans.xsd">

    <!-- 1.可以使用无参数构造函数实例化的组件，如何进行ioc配置呢
    <bean  -  一个组件信息  - 一个组件对象
            id :组件的标识 唯一 方便后期读取
            class :组件的类的权限定符
            将一个组件类 - 声明两个组件信息 - [默认是单例模式] - 会实例化两个组件对象
            new
            new
      -->
    <bean id="happyComponent1" class="org.example.ioc_01.HappyComponent"/>
    <bean id="happyComponent2" class="org.example.ioc_01.HappyComponent"/>


    <!-- 2.静态工厂类如何声明工厂方法进行ioc配置
        <bean
            id="组件的表示"
            class="工厂类的全限定符"
            factory-method="静态工厂方法"
            -->
    <bean id="clientService" class="org.example.ioc_01.ClientService" factory-method="createInstance"/>

</beans>
```

class属性：指定工厂类的全限定符

factory-method:指定静态工厂方法  <font color=red>注意：该方法必须是静态方法，去掉static，就会报错</font>

6.基于实例工厂方法实例化

> 接下来我们讲解一下如何定义使用实例工厂方法创建Bean的配置

a.准备组件类

```java
package org.example.ioc_01;

public class ClientServiceImpl {
}

```

```java
package org.example.ioc_01;

public class DefaultServiceLocator {
    private static ClientServiceImpl clientService = new ClientServiceImpl();

    public ClientServiceImpl createClientServiceInstance() {
        return clientService;
    }
}

```

b.xml配置文件编写

文件：resources/spring-bean-01.xml

```java
<?xml version="1.0" encoding="UTF-8"?>
<beans xmlns="http://www.springframework.org/schema/beans"
       xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
       xsi:schemaLocation="http://www.springframework.org/schema/beans http://www.springframework.org/schema/beans/spring-beans.xsd">

    <!-- 1.可以使用无参数构造函数实例化的组件，如何进行ioc配置呢
    <bean  -  一个组件信息  - 一个组件对象
            id :组件的标识 唯一 方便后期读取
            class :组件的类的权限定符
            将一个组件类 - 声明两个组件信息 - [默认是单例模式] - 会实例化两个组件对象
            new
            new
      -->
    <bean id="happyComponent1" class="org.example.ioc_01.HappyComponent"/>
    <bean id="happyComponent2" class="org.example.ioc_01.HappyComponent"/>


    <!-- 2.静态工厂类如何声明工厂方法进行ioc配置
        <bean
            id="组件的表示"
            class="工厂类的全限定符"
            factory-method="静态工厂方法"
            -->
    <bean id="clientService" class="org.example.ioc_01.ClientService" factory-method="createInstance"/>

    <!-- 3.非静态工厂如何声明ioc配置-->
    <!-- 3.1 配置工厂类的组件信息 -->
    <bean id="defaultServiceLocator" class="org.example.ioc_01.DefaultServiceLocator"/>
    <!-- 3.2 通过指定非静态工厂对象和方法名 来配置生成的ioc信息-->
    <bean id="clientService2" factory-bean="defaultServiceLocator" factory-method="createClientServiceInstance"/>
</beans>
```

factory-bean属性：指定当前容器中工厂Bean的名称

factory-method:指定实例工厂方法名。<font color=red>注意：实例方法必须是非static</font>

7.图解IoC配置流程

![image](C:\Users\dyj\Pictures\Saved Pictures\image.png)



#### 2.2实验二：组件(Bean)依赖注入配置

1. 目标

    通过配置文件,实现IoC容器中Bean之间的引用（依赖注入DI配置）。

    主要涉及注入场景：基于构造函数的依赖注入和基于 Setter 的依赖注入。
2. 思路

    ![](https://secure2.wostatic.cn/static/opfLAb8XnCZDyPMm9BuiMc/image.png?auth_key=1698412784-74xpUUtFue3RtfnY3cZXHb-0-a666cac98565988c8c05d9b3fd9ba007)

3.基于构造函数的依赖注入（单个构造函数）

a.介绍：

基于构造函数的 DI 是通过容器调用具有多个参数的构造函数来完成的，每个参数表示一个依赖项。

下面的示例演示一个只能通过构造函数注入进行依赖项注入的类！

b.准备组件类

```java
public class UserDao {
}


public class UserService {
    
    private UserDao userDao;

    public UserService(UserDao userDao) {
        this.userDao = userDao;
    }
}

```

c.编写配置文件

文件：resources/spring-02.xml

```xml
<?xml version="1.0" encoding="UTF-8"?>
<beans xmlns="http://www.springframework.org/schema/beans"
       xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
       xsi:schemaLocation="http://www.springframework.org/schema/beans http://www.springframework.org/schema/beans/spring-beans.xsd">

    <!-- 引用和被引用的组件 必须全部在ioc容器！ 不能乡愁！！-->

    <!--1.单个构造参数注入-->

    <!--
    springioc容器是一个高级容器，内部会有缓存动作！1.先创建对象[ioc] 2.再进行属性赋值[di]
    -->
    <!--步骤一：将他们都存放在ioc容器[ioc]-->
    <bean id="userDao" class="org.example.ioc_02.UserDao"/>
    <bean id="userService" class="org.example.ioc_02.UserService">
        <!--构造参数传值 di的配置
            <constructor-arg 构造参数传值的di配置
                value=直接属性值 String name="二狗子"  int age="18"
                ref=引用其他的bean beanId值
                -->
        <constructor-arg ref="userDao"/>
    </bean>
    
    <!--也可以放在这里-->
    <!--步骤一：将他们都存放在ioc容器[ioc]-->
    <bean id="userDao" class="org.example.ioc_02.UserDao"/>
</beans>
```

- constructor-arg标签：可以引用构造参数 ref引用其他bean的标识。

4.基于构造函数的依赖注入（多构造参数解析）

1. 介绍

    基于构造函数的 DI 是通过容器调用具有多个参数的构造函数来完成的，每个参数表示一个依赖项。

    下面的示例演示通过构造函数注入多个参数，参数包含其他bean和基本数据类型！
2. 准备组件类

```Java
public class UserDao {
}


public class UserService {
    
    private UserDao userDao;
    
    private int age;
    
    private String name;

    public UserService(int age , String name ,UserDao userDao) {
        this.userDao = userDao;
        this.age = age;
        this.name = name;
    }
}
```
3. 编写配置文件

```XML
<!-- 场景1: 多参数，可以按照相应构造函数的顺序注入数据 -->
<beans>
  <bean id="userService" class="x.y.UserService">
    <!-- value直接注入基本类型值 -->
    <constructor-arg  value="18"/>
    <constructor-arg  value="赵伟风"/>
    
    <constructor-arg  ref="userDao"/>
  </bean>
  <!-- 被引用类bean声明 -->
  <bean id="userDao" class="x.y.UserDao"/>
</beans>


<!-- 场景2: 多参数，可以按照相应构造函数的名称注入数据 -->
<beans>
  <bean id="userService" class="x.y.UserService">
    <!-- value直接注入基本类型值 -->
    <constructor-arg name="name" value="赵伟风"/>
    <constructor-arg name="userDao" ref="userDao"/>
    <constructor-arg name="age"  value="18"/>
  </bean>
  <!-- 被引用类bean声明 -->
  <bean id="userDao" class="x.y.UserDao"/>
</beans>

<!-- 场景2: 多参数，可以按照相应构造函数的角标注入数据 
           index从0开始 构造函数(0,1,2....)
-->
<beans>
    <bean id="userService" class="x.y.UserService">
    <!-- value直接注入基本类型值 -->
    <constructor-arg index="1" value="赵伟风"/>
    <constructor-arg index="2" ref="userDao"/>
    <constructor-arg index="0"  value="18"/>
  </bean>
  <!-- 被引用类bean声明 -->
  <bean id="userDao" class="x.y.UserDao"/>
</beans>

```
        - constructor-arg标签：指定构造参数和对应的值
        - constructor-arg标签：name属性指定参数名、index属性指定参数角标、value属性指定普通属性值
5.**基于Setter方法依赖注入**

1. 介绍

    开发中，除了构造函数注入（DI）更多的使用的Setter方法进行注入！

    下面的示例演示一个只能使用纯 setter 注入进行依赖项注入的类。
2. 准备组件类

```Java
public Class MovieFinder{

}

public class SimpleMovieLister {

  private MovieFinder movieFinder;
  
  private String movieName;

  public void setMovieFinder(MovieFinder movieFinder) {
    this.movieFinder = movieFinder;
  }
  
  public void setMovieName(String movieName){
    this.movieName = movieName;
  }

  // business logic that actually uses the injected MovieFinder is omitted...
}
```
3. 编写配置文件

```XML
<bean id="simpleMovieLister" class="examples.SimpleMovieLister">
  <!-- setter方法，注入movieFinder对象的标识id
       name = 属性名setter方法的 去set和首字母小写的值！调用set方法的名
  setMovieFinder->movieFinder
ref = 引用bean的id值
   -->
  <property name="movieFinder" ref="movieFinder" />

  <!-- setter方法，注入基本数据类型movieName
       name = 属性名 value= 基本类型值
   -->
  <property name="movieName" value="消失的她"/>
</bean>

<bean id="movieFinder" class="examples.MovieFinder"/>

```
        - property标签： 可以给setter方法对应的属性赋值
        - property 标签： name属性代表**set方法标识**、ref代表引用bean的标识id、value属性代表基本属性值

**总结：**

  依赖注入（DI）包含引用类型和基本数据类型，同时注入的方式也有多种！主流的注入方式为setter方法注入和构造函数注入，两种注入语法都需要掌握！

  需要特别注意：引用其他bean，使用ref属性。直接注入基本类型值，使用value属性。

#### 2.3实验三：IoC容器创建和使用

1.介绍

上面的实验只是讲解了如何在XML格式的配置文件编写IoC和DI配置！

如图：

![](https://secure2.wostatic.cn/static/ngQZT7qhVfAzTxrr2oX1ny/image.png?auth_key=1698748379-gU9RECzwFYTF2r2vfee5fE-0-571657b25494e4bf549fba3f5b611118)

想要配置文件中声明组件类信息真正的进行实例化成Bean对象和形成Bean之间的引用关系，我们需要声明IoC容器对象，读取配置文件，实例化组件和关系维护的过程都是在IoC容器中实现的！

2.容器实例化和Bean对象读取

```java
package org.example.test;

//文件地址D:\javacode\ssm-spring-part\spring-ioc-xml-01\src\test\java\org.example.test\SpringIoCTest

//ioc容器创建和读取组件的测试类
//创建就是实例化

import org.example.ioc_03.HappyComponent;
import org.junit.jupiter.api.Test;
import org.springframework.context.ApplicationContext;
import org.springframework.context.support.ClassPathXmlApplicationContext;

public class SpringIoCTest {

    //讲解如何创建ioc容器并且读取配置文件
    public void createIoC()
    {
        //创建容器 选择合适的容器实现即可
        /*
        接口
        BeanFactory

        ApplicationContext

        实现类

        ClassPathXmlApplicationContext 读取类路径下的xml配置方式
        FileSystemXmlApplicationContext 读取指定文件位置的xml配置方式 比如说c盘D盘
        AnnotationConfigApplicationContext 读取配置类方式的ioc容器
        WebApplicationContext web项目专属的配置的ioc容器
         */

        //方式一：直接创建容器并且指定配置文件
        //构造函数（Spring...配置文件）可以填写一个或者多个
        ApplicationContext applicationContext=new ClassPathXmlApplicationContext("spring-03.xml","spring-x.xml");
        //方式二;先创建ioc容器对象，再指定配置文件，再刷新
        //源码的配置过程！创建容器[spring]和配置文件指定分开[自己指定]
        ClassPathXmlApplicationContext applicationContext1=new ClassPathXmlApplicationContext();
        applicationContext1.setConfigLocations("spring-03.xml");//外部配置文件的设置
        applicationContext1.refresh();//调用ioc和DI的流程



    }
    @Test

    //讲解如何在IoC容器中获取组件Bean
    public void getBeanFromIoC() {
        //1.创建ioc容器对象
        ClassPathXmlApplicationContext applicationContext = new ClassPathXmlApplicationContext();
        applicationContext.setConfigLocations("spring-03.xml");
        //注意不刷新不行
        applicationContext.refresh();

        //2.读取ioc容器的组件
        //方案一：直接根据beanId获取即可  返回值类型是Object 需要强转（不推荐）
        HappyComponent happyComponent = (HappyComponent) applicationContext.getBean("happyComponent");

        //方案二：根据beanId,同时指定bean的类型Class
        //applicationContext.getBean("happycomponent", HappyComponent.class).var回车

        HappyComponent happyComponent1 = applicationContext.getBean("happyComponent", HappyComponent.class);

        //方案三：：直接根据类型获取
        //注意：根据bean类型获取，同一个类型，在ioc容器中只能有一个bean
        //如果ioc容器存在多个同类型的Bean，会出现：NoUniqueBeanDefinitionException
        //ioc的配置一定是实现类，但是可以根据接口类型获取值！getBean(类型);instanceof ioc容器的类型==true
        /*
        根据类型来获取bean时，在满足bean唯一性的前提下，其实只是看：『对象 instanceof 指定的类型』的返回结果，
       只要返回的是true就可以认定为和类型匹配，能够获取到。
        */
        HappyComponent happyComponent2 = applicationContext.getBean(HappyComponent.class);

        happyComponent2.doWork();
        System.out.println(happyComponent==happyComponent1);
        System.out.println(happyComponent2==happyComponent1);

        //运行结果
        //HappyComponent.doWork
        //true
        //true
    }
    }

```

```xml
<!--spring-03.xml-->
<?xml version="1.0" encoding="UTF-8"?>
<beans xmlns="http://www.springframework.org/schema/beans"
       xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
       xsi:schemaLocation="http://www.springframework.org/schema/beans http://www.springframework.org/schema/beans/spring-beans.xsd">


        <!--组件的信息 ioc的配置-》applicationContext读取了-》实例化对象
                ioc的配置一定是实现类！真正要进行实例化！
        -->
        <bean id="happyComponent" class="org.example.ioc_03.HappyComponent"/>
</beans>
```

```java
package org.example.ioc_03;
//HappyComponent.java
public class HappyComponent {
    //默认包含无参数构造函数
    public void doWork(){
        System.out.println("HappyComponent.doWork");
  
  }
}
```

#### 2.4实验四：高级特性：Bean作用域和周期方法

1.组件周期方法配置

a.周期方法概念：我们可以在组件类中定义方法，然后当IoC容器实例化和销毁组件对象的时候进行调用！这两个方法我们称为生命周期方法！

类似于Servlet的init/destroy方法,我们可以在周期方法完成初始化和释放资源等工作。

b.周期方法声明

```java
public class JavaBean{
    //周期方法要求：方法命名随意，但是要求方法必须是public void 无形参列表
    public void init(){
        //初始化逻辑
    }
    public void clear(){
        //释放资源逻辑
    }
}
```

c.周期方法配置

```xml
<!--
init-method="初始化方法名"
destory-method="销毁方法名"
spring ioc容器就会在对应的时间节点回调对应的方法，我们可以在其中写对应的业务就可以啦！
-->
<beans>
    <bean id="javaBean" class="com.atguigu.ioc_04.JavaBean" init-method="init" destory-method="clear"/>
</beans>
```

d.test文件

```java
@Test
public void test_04(){
    //1.创建ioc容器，就会进行组件对象的实例化->init
    ClassPathXmlApplicationContext applicationConetxt=new  ClassPathXmlApplicationContext("spring-04.xml");
    
    //ioc->容器去调用destory
    //ioc会立即释放，死了！
    
    //2.正常结束ioc容器
    applicationContext.close();
}
```

2.组件作用域配置

a.Bean作用域概念

> `<bean` 标签声明Bean，只是将Bean的信息配置给SpringIoC容器！
>
> 在IoC容器中，这些`<bean`标签对应的信息转成Spring内部 `BeanDefinition` 对象，`BeanDefinition` 对象内，包含定义的信息（id,class,属性等等）！
>
> 这意味着，`BeanDefinition`与`类`概念一样，SpringIoC容器可以可以根据`BeanDefinition`对象反射创建多个Bean对象实例。
>
> 具体创建多少个Bean的实例对象，由Bean的作用域Scope属性指定！

b.作用域可选值

| 取值      | 含义                                        | 创建对象的时机   | 默认值 |
| --------- | ------------------------------------------- | ---------------- | ------ |
| singleton | 在 IOC 容器中，这个 bean 的对象始终为单实例 | IOC 容器初始化时 | 是     |
| prototype | 这个 bean 在 IOC 容器中有多个实例           | 获取 bean 时     | 否     |

如果是在WebApplicationContext环境下还会有另外两个作用域（但不常用）：

| 取值    | 含义                 | 创建对象的时机 | 默认值 |
| ------- | -------------------- | -------------- | ------ |
| request | 请求范围内有效的实例 | 每次请求       | 否     |
| session | 会话范围内有效的实例 | 每次会话       | 否     |

c.作用域配置

配置scope范围

```xml
<!-- scope属性：取值singleton（默认值），bean在IOC容器中只有一个实例，IOC容器初始化时创建对象 -->
<!-- scope属性：取值prototype，bean在IOC容器中可以有多个实例，getBean()时创建对象 -->
<!--声明一个组件信息！默认就是单例模式 一个<bean-beanDefinition-组件对象getBean一次就会创建一个组件对象-->
<bean id="javaBean2" class="com.atguigu.ioc_04.JavaBean2" scope="singleton"/>
<bean id="javaBean2" class="com.atguigu.ioc_04.JavaBean2" scope="prototype"/>
```

d.作用域测试

```java
@Test
public void test_04(){
    //1.创建ioc容器，就会进行组件对象的实例化->init
    ClassPathXmlApplicationContext applicationConetxt=new  ClassPathXmlApplicationContext("spring-04.xml");
    
    //ioc->容器去调用destory
    //ioc会立即释放，死了！
    
    JavaBean2 bean=applicationContext.getBean(JavaBean2.class);
    JavaBean2 bean1=applicationContext.getBean(JavaBean2.class);
    System.out.println(bean==bean1);//单例true 多例false
    
    //2.正常结束ioc容器
    applicationContext.close();
}
```

#### 2.5实验五：高级特性：FactoryBean特性和使用

FactoryBean简化两种工厂模式,其实也是个组件

FactoryBean是标准化工厂，是个接口，提供了getObject方法，重写这个方法编写自己的实例化逻辑，不像其他工厂一样需要写factory-method="方法名"

```
<bean id class="工厂类的全限定符即可"/>
```

1.FactoryBean简介

`FactoryBean` 接口是Spring IoC容器实例化逻辑的可插拔性点。

用于配置复杂的Bean对象，可以将创建过程存储在`FactoryBean` 的getObject方法！

`FactoryBean<T>` 接口提供三种方法：

- `T getObject()`: 

    返回此工厂创建的对象的实例。该返回值会被存储到IoC容器！
- `boolean isSingleton()`: 

    如果此 `FactoryBean` 返回单例，则返回 `true` ，否则返回 `false` 。此方法的默认实现返回 `true` （注意，lombok插件使用，可能影响效果）。
- `Class<?> getObjectType()`: 返回 `getObject()` 方法返回的对象类型，如果事先不知道类型，则返回 `null` 。

2.FactoryBean使用场景

1. 代理类的创建
2. 第三方框架整合
3. 复杂对象实例化等

3.Factorybean应用

1.准备FactoryBean实现类

```Java
// 实现FactoryBean接口时需要指定泛型
// 泛型类型就是当前工厂要生产的对象的类型
public class HappyFactoryBean implements FactoryBean<HappyMachine> {
    
    private String machineName;
    
    public String getMachineName() {
        return machineName;
    }
    
    public void setMachineName(String machineName) {
        this.machineName = machineName;
    }
    
    @Override
    public HappyMachine getObject() throws Exception {
    
        // 方法内部模拟创建、设置一个对象的复杂过程
        HappyMachine happyMachine = new HappyMachine();
    
        happyMachine.setMachineName(this.machineName);
    
        return happyMachine;
    }
    
    @Override
    public Class<?> getObjectType() {
    
        // 返回要生产的对象的类型
        return HappyMachine.class;
    }
}
```
2. 配置FactoryBean实现类

```XML
<!-- FactoryBean机制 -->
<!-- 这个bean标签中class属性指定的是HappyFactoryBean，但是将来从这里获取的bean是HappyMachine对象 -->
<!--
id->getObject方法返回的对象的标识
Class->factoryBean标准化工厂类
-->
<bean id="happyMachine7" class="com.atguigu.ioc.HappyFactoryBean">
    <!-- property标签仍然可以用来通过setXxx()方法给属性赋值 -->
    <!--此位置的属性 ：HappyMachine工厂类配置 而不是getObject方法-->
    <property name="machineName" value="iceCreamMachine"/>
</bean>
```
3. 测试读取FactoryBean和FactoryBean.getObject对象

```Java
@Test
public void testExperiment07()  {

    ApplicationContext iocContainer = new ClassPathXmlApplicationContext("spring-bean-07.xml");

    //注意: 直接根据声明FactoryBean的id,获取的是getObject方法返回的对象
    HappyMachine happyMachine = iocContainer.getBean("happyMachine7",HappyMachine.class);
    System.out.println("happyMachine = " + happyMachine);

    //如果想要获取FactoryBean对象, 直接在id前添加&符号即可!  &happyMachine7 这是一种固定的约束
    Object bean = iocContainer.getBean("&happyMachine7");
    System.out.println("bean = " + bean);
}
```
4.FactoryBean和BeanFactory区别

*********

都是接口

BeanFactory IoC容器最大的接口 IoC容器

FactoryBean 标准化组件工厂的接口 组件

************

**FactoryBean **是 Spring 中一种特殊的 bean，可以在 getObject() 工厂方法自定义的逻辑创建Bean！是一种能够生产其他 Bean 的 Bean。FactoryBean 在容器启动时被创建，而在实际使用时则是通过调用 getObject() 方法来得到其所生产的 Bean。因此，FactoryBean 可以自定义任何所需的初始化逻辑，生产出一些定制化的 bean。

一般情况下，整合第三方框架，都是通过定义FactoryBean实现！！！

**BeanFactory** 是 Spring 框架的基础，其作为一个顶级接口定义了容器的基本行为，例如管理 bean 的生命周期、配置文件的加载和解析、bean 的装配和依赖注入等。BeanFactory 接口提供了访问 bean 的方式，例如 getBean() 方法获取指定的 bean 实例。它可以从不同的来源（例如 Mysql 数据库、XML 文件、Java 配置类等）获取 bean 定义，并将其转换为 bean 实例。同时，BeanFactory 还包含很多子类（例如，ApplicationContext 接口）提供了额外的强大功能。

总的来说，FactoryBean 和 BeanFactory 的区别主要在于前者是用于创建 bean 的接口，它提供了更加灵活的初始化定制功能，而后者是用于管理 bean 的框架基础接口，提供了基本的容器功能和 bean 生命周期管理。

#### 2.6实验六：基于XML方式整合三层架构组件

java代码包括获取对象（全局变量和set方法）和适用对象，然后配置，然后IoC容器

1.需求分析：

搭建一个三层架构案例，模拟查询全部学生（学生表）信息，持久层使用JdbcTemplate和Druid技术，使用XML方式进行组件管理！![img](https://secure2.wostatic.cn/static/dMe3en4EMVQ5JEi3PVDjae/image.png?auth_key=1699169845-tirckEDTZXWxRksJxm4MEo-0-9ed98a1292a98689a376eedbec088b23&file_size=78180)

> XML（可扩展标记语言）是一种用于描述数据结构和传输数据的标记语言。它被广泛应用于各种领域，包括Web开发、数据交换和配置文件等。在软件开发中，XML常用于定义和组织应用程序的配置信息、数据模型和其他结构化数据。
>
> 在上述三层架构案例中，XML方式被用于组件管理。组件管理是指通过配置文件来管理应用程序中的组件（例如，持久层的实现类、业务逻辑层的实现类等）。使用XML方式进行组件管理的好处是可以将组件的创建、依赖关系和配置信息集中在一个配置文件中，提供了更灵活和可维护的方式来管理应用程序的组件。
>
> 在这个案例中，XML文件可以用于定义以下内容：
>
> 1. 数据库连接信息：可以在XML文件中定义数据库的连接URL、用户名、密码等信息，以供持久层组件使用。
> 2. 组件的配置信息：可以在XML文件中定义各个组件的配置信息，例如持久层组件JdbcTemplate和Druid的配置信息，以及其他相关的配置项。
> 3. 组件的依赖关系：可以在XML文件中定义各个组件之间的依赖关系，例如业务逻辑层组件依赖于持久层组件，在XML文件中进行配置。
>
> 通过使用XML方式进行组件管理，可以实现对应用程序的组件进行集中管理，并且可以根据需要进行灵活的配置和调整。

持久层

> 持久层（Persistence Layer）是指在软件系统中负责处理数据持久化的一层。它负责将应用程序的数据存储到持久存储介质（如数据库、文件系统等）中，并提供数据的读取、写入、更新和删除等操作。
>
> 持久层组件是在三层架构中的其中一层，通常位于业务逻辑层和数据访问层之间。它的主要功能是处理数据的持久化操作，包括与数据库的交互、数据的增删改查等。
>
> 在软件开发中，常用的持久层组件包括对象关系映射（ORM）框架、数据库访问框架等。这些组件提供了简化数据库操作的接口和功能，使开发人员可以更方便地进行数据库操作，而无需直接编写SQL语句。
>
> 在您的案例中，持久层组件使用了JdbcTemplate和Druid技术。JdbcTemplate是Spring框架提供的一个用于简化JDBC编程的工具类，它封装了JDBC的底层细节，提供了更简洁的API来执行SQL查询和更新操作。Druid是一种高性能的数据库连接池技术，它可以提供连接池管理、监控和优化等功能，用于管理数据库连接的创建和释放。
>
> 通过使用JdbcTemplate和Druid等持久层组件，可以简化数据库操作的代码编写，并提供高效、可靠的数据库访问功能。

2.数据库准备

```java
create database studb;

use studb;

CREATE TABLE students (
  id INT PRIMARY KEY,
  name VARCHAR(50) NOT NULL,
  gender VARCHAR(10) NOT NULL,
  age INT,
  class VARCHAR(50)
);

INSERT INTO students (id, name, gender, age, class)
VALUES
  (1, '张三', '男', 20, '高中一班'),
  (2, '李四', '男', 19, '高中二班'),
  (3, '王五', '女', 18, '高中一班'),
  (4, '赵六', '女', 20, '高中三班'),
  (5, '刘七', '男', 19, '高中二班'),
  (6, '陈八', '女', 18, '高中一班'),
  (7, '杨九', '男', 20, '高中三班'),
  (8, '吴十', '男', 19, '高中二班');

```

3.项目准备

a.项目创建

spring-ioc-xml-practice-02

b.依赖导入

```xml
<!--  ssm-spring-part  pomm.xml-->
<?xml version="1.0" encoding="UTF-8"?>
<project xmlns="http://maven.apache.org/POM/4.0.0"
         xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
         xsi:schemaLocation="http://maven.apache.org/POM/4.0.0 http://maven.apache.org/xsd/maven-4.0.0.xsd">
    <modelVersion>4.0.0</modelVersion>

    <groupId>org.example</groupId>
    <artifactId>ssm-spring-part</artifactId>
    <version>1.0-SNAPSHOT</version>
    <packaging>pom</packaging>
    <modules>
        <module>spring-ioc-xml-01</module>
        <module>spring-ioc-xml-practice-02</module>
    </modules>

    <properties>
        <maven.compiler.source>17</maven.compiler.source>
        <maven.compiler.target>17</maven.compiler.target>
        <project.build.sourceEncoding>UTF-8</project.build.sourceEncoding>
    </properties>

    <dependencies>
        <!--spring context依赖-->
        <!--当你引入Spring Context依赖之后，表示将Spring的基础依赖引入了-->
        <dependency>
            <groupId>org.springframework</groupId>
            <artifactId>spring-context</artifactId>
            <version>6.0.6</version>
        </dependency>
        <!--junit5测试-->
        <dependency>
            <groupId>org.junit.jupiter</groupId>
            <artifactId>junit-jupiter-api</artifactId>
            <version>5.3.1</version>
        </dependency>
        <!-- 数据库驱动和连接池-->
        <dependency>
            <groupId>mysql</groupId>
            <artifactId>mysql-connector-java</artifactId>
            <version>8.0.25</version>
        </dependency>

        <dependency>
            <groupId>com.alibaba</groupId>
            <artifactId>druid</artifactId>
            <version>1.2.8</version>
        </dependency>

        <!-- spring-jdbc -->
        <dependency>
            <groupId>org.springframework</groupId>
            <artifactId>spring-jdbc</artifactId>
            <version>6.0.6</version>
        </dependency>

    </dependencies>

</project>
```

c.实体类准备

```java
//Student.java
package org.example.pojo;

public class Student {

    private Integer id;
    private String name;
    private String gender;
    private Integer age;
    private String classes;

    public Integer getId() {
        return id;
    }

    public void setId(Integer id) {
        this.id = id;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public String getGender() {
        return gender;
    }

    public void setGender(String gender) {
        this.gender = gender;
    }

    public Integer getAge() {
        return age;
    }

    public void setAge(Integer age) {
        this.age = age;
    }

    public String getClasses() {
        return classes;
    }

    public void setClasses(String classes) {
        this.classes = classes;
    }

    @Override
    public String toString() {
        return "Student{" +
                "id=" + id +
                ", name='" + name + '\'' +
                ", gender='" + gender + '\'' +
                ", age=" + age +
                ", classes='" + classes + '\'' +
                '}';
    }
}

```

4.JdbcTemplate技术讲解

为了在特定领域帮助我们简化代码，Spring封装了很多【Template】形式的模板类，例如：RedisTemplate、RestTemplate、等等，包括我们今天要学习的JdbcTemplate

main->resources->jdbc.properties  提取数据库连接信息

```properties
atguigu.url=jdbc:mysql://localhost:3306/studb
atguigu.driver=com.mysql.cj.jdbc.Driver
atguigu.username=root
atguigu.password=40111004
```

springioc配置文件

```xml
<?xml version="1.0" encoding="UTF-8"?>
<beans xmlns="http://www.springframework.org/schema/beans"
       xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
       xmlns:context="http://www.springframework.org/schema/context"
       xsi:schemaLocation="http://www.springframework.org/schema/beans http://www.springframework.org/schema/beans/spring-beans.xsd http://www.springframework.org/schema/context https://www.springframework.org/schema/context/spring-context.xsd">

    <!--方案二-->
    <!--读取外部配置文件 .properties =>value ="${key}"
       <context:property-placeholder location="classpath:jdbc.properties,classpath:其他配置，可以添加多个外部配置" />
       -->
    <context:property-placeholder location="classpath:jdbc.properties" />

    <bean id="dataSource" class="com.alibaba.druid.pool.DruidDataSource">
        <property name="url" value="${atguigu.url}"/>
        <property name="driverClassName" value="${atguigu.driver}"/>
        <property name="username" value="${atguigu.username}"/>
        <property name="password" value="${atguigu.password}"/>
    </bean>

    <!-- 方案一
    <bean id="dataSource" class="com.alibaba.druid.pool.DruidDataSource">
        <property name="url" value="jdbc:mysql:///studb"/>
        <property name="driverClassName" value="com.mysql.cj.jdbc.Driver"/>
        <property name="username" value="root"/>
        <property name="password" value="40111004"/>
     </bean>
     -->

    <bean id="jdbcTemplate" class="org.springframework.jdbc.core.JdbcTemplate">
        <property name="dataSource" ref="dataSource"/>
    </bean>
    
</beans>
```

基于jdbcTemplate的CRUD使用

```java
package org.example.jdbc;

import com.alibaba.druid.pool.DruidDataSource;
import org.example.pojo.Student;
import org.junit.jupiter.api.Test;
import org.springframework.context.ApplicationContext;
import org.springframework.context.support.ClassPathXmlApplicationContext;
import org.springframework.jdbc.core.BeanPropertyRowMapper;
import org.springframework.jdbc.core.JdbcTemplate;
import org.springframework.jdbc.core.RowMapper;

import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.List;

//测试javaTemplateTest如何使用
public class JdbcTemplateTest {
    public void testForJava() {

        //JdbcTemplate 简化数据库的增删改查 不提供连接池
        //DruidDataSource 负责连接的创建和数据库驱动的注册等等

        //0.创建一个连接池对象
        DruidDataSource  dataSource=new DruidDataSource();
        dataSource.setUrl("jdbc:mysql:///studb");//url地址
        dataSource.setDriverClassName("com.mysql.cj.jdbc.Driver");//jdbc驱动
        dataSource.setUsername("root");//账号
        dataSource.setPassword("40111004");//密码

        //1.实例化对象即可
        JdbcTemplate jdbcTemplate = new JdbcTemplate();

        jdbcTemplate.setDataSource(dataSource);

        //2.调用方法即可
        //jdbcTemplate.update() DDL DML DCL ...非查询语句
        //jdbcTemplate.queryForObject() DQL 查询单个对象
        //jdbcTemplate.query() DQL查询集合
    }



    //通过ioc容器读取配置的JdbcTemplate组件
    @Test
    public void testForIoC()
    {
        //1.创建ioc容器
        ApplicationContext applicationContext=new ClassPathXmlApplicationContext("spring-01.xml");
        //2.获取jdbcTemplate组件
        JdbcTemplate jdbcTemplate=applicationContext.getBean(JdbcTemplate.class);

        //3.进行数据库的curd动作增删改查
        //3.1插入 删除和修改DML updata
        String sql="insert into students(id,name,gender,age,class) values(?,?,?,?,?)";
        //参数1：String sql可以带占位符？ ？只能替代值 不能替代关键字和容器名
        //参数二：Object...param 传入占位符的值 顺序 从左开始对象
        //返回值：int 影响函数

        int rows=jdbcTemplate.update(sql,9,"二狗子","男",18,"三年二班");
        System.out.println("rows="+rows);

        //3.2查询单条数据
        //根据id查询学生数据 返回一个对应的实体对象
        sql="select* from students where id=?;";
        /*
        参数一：sql语句 可以使用?
        参数二：RowMapper 列名很多属性名的映射器接口
        参数三：Object...param 可以变参数 占位符的值
        返回值：rowMapper指定的对象
         */
        Student student1 = jdbcTemplate.queryForObject(sql, new RowMapper<Student>() {

            @Override
            public Student mapRow(ResultSet rs, int rowNum) throws SQLException {
                //rs结果集
                //rowNum 行数
                //rs结果集中获取列的值 赋值给实体类对象即可.
                Student student = new Student();
                student.setId(rs.getInt("id"));
                student.setName(rs.getString("name"));
                student.setGender(rs.getString("gender"));
                student.setAge(rs.getInt("age"));
                student.setClasses(rs.getString("class"));
                return student;


            }
        }, 1);
        System.out.println("student1 = " + student1);

        //3.3查询所有学生的数据
        sql="select id,name,gender,age,class as classes from students;";

        //TODO:BeanPropertyRowMapper帮助我们自动映射列和属性值！要求列名和属性名一致！不一致 起别名！
        List<Student> studentList=jdbcTemplate.query(sql,new BeanPropertyRowMapper<Student>(Student.class));
        System.out.println("studentList="+ studentList);

    }
}

```

5.三层架构搭建和实现

![image-20231105182327996](C:\Users\dyj\AppData\Roaming\Typora\typora-user-images\image-20231105182327996.png)

a.持久层

```java
package org.example.dao;

import org.example.pojo.Student;

import java.util.List;

public interface StudentDao {
    //查询全部学生数据
    List<Student> queryAll();
}

```

```java
package org.example.dao.impl;

import org.example.dao.StudentDao;
import org.example.pojo.Student;
import org.springframework.jdbc.core.BeanPropertyRowMapper;
import org.springframework.jdbc.core.JdbcOperations;
import org.springframework.jdbc.core.JdbcTemplate;

import java.util.List;

public class StudentDaoImpl implements StudentDao {
    private JdbcTemplate jdbcTemplate;
    //注入我们的jdbcTemplate对象
    public void setJdbcTemplate(JdbcTemplate jdbcTemplate)
    {
        this.jdbcTemplate=jdbcTemplate;
    }

    //查询全部学生数据

    @Override
    public List<Student> queryAll() {
        String sql="select id,name,age,gender,class as classes from students;";

        //query可以返回集合！
        //BeanPropertyRowMapper就是封装好RowMapper的实现，要求属性名和列名相同即可‘
        List<Student> studentList=jdbcTemplate.query(sql,new BeanPropertyRowMapper<>(Student.class));

        return studentList;
    }
}

```

b.业务层

```java
package org.example.service;

import org.example.pojo.Student;

import java.util.List;

public interface StudentService {
    //查询全部学员业务
    List<Student> findAll();
}

```

```java
package org.example.service.impl;

import org.example.dao.StudentDao;
import org.example.pojo.Student;
import org.example.service.StudentService;

import java.util.List;

public class StudentServiceImpl implements StudentService {

    private StudentDao studentDao;
    public void setStudentDao(StudentDao studentDao)
    {
        this.studentDao=studentDao;
    }
    //查询全部学员业务
    @Override
    public List<Student> findAll() {
        List<Student> studentList=studentDao.queryAll();
        return studentList;
    }
}

```

c.表述层

```java
package org.example.controller;

import org.example.pojo.Student;
import org.example.service.StudentService;

import java.util.List;

public class StudentController {
    private StudentService studentService;
    public void setStudentService(StudentService studentService)
    {
        this.studentService=studentService;
    }
    public void findAll()
    {
        List<Student> studentList=studentService.findAll();
        System.out.println("studentList="+studentList);
    }
}

```

6.三层架构IoC配置

```xml
<!--spring-02.xml-->
<?xml version="1.0" encoding="UTF-8"?>
<beans xmlns="http://www.springframework.org/schema/beans"
       xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
       xmlns:context="http://www.springframework.org/schema/context"
       xsi:schemaLocation="http://www.springframework.org/schema/beans http://www.springframework.org/schema/beans/spring-beans.xsd http://www.springframework.org/schema/context https://www.springframework.org/schema/context/spring-context.xsd">

    <!--导入外部属性文件-->
    <context:property-placeholder location="classpath:jdbc.properties"/>
    <!--配置数据源-->
    <bean id="druidDataSource" class="com.alibaba.druid.pool.DruidDataSource">
        <property name="url" value="${atguigu.url}"/>
        <property name="driverClassName" value="${atguigu.driver}"/>
        <property name="username" value="${atguigu.username}"/>
        <property name="password" value="${atguigu.password}"/>
    </bean>

    <!--配置JdbcTemplate-->
    <bean id="jdbcTemplate" class="org.springframework.jdbc.core.JdbcTemplate">
        <!--装配数据源-->
        <property name="dataSource" ref="druidDataSource"/>
    </bean>

    <bean id="studentDao" class="org.example.dao.impl.StudentDaoImpl">
        <property name="jdbcTemplate" ref="jdbcTemplate"/>
    </bean>

    <bean id="studentService" class="org.example.service.impl.StudentServiceImpl">
        <property name="studentDao" ref="studentDao"/>
    </bean>

    <bean id="studentController" class="org.example.controller.StudentController">
        <property name="studentService" ref="studentService"/>
    </bean>
</beans>
```

7.运行测试

```java

public class JdbcTemplateTest {//从ioc容器中获取controller并且调用业务！内部都是ioc容器进行组装
    @Test
    public void testQueryAll()
    {
        //创建ioc容器
        ClassPathXmlApplicationContext applicationContext=new ClassPathXmlApplicationContext("spring-02.xml");
        //获取组件对象
        StudentController studentController=applicationContext.getBean(StudentController.class);
        //使用组件对象
        studentController.findAll();
        //关闭容器
       // applicationContext.close();
    }
    }
```

```
运行结果

studentList=[Student{id=1, name='张三', gender='男', age=20, classes='高中一班'}, Student{id=2, name='李四', gender='男', age=19, classes='高中二班'}, Student{id=3, name='王五', gender='女', age=18, classes='高中一班'}, Student{id=4, name='赵六', gender='女', age=20, classes='高中三班'}, Student{id=5, name='刘七', gender='男', age=19, classes='高中二班'}, Student{id=6, name='陈八', gender='女', age=18, classes='高中一班'}, Student{id=7, name='杨九', gender='男', age=20, classes='高中三班'}, Student{id=8, name='吴十', gender='男', age=19, classes='高中二班'}, Student{id=9, name='二狗子', gender='男', age=18, classes='三年二班'}]
```

8.XMLIoC方式问题总结

<font color=red>a.注入的属性必须添加setter方法，代码结构混乱</font>

<font color=red>b.配置文件和Java代码分离，编写不是很方便</font>

<font color=red>c.XML配置文件解析效率低</font>

### 3.基于注解方式管理Bean

#### 3.1实验一：Bean注解标记和扫描（IoC)

**注解理解**

和 XML 配置文件一样，注解本身并不能执行，注解本身仅仅只是做一个标记，具体的功能是框架检测到注解标记的位置，然后针对这个位置按照注解标记的功能来执行具体操作。

本质上：所有一切的操作都是 Java 代码来完成的，XML 和注解只是告诉框架中的 Java 代码如何执行。

**扫描理解**

Spring 为了知道程序员在哪些地方标记了什么注解，就需要通过扫描的方式，来进行检测。然后根据注解进行后续操作。

**准备Spring项目和组件**

a.准备项目pom.xml

```xml
<dependencies>
    <!--spring context依赖-->
    <!--当你引入Spring Context依赖之后，表示将Spring的基础依赖引入了-->
    <dependency>
        <groupId>org.springframework</groupId>
        <artifactId>spring-context</artifactId>
        <version>6.0.6</version>
    </dependency>

    <!--junit5测试-->
    <dependency>
        <groupId>org.junit.jupiter</groupId>
        <artifactId>junit-jupiter-api</artifactId>
        <version>5.3.1</version>
    </dependency>
</dependencies>
```

b.准备组件类

普通组件

```Java
/**
 * projectName: com.atguigu.components
 *
 * description: 普通的组件
 */
public class CommonComponent {
}

```

Controller组件

```Java
/**
 * projectName: com.atguigu.components
 *
 * description: controller类型组件
 */
public class XxxController {
}

```

Service组件

```Java
/**
 * projectName: com.atguigu.components
 *
 * description: service类型组件
 */
public class XxxService {
}

```

Dao组件

```Java
/**
 * projectName: com.atguigu.components
 *
 * description: dao类型组件
 */
public class XxxDao {
}

```

**组件添加标记注解**

1. 组件标记注解和区别

    Spring 提供了以下多个注解，这些注解可以直接标注在 Java 类上，将它们定义成 Spring Bean。

| 注解        | 说明                                                         |
| ----------- | ------------------------------------------------------------ |
| @Component  | 该注解用于描述 Spring 中的 Bean，它是一个泛化的概念，仅仅表示容器中的一个组件（Bean），并且可以作用在应用的任何层次，例如 Service 层、Dao 层等。 使用时只需将该注解标注在相应类上即可。 |
| @Repository | 该注解用于将数据访问层（Dao 层）的类标识为 Spring 中的 Bean，其功能与 @Component 相同。 |
| @Service    | 该注解通常作用在业务层（Service 层），用于将业务层的类标识为 Spring 中的 Bean，其功能与 @Component 相同。 |
| @Controller | 该注解通常作用在控制层（如SpringMVC 的 Controller），用于将控制层的类标识为 Spring 中的 Bean，其功能与 @Component 相同。 |

![img](https://api.wolai.com/v1/proxy/image?src=http%3A%2F%2Fheavy_code_industry.gitee.io%2Fcode_heavy_industry%2Fassets%2Fimg%2Fimg017.93fb56c5.png&spaceId=fqkGyHKKxSnzkhVZnoSxhC&userId=&image_process=resize,w_1130)

​    通过查看源码我们得知，@Controller、@Service、@Repository这三个注解只是在@Component注解的基础上起了三个新的名字。

​    对于Spring使用IOC容器管理这些组件来说没有区别，也就是语法层面没有区别。所以@Controller、@Service、@Repository这三个注解只是给开发人员看的，让我们能够便于分辨组件的作用。

​    注意：虽然它们本质上一样，但是为了代码的可读性、程序结构严谨！我们肯定不能随便胡乱标记。
2. 使用注解标记

    普通组件

```Java
/**
 * projectName: com.atguigu.components
 *
 * description: 普通的组件
 */
@Component
public class CommonComponent {
}

```

​    Controller组件

```Java
/**
 * projectName: com.atguigu.components
 *
 * description: controller类型组件
 */
@Controller
public class XxxController {
}

```

​    Service组件

```Java
/**
 * projectName: com.atguigu.components
 *
 * description: service类型组件
 */
@Service
public class XxxService {
}

```

​    Dao组件

```Java
/**
 * projectName: com.atguigu.components
 *
 * description: dao类型组件
 */
@Repository
public class XxxDao {
}

```
2. **配置文件确定扫描范围**

    情况1：基本扫描配置

```XML
<?xml version="1.0" encoding="UTF-8"?>
<beans xmlns="http://www.springframework.org/schema/beans"
       xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
       xmlns:context="http://www.springframework.org/schema/context"
       xsi:schemaLocation="http://www.springframework.org/schema/beans http://www.springframework.org/schema/beans/spring-beans.xsd http://www.springframework.org/schema/context https://www.springframework.org/schema/context/spring-context.xsd">
    <!-- 配置自动扫描的包 -->
    <!-- 1.包要精准,提高性能!
         2.会扫描指定的包和子包内容
         3.多个包可以使用,分割 例如: com.atguigu.controller,com.atguigu.service等
    -->
    <context:component-scan base-package="com.atguigu.components"/>
  
</beans>
```

情况2：指定排除组件

```XML
<!-- 情况三：指定不扫描的组件 -->
<context:component-scan base-package="com.atguigu.components">
    
    <!-- context:exclude-filter标签：指定排除规则 -->
    <!-- type属性：指定根据什么来进行排除，annotation取值表示根据注解来排除 -->
    <!-- expression属性：指定排除规则的表达式，对于注解来说指定全类名即可 -->
    <context:exclude-filter type="annotation" expression="org.springframework.stereotype.Controller"/>
</context:component-scan>
```

情况3：指定扫描组件

```XML
<!-- 情况四：仅扫描指定的组件 -->
<!-- 仅扫描 = 关闭默认规则 + 追加规则 -->
<!-- use-default-filters属性：取值false表示关闭默认扫描规则 -->
<context:component-scan base-package="com.atguigu.ioc.components" use-default-filters="false">
    
    <!-- context:include-filter标签：指定在原有扫描规则的基础上追加的规则 -->
    <context:include-filter type="annotation" expression="org.springframework.stereotype.Controller"/>
</context:component-scan>
```
3. **组件BeanName问题**

    在我们使用 XML 方式管理 bean 的时候，每个 bean 都有一个唯一标识——id 属性的值，便于在其他地方引用。现在使用注解后，每个组件仍然应该有一个唯一标识。

    默认情况：

    类名首字母小写就是 bean 的 id。例如：SoldierController 类对应的 bean 的 id 就是 soldierController。

    使用value属性指定：

```Java
@Controller(value = "tianDog")
public class SoldierController {
}
```

    当注解中只设置一个属性时，value属性的属性名可以省略：

```Java
@Service("smallDog")
public class SoldierService {
}
```
4. **总结**
    1. 注解方式IoC只是标记哪些类要被Spring管理
    2. 最终，我们还需要XML方式或者后面讲解Java配置类方式指定注解生效的包
    3. **现阶段配置方式为 注解 （标记）+ XML（扫描）**

#### 3.2实验二：组件（Bean)作用域和周期方法注解

周期方法声明和作用域配置

```java
@Scope(scopeName = ConfigurableBeanFactory.SCOPE_SINGLETON) //单例,默认值
@Scope(scopeName = ConfigurableBeanFactory.SCOPE_PROTOTYPE) //多例  二选一
public class JavaBean{
    //周期方法要求:方法命名随意，但是要求方法必须是public void 无形参列表
    @PostConstruct//注解指定初始化方法
    public void init()
    {
        //初始化逻辑
    }
    
    @PreDestory//注解指定销毁方法
    public void clear(){
        //释放资源逻辑
    }
}
```

