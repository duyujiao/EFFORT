```c++
#include <iostream>
using namespace std;
    //1.new的基本语法
int*func()
{
    //在堆区创建整形数据
    //new返回是该数据类型的指针
    int*p=new int(10);//相当于这块内存中存放了数据10；只开辟了一个变量，存放的是10
    return p;

}
void test01()
{
    int*p=func();
    cout<<*p<<endl;
    cout<<*p<<endl;
    cout<<*p<<endl;
    //堆区的数据由程序员开辟，程序员管理释放如果想释放堆区的数据，利用关键字delete
    delete p;
    //cout<<*p<<endl;//内存已经被释放，再次访问就是非法访问，回报错
}
    //2.在堆区利用new开辟数组
void test02()
{
    //创建10个整形数据的数组，在堆区
    int*arr=new int[10];//10代表数组有十个元素
    for(int i=0;i<10;i++)
    {
        arr[i]=i+100;//给十个元素赋值100～109
    }
    for(int i=0;i<10;i++)
    {
        cout<<arr[i]<<endl;
    }
    //释放堆区数组
    //释放数组的时候，要加[]才行
    delete[] arr;
}
int main(){
    test02();
    system("pause");
    return 0;
}
```

