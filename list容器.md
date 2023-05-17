# list容器

## list基本概念

功能：将数据进行链式存储

链表(list)：是一种物理存储单元上非连续的存储结构，数据元素的逻辑顺序是通过链表中的指针链接来实现的。

链表的组成：链表由一系列结点组成。

结点的组成：一个是存储数据元素的数据域，另一个是存储下一个结点地址的指针域。

SLT中的链表是一个双向循环链表。

![img](https://img-blog.csdnimg.cn/5645d63777ad4dec916dc8b2ac85212f.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzUxNjA0MzMw,size_16,color_FFFFFF,t_70)

由于链表的存储方式并不是连续的内存空间，因此链表list中的迭代器只支持前移和后移，属于双向迭代器。

list的优点:

采用动态存储分配，不会造成内存浪费和溢出
链表执行插入和删除操作十分方便，修改指针即可，不需要移动大量元素
list的缺点:

链表灵活，但是空间(指针域)和时间(遍历)额外耗费较大。

list有一个重要的性质，插入操作和删除操作都不会造成原有list迭代器的失效，这在vector是不成立的。

总结：
STL中List和vector是两个最常用的容器，各有优缺点。

## list构造函数

```c++
#include <iostream>
using namespace std;
#include <list>

// list容器构造函数
void printList(const list<int> &L)
{
    for (list<int>::const_iterator it = L.begin(); it != L.end(); it++)
    {
        cout << *it << " ";
    }
    cout << endl;
}

void test01()
{
    // 创建list容器
    list<int> L1; // 默认构造

    // 添加数据,尾插法
    L1.push_back(10);
    L1.push_back(20);
    L1.push_back(30);
    L1.push_back(40);

    // 遍历容器
    printList(L1);

    // 区间方式构造
    list<int> L2(L1.begin(), L1.end());
    printList(L2);

    // 拷贝构造
    list<int> L3(L2);
    printList(L3);

    // n个elem
    list<int> L4(10, 1000);
    printList(L4);
}

int main()
{
    test01();

    return 0;
}
```

## list赋值和交换

```c++
 #include<iostream>
#include<list>
using namespace std;
void PrintList(const list<int>& L)
{
	for (list<int>::const_iterator it = L.begin(); it != L.end(); it++)
	{
		cout << *it << " ";
	}
	cout << endl;
}
void test01()
{
	list<int>l1;

	l1.push_back(1);
	l1.push_back(2);
	l1.push_back(3);
	l1.push_back(4);
	PrintList(l1);

	list<int>l2;
	l2 = l1;//operator=
	PrintList(l2);

	list<int>l3;
	l3.assign(l2.begin(), l2.end());
	PrintList(l3);

	list<int>l4;
	l4.assign(10, 100);
	PrintList(l4);

}
void test02()
{
	list<int>l5;

	l5.push_back(1);
	l5.push_back(2);
	l5.push_back(3);
	l5.push_back(4);

	list<int>l6;
	l6.push_back(4);
	l6.push_back(3);
	l6.push_back(2);
	l6.push_back(1);
	cout << "交换前" << endl;
	PrintList(l5);
	PrintList(l6);

	l5.swap(l6);
	cout << "交换后" << endl;
	PrintList(l5);
	PrintList(l6);
}
int main(void)
{
	test01();
	test02();
	return 0;
}


```

## List大小操作

```
size();//返回容器中元素的个数
empty();//判断容器是否为空
resize(num);//重新指定容器的长度num，若容器变长，则以默认值填充新位置
//如果容器变短，则末尾超出容器长度的元素被删除
resize(num,elem);//重新指定容器的长度num，若容器变长，则以elem值填充新位置
//如果容器变短，则末尾超出容器长度的元素被删除
```



```c++
#include<iostream>
#include<list>
using namespace std;
void PrintList(const list<int>& L)
{
	for (list<int>::const_iterator it = L.begin(); it != L.end(); it++)
	{
		cout << *it << " ";
	}
	cout << endl;
}
void test01()
{
	list<int>l1;
	l1.push_back(1);
	l1.push_back(2);
	l1.push_back(3);
	l1.push_back(4);
	
	PrintList(l1);

	if (l1.empty())
	{
		cout << "空" << endl;
	}
	else
	{
		cout << "不空" << endl;
		cout << "元素个数=" << l1.size()<<endl;
	}
	
	//重新指定大小
	l1.resize(10, 1000);
	PrintList(l1);
}
int main(void)
{
	test01();
	return 0;
}


```

## List插入和删除

```c++
#include<iostream>
#include<list>
using namespace std;
void PrintList(const list<int>& L)
{
	for (list<int>::const_iterator it = L.begin(); it != L.end(); it++)
	{
		cout << *it << " ";
	}
	cout << endl;
}
void test01()
{
	list<int>l1;
	//尾插
	l1.push_back(10);
	l1.push_back(20);
	l1.push_back(30);
	//头插
	l1.push_front(100);
	l1.push_front(200);
	l1.push_front(300);
    //300 200 100 10 20 30
	PrintList(l1);

	//尾删
	l1.pop_back();
    //300 200 100 10 20 
	PrintList(l1);
    //头删
	l1.pop_front();
    //200 100 10 20 
	PrintList(l1);

	//insert插入
	list<int>::iterator it = l1.begin();
	it++;
	l1.insert(it, 1000);//括号里面是迭代器
    //L1.insert(L.begin(),1000)
    //1000 200 100 10 20 
    //200  1000 100 10 20 
	PrintList(l1);

	//删除
	//用的时候指定it
	it = l1.begin();
	l1.erase(++it);
    //200 100 10 20 
	PrintList(l1);

	//移除
	l1.push_back(10000);
	l1.push_back(10000);
	l1.push_back(10000);
     //200 100 10 20 10000 10000 10000
	PrintList(l1);
	l1.remove(1000);//删除所有匹配的元素
    //200 100 10 20 
	PrintList(l1);


	//清空
	l1.clear();
    //      ;
	PrintList(l1);
}

int main(void)
{
	test01();

	return 0;
}


```

## list数据存取

功能描述：对list容器中数据进行存取

```
front();//返回第一个元素
back();//返回最后一个元素
```

```c++
#include<iostream>
#include<list>
using namespace std;
void PrintList(const list<int>& L)
{
	for (list<int>::const_iterator it = L.begin(); it != L.end(); it++)
	{
		cout << *it << " ";
	}
	cout << endl;
}
void test01()
{
	list<int>l1;
	l1.push_back(1);
	l1.push_back(2);
	l1.push_back(3);
	l1.push_back(4);

	//list中不可以用[]访问容器中的元素
	//at()也不行
	//因为List本质是链表，不是用连续的线性空间存储数据，迭代器也是不支持随机访问的

	cout << "第一个元素=" << l1.front() << endl;
	cout << "最后一个元素=" << l1.back() << endl;

	//验证迭代器是不支持随机访问的
	list<int>::iterator it = l1.begin();
	it++;//支持++ --  双向
	it--;
	//it = it+1;不行——不支持随机访问

}
int main(void)
{
	test01();
	return 0;
}


```

## list反转和排序

功能描述：将容器中的元素反转，以及将容器中的数据进行排序

函数原型：

```
reserve();//反转链表
sort();//链表排序
```

```c++
#include<iostream>
#include<list>
#include<algorithm>
using namespace std;
void PrintList(const list<int>& L)
{
	for (list<int>::const_iterator it = L.begin(); it != L.end(); it++)
	{
		cout << *it << " ";
	}
	cout << endl;
}
void test01()
{
	list<int>l1;
	l1.push_back(1);
	l1.push_back(2);
	l1.push_back(3);
	l1.push_back(4);
	
	cout << "反转前" << endl;
	PrintList(l1);

	//反转
	cout << "反转后" << endl;
	l1.reverse();
	PrintList(l1);
}

bool myCompare(int v1, int v2)
{
	//降序 第一个数>第二个数
	return v1 > v2;
}

//排序
void test02()
{
	list<int>l2;
	l2.push_back(20);
	l2.push_back(10);
	l2.push_back(50);
	l2.push_back(30);
	l2.push_back(40);
	cout << "排序前" << endl;
	PrintList(l2);

	//所有不支持随机访问迭代器的容器不可以用标准算法
	//不支持随机访问迭代器的容器，内部会提供对应的一些算法

	cout << "排序后" << endl;
	l2.sort();
	PrintList(l2);

	l2.sort(myCompare);//降序
	PrintList(l2);
}
int main(void)
{
	test01();
	test02();

	return 0;
}


```

