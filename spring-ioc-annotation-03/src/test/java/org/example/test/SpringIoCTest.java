package org.example.test;

import org.example.ioc_01.XxxDao;
import org.junit.jupiter.api.Test;
import org.springframework.context.support.ClassPathXmlApplicationContext;

//springioc测试
public class SpringIoCTest {
    @Test
    public void testIoC_01()
    {

        //1.创建ioc容器
        ClassPathXmlApplicationContext applicationContext=new ClassPathXmlApplicationContext("spring-01.xml");
        //2.获取组件
        XxxDao bean = applicationContext.getBean(XxxDao.class);
        System.out.println("bean="+bean);

        //添加ioc注解，默认的组件名为 类的首字母小写
        Object xxxService=applicationContext.getBean("xxxService");
        System.out.println("xxxService="+xxxService);
        //3.close容器
        applicationContext.close();
        //运行结果
        /*
        bean=org.example.ioc_01.XxxDao@769a1df5
        xxxService=org.example.ioc_01.XxxService@41f69e84
         */






    }
}
