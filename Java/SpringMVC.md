# 一、SpringMVC简介

![image-20231119213719932](C:\Users\dyj\AppData\Roaming\Typora\typora-user-images\image-20231119213719932.png)

![img](https://secure2.wostatic.cn/static/no1PDXU3JX5K4cecSAx5oL/image.png?auth_key=1700400839-bsUapGSSd9UmXxuYXeHWsj-0-95951838db3dc12abf02d007c9c8c40d&image_process=resize,w_1053&file_size=110526)

# 二、SpringMVC接收数据

## 1.访问路径设置

```
//每一个方法就是一个handler->handlerMapping 指定访问地址
/*
@WebServlet("必须使用/开头")

@RequestMapping(不要必须使用/开头) user/login  /user/login

1.精准地址 [一个|多个]    /user/login  {"地址一","地址二"}
2.支持模糊地址 * 任意一层字符串|** 任意层任意字符串
        /user/* ->user/a  user/aaaa 可以  /user/a/b不行，*是一层的
        /user/** ->user user/a user/a/a/a/a/a
3.类上和方法上添加@RequestMapping的区别
        类上提取通用的访问地址，不是必须加的
        方法上是具体的handler地址,必须加的
        访问：类地址+方法地址即可
4.请求方式指定
客户端->http(get|post|put|delete)->ds->handler
默认情况：@RequestMapping("login") 只要地址正确，任何请求方式都可以访问呢
指定请求方式：method={RequestMethod.GET,RequestMethod.POST}
不符合请求方式：会出现405异常！
5.注解进阶----只能使用在方法上
get方式 @GetMapping==@RequestMapping(xxx,method=GET);
post方式 @PostMapping==@RequestMapping(xxx,method=POST);
put方式 @PutMapping==@RequestMapping(xxx,method=PUT);
delete方式 @DeleteMapping==@RequestMapping(xxx,method=DELETE);

 */
```

## 2.Param参数接收-四种

1.直接接收

/param/data?data?name=root&age=18

形参列表，填写对应名称的参数即可！请求参数名=形参参数名即可！

①名称相同 ②可以不传递，不报错

![image-20231121191857131](C:\Users\dyj\AppData\Roaming\Typora\typora-user-images\image-20231121191857131.png)

2.注解指定

//指定任意的请求参数名 要求必须拆掉你  要求不必须传递 给与一个默认值

/param/data1?account=root&page=1

account必须传递 page可以不必须传递，如果不传递默认就是1

> @RequestParam ->形参列表 指定请求参数名 或者是否必须传递 或者 非必须传递设置默认值
>
> 用法: @RequestParam(value=”指定请求参数名,如果形参名和请求参数名一致，可以省略!"
>
> required = false 前端是否必须传递此参数，默认是必须， 不传400异常!
>
> defaultValue="1”当非必须传递 false，可以设置默认值)

![image-20231121191919554](C:\Users\dyj\AppData\Roaming\Typora\typora-user-images\image-20231121191919554.png)

3.特殊值

一名多值 key=1&key=2 直接使用集合接值即可

//param/data2?hbs=吃&hbs=玩&hbs=学习

//不加注解@RequestParam 将 hbs对应的一个字符串直接赋值给集合! 类型异常!

//加了注解，经理就会将集合 add加入对应的字符串

![image-20231121191842561](C:\Users\dyj\AppData\Roaming\Typora\typora-user-images\image-20231121191842561.png)

4.使用实体对象接值 用户注册（用户信息）  ---》对应的实体类---》插入到数据库 表

/param/data3?name=二狗子&age=18 准备一个对应属性和get|set方法的实体类即可！->形参列表声明对象参数即可

![image-20231121191832477](C:\Users\dyj\AppData\Roaming\Typora\typora-user-images\image-20231121191832477.png)