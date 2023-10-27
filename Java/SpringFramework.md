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

