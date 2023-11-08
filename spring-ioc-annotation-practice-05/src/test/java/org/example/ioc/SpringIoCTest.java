package org.example.ioc;

import org.example.controller.StudentController;
import org.junit.jupiter.api.Test;
import org.springframework.context.ApplicationContext;
import org.springframework.context.support.ClassPathXmlApplicationContext;

public class SpringIoCTest {
    @Test
    public void test()
    {
        ApplicationContext applicationContext=new ClassPathXmlApplicationContext("spring.xml");
        StudentController controller = applicationContext.getBean(StudentController.class);
        controller.findAll();
    }
}
