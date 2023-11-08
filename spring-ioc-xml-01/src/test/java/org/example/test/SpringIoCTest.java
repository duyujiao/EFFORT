package org.example.test;

//ioc容器创建和读取组件的测试类
//创建就是实例化

import org.example.ioc_03.HappyComponent;
import org.junit.jupiter.api.Test;
import org.springframework.context.ApplicationContext;
import org.springframework.context.support.ClassPathXmlApplicationContext;

public class SpringIoCTest {

    //讲解如何创建ioc容器并且读取配置文件
    public void createIoC()
    {
        //创建容器 选择合适的容器实现即可
        /*
        接口
        BeanFactory

        ApplicationContext

        实现类

        ClassPathXmlApplicationContext 读取类路径下的xml配置方式
        FileSystemXmlApplicationContext 读取指定文件位置的xml配置方式 比如说c盘D盘
        AnnotationConfigApplicationContext 读取配置类方式的ioc容器
        WebApplicationContext web项目专属的配置的ioc容器
         */

        //方式一：直接创建容器并且指定配置文件
        //构造函数（Spring...配置文件）可以填写一个或者多个
        ApplicationContext applicationContext=new ClassPathXmlApplicationContext("spring-03.xml","spring-x.xml");
        //方式二;先创建ioc容器对象，再指定配置文件，再刷新
        //源码的配置过程！创建容器[spring]和配置文件指定分开[自己指定]
        ClassPathXmlApplicationContext applicationContext1=new ClassPathXmlApplicationContext();
        applicationContext1.setConfigLocations("spring-03.xml");//外部配置文件的设置
        applicationContext1.refresh();//调用ioc和DI的流程



    }
    @Test

    //讲解如何在IoC容器中获取组件Bean
    public void getBeanFromIoC() {
        //1.创建ioc容器对象
        ClassPathXmlApplicationContext applicationContext = new ClassPathXmlApplicationContext();
        applicationContext.setConfigLocations("spring-03.xml");
        //注意不刷新不行
        applicationContext.refresh();

        //2.读取ioc容器的组件
        //方案一：直接根据beanId获取即可  返回值类型是Object 需要强转（不推荐）
        HappyComponent happyComponent = (HappyComponent) applicationContext.getBean("happyComponent");

        //方案二：根据beanId,同时指定bean的类型Class
        //applicationContext.getBean("happycomponent", HappyComponent.class).var回车

        HappyComponent happyComponent1 = applicationContext.getBean("happyComponent", HappyComponent.class);

        //方案三：：直接根据类型获取
        //注意：根据bean类型获取，同一个类型，在ioc容器中只能有一个bean
        //如果ioc容器存在多个同类型的Bean，会出现：NoUniqueBeanDefinitionException
        //ioc的配置一定是实现类，但是可以根据接口类型获取值！getBean(类型);instanceof ioc容器的类型==true
        /*
        根据类型来获取bean时，在满足bean唯一性的前提下，其实只是看：『对象 instanceof 指定的类型』的返回结果，
       只要返回的是true就可以认定为和类型匹配，能够获取到。
        */
        HappyComponent happyComponent2 = applicationContext.getBean(HappyComponent.class);

        happyComponent2.doWork();
        System.out.println(happyComponent==happyComponent1);
        System.out.println(happyComponent2==happyComponent1);

        //运行结果
        //HappyComponent.doWork
        //true
        //true
    }
    }
