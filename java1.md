# java语法  
## 1.自动类型转换 
·**类型范围小**的变量，可以**直接**赋值给**类型范围大**的
```java
byte a=12;//8位
int b=a;//32位,发生了自动类型转换
System.out.println(b);//12
```
自动类型转换的其他形式：  
byte->short->int->long->float->double(char->int)  
## 2.表达式的自动类型转换  
在表达式中，小范围类型的变量，会自动转换成表达式中较大范围。 
表达式的最终结果类型由表达式中的最高类型决定
在表达式中，byte，short，char是直接转换成int类型参与运算  
## 强制类型转换  
强行将类型范围**大**的赋值给范围**小**的  
数据类型 变量2=（数据类型）变量1、数据
```java
int a=20;
byte b=(byte)a;
```
强制类型转换可能会造成数据丢失（溢出）  
浮点型强转成整形，直接丢掉小数部分，保留整数部分返回 
# Java方法
## 方法概述
方法是一种语法结构，可以把一段代码封装成一个功能，以便重复调用。

`
修饰符 返回值类型 方法名（形参列表）{  
    方法体代码（需要执行的功能代码）  
    return 返回值；  
}
`
```java
int rs=sum(10,20);
public static int sum(int a,int b)
{
    int c=a+b;
    return c;
}
```
方法的修饰符：暂时都使用public static修饰     
方法申请了具体的返回值类型，内部必须使用return返回对应类型的数据  
形参列表可以有多个或者没有，如果有多个形参，多个形参要用“，”隔开，且不呢个给初始化值  
## 方法的其他形式
```java
public static void printhello()
{
    "打印输出内容"
}
```
## 方法案例
```java
public class Main {
    public static void main(String[] args) {
    //目标：掌握设计方法的技巧
        int rs=add(5);
        System.out.println("1-5的和是：" + rs);//10

    }
    public static int add(int n)
    {
        int sum=0;
        for (int i = 0; i <= n; i++) {
            sum+=i;
        }
        return sum;
    }
}
```
## 方法在计算机中的执行原理
1.方法的运行区域在栈内存中，先进后出  
2.保证一个方法调用完另一个方法后，可以回来
## 方法参数传递  
基本类型和引用类型的参数在传递的时候都是值传递  
基本类型的参数传输存储的**数据值**  
引用类型的参数传输存储的**地址值**  
## 方法重载
1.一个类中，只要一些方法的名称相同，形参列表不同，那他们就是方法重载喽！（修饰符，返回值类型是否一样都无所谓）
2.形参列表不同指的是:形参的个数、类型、顺序不同，不关心形参的名称
## return关键字在方法中单独使用  
return;可以用在无返回值的方法中，作用是:立即跳出并结束当前方法的执行 
1.return;跳出并立即结束所在方法的执行  
2.break;跳出并结束当前所在循环的执行  
3.continue; 结束当前所在循环的当次继续，进入下一次执行  

# 案例
案例1
```java
public class exercise {
    public static void main(String[] args) {
        //买飞机票的案例
        double price=calculate(1000,11,"头等舱");
        System.out.println("优惠后的价格是："+price);

    }
    public static double calculate(double price,int month,String type)
    {
        if(month>=5&&month<=10)//旺季
        {
            switch(type)
            {
                case "头等舱":
                    price*=0.9;
                    break;
                case "经济舱":
                    price*=0.85;
                    break;
            }
        }
        else {
            //淡季
            switch(type) {
                case "头等舱":
                    price *= 0.8;
                    break;
                case "经济舱":
                    price *= 0.75;
                    break;
            }
        }
        return price;
    }
}
```
案例2
```java
import java.util.Random;

public class exercise {
    public static void main(String[] args) {
        System.out.println(createcode(5));


    }
    public static String createcode(int n) {
        //1.定义一个for循环用于控制产生多少位随机字符
        Random r=new Random();
        //定义一个String类型的变量用于记住产生的每位随机字符
        String code="";
        for(int i=1;i<=n;i++)
        {
            //为每个位置生成一个随机字符，可能是数字，大小写字母
            //思路：随机一个0 1 2之间的数字出来，0代表随机一个数字字符，1大写字符，2小写字符
            int type=r.nextInt(3);//0 1 2
            switch(type)
            {
                case 0:
                    //随机一个数字字符
                    code+=r.nextInt(10);
                    break;
                case 1:
                    //随机一个大写字符
                    //A 65   Z 65+25   (0~25)+65
                    char ch1=(char)(r.nextInt(26)+65);
                    code+=ch1;
                    break;
                case 2:
                    //随机一个小写字符
                    //a 97   z=97+25   （0~25）+97
                    char ch2=(char)(r.nextInt(26)+97);
                    code+=ch2;
                    break;
            }
        }
        return code;

    }
}
```
# 面向对象
## 入门
开发一个一个对象，把数据交给对象，再调用对象的方法来完成对数据的处理  
```java
//Student.java文件
public class Student {
    String name;
    double chinese;
    double math;
    public void printTotalScore()
    {
        System.out.println(name+"同学的各科总分是："+(chinese+math));
    }
    public void printAverageScore()
    {
        System.out.println(name+"同学的各科平均成绩："+(chinese+math)/2.0);
    }
}
//Test.java文件
public class Test {
    public static void main(String[] args) {
        Student s1=new Student();
        s1.name="谢明志";
        s1.chinese=0;
        s1.math=0;
        s1.printTotalScore();;
        s1.printAverageScore();

        Student s2=new Student();
        s1.name="杜玉娇";
        s1.chinese=100;
        s1.math=100;
        s1.printTotalScore();;
        s1.printAverageScore();

    }
}
```
那程序中的对象到底是个啥呢？
对象本质上是一种特殊的数据结构。
s1就相当于s1的学生表；s2就相当于s2的学生表
class也就是类，也称为对象的设计图（或者对象的模板）
## 对象在计算机中的执行原理
1.Student s1=new Student();  
2.每次new Student(),就是在堆内存中开辟一块内存区域代表一个学生对象  
3.s1变量里面记住的是学生对象的地址  
## 类和对象使用注意事项
目标: 掌握类与对象的一些注意事项。
1、类名建议用英文单词，**首**字母**大写**，满足驼峰模式，且要有意义，比如: Student、Car.
2、类中定义的变量也称为**成员变量**(对象的属性)，类中定义的方法也称为成员方法(对象的行为).
3、成员变量本身存在**默认值**，同学们在定义成员变量时一般来说不需要赋初始值(没有意义)。
4、一个代码文件中，可以写**多个cLass类**,但只能**一个用public** 修饰，且public修饰的类名必须成为代码文件名。  
5、对象与对象之间的数据不会相互影响，但多个变量指向同一个对象时就会相互影响了。   
```java
Student s1=new Student();
s1.name="张三";
//把s1变量中存储的学生对象的地址赋值给了s2变量
Student s2=s1;
s2.name="李四";
System.out.println(s1.name);//李四
```
 6、如果某个对象没有一个变量引用它，则该对象无法被操作了，该对象会成为所谓的垃圾对象。  
 ## this关键字
 1.this关键字就是一个变量，可以用在方法中，用来拿到当前对象，哪个对象调用方法，this就指向哪个对象，也就是拿到哪个对象  
 2.this关键字在实际开发中常用来**解决对象的成员变量与方法内部变量的名称**，导致访问冲突  
 ```java
 public class Test
 {
    public static void main(String[] args)
    {
        Student s1=new Student();
        System.out.println(s1);
        s1.printThis();

        System.out.println("---------------");
        Student s2=new Student();
        System.out.println(s2);
        s2.printThis();

        Student s3=new Student();
        s3.score=325;
        s3.printPass(250);
    }
 }
 public class Student
 {
    double score;
    public void printThis()
    {
        System.out.println(this);
    }

    public void printPass(double score)
    {
        if(this.score > score){
        System.out.println("恭喜您，您成功考入了哈佛大学了~~");
        }
        else {
        System.out.println("落选了~");
        }
    }
 }
```
## 构造器
1.构造器是什么样子的？（相当于c++中的构造函数）
```java
public class Student
{
    //构造器
    //无参构造器
    public Student()
    {
         ···
    }
    //有参构造器
    public Student(String name,double score)
    {

    }
}
```
2.构造器有什么特点？  
创建对象时，对象会去调用构造器  
`Student s=new Student();`   
3.构造器的常见应用场景  
创建对象时，同时完成对对象成员变量（属性）的初始化赋值
```java
//Test.java文件
Student s2=new Student("小谢",19);
System.out.println(s2.name);
System.out.println(s2.score);

//Student.java文件
public class Student
{
    String name;
    double score;
    //无参构造器
    public Student()
    {
        System.out.println("无参构造器执行");
    }
    public Student(String name,double score)
    {
        System.out.println("有参构造器执行");
        this.name=name;
        this.score=score;
    }
}
```
**注意事项**   
1.类在设计时，如果不写构造器，Java会为类自动生成一个无参构造器的  
2.一旦定义了有参构造器，Java就不会帮我们的类生成无参构造器了，此时就建议自己手写一个无参构造器出来了
## 封装
1.封装就是用类设计对象处理某一个事务的数据时候，应该把要处理的数据以及处理数据的方法涉及到一个对象中去  
2.封装的设计规范是合理隐藏，合理暴露  
3.代码层面如何控制对象的成员公开或者隐藏？  
公开成员，用public进行修饰           
隐藏成员，使用private进行修饰   
## 实体类 JavaBean  
什么是实体类？  
1.必须私有成员变量，并为每个成员变量都提供get set方法  
2.必须为类提供一个公开无参构造器  
3.实体类仅仅是用来**存取数据**的 
实体类有啥应用场景？  
数据和数据的业务处理相分离

```java
//Student.java文件
public class Student {
    //1.必须私有成员变量，并为每个成员变量都提供get set方法，
    //这里右击点生成，注意一定要把光标放在类里面
    private String name;
    private double score;
    //2.必须为类提供一个公开无参构造器
    public Student() {
    }

    public Student(String name, double score) {
        this.name = name;
        this.score = score;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public double getScore() {
        return score;
    }

    public void setScore(double score) {
        this.score = score;
    }


}
//Test.java文件
public class Test {
    public static void main(String[] args) {
        Student s1=new Student();
        s1.setName("波妞");
        s1.setScore(99);
        System.out.println(s1.getName());//波妞
        System.out.println(s1.getScore());//99.0
    }
}
```
## 成员变量和局部变量
public class Test {
public static void main(String[] args) {  
// 目标:搞清楚成员变量和局部变量的区别  
// 1、类中位置不同: 成员变量(类中，方法外)、 局部变量(常见于方法中)int a = 20;  
// 2、初始化值不同: 成员变量(有默认值，不需要初始化赋值)，局部变量(没有默认值，使用之前必须完成赋值)int b = 20;
System.out.printin(b);   
// 3、内存位置不同:成员变量(存在于堆内存)，局部变量(栈内存)  
// 4、作用域不同: 成员变量(整个对象)，局部变量(在所归属的大括号中)String name ="黑马";     
// 5、生命周期不同: 成员变量 (与对象同生共死)，局部变量(方法调用而生，方法结束而亡)   
}}

# 常用API
## 包
在自己程序中调用其他包下的程序的**注意事项**：  
1.如果当前程序中，要调用自己所在包下的其他程序，可以直接调用。(同一个包下的类，互相可以直接调用)  
2.如果当前程序中，要调用其他包下的程序，则必须在当前程序中导包,才可以访问!导包格式:import 包名.类名；   
3.如果当前程序中，要调用lava提供的程序，也需要先导包才可以使用:但是Java.lang包下的程序是不需要我们导包的，可以直接使用  
4.如果当前程序中，要调用多个不同包下的程序，而这些程序名正好一样，此时默认只能导入一个程序，另一个程序必须带包名访问。
## String
1.String对象的内容不可改变，被称为不可变字符串对象  
2.只要是"···"方式写出的字符串，都会写入字符串常量池，且相同的内容字符串只会存储一份  
3.且通过new方式创建字符串对象，每new一次都会产生一个新的对象放在堆内存里面  
## ArrayList
## static
static 是静态，可以修饰成员变量，成员方法  
### static修饰成员变量
成员变量按照有无static修饰，分为两种：类变量（有static修饰，属于类，在计算机中只有一份，会被类的全部对象**共享**）和实例变量（对象的变量，无static修饰，属于每个对象的）  
①类变量的用法：  
类名.类变量（推荐）   
```java
Student.name="明志";
```
对象.类变量（不推荐）
```java
Student s1=new Student();
s1.name="明志";
```
②实例对象的用法：  
对象.实例变量
### 类变量的应用场景
在开发中，如果某个数据只需要一份，且希望能够被共享（访问，修改），则该数据可以定义成类变量来记住    
**案例导学**
```java
public class User
{
    //类变量
    public static int number;

    //构造器
    public User()
    {
        //在访问自己类中的类变量时，可以省略类名不写
        //number++;
        User.number++;
    }
}


new User();
new User();
new User();//最后会输出3
```
### static修饰成员方法
1.类方法：有static修饰的成员方法，属于类  
①类方法的用法：
类名.类方法（推荐）  
对象.类方法（不推荐）  
2.实例方法：没有static修饰的成员方法，属于对象  
②实例方法的用法  
对象.实例方法

```java
//类方法
public static void printHelloWorld()
{
    System.out.println("HelloWorld");
}


//实例方法（对象的方法）
public void printHello()
{
    System.out.println("···");
}


//类名.类方法（推荐）
Student.printHelloWorld();

//对象.类方法（不推荐）
Student s=new Student();
s.printHelloWorld();

//实例方法的用法
//对象.实例方法
s.printHello();
```
### static注意事项
1.类方法中可以直接访问类的成员变量，不可以直接访问实例成员  
2.实例方法既可以直接访问类成员，也可以直接访问实例成员   
3.实例方法中可以出现this关键字，类方法中不可以出现this关键字  
### static应用-代码块 
静态代码块：   
格式:static{}  
特点：类加载时自动执行，由于类只会加载一次，所以静态代码块也**只会执行一次**   
作用：完成类的初始化，例如：对类变量的初始化赋值   
实例代码块：  
格式：{}  
特点：每次创建对象的时候，执行实例代码块，并在构造器前执行  
作用：和构造器一样，都是用来完成对象的初始化的，例如:对实例变量进行初始化赋值   
### 单例设计模式
什么时单例设计模式？  
一个问题通常有n种解法，其中肯定有一种解法是最优的，这个最优的解法被人总结出来了，称之为设计模式。设计模式有20多种，对应20多种软件开发中会遇到的问题。  
单例设计模式  
确保一个类只有一个对象  
写法：  
1.必须私有类的构造器  
2.定义一个类变量记住类的一个对象  
3.定义一个类方法用来接受类的对象  
```java
public class Test {
 //2.定义一个类变量记住类的一个对象。类变量只会执行一次哦！
    private static Test t=new Test();

    //1.必须私有类的构造器,外面就不能创建对象了呀
    private Test()
    {

    }
    //3.定义一个类方法返回类的对象
    public static Test getobj()
    {
        return t;
    }
}

Test t=Test.getobj();
```
上面写的代码称为**饿汉式单例**
单例模式的应用场景  
比如：任务管理器对象，获取运行时对象    
下面介绍一下**懒汉式单例**设计模式:  
拿对象时，才开始创建对象   
```java
public class Test {
 //2.定义一个类变量，用来记住类的一个对象
    private static Test t;

    //1.必须私有类的构造器,外面就不能创建对象了呀
    private Test()
    {

    }
    //3.定义一个类方法,保证返回的是同一个对象
    public static Test getobj()
    {
        if(t==null)
        {
            System.out.println("第一次创建对象~");
            t=new Test();
        }
        return t;
    }
}


Test t=Test.getobj();//第一次拿对象
```   
## 继承
### 什么是继承？使用继承的好处
Java中提供了一个关键字**extends**,用这个关键字，可以让一个类和另一个类建立起父子关系    
`public class B extends A{}`  
A类称为父类（基类或超类）  
B类称为子类（派生类）  
**继承的特点**：子类能继承父类的非私有成员（成员变量，成员方法）        
**继承后对象的创建**：子类的对象是由子类，父类共同完成的  
带继承关系的类，java会用 ，这多张设计图来一起创建类的对象。  
对象能直接访问什么成员，是由**子父**类这多张设计图**共同决定的**，这多张设计图**对外暴露**了什么成员（public）,对象就**可以访问**什么成员  
使用继承的**好处**是减少重复代码的编写
### 继承的注意事项-权限修饰符
public，private，protected，缺省就是不写   
访问的范围：  
**public**:在本类中，同一个包下的其他类，任意包下的子类，任意包下的任意类  
**private**:在本类中  
**protected**:在本类中，同一个包下的其他类，任意包下的子类  
**缺省**:在本类中，同一个包下的其他类  
### 单继承,Object,方法重写
目标: 掌握继承的两个注意事项事项   
1、Java是单继承的:一个类只能继承一个直接父类，Java中的类不支持多继承，但是支持**多层继承**。  
2、Object类是Java中所有类的祖宗。
### 子类访问成员变量
子类访问成员变量，遵循就近原则  
先子类局部范围找，然后子类成员范围找，然后父类成员范围找，如果父类范围还没有找到就报错。   
用**this**.name访问子类成员变量，**super**.name访问父类成员变量   
### 子类构造器的特点  
子类的全部构造器，都会先调用父类的构造器，再执行自己  
子类构造器是如何实现调用父类构造器的:  
默认情况下，子类全部构造器的第一行代码都super() (写不写都有) ，它会调用父类的无参数构造器      
如果父类没有无参数构造器，则我们必须在子类构造器的第一行手写super(....)，指定去调用父类的有参数构造器    
this(...)的作用是在构造器中调用本类的其他构造器  
this(...)和super(...)在使用时都必须放在构造器的第一行  
## 多态
什么是多态?  
多态是在<font color=red>继承/实现</font>情况下的一种现象，表现为:对象多态、行为多态。   
多态的具体代码体现 
``` java
People p1 =new Student();
p1.run();//编译看左边，运行看右边，就是编译的时候先找People这个类，然后运行的时候找student()
//细节，对于变量：编译看左边，运行看左边
People P2=new Teacher()
p2.run();
```
多态的前提  
有继承/实现关系;存在父类引用子类对象;存在方法重写  
多态的一个注意事项  
多态是对象、行为的多态，Java中的属性(成员变量)不谈多态   
使用多态的好处  
1.在多态形式下，右边对象是使用解耦合，便于扩展和维护。   
2。可以使用父类类型的变量作为形参，可以接受一切子类对象   
```java
public static void go(People p)
{

}
Student p1 =new Student();
go(p1);
Teacher P2=new Teacher()
go(p2);
```
多态存在的问题：无法直接调用子类的独有功能    
### 多态下的类型转换问题
**类型转换**
自动类型转换:父类 变量名=new 子类()  
例如: `People p= new Teacher();`  
强制类型转换:子类 变量名 =(子类)类变量     
例如 `Teacher t=(Teacher)p;`   
**强制类型转换的一个注意事项 **  
存在继承/实现关系就可以在编译阶段进行强制类型转换，编译阶段不会报错     
运行时，如果发现对象的真实类型与强转后的类型不同，就会报类型转换异常 (ClassCastException) 的错误出来   
强转前建议使用instanceof关键字，判断当前对象的真实类型，再进行强转   
`p instanceof Student`
```java
public static void go(People p)
{
    p.run();
    if(p instanceof Student)
    {
        Student s=(Student)p;
        s.test();
    }
    else if(p instanceof Teacher)
    {
        Teacher t=(Teacher)p;
        t.teach();
    }
}
```
## final
·final 关键字是最终的意思，可以修饰（类，方法，变量）  
·修饰类：该类被称为最终类，特点是不能被继承了  
·修饰方法：该方法被称为最终方法，特点是不能被重写了   
·修饰变量：该变量只能被复制一次   
注意事项：  
final修饰基本类型的变量，变量存储的<font color=red>数据</font>不能被改变  
final修饰引用类型的变量，变量存储的<font color=red>地址</font>不能被改变，但地址所指向对象的内容是可以被改变的     
### 常量
使用了 static final 修饰的成员变量就被称为常量  
作用:通常用于记录系统的配置信息   
```java
public class Constant()
{
    public static final String SCHOOL_NAME="西安邮电大学";

    System.out.println(SCHOOL_NAME)
}
```

注意:  
常量名的命名规范:建议使用大写英文单词，多个单词使用下划线连接起来  
使用常量记录系统配置信息的优势、执行原理:   
·代码可读性更好，可维护性也更好   
·程序编译后，常量会被“宏替换”:出现常量的地方全部会被替换成其记住的字面量这样可以保证使用常量和直接用字面量的性能是一样的。  
## 抽象类
抽象方法：必须用abstract修饰，只有方法签名，一定不能有方法体  
```java
public abstract class A
{
    //只有方法签名，一定不能有方法体  
    public abstract void run();
}
```
抽象类的注意事项、特点:    
抽象类中不一定有抽象方法，有抽象方法的类一定是抽象类  
类该有的成员(成员变量、方法、构造器)抽象类都可以有。  
抽象类最主要的特点:抽象类不能创建对象，仅作为一种特殊的父类，让子类继承并实现。   
个类继承抽象类，必须
重写完抽象类的全部抽象方法，否则这个类也必须定义成抽象类  
### 抽象类的常用应用场景-模板方法设计模式  
```java
我最爱杜玉娇了，杜玉娇是我的心肝宝贝儿呢，你说对不对啊杜玉娇宝贝
//People.java
public abstract class People {
    //设计模板方法设计模式
    //1.定义一个模板方法出来
    public final void write()
    {
        System.out.println("\t\t\t\t《我的爸爸》。");
        System.out.println("\t\t我的爸爸好啊，牛逼啊，来看看我的爸爸。");
        //2.模板方法并不清楚正文部分到底怎么写 ，但是它知道子类肯定要写
        System.out.println(writeMain());
        System.out.println("有这样的爸爸真好");
    }
    //3.设计一个抽象方法写正文，具体的实现交给子类来完成
    //子类重写就行了
    public abstract String writeMain();

}
//Teacher.java
public class Teacher extends People
{
    @Override
    public String writeMain() {
    return"我的爸爸也挺好的，让我站在这里别走，他去买点橘子~~~"
    }
}
//Test.java
public class Test {
   public static void main(String[] args) {
      //目标：搞清楚抽象类的应用场景之一，经常用来设计模板方法设计模式
      //场景：学生，老师都要写一篇作文，我的爸爸
      //第一段是一样的
      //正文部分自由发挥，
      //最后一段也是一样的
      Teacher t=new Teacher;
      t.write();
   }
}
```
建议使用**final关键字**，修饰模板方法  
模板方法是直接给对象使用的，不能给子类重写  
一旦子类方法重写了，模板就失效了  
## 接口
```java
public interface 接口名
{
    //成员变量（常量）
    //成员方法（抽象方法）
}
```
注意：接口不能创建对象(interface后面的不能new)，接口是用来被类实现(implements)的,实现接口的类称为实现类  
`
修饰符 class implements 接口1，接口2，接口3...
{

}
`
一个类可以实现多个接口（接口可以理解成干爹）。实现类实现多个接口，必须重写完全部接口的全部抽象方法，否则实现类需要定义成抽象类（alt+回车，回车）  
接口的好处：(重点)  
弥补了类单继承的不足，一个类同时可以实现多个接口   
让程序可以面向接口编程，这样程序员就可以灵活方便的切换各种业务实现   
### 接口的应用案例-班级学生信息管理模块的开发
请设计一个班级学生的信息管理模块:   
学生的数据有:姓名、性别、成绩    
功能1:要求打印出全班学生的信息;     
功能2:要求打印出全班学生的平均成绩;   
注意!以上功能的业务实现是有多套方案的，比如:
第1套方案:能打印出班级全部学生的信息，能打印班级全部学生的平均分    
第2套方案:能打印出班级全部学生的信息(包含男女人数)，能打印班级全部学生的平均分(要求是去掉最高分、最低分)。要求:系统可以支持灵活的切换这些实现方案。
解决步骤：先创建一个学生类，再定义一个班级管理类，负责处理班级的学生数据，在班级管理类中有许多学生，所以创建一个学生集合。由于需求需要提供两套方案，因此不能直接在两个方法里面把需求实现，这样就会把程序写死，以后切换方案就要把方法修改，这个时候就可以使用面向接口的编程    
```java
//Student.java
public class Student {
    private String name;
    private char sex;
    private double score;

    public Student() {
    }

    public Student(String name, char sex, double score) {
        this.name = name;
        this.sex = sex;
        this.score = score;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public char getSex() {
        return sex;
    }

    public void setSex(char sex) {
        this.sex = sex;
    }

    public double getScore() {
        return score;
    }

    public void setScore(double score) {
        this.score = score;
    }
}
//classManager.java
import java.util.ArrayList;

public class classManager {
    private ArrayList<Student> students=new ArrayList<>();
    private StudentOperator studentOperator=new StudentOperatorImpl2();
    public classManager(){
        students.add(new Student("谢明志",'男',1));
        students.add(new Student("谢志明",'女',2));
        students.add(new Student("杜宇",'女',99));
    }
    //打印全班学生信息
    public void printInfo()
    {
        studentOperator.printAllInfo(students);
    }
    //打印全班学生的平均分
    public void printScore()
    {
        studentOperator.printAverageScore(students);
    }
}

//StudentOperator.java
import java.util.ArrayList;

public interface StudentOperator {
    void printAllInfo(ArrayList<Student> students);
    void printAverageScore(ArrayList<Student> students);
}
//StudentOperatorImpl1.java
import java.util.ArrayList;

public class StudentOperatorImpl1 implements StudentOperator {
    @Override
    public void printAllInfo(ArrayList<Student> students) {
        System.out.println("--------全班全部学生信息如下---------");
        for (int i = 0; i < students.size(); i++) {
            Student s=students.get(i);
            System.out.println("学生的姓名："+s.getName()+",性别："+s.getSex()+",成绩："+s.getScore());
        }
        System.out.println("---------------------------------");
    }

    @Override
    public void printAverageScore(ArrayList<Student> students) {
        double allScore=0.0;
        for (int i = 0; i < students.size(); i++) {
            Student s=students.get(i);
            allScore+=s.getScore();
        }
        System.out.println("学生的平均成绩是"+(allScore)/ students.size());

    }
}
//StudentOperatorImpl2.java
import java.util.ArrayList;

public class StudentOperatorImpl2 implements StudentOperator {
    @Override
    public void printAllInfo(ArrayList<Student> students) {
        int cout1=0;
        int cout2=0;
        System.out.println("--------全班全部学生信息如下---------");
        for (int i = 0; i < students.size(); i++) {
            Student s=students.get(i);
            System.out.println("学生的姓名："+s.getName()+",性别："+s.getSex()+",成绩："+s.getScore());
            if(s.getSex()=='男')
            {
                cout1++;
            }
            if(s.getSex()=='女')
            {
                cout2++;
            }
        }
        System.out.println("男生的人数是："+cout1+"，女生的人数是："+cout2);
        System.out.println("班级总人数是："+students.size());
        System.out.println("---------------------------------");
    }

    @Override
    public void printAverageScore(ArrayList<Student> students) {
        double allScore=0.0;
        double max=students.get(0).getScore();
        double min=students.get(0).getScore();
        for (int i = 0; i < students.size(); i++) {
            Student s=students.get(i);
            allScore+=s.getScore();
            if(s.getScore()>max)
            {
                max=s.getScore();
            }
            if(s.getScore()<min)
            {
                min=s.getScore();
            }
        }
        System.out.println("学生的最高成绩是："+max+"学生的最低成绩是："+min);
        System.out.println("学生的平均成绩是"+(allScore-max-min)/ (students.size()-2));

    }
}
//Test.java
public class Test {
   public static void main(String[] args) {
   classManager clazz=new classManager();
   clazz.printInfo();
   clazz.printScore();
   }
}
```
### 掌握接口新增的三种方法形式  
1.默认方法，必须用default修饰，默认会被public修饰     
实例方法：对象的方法，必须使用实现类的对象来实现   
```java
public interface A
{
    //public default void test()
    default void test1()
    {
        System.out.println("----默认方法----");
        test2();
    }
    //2.私有方法：必须用private修饰(jdk9开始支持)
    //实例方法：对象的方法
    private void test2()
    {
        System.out.println("----私有方法----");
    }
    //静态方法：必须使用static修饰，默认会用public修饰
    //public static void test3()
    static void test3()
    {
        System.out.println("----静态方法----");
    }

}
```
接口的多继承----一个接口可以同时继承多个接口,便于实现类的实现   
```java
public interface A extends B,C
{

}
```
接口其他注意事项(了解)   
1、一个接口继承多个接口，如果多个接口中存在方法签名冲突，则此时不支持多继承。  
2、一个类实现多个接口，如果多个接口中存在方法签名冲突，则此时不支持多实现   
3、一个类继承了父类，又同时实现了接口，父类中和接口中有同名的默认方法，实现类会优先用父类的    
4、一个类实现了多个接口，多个接口中存在同名的默认方法，可以不冲突，这个类重写该方法即可。
# 内部类
内部类是类中的五大成分之一（成员变量，方法，构造器，内部类，代码块），如果一个类定义在另一个类的内部，这个类就是内部类。    
```java
public class Car
{
    //内部类
    public class Engine{

    }
}
```
内部类有四种形式：成员内部类，静态内部类，局部内部类，**匿名内部类**（重点）   
1.成员内部类  
就是类中的普通成员，类似我们前面学过的普通成员变量，成员方法    
创建对象的格式:`外部类名.内部类名 对象名=new 外部类(...).new 内部类(...); `     
成员内部类中访问其他成员的特点:    
1、和前面学过的实例方法一样，成员内部类的实例方法中，同样可以直接访问外部类的实例成员、静态成员   
2、可以在成员内部类的实例方法中，拿到当前外部类对象，格式是:外部类名.this。   
```java
//  People.java
public class People {
    private int age=99;
    public static String a;
    //成员内部类
    public class Student
    {
        private String name;
        private int age=88;
        public static String SchoolName;//JDK16才开始支持定义静态成员的
        public void test()
        {
            int age=66;
            //66
            System.out.println(age);
            //88
            System.out.println(this.age);
            //99
            System.out.println(People.this.age);
            System.out.println("-------------------");
            System.out.println(age);
            System.out.println(a);
        }
        public String getName() {
            return name;
        }

        public void setName(String name) {
            this.name = name;
        }

    }
    public void test()
    {
        System.out.println(age);
        System.out.println(a);
    }


}

//Test.java
public class Test {
   public static void main(String[] args) {
    //创建对象的格式
    //外部类名.内部类名 对象名=new 外部类(...).new 内部类(...)
   People.Student s=new People().new Student();
   s.test();
   }
}
```
2.静态内部类  
有static修饰的内部类，属于外部类自己持有的  
创建对象的格式：`外部类名.内部类名 对象名=new 外部类.内部类(...)`    
静态内部类中访问外部类成员的特点：可以直接访问外部类的静态成员，不可以直接访问外部类的实例成员   
```java
public class Car
{
    //静态内部类
    public static class Engine{

    }
}
```
```java
//  People.java
public class People {
    private int age;
    public static String a;

    //静态内部类
    public static class Student
    {
        private String name;
        public static String SchoolName;//JDK16才开始支持定义静态成员的
        public void test()
        {
            //不能直接访问外部类的实例成员
            //System.out.println(age);
            //可以直接访问外部类的静态成员
            System.out.println(a);
        }
        public String getName() {
            return name;
        }

        public void setName(String name) {
            this.name = name;
        }

    }
    public static void test()
    {
        //不能直接访问外部类的实例成员
        //System.out.println(age);
        //可以直接访问外部类的静态成员
        System.out.println(a);
    }


}
//Test.java
public class Test {
   public static void main(String[] args) {
    //创建对象的格式
   People.Student in=new People.Student();
   in.test();
   }
}
```
3.局部内部类
局部内部类是定义在方法中，代码块中，构造器等执行体中   
```java
public class Test
{
    public static void main(String[] args) {
        
    }
    public static void go(){
        class A{
            
        }
        abstract class B{
            
        }
        interface C{
            
        }
    }
}
```
4.匿名内部类     
一种特殊的局部内部类，所谓匿名，是程序员不需要给这个类声明名字    
`
new 类或接口（参数值...）{  
    类体（一般是方法重写）;
};
`
匿名内部类在开发中的使用场景：通常作为一个参数传输给方法   

```java
public class Test {
   public static void main(String[] args) {
      //目标：认识匿名内部类，并掌握其作用
      //Animal a=new Cat();
      //a.cry();


      //1.把这个匿名内部类编译成一个子类，然后会立即创建一个子类对象
      Animal a=new Animal()
      {
         @Override
         public void cry()
         {
            System.out.println("猫喵喵喵的叫~~~~");
         }
      };
      a.cry();
   }
}
//class Cat extends Animal{
//   @Override
//   public void cry() {
//      System.out.println("猫喵喵喵的叫~~~~");
//   }
//}
abstract class Animal{
   public abstract void cry();
}
```
匿名对象的应用场景：
1.可以方便的创建出一个子类对象   
2.匿名内部类通常作为一个参数传输给方法   
```java
public class Test {
   public static void main(String[] args) {
      //目标：掌握匿名的常见使用场景
      Swimming s1 = new Swimming() {
         @Override
         public void swim() {
            System.out.println("狗游泳的飞快~");
         }
      };
      go(s1);

      go(new Swimming() {
         @Override
         public void swim() {
            System.out.println("狗游泳的飞快~");
         }
      });
   }

      //设计一个方法，可以接收swimming接口的一切实现类对象进来参加游泳比赛
      public static void go(Swimming s)
      {
         System.out.println("开始-------");
         s.swim();
      }


}
//猫和狗都要参加游泳比赛
interface Swimming{
   void swim();
}


```
# 枚举
枚举是一种特殊的类   
枚举类的格式：   
修饰符 enum 枚举类名{  
    名称1，名称2，...;  
    其他成员...   
}   
```java
public enum A{
    X,Y,Z;
    ...
}
```
注意：   
·枚举类中的第一行，只能写一些合法的标识符（名称），多个名称用逗号隔开。  
这些名称，本质是常量，每个常量都会记住枚举类的一个对象。   
·枚举都是最终类，不可以被继承   
·枚举类中，从第二行开始，可以定义类的其他各种成员

```java
//Test.java
public class Test {
   public static void main(String[] args) {
      //目标：认识枚举
      exercise a1=exercise.X;
      System.out.println(a1);//X
      //枚举类的构造器是私有的，不能对外创建对象
      //exercise a=new exercise();
      //枚举类的第一行都是常量，记住的是枚举类的对象
      exercise a2=exercise.Y;
      //枚举类提供一些额外的API
      exercise[] as=exercise.values();//拿到全部对象
      exercise a3=exercise.valueOf("Z");
      System.out.println(a3.name());//Z
      System.out.println(a3.ordinal());//2  //索引

   }
}

//exercise.java
public enum exercise
{
    X,Y,Z;
    private String name;

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }
}
```
抽象枚举  
```java
public enum B
{
   //拓展：抽象枚举
   X(){
      @Override
      public void go() {

      }
   },
   Y("张三"){
      @Override
      public void go() {
         System.out.println(getName()+"在跑~~");
      }
   };
   public abstract void go();
   private String name;

   public String getName() {
      return name;
   }

   public void setName(String name) {
      this.name = name;
   }

   B(String name) {
      this.name = name;
   }

   B(){

   }

}
```
用枚举实现单例模式   
```java  
public enum C{
    X();//单例
}
```
枚举的应用场景：做信息标志和分类   
# 泛型
认识泛型-定义类、接口、方法时，同时声明了一个或者多个类型变量 (如: <E>)称为泛型类、泛型接口，泛型方法、它们统称为泛型。   
作用：泛型提供了在编译阶段约束所能操作的数据类型，并自动进行检查的能力，这样就可以避免强制类型转换，及其可能出现的异常   
泛型的本质是：把具体的数据类型作为参数传给类型变量
```java
import java.util.ArrayList;

public class Test {
   public static void main(String[] args) {
      //目标：认识泛型
      ArrayList list=new ArrayList();
      list.add("java1");
      list.add("java2");
      list.add("java3");
      // list.add(new Cat());//会报错，不能把一个对象转成String类型

      for(int i=0;i<list.size();i++)
      {
         String s= (String) list.get(i);
         System.out.println(s);
      }

      System.out.println("--------------------");
      //相当于男女厕所贴上标签的作用，贴上女就只能女的进
      //ArrayList<String> list1=new ArrayList<String>();
      ArrayList<String> list1=new ArrayList<>();//jdk 1.7开始可省略
      list1.add("java1");
      list1.add("java2");
      list1.add("java3");
      //list1.add(new Cat());//只能加String类型的
      for(int i=0;i<list1.size();i++)
      {
         String s= list1.get(i);
         System.out.println(s);
      }


   }
}
class Cat{}

```
## 泛型类
自己如何去定义一个泛型类呢？   
```java
//修饰符 class 类名<类型变量，类型变量，...>{
//
//}
public class ArrayList<E>
{
    ...
}
```
```java
//Test.java
import java.util.ArrayList;

public class Test {
   public static void main(String[] args) {
      //目标：认识泛型
      MyArrayList<String> list = new MyArrayList<>();
      list.add("java1");
      list.add("java2");
      list.add("java3");
      String ele = list.get(1);
      System.out.println(ele);

    
      MyClass<String,String> c=new MyClass <>();
      c.put(这里面都是String类型);

      //不能是String类型
      //MyClass2<String> c=new MyClass2<>();
      MyClass2<Animal> c2=new MyClass2<>();
      //Dog必须继承Animal
      MyClass2<Dog> c3=new MyClass2<>();

   }


   }
//MyArrayList.java
public class MyArrayList<E> {
    private Object[] arr=new Object[10];
    private int size;//记录当前位置的

    public boolean add(E e){
        arr[size++]=e;
        return true;
    }
    public E get(int index){
        return (E) arr[index];
    }

}
//MyClass.java
public class MyClass<E,T>{
    public void put(E e,T t)
    {}
}
//MyClass2.java
public class MyClass2<E extends Animal>{
   
}
```
## 泛型接口
注意：类型变量建议用大写的英文字母，常用的有：E,T,K,V等    
自己如何去定义一个泛型接口呢？   
```java
//修饰符 interface 接口名<类型变量，类型变量，...>{
//
//}
public interface A<E>
{
    ...
}
```
```java
public interface Data<T extends Animal>
{
    void add(T t);
    ArrayList<T> getByName(String name);
}

public class StudentData implement Data<Dog>
{

}
```
## 泛型方法
？是通配符，在使用泛型的时候可以代表一切类型。   
? extends Car(上限) :?能接受的必须是Car或者其子类。   
 ? super Car(下限)：?能接受的必须是Car或者其子类   
```java
//修饰符 <类型变量，类型变量，...>返回值类型 方法名(形参列表){
//
//}
//这个是自己声明的类型变量
public static <T> void test(T t)
{
    ...
}
//下面这个不是泛型方法，E不是这个方法自己定义的，而是泛型类它声明的给到这些方法使用的 
public E get(int index)
{
    return (E) arr[index];
}

public static void go(ArrayList<?> cars){
    
}
public static void go(ArrayList<? extends Car> cars){

}
```
## 泛型的擦除问题和注意事项
1.泛型是工作在编译阶段，一旦程序编译成class文件，class文件就不存在泛型了，这就是泛型擦除   
2.泛型不支持基本数据类型（int,double），只能支持对象类型（引用数据类型）（Integer,Double）    
# 常用API
![Alt text](image.png)
## Object
Object类的常见方法  
1.方法名：public String toString(),说明：返回对象的字符串表示形式   
2.方法名：public boolean equals(Object o),说明：判断两个对象是否相等，判断的是地址    
3.方法名：protected Object clone(),说明：对象克隆   
toString存在的意义:tostring()方法存在的意义就是为了被子类重写，以便返回对象具体的内容    
equals存在的意义:直接比较两个对象的地址是否相同完全可以用“==”替代等式，等式存在的意义就是为了被子类重写，以便子类自己来定制比较规则(比如比较对象内容)。  
clone是当某个对象调用这个方法时，这个方法会复制一个一模一样的新对象返回。规则：public class User implements Cloneable{},Cloneable是一个标记接口     
浅克隆：拷贝出的新对象，与原对象中的数据一模一样（引用类型拷贝的只是地址）   
![Alt text](image-1.png)   
 深克隆：对象中基本类型的数据直接拷贝，对象中的字符串数据拷贝的还是地址，对象中还包含的其他对象，不会拷贝地址，会创建新对象    
 ![Alt text](image-2.png)      
```java
//Test.java
import java.util.ArrayList;

public class Test {
   public static void main(String[] args) {
    Student s=new Student("谢",20);
      //System.out.println(s.toString());
      System.out.println(s);

      Student s2=new Student("谢",20);
      //重写的情况下返回true,比较的是内容
      System.out.println(s2.equals(s));//不重写的情况下返回false,两个对象内容一样，地址不一样
      System.out.println(s==s2);
   }

   }

//Student.java
import java.util.Objects;

public class Student {
  private String name;
    private int age;
    private double[] score;

    @Override
    protected Object clone() throws CloneNotSupportedException {
        //浅克隆
        //return super.clone();
        //深克隆
        Student st=(Student) super.clone();
        st.score=st.score.clone();
        return st;

    }


    // 重写equals类，可以比较内容
    //比较者：s2==this
    //被比较者：s==o
    @Override
    public boolean equals(Object o) {
        //判断两个对象的地址是否一样，一样直接返回true
        if (this == o) return true;
        //判断o是不是空，是null直接返回false,或者比较两个对象的类型是否一样，不一样返回false
        //               Student.class!=Pig.class
        if (o == null || this.getClass() != o.getClass()) return false;
        //o不是null，且o一定是学生类型的对象，开始比较内容了
        Student student = (Student) o;
        return age == student.age && Objects.equals(name, student.name);
    }

    //子类重写父类Object，否则返回的是地址
    @Override
    public String toString() {
        return "Student{" +
                "name='" + name + '\'' +
                ", age=" + age +
                '}';
    }

    public Student() {
    }

    public Student(String name, int age) {
        this.name = name;
        this.age = age;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public int getAge() {
        return age;
    }

    public void setAge(int age) {
        this.age = age;
    }



}

```
## Objects
Objects是一个工具类，提供了很多操作对象的静态方法给我们使用    
1.方法名：public static boolean equals(Object a,Object b) 说明：先做非空判断，再比较两个对象   
2.方法名：public static boolean isNull(Object obj) 说明：判断对象是否为null,为null返回true,反之   
3.方法名：public static boolean nonNull(Object obj) 说明：判断对象是否不为null,不为null则返回true,反之   
```java
import java.util.ArrayList;
import java.util.Objects;

public class Test {
   public static void main(String[] args) {
    String s1="haha";
    String s2="haha";
    String s3=null;
      //Objects.equals源码刨析
      // public static boolean equals(Object a, Object b)
      // {return (a == b)|| (a != nul1 && a.equals(b));}
      System.out.println(s1.equals(s2));//true
      System.out.println(Objects.equals(s1, s2));//true

      System.out.println(s1.equals(s3));//false
      System.out.println(Objects.equals(s1, s3));//false

      //System.out.println(s3.equals(s1));//报错
      //使用Objects.equals可以允许s3为null,用自己的equals不能为null
      System.out.println(Objects.equals(s3, s1));//false

      System.out.println(Objects.isNull(s1));//false
      System.out.println(s1 == null);//false
      System.out.println(Objects.isNull(s3));//true
      System.out.println(s3 == null);//true


      System.out.println(Objects.nonNull(s1));//true
      System.out.println(Objects.nonNull(s3));//false
   }

   }
```
## 包装类
包装类就是把基本类型的数据包装成对象   
基本数据类型和对应的包装类（引用数据类型）    
byte-Byte;short-Short;<font color=red>int-Integer</font>;long-Long;<font color=red>char-Character</font>;float-Float;double-Double;boolean-Boolean   
```java
public class Test {
   public static void main(String[] args) {
      //Integer a1=new Integer(12);//已过时
      Integer a2=Integer.valueOf(12);
      System.out.println(a2);

      //自动装箱：可以自动把基本类型的数据转换成对象
      Integer a3=12;

      //自动拆箱:可以自动把包装类型的对象转换成对应的基本数据类型
      int a4=a3;

      //泛型和集合不支持基本数据类型，只能支持引用数据类型
      ArrayList<Integer> list=new ArrayList<>();
      list.add(12);//自动装箱
      list.add(13);//自动装箱

      int rs=list.get(1);
      System.out.println("------------");

      //1.把基本类型的数据转换成字符串
      Integer a=23;
      String rs1=Integer.toString(a);//"23"
      System.out.println(rs1+1);//231

      String rs2=a.toString();//"23"
      System.out.println(rs2+1);//231

      String rs3=a+"";//"23"
      System.out.println(rs3+1);//231

      //2.把字符串类型的数值转换成对应的基本类型
      String ageStr="29";
      //int ageI=Integer.parseInt(ageStr);//29
      int ageI=Integer.valueOf(ageStr);//29
      System.out.println(ageI+1);//30

      String scoreStr="99.5";
      //double score=Double.parseDouble(scoreStr);//99.5
      double score=Double.valueOf(scoreStr);//99.5
      System.out.println(score+0.5);//100.0

   }

   }
```
## StringBuilder,StringBuffer
StringBuilder代表可变字符串对象，相当于一个容器，它里面装的字符串是可以改变的，就是用来操作字符串的   
好处：StringBuilder比String更适合做字符串的修改操作，效率会更高，代码也会更简洁

构造器：    
public StringBuilder()创建一个空白的可变的字符串对象，不包含任何内容  
public StringBuilder(String str)创建一个指定字符串内容的可变字符串对象     
方法名称：   
publicStringBuilder append(任意类型)添加数据并返回stringBuilder对象本身       
public StringBuilder reverse() 将对象的内容反转    
public int ength()返回对象内容长度   
public String toString()通过toString()就可以实现StringBuilder转换为String    

对于字符串的相关操作，如频繁的拼接，修改等，建议用StringBuilder,效率更高哦！    
s=s+"abc";效率不如s=s.append("abc");   
注意：如果操作字符串较少，或者不需要操作，以及定义字符串常量，还是建议用String     

StringBuffer与StringBuilder用法是一模一样的，但前者线程安全的，而后者线程不安全    
### 案例-返回任意整形数组的内容  
```java
import java.util.ArrayList;
import java.util.Objects;

public class Test {
   public static void main(String[] args) {
      int[] arr={11,22,33};
      System.out.println(getArrayData(arr));

   }
   public static String getArrayData(int[] arr) {
      if (arr == null) {
         return null;
      }
      StringBuilder sb=new StringBuilder();
      sb.append("[");
      for (int i = 0; i < arr.length; i++) {
         if(i==arr.length-1)
         {
            sb.append(arr[i]);
         }
         else
            sb.append(arr[i]).append(",");
      }
      sb.append("]");
      return sb.toString();

   }

   }
```
## StringJoiner
DK8开始才有的，跟StringBuilder一样，也是用来操作字符串的，也可以看成是一个容器，创建之后里面的内容是可变的。   
好处:不仅能提高字符串的操作效率，并且在有些场景下使用它操作字符串，代码会更简洁     
构造器：    
public StringJoiner (间隔符号) 创建一个stringJoiner对象，指定拼接时的间隔符号    
public stringJoiner (间隔符号，开始符号，结束符号)  创建一个stringJoiner对象，指定拼接时的间隔符号、开始符号、结束符号       
方法名称:    
public stringJoiner add (添加的内容) 添加数据，并返回对象本身   
public int length()  返回长度(字符出现的个数)   
public String toString() 返回一个字符串(该字符串就是拼接之后的结果)    
## Math
Math代表数学，是一个工具类，里面提供的都是对数据进行操作的一些静态方法     
方法名
public static int abs(int a)   
public static double ceil(double a)    
public static double floor(double a)   
public static int round(float a)   
public static int max(int a,int b)    
public static double pow(double a,double b)   
public static double random()    
说明
获取参数绝对值      
向上取整         
向下取整         
四舍五入      
获取两个int值中的较大值     
返回a的b次暴的值  
返回值为double的随机值，范围[0.0,1.0)    
```java
import java.util.ArrayList;
import java.util.Objects;

public class Test {
   public static void main(String[] args) {
     //目标：了解Math类提供的常见方法
      //1.public static int abs(int a)//取绝对值拿到的结果一定是正数
     // public static double abs(double a);
      System.out.println(Math.abs(-12));//12
      System.out.println(Math.abs(123));//123
      System.out.println(Math.abs(-3.14));//2.14

      //2.public static double ceil(double a);向上取整
      System.out.println(Math.ceil(4.0000001));//5.0
      System.out.println(Math.ceil(4.0));//4.0

      //3.public static double floor(double a);向下取整
      System.out.println(Math.floor(4.999999));//4.0
      System.out.println(Math.floor(4.0));//4.0

      //4.public static long round(double a);四舍五入
      System.out.println(Math.round(3.499999));//3
      System.out.println(Math.round(3.59999));//4

      //5.public static int max(int a,int b);取较大值
      //public static int min(int a,int b);取较小值
      System.out.println(Math.max(10,20));//20
      System.out.println(Math.min(10,20));//10
      System.out.println(Math.max(10.1,20));//20.0

      //6.public static double pow(double a,double b);取次方
      System.out.println(Math.pow(2,3));//8.0
      System.out.println(Math.pow(3,2));//9.0

      //7.public static double random();取随机数[0.0,1.0)(包前不包后)
      System.out.println(Math.random());//0.5027010881044325


   }


   }
```
## System
System代表程序所在的系统，也是一个工具类    
System类提供的常见方法：   
方法名    
public static void exit(int status)终止当前运行的java虚拟机。该参数用作状态代码；按照惯例，非零状态代码表示异常退出         

public static long currentTimeMillis()返回当前系统的时间 毫秒值形式指的是1970-1-1 0：0：0开始走到此刻的总的毫秒值，1s=1000ms       
## Runtime
Runtime代表程序所在的运行环境，它是一个单例类
`Runtime r=Runtime.getRuntime();`
Runtime类提供的常见方法
方法名
public static Runtime getRuntime()    
public void exit(int status)      
public int availableProcessors()    
public long totalMemory()    
public long freeMemory()
public Process exec(String command)    
说明
返回与当前Java应用程序关联的运行时对象终止当前运行的虚拟机      
返回Java虚拟机可用的处理器数。       
返回Java虚拟机中的内存总量   
返回lava虚拟机中的可用内存    
启动某个程序，并返回代表该程序的对象     
## BigDecimal
解决浮点型运算时，小数运算的时候出现结果失真的问题
构造器
public BigDecimal(double val)注意:不推荐使用这个   
public BigDecimal(String val)   
方法名
public static BigDecimal valueof(double val)   
public BigDecimal add(BigDecimal b)    
public BigDecimal subtract(BigDecimal b)    
public BigDecimal multiply(BigDecimal b)           
public BigDecimal divide(BigDecimal b)         
public BigDecimal divide (另一个BigDecimal对象，精确几位，舍入模式)         
public double doubleValue()
说明      
将 double转换为 BigDecimal     
把string转成BigDecimal       
说明      
转换一个 double成 BigDecimal      
加法       
减法     
乘法    
除法       
除法、可以控制精确到小数几位     
将BigDecimal转换为double 
```java
import java.math.BigDecimal;
import java.math.RoundingMode;
import java.util.ArrayList;
import java.util.Objects;

public class Test {
   public static void main(String[] args) {
     //目标：掌握BigDecimal的使用，解决小数运算失真的问题
      double a=0.1;
      double b=0.2;
      double c=a+b;
      System.out.println(c);//0.30000000000000004
      System.out.println("--------------");

      //1.把他们变成字符串封装成BigDecimal对象来运算
//      BigDecimal a1=new BigDecimal(Double.toString(a));
//      BigDecimal b1=new BigDecimal(Double.toString(b));
      //推荐用以下方法，把小数转换成字符串再得到BigDecimal对象来使用（更简洁）
      BigDecimal a1=BigDecimal.valueOf(a);
      BigDecimal b1=BigDecimal.valueOf(b);

      BigDecimal c1=a1.add(b1);//加//0.3
      BigDecimal c2=a1.subtract(b1);//减//-0.1
      BigDecimal c3=a1.multiply(b1);//乘//0.02
      BigDecimal c4=a1.divide(b1);//除//0.5
      System.out.println(c1);
      System.out.println(c2);
      System.out.println(c3);
      System.out.println(c4);

      BigDecimal i=BigDecimal.valueOf(0.1);
      BigDecimal j=BigDecimal.valueOf(0.3);
      BigDecimal k=i.divide(j,2, RoundingMode.HALF_UP);
      System.out.println(k);//0.33

      //把BigDecimal对象转换成double类型的数据
      double rs=k.doubleValue();
      System.out.println(rs);

   }


   }
```
## JDK8之前传统的日期，时间
### Date
构造器    
public Date()   
public Date(long time)   
常见方法   
public long getTime()
public void setTime(long time)      
说明      
创建一个Date对象，代表的是系统当前此刻日期时间。      
把时间辜秒值转换成Date日期对象。     
说明       
返回从1970年1月1日 00:00:00走到此刻的总的毫秒数       
设置日期对象的时间为当前时间毫秒值对应的时间   
```java
import java.util.Date;
import java.math.BigDecimal;
import java.math.RoundingMode;
import java.util.ArrayList;
import java.util.Objects;

public class Test {
   public static void main(String[] args) {
     //目标：掌握Data日期类的使用
      //1.创建一个Data的对象，代表系统当前时间信息
      Date d=new Date();
      System.out.println(d);//Thu Oct 12 20:45:24 CST 2023

      //2.拿到时间毫秒值
      long time=d.getTime();
      System.out.println(time);//1697114724482
      //3.把时间毫秒值转换成日期对象。2s之后的时间
      time+=2*1000;
      Date d2=new Date(time);
      System.out.println(d2);//Thu Oct 12 20:45:26 CST 2023
      //4.直接把日期对象的时间通过setTime方法进行修改
      Date d3=new Date();
      d3.setTime(time);
      System.out.println(d3);//Thu Oct 12 20:45:26 CST 2023


   }


   }

```
### SimpleDateFormat
简单日期格式化，得到我们看到的样子       
SimpleDateFormat的时间格式：      XXXX-XX-XX XX:XX:XX   
格式化：Date--->2099-11-12 11:11:11     
时间毫秒值--->2099-11-12 11:11:11  

常见构造器      
public SimpleDateFormat(String pattern)         
格式化时间的方法      
public final String format(Date date)           
public final String format(Object time)        
说明    
创建简单日期格式化对象，并封装时间的格式
说明          
将日期格式化成日期/时间字符串      
将时间毫秒值式化成日期/时间字符串     
```java
import java.text.SimpleDateFormat;
import java.util.Date;
import java.math.BigDecimal;
import java.math.RoundingMode;
import java.util.ArrayList;
import java.util.Objects;

public class Test {
   public static void main(String[] args) {
     //目标：掌握Data日期类的使用
      //1.创建一个Data的对象，代表系统当前时间信息
      Date d=new Date();
      System.out.println(d);//Thu Oct 12 20:51:19 CST 2023

      //2.拿到时间毫秒值
      long time=d.getTime();
      System.out.println(time);//1697115079495

      //格式化时间
      SimpleDateFormat sdf=new SimpleDateFormat("yyy年MM月dd日 HH:mm:ss EEE a");
      String str=sdf.format(d);
      System.out.println(str);//2023年10月12日 20:51:19 周四 下午
      String str2=sdf.format(time);
      System.out.println(str2);//2023年10月12日 20:51:19 周四 下午

      //3.把时间毫秒值转换成日期对象。2s之后的时间
      time+=2*1000;
      Date d2=new Date(time);
      System.out.println(d2);//Thu Oct 12 20:51:21 CST 2023
      //4.直接把日期对象的时间通过setTime方法进行修改
      Date d3=new Date();
      d3.setTime(time);
      System.out.println(d3);//Thu Oct 12 20:51:21 CST 2023


   }


   }
```
SimpleDateFormat解析字符串时间成为日期对象    
2022-12-12 12:30:30---->Date日期对象    
解析方法：public Date parse(String source)  把字符串时间解析成日期对象    
```java
import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.Date;
import java.math.BigDecimal;
import java.math.RoundingMode;
import java.util.ArrayList;
import java.util.Objects;

public class Test {
   public static void main(String[] args) throws ParseException {
     //目标：掌握Data日期类的使用
      //1.创建一个Data的对象，代表系统当前时间信息
      Date d=new Date();
      System.out.println(d);//Thu Oct 12 21:02:39 CST 2023

      //2.拿到时间毫秒值
      long time=d.getTime();
      System.out.println(time);//1697115759135

      //格式化时间
      SimpleDateFormat sdf=new SimpleDateFormat("yyy年MM月dd日 HH:mm:ss EEE a");
      String str=sdf.format(d);
      System.out.println(str);//2023年10月12日 21:02:39 周四 下午
      String str2=sdf.format(time);
      System.out.println(str2);//2023年10月12日 21:02:39 周四 下午

      //3.把时间毫秒值转换成日期对象。2s之后的时间
      time+=2*1000;
      Date d2=new Date(time);
      System.out.println(d2);//Thu Oct 12 21:02:41 CST 2023
      //4.直接把日期对象的时间通过setTime方法进行修改
      Date d3=new Date();
      d3.setTime(time);
      System.out.println(d3);//Thu Oct 12 21:02:41 CST 2023

      System.out.println("-----------------------");
      String str3="2023-10-12 20:51:19";
      SimpleDateFormat sdf2=new SimpleDateFormat("yyy-MM-dd HH:mm:ss");
      Date d4=sdf2.parse(str3);//Alt+回车抛出错误
      System.out.println(d4);//Thu Oct 12 20:51:19 CST 2023


   }


   }
```
### Calendar-日历
 1.Calendar代表的是此刻时间对应的日历     
 2.通过它可以单独获取，修改时间中的年月日时分秒等  
 方法名      
public static Calendar getInstance()   
public int get(int field)      
public final Date getTime()      
public long getTimeInMillis()        
public void set(int field,int value)public void add(int field,int amount)    
说明
获取当前日历对象   
获取日历中的某个信息。        
获取日期对象      
获取时间毫秒值       
修改日历的某个信息。    
为某个信息增加/减少指定的值     
```java
import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.Calendar;
import java.util.Date;
import java.math.BigDecimal;
import java.math.RoundingMode;
import java.util.ArrayList;
import java.util.Objects;

public class Test {
   public static void main(String[] args) throws ParseException {
       //目标：掌握Calendar的使用方法
       // 1.得到系统此刻时间对应的日历对象
       Calendar now=Calendar.getInstance();
       System.out.println(now);

       //2.获取日历中的某个信息
       int year=now.get(Calendar.YEAR);
       System.out.println(year);//2023

       int days=now.get(Calendar.DAY_OF_MONTH);
       System.out.println(days);//13

       //3.拿到日历中记录的日期对象
       Date d=now.getTime();
       System.out.println(d);//Fri Oct 13 19:43:50 CST 2023


   }


   }
```
## JDK8开始新增的日期，时间
JDK8之前传统的时间API    
1、设计不合理，使用不方便很多都被淘汰了   
2、都是可变对象，修改后会丢失最开始的时间信息。       
3、线程不安全             
4、只能精确到毫秒           
JDK8开始之后新增的时间API       
1、设计更合理，功能丰富，使用更方便。         
2、都是不可变对象，修改后会返回新的时间对象，不会丢失最开始的时间          
3、线程安全         
4.能精确到毫秒、纳秒。      
JDK8新增的时间： 
代替Calendar:      
LocalDate:年、月、日、星期          
LocalTime: 时、分、秒、纳秒      
LocalDateTime: 年、月、日 时、分、秒       
ZoneId:时区        
ZonedDateTime:带时区的时间     
代替Date:       
Instant: 时间戳/时间线  
代替SimpleDateFormat:         
DateTimeFormatter:用于时间的格式化和解析        
其他补充：    
Duration:时间间隔 (时、分、秒，纳秒)           
Period:时间间隔(年，月，日)         
### LocalDate LocalTime LocalDateTime
方法名:  
public static Xxxx now(): 获取系统当前时间对应的该对象    
public static Xxxx of(): 获取指定时间的对象    
示例:   
LocaDate ld = LocalDate.now();     
LocalTime lt= LocalTime.now();      
LocalDateTime ldt = LocalDateTime.now();         
```java
import java.text.ParseException;
import java.time.LocalDate;


public class Test {
   public static void main(String[] args) throws ParseException {
      //0.获取本地日期对象（不可变对象）
       LocalDate ld=LocalDate.now();//年 月 日
       System.out.println(ld);

       //1.获取日期对象中的信息
       int year=ld.getYear();//年
       int month=ld.getMonthValue();//月（1-12）
       int day=ld.getDayOfMonth();//日
       int dayOfYear=ld.getDayOfYear();//一年中的第几天
       int dayOfWeek=ld.getDayOfWeek().getValue();//星期几
       System.out.println(year);
       System.out.println(month);
       System.out.println(day);
       System.out.println(dayOfWeek);
       System.out.println(dayOfYear);

       //2.直接修改某个信息：withYear,withMonth,withDayOfMonth,withDayOfYear
       LocalDate ld2=ld.withYear(2099);
       System.out.println(ld2);
       System.out.println(ld);

       //3.把某个信息加多少：plusYears,plusMonths,plusDays,plusWeeks
       LocalDate ld3=ld.plusYears(2);
       System.out.println(ld3);

       //4.把某个信息减多少：minusYears,minusMonths,minusDays,minusWeeks
       LocalDate ld4=ld.minusYears(2);
       System.out.println(ld4);
       //5.获取指定日期的LocalDate对象：public static LocalDate of();
       LocalDate ld5=LocalDate.of(2099,12,12);
       LocalDate ld6=LocalDate.of(2099,12,12);
       System.out.println(ld5);

       //6.判断2个日期对象，是否相等，在前还是在后，equals ifBefore isAfter
       System.out.println(ld5.equals(ld6));//true
       System.out.println(ld5.isAfter(ld));//true
       System.out.println(ld5.isBefore(ld));//false
   }


   }
```
```java
import java.text.ParseException;
import java.time.LocalDate;
import java.time.LocalTime;


public class Test {
   public static void main(String[] args) throws ParseException {

       LocalTime lt=LocalTime.now();
       System.out.println(lt);//20:34:40.088590900

       //1.获取时间中的信息
       int hour=lt.getHour();//时
       int minute=lt.getMinute();//分
       int second=lt.getSecond();//秒
       int nano=lt.getNano();//纳秒
       System.out.println(hour);//20
       System.out.println(minute);//34
       System.out.println(second);//40
       System.out.println(nano);//88590900

       //2.修改时间：withHour,withMinute,withSecond,withNano
       LocalTime lt3=lt.withHour(10);
       System.out.println(lt3);
       //3.加多少：plusHours,plusMinutes,plusSeconds,plusNanos
       //4.减多少：minusHours,minusMinutes,minusSeconds,minusNanos
       //5.获取指定时间的LocalTime对象
       //public static LocalTime of(int hour,int minutes,int second)
       LocalTime lt4=LocalTime.of(12,12,12);
       LocalTime lt5=LocalTime.of(12,12,12);
       //6.判断2个时间对象，是否相等，在前还是在后，equals isBefore,isAfter
       System.out.println(lt4.equals(lt5));
       System.out.println(lt5.isAfter(lt));
       System.out.println(lt5.isBefore(lt));
   }


   }
```
了解时区和带时区的时间  
```java
import java.text.ParseException;
import java.time.*;


public class Test {
   public static void main(String[] args) throws ParseException {
        //目标：了解时区和带时区的时间
       //1。ZoneId的常见方法
       //public static ZoneId systemDefault();获取系统默认的时区
       ZoneId zoneId= ZoneId.systemDefault();
       System.out.println(zoneId.getId());
       System.out.println(zoneId);
       //public static Set<String> getAvailableZoneIds():获取Java支持的全部时区Id
       System.out.println(ZoneId.getAvailableZoneIds());
        //public static ZoneId of(String zoneId):把某个时区id封装成ZoneId对象
       ZoneId zoneId1=zoneId.of("America/New_York");

       //2.ZoneDateTime:带时区的时间
       //public static ZoneDateTime now(ZoneId zone):获取某个时区的ZoneDateTime对象
       ZonedDateTime now=ZonedDateTime.now(zoneId1);
       System.out.println(now);//2023-10-13T09:18:32.920966-04:00[America/New_York]
        //世界标准时间
       ZonedDateTime now1=ZonedDateTime.now(Clock.systemUTC());
       System.out.println(now1);
       //public static ZoneDateTime now():获取系统默认时区时区的ZonedDateTime对象
       ZonedDateTime now2=ZonedDateTime.now();
       System.out.println(now2);

   }


   }
```
### Instant
时间线上的某个时刻/时间戳   
通过Instance的对象可以拿到此刻的时间，该时间由两部分组成：从1970-01-01 00：00：00开始走到此刻的总秒数+不够1秒的纳秒数1s=1000000000纳秒   
```java
import java.text.ParseException;
import java.time.*;


public class Test {
   public static void main(String[] args) throws ParseException {
      //1.创建Instant的对象，获取此刻时间信息
       Instant now=Instant.now();//不可变对象

       //2.获取总秒数
       long second=now.getEpochSecond();
       System.out.println(second);//1697203955

       //3.不够1s的纳秒数
       int nano=now.getNano();
       System.out.println(nano);//150283400

       System.out.println(now);//2023-10-13T13:32:35.150283400Z
        Instant instant=now.plusNanos(111);

        //Instant对象的作用，做代码的性能分析，或者记录用户的操作时间点
       Instant now1=Instant.now();
       //代码执行。。。
       Instant now2=Instant.now();
   }


   }
```
### DateTimeFormatter
DateTimeFormatter：格式化器，用于时间的格式化，解析，线程安全    
方法名：          
 public static DateTimeFormatter ofPattern(时间格式)：获取格式化器   
 public String format(时间对象)：格式化时间      
 LocalDateTime提供的格式化，解析时间的方法    
 方法名：    
 public String format(DateTimeFormatter formatter);格式化时间    
 public static LocalDateTime parse(CharSequence text,DateTimeFormatter formatter);解析时间         
 ```java
 import java.text.ParseException;
import java.time.*;
import java.time.format.DateTimeFormatter;


public class Test {
   public static void main(String[] args) throws ParseException {
      //1.创建一个日期时间格式化器对象出来
       DateTimeFormatter formatter=DateTimeFormatter.ofPattern("yyyy年MM月dd日 HH:mm:ss");

       //2.对时间进行格式化
       LocalDateTime now=LocalDateTime.now();
       System.out.println(now);

       String rs=formatter.format(now);//正向格式化，格式化器格式化时间
       System.out.println(rs);

       //格式化时间，其实还有一种方案
       String rs2= now.format(formatter);//反向格式化，时间格式化格式器
       System.out.println(rs2);

       //解析时间，解析时间一般使用LocalDateTime提供的解析方法来解析
       String dateStr="2029年12月12日 12:12:11";//这里要和定义的格式化器格式一样
       LocalDateTime ldt=LocalDateTime.parse(dateStr,formatter);
       System.out.println(ldt);

   }


   }
```
### Period(一段时间)
可以用于计算两个LocalDate对象相差的年数，月数，天数   
方法名           
public static Period between(LocalDate start,LocalDate end)          
public int getYears()         
public int getMonths()       
public int getDays()      
说明           
传入2个日期对象，得到Period对象       
计算隔几年，并返回        
计算隔几个月，年返回      
计算隔多少天，并返回      
```java
import java.text.ParseException;
import java.time.*;
import java.time.format.DateTimeFormatter;


public class Test {
   public static void main(String[] args) throws ParseException {
      LocalDate start=LocalDate.of(2029,8,10);
      LocalDate end=LocalDate.of(2029,8,15);

      //1.创建Period对象，封装两个日期对象
      Period period=Period.between(start,end);
      //if(end<start)输出是负的
      //2.通过period对象获取两个日期对象相差的信息
      System.out.println(period.getYears());//0
      System.out.println(period.getMonths());//0
      System.out.println(period.getDays());//5

   }


   }
```
### Duration(持续时间)
可以用于计算两个事件对象相差的天数，小时数，分数，秒数，纳秒数；支持LocalTime,LocalDateTime,Instant等时间     
方法名        
public static Duration between(开始时间对象1,截止时间对象2)          
public long toDays()   
public long toHours()       
public long toMinutes()     
public long toSeconds()      
public long toMillis()             
public long toNanos()         
说明        
传入2个时间对象，得到Duration对象            
计算隔多少天，并返回        
计算隔多少小时，并返回         
计算隔多少分，并返回       
计算隔多少秒，并返回      
计算隔多少毫秒，并返回    
计算隔多少纳秒，并返回       
```java
import java.text.ParseException;
import java.time.*;
import java.time.format.DateTimeFormatter;


public class Test {
   public static void main(String[] args) throws ParseException {
      LocalDateTime start=LocalDateTime.of(2025,11,11,11,10,10);
      LocalDateTime end=LocalDateTime.of(2025,11,11,11,11,11);

      //1.创建Duration对象
      Duration duration=Duration.between(start,end);
      //if(end<start)输出是负的
      //2.获取两个时间对象的间隔信息
      System.out.println(duration.toDays());
      System.out.println(duration.toHours());
      System.out.println(duration.toMinutes());
      System.out.println(duration.toSeconds());
      System.out.println(duration.toMillis());
      System.out.println(duration.toNanos());
   }


   }
```
## Arrays
用来操作数组的一个工具类    
Arrays类提供的常见方法    
 方法名       
public static String toString(类型门arr)       
public static intl] copyofRange(类型I arr,起始索引,结束索)         
public static copyof(类型 arr, int newLength)          
public static setAll(doublell array, IntToDoubleFunction generator)           
public static void sort(类型arr)          
说明          
返回数组的内容      
拷贝数组(指定范围)           
拷贝数组         
把数组中的原数据改为新数据       
对数组进行排序(默认是升序排序)       
## Lambda表达式
Lambda表达式是JDK8开始新增的一种语法形式；作用：用于简化匿名内部类的代码写法     
注意：Lambda表达式并不是说能简化全部匿名内部类的写法，只能简化函数式接口的匿名内部类      
函数式接口：有且仅有一个抽象方法的接口    
注意：将来我们见到的大部分函数式接口，上面都可能会有一个@FunctionalInterface的注释，有该注解的接口就必定是函数式接口     
格式：
```java
(被重写方法的形参列表)->{
    被重写方法的方法体代码。
}
```
```java
import java.text.ParseException;
import java.time.*;
import java.time.format.DateTimeFormatter;


public class Test {
   public static void main(String[] args) throws ParseException {
      //目标：认识Lamdba表达式
      Animal a=new Animal() {
         @Override
         public void run() {
            System.out.println("狗跑的贼快~");//狗跑的贼快~
         }
      };
      a.run();

      //注意：Lambda表达式并不是说能简化全部匿名内部类的写法，只能简化函数式接口的匿名内部类
      //错误代码！
//      Animal a=()->{
//         System.out.println("狗跑的贼快~");
//      };
//      a.run();
//     Swimming s=new Swimming(){
//        @Override
//        public void swim() {
//           System.out.println("学生快乐的游泳~~~");
//        }
//     };
//     s.swim();

     Swimming s=()->{
            System.out.println("学生快乐的游泳~~~");

      };
      s.swim();




   }


   }
   interface  Swimming{
   void swim();
   }
   abstract class Animal
   {
      public abstract void run();
   }
```
Lambda表达式的省略写法(进一步简化Lambda表达式的写法)       
参数类型可以省略不写               
如果只有一个参数，参数类型可以省略，同时()也可以省略           
如果Lambda表达式中的方法体代码只有一行代码，可以省略大括号不写，同时要省略分号!此时，如果这行代码是return语句，也必须去掉return不写             
## 方法引用   
静态方法的引用：类名::静态方法   
使用场景：如果某个Lambda表达式里只是调用一个静态方法，并且前后参数的形式一致，就可以使用静态方法引用   
实例方法引用：对象名::实例方法   
使用场景：如果某个Lambda表达式里只是调用一个实例方法，并且前后参数的形式一致，就可以使用实例方法引用     
特定类型的方法引用：类型::方法   
使用场景：如果某个Lambda表达式里只是调用一个实例方法，并且前面参数列表中的第一个参数是作为方法的主调，后面的所有参数是作为该实例方法的入参的，那此时就可以使用特点类型的方法引用    
构造器引用：类名::new    
使用场景：如果某个Lamdba表达式只是在创建对象，并且前后参数情况一致，就可以使用构造器引用   
# 正则表达式  
正则表达式就是由一些特定的字符组成，代表的是一个规则   
作用一：用来校验数据格式是否合法，比如校验用户输入的电话号码是否格式合法，校验用户输入的邮箱格式是否合法，校验用户输入的qq号码是否合法     
作用二：在一段文本中查找满足要求的内容   
```java
import java.text.ParseException;
import java.time.*;
import java.time.format.DateTimeFormatter;
//目标: 体验一下使用正则表达式来校验数据格式的合法性
//需求:校验QQ号码是否正确，要求全部是数字，长度是《6-20)之间，不能以0开头

public class Test {
   public static void main(String[] args) throws ParseException {
      System.out.println(checkQQ(null));//false
      System.out.println(checkQQ("2335445667"));//true
      System.out.println(checkQQ("2345aaa3455"));//false
      System.out.println("-------------------");
      System.out.println(checkQQ1(null));//false
      System.out.println(checkQQ1("2335445667"));//true
      System.out.println(checkQQ1("2345aaa3455"));//false


   }
   public static boolean checkQQ1(String qq)
   {
      return qq!=null&&qq.matches("[1-9]\\d{5,19}");
   }
   public static boolean checkQQ(String qq)
   {
      //1.判断qq号码是否为null等
      if(qq==null||qq.startsWith("0")||qq.length()<6||qq.length()>20)
         return false;
      //2.qq至少是不是null,不是以0开头，阿玛尼组6~20之间的长度
      //判断qq号码中是否都是数字
      //qq=2514ghd234
      for (int i = 0; i < qq.length(); i++) {
         //根据索引提取当前位置处的字符
         char ch=qq.charAt(i);
         if(ch<'0'||ch>'9')
            return false;
      }
      return true;
   }


   }
```
String 提供了一个匹配正则表达式的方法   
public boolean matches(String regex);判断字符串是否匹配正则表达式，匹配返回true,不匹配返回false   
正则表达式的书写规则    
字符类（只匹配单个字符）    
[abc] 只能是a，b，或c    
[^abc] 除了a，b，c之外的任何字符     
[a-zA-z] a到z A到Z，包括 (范围)     
[a-d[m-p]] a到d，或m到p        
[a-z&&[def]] d，e，或f(交集)      
[a-z&&[^bc]]  a到z，除了b和c (等同于[ad-z])        
[a-z&&[^m-p]] :a到z，除了m到p(等同于[a-lq-z])    
预定义字符（只匹配单个字符）   
. 任何字符   
\d 一个数字[0-9]     
\D 非数字: [^0-9]      
\s 一个空白字符:      
\S 非空白字符: [^\s]     
\w [a-zA-Z_0-9]          
\W [^\w]一个非单词字符       
数量词：   
X? X,一次或0次     
X* X，零次或多次   
X+ X，一次或多次    
X {n}  X,正好n次     
X {n, } X,至少n次    
X {n,m} X，至少n但不超过m次      
## 应用案例
```java
import java.text.ParseException;
import java.util.Scanner;
//检验用户输入的电话，邮箱，时间是否合法

public class Test {
   public static void main(String[] args) {
   checkPhone();


   }
   public static void checkPhone() {
      while (true) {
         System.out.println("请输入您的电话号码（手机或座机）：");
         Scanner sc = new Scanner(System.in);
         String phone = sc.nextLine();
         //18629687099 010-4324242424 0102233434
         if (phone.matches("(1[3-9]\\d{9})|(0\\d{2,7}-?[1-9]\\d{4,19})")) {
            System.out.println("您输入的号码格式正确");
            break;
         } else {
            System.out.println("您输入的号码格式不正确~请重新输入");
         }
      }
   }
      public static void checkEmail()
      {
         while (true) {
            System.out.println("请输入您的邮箱：");
            Scanner sc=new Scanner(System.in);
            String email=sc.nextLine();
            //dlei0009@163.com
            //26354876@qq.com
            //itheima@itcast.com
            if(email.matches("\\w{2,}@\\w{2,20}(\\.\\w{2,10}){1,2}"))
            {
               System.out.println("您输入的邮箱格式正确");
               break;
            }
            else{
               System.out.println("您输入的号码邮箱不正确~请重新输入");
            }
         }
   }




   }
   ```
   爬取信息  
```java
import java.text.ParseException;
import java.util.Scanner;
import java.util.regex.Matcher;
import java.util.regex.Pattern;
//检验用户输入的电话，邮箱，时间是否合法

public class Test {
   public static void main(String[] args) {
method1();


   }
   public static void method1()
   {
      String data="来黑马程序员学习Java.\n" +
              "电话: 18666688888，18699997777\n" +
              "或者联系邮箱: boniu@itcast.cn\n" +
              "座机电话: 01036517895，010-98951256\n" +
              "邮箱: bozai@itcast.cn.\n" +
              "邮箱: dlei0009@163.com.\n" +
              "热线电话: 400-618-9090 ，400-618-4000，4006184000，4006189090";
      //1.定义爬取规则
      String regex="(1[3-9]\\d{9})|(0\\d{2,7}-?[1-9]\\d{4,19})|(\\w{2,}@\\w{2,20}(\\.\\w{2,10}){1,2})"+"|(400-?\\d{3,7}-?\\d{3,7})";
      //2.把正则表达式封装成一个Pattern对象
      Pattern pattern=Pattern.compile(regex);
      //3.通过pattern对象去获取查找内容的匹配器对象
      Matcher matcher=pattern.matcher(data);
      //4.定义一个循环开始爬取信息
      while(matcher.find())
      {
         String rs=matcher.group();//获取到了找到的内容
         System.out.println(rs);//18666688888
//         18699997777
//         boniu@itcast.cn
//         01036517895
//         010-98951256
//         bozai@itcast.cn
//      dlei0009@163.com
//         400-618-9090
//         400-618-4000
//         4006184000
//         4006189090
      }
   }




   }

```
正则表达式用于搜索替换，分割内容，需要结合String提供的如下方法完成：   
方法名      
public String replaceAll(String regex ，String newStr)           
public String[] split(String regex)         
说明       
按照正则表达式匹配的内容进行替换    
按照正则表达式匹配的内容进行分割字符串，反回一个字符串数组。                      



 














