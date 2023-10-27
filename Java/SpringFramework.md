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



