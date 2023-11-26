package org.example.config;

import org.springframework.context.annotation.ComponentScan;
import org.springframework.context.annotation.Configuration;
import org.springframework.web.servlet.config.annotation.*;

//控制层的配置类@Configuration//配置类（controller,springmvc)
/*
1.controller   @ComponentScan({"org.example.controller","org.example.exceptionhandler"})
2.全局异常处理器  @ComponentScan({"org.example.controller","org.example.exceptionhandler"})
3.handlerMapping handlerAdapter  @EnableWebMvc
4.静态资源处理   configureDefaultServletHandling
5.jsp 视图解析器的前后缀 configureViewResolvers
6.json转换器   @EnableWebMvc
7.拦截器。。。 addInterceptors
 */
@EnableWebMvc
@Configuration//配置类
@ComponentScan({"org.example.controller","org.example.exceptionhandler"})
public class WebMvcJavaConfig implements WebMvcConfigurer {


    @Override//Ctrl+o
    public void configureDefaultServletHandling(DefaultServletHandlerConfigurer configurer) {
       configurer.enable();//开启
    }

    @Override
    public void configureViewResolvers(ViewResolverRegistry registry) {
        registry.jsp("/WEB-INF/views/","jsp");
    }

    @Override
    public void addInterceptors(InterceptorRegistry registry) {
       // registry.addInterceptor(new xx()).addPathPatterns().excludePathPatterns()
        //xx是拦截器的类
    }
}
