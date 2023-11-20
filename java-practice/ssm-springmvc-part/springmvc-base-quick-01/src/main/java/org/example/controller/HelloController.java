package org.example.controller;

import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.ResponseBody;

@Controller
public class HelloController {
    //hander -> 地址：springmvc/hello 最终返回的是return "hello springmvc!!"
    //秘书得知道有你呀，所有要加@RuquestMapping
    @RequestMapping("springmvc/hello")//对外访问的地址 到handlerMapping注册的注解
    @ResponseBody//直接返回字符串给前端，不要找视图解析器
    public String hello()
    {
        System.out.println("HelloController.hello");
        //返回给前端
        return "hello springmvc!!";
    }
}
