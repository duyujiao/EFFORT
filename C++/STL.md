## STL初识

### STL的诞生

长久以来，软件界一直希望建立一种可重复利用的东西

C++的面向对象和泛型编程思想，目的就是复用性的提升

大多情况下，数据结构和算法都未能有一套标准，导致被迫从事大量重复工作

为了建立数据结构和算法的一套标准，诞生了STL

### STL基本概念

STL（Standard Template Library，标准模板库）

STL从广义上分为：容器，算法，迭代器

容器和算法之间通过迭代器进行无缝衔接

STL几乎所有的代码都采用了模板类或者模板函数

### STL六大组件

1、容器（containers）
容器用来存放数据，包括各种数据结构，如vector，list，deque，set，map等。从实现的角度来看，STL容器是一种class template。

2、算法（algorithms）
算法包括各种常用的sort，search，copy，erase， find等等。才实现的角度来看，STL算法是一种function template。

3、迭代器（iterators）
迭代器作为“泛型指针”，扮演容器和算法之间的粘合剂，用来连接容器和算法。从实现角度来看，迭代器是一种将operator*，operator->，operator++，operator--等指针相关操作进行重载的class template。所有的STL容器都带有自己专属的迭代器。原生指针也是一种迭代器。

所谓的原生指针就是我们定义的最普通的指针，形如  类型名  *指针名，类型名可以是基础类型int，double等，也可以是一个类。

当一个类将*和->操作符进行重载时，虽然也可以进行类似指针的操作，但是它已经不是原生指针。

4、仿函数（functors）
仿函数是让一个类看起来像一个函数。其实就是一种重载了operator（）的class或者class template。

5、配接器（adapters）
一种用来修饰容器，仿函数或者迭代器的接口的东西。配接器修改类的接口，使原来不相互匹配的两个类可以相互匹配，进行合作。

6、配置器（allocators）
配置器主要负责空间的配置和管理。从实现角度来看，配置器是一个实现了动态空间配置、空间管理、空间释放的class template

