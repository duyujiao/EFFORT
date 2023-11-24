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

## 3.路径 参数接收

//path/账号/密码

动态路径设计 {key}=*   {key}在形参列表获取传入的参数

接收路径参数 String account,String password->接收param格式参数

必须使用@PathVariable

![image-20231121193852896](C:\Users\dyj\AppData\Roaming\Typora\typora-user-images\image-20231121193852896.png)

 ![image-20231121193958233](C:\Users\dyj\AppData\Roaming\Typora\typora-user-images\image-20231121193958233.png) 

## 3.json 参数接收

①正常声明实体类

②参数列表前加@RequestBody

③导入json处理的依赖

④handlerAdapter配置json转化器 @EnableWebMvc，这是交给经理

添加秘书，添加经理，给经理添加jacksonjson处理器

postman

![image-20231121200204153](C:\Users\dyj\AppData\Roaming\Typora\typora-user-images\image-20231121200204153.png)

data-->请求体 post {name,age,gender}

前端--》json->415 不支持数据类型呢？？

原因：Java原生的api，只支持路径参数和param参数 request.getParameter("key")；param   不支持json，json就是前端的格式

解决：1.导入json处理的依赖

```html
<dependency>
    <groupId>com.fasterxml.jackson.core</groupId>
    <artifactId>jackson-databind</artifactId>
    <version>2.15.0</version>
</dependency>
```

2.handlerAdapter配置json转化器 @EnableWebMvc

## 4.接收Cookie数据

@CookieValue

## 5.接收请求头数据

@RequestHeader

## 6.原生Api对象操作

![image-20231121210037091](C:\Users\dyj\AppData\Roaming\Typora\typora-user-images\image-20231121210037091.png)

```java
/**
 * 如果想要获取请求或者响应对象,或者会话等,可以直接在形参列表传入,并且不分先后顺序!
 * 注意: 接收原生对象,并不影响参数接收!
 */
@GetMapping("api")
@ResponseBody
public String api(HttpSession session , HttpServletRequest request,
                  HttpServletResponse response){
    String method = request.getMethod();
    System.out.println("method = " + method);
    return "api";
}
```

## 7.共享域获取

共享域的作用是提供了方便实用的方式在同一 Web 应用程序的多个组件之间传递数据，并且可以将数据保存在不同的共享域中，根据需要进行选择和使用。

Model,ModelMap,Map,ModelAndView

## 8.总结

![](C:\Users\dyj\Pictures\Screenshots\屏幕截图 2023-11-21 214948.png)

servlet流程

![image-20231121230242394](C:\Users\dyj\AppData\Roaming\Typora\typora-user-images\image-20231121230242394.png)****

# 三、SpringMVC响应数据

![image-20231123204018888](C:\Users\dyj\AppData\Roaming\Typora\typora-user-images\image-20231123204018888.png)

## 1.转发和重定向

路径细节：（不使用springmvc request response)

转发是项目下的资源跳转。路径：项目下的地址 /jsp/index 忽略：applicationContext

重定向项目下的资源可以是项目外的地址 重定向属于二次请求 路径：项目下的地址 全地址 不忽略/springmvc/jsp/index

（ 使用springmvc路径语法）：

”forward:路径|redirect:路径“ 重定向，资源的地址也不需要写项目的根路径！  /jsp/index    转发和重定向的地址都一样了！

转发：方法返回值写成字符串类型；不能添加responseBody注解，返回字符串前面forward:/转发的地址

重定向：方法返回值写成字符串类型；不能添加responseBody注解，返回字符串前面redirect:/重定向的地址

转发这个/jsp/forward

![image-20231123212759369](C:\Users\dyj\AppData\Roaming\Typora\typora-user-images\image-20231123212759369.png)

重定向跳转到/jsp/index

![image-20231123212743728](C:\Users\dyj\AppData\Roaming\Typora\typora-user-images\image-20231123212743728.png)

## 2.返回json数据

return user;user对象给handlerAdapter转成json，添加@ResponseBody注解，不用找视图解析器，json直接返回

@Controller+@ResponseBody==@RestController 加到类上

@ResponseBody 数据直接放入响应体返回！也不会在走视图解析器   快速查找视图，转发和重定向都不生效了

## 3.静态资源处理

![image-20231123220938187](C:\Users\dyj\AppData\Roaming\Typora\typora-user-images\image-20231123220938187.png)

# 四、RESTFul

Http协议的标准使用方案和风格

![image-20231123222133003](C:\Users\dyj\AppData\Roaming\Typora\typora-user-images\image-20231123222133003.png)

 ![image-20231123223959261](C:\Users\dyj\AppData\Roaming\Typora\typora-user-images\image-20231123223959261.png)

![image-20231123225637134](C:\Users\dyj\AppData\Roaming\Typora\typora-user-images\image-20231123225637134.png)

|          |                  |                               |              |
| -------- | ---------------- | ----------------------------- | ------------ |
| 功能     | 接口和请求方式   | 请求参数                      | 返回值       |
| 分页查询 | GET  /user       | page=1&size=10                | { 响应数据 } |
| 用户添加 | POST /user       | { user 数据 }                 | {响应数据}   |
| 用户详情 | GET /user/1      | 路径参数                      | {响应数据}   |
| 用户更新 | PUT /user        | { user 更新数据}              | {响应数据}   |
| 用户删除 | DELETE /user/1   | 路径参数                      | {响应数据}   |
| 条件模糊 | GET /user/search | page=1&size=10&keywork=关键字 | {响应数据}   |

# 五、异常处理

## 全局异常处理器

![image-20231124174651216](C:\Users\dyj\AppData\Roaming\Typora\typora-user-images\image-20231124174651216.png)

![image-20231124174726118](C:\Users\dyj\AppData\Roaming\Typora\typora-user-images\image-20231124174726118.png)

## 拦截器

![image-20231124175539945](C:\Users\dyj\AppData\Roaming\Typora\typora-user-images\image-20231124175539945.png)

多个拦截器执行顺序

![image-20231124182417164](C:\Users\dyj\AppData\Roaming\Typora\typora-user-images\image-20231124182417164.png)

## 参数校验

@NotNull  包装类型

 @NotEmpty 集合类型

 @NotBlank 字符串，不为null，切不为"  "字符串

![image-20231124201619206](C:\Users\dyj\AppData\Roaming\Typora\typora-user-images\image-20231124201619206.png)

JSR 303 是 Java 为 Bean 数据合法性校验提供的标准框架，它已经包含在 JavaEE 6.0 标准中。JSR 303 通过在 Bean 属性上标注类似于 @NotNull、@Max 等标准的注解指定校验规则，并通过标准的验证接口对Bean进行验证。

| 注解                       | 规则                                           |
| -------------------------- | ---------------------------------------------- |
| @Null                      | 标注值必须为 null                              |
| @NotNull                   | 标注值不可为 null                              |
| @AssertTrue                | 标注值必须为 true                              |
| @AssertFalse               | 标注值必须为 false                             |
| @Min(value)                | 标注值必须大于或等于 value                     |
| @Max(value)                | 标注值必须小于或等于 value                     |
| @DecimalMin(value)         | 标注值必须大于或等于 value                     |
| @DecimalMax(value)         | 标注值必须小于或等于 value                     |
| @Size(max,min)             | 标注值大小必须在 max 和 min 限定的范围内       |
| @Digits(integer,fratction) | 标注值值必须是一个数字，且必须在可接受的范围内 |
| @Past                      | 标注值只能用于日期型，且必须是过去的日期       |
| @Future                    | 标注值只能用于日期型，且必须是将来的日期       |
| @Pattern(value)            | 标注值必须符合指定的正则表达式                 |


JSR 303 只是一套标准，需要提供其实现才可以使用。Hibernate Validator 是 JSR 303 的一个参考实现，除支持所有标准的校验注解外，它还支持以下的扩展注解：

| 注解      | 规则                               |
| --------- | ---------------------------------- |
| @Email    | 标注值必须是格式正确的 Email 地址  |
| @Length   | 标注值字符串大小必须在指定的范围内 |
| @NotEmpty | 标注值字符串不能是空字符串         |
| @Range    | 标注值必须在指定的范围内           |


Spring 4.0 版本已经拥有自己独立的数据校验框架，同时支持 JSR 303 标准的校验框架。Spring 在进行数据绑定时，可同时调用校验框架完成数据校验工作。在SpringMVC 中，可直接通过注解驱动 @EnableWebMvc 的方式进行数据校验。Spring 的 LocalValidatorFactoryBean 既实现了 Spring 的 Validator 接口，也实现了 JSR 303 的 Validator 接口。只要在Spring容器中定义了一个LocalValidatorFactoryBean，即可将其注入到需要数据校验的 Bean中。Spring本身并没有提供JSR 303的实现，所以必须将JSR 303的实现者的jar包放到类路径下。

配置 @EnableWebMvc后，SpringMVC 会默认装配好一个 LocalValidatorFactoryBean，通过在处理方法的入参上标注 @Validated 注解即可让 SpringMVC 在完成数据绑定后执行数据校验的工作。

## 六、总结

|                 |                                            |
| --------------- | ------------------------------------------ |
| 核心点          | 掌握目标                                   |
| springmvc框架   | 主要作用、核心组件、调用流程               |
| 简化参数接收    | 路径设计、参数接收、请求头接收、cookie接收 |
| 简化数据响应    | 模板页面、转发和重定向、JSON数据、静态资源 |
| restful风格设计 | 主要作用、具体规范、请求方式和请求参数选择 |
| 功能扩展        | 全局异常处理、拦截器、参数校验注解         |

