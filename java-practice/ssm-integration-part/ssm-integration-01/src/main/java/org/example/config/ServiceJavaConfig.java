package org.example.config;

//业务层配置类 service aop tx

import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.ComponentScan;
import org.springframework.context.annotation.Configuration;
import org.springframework.context.annotation.EnableAspectJAutoProxy;
import org.springframework.jdbc.datasource.DataSourceTransactionManager;
import org.springframework.transaction.TransactionManager;
import org.springframework.transaction.annotation.EnableTransactionManagement;

import javax.sql.DataSource;

/*
1.service
2.开启aop注解的支持@EnableAspectJAutoProxy  aspect:@After @Before @AfterReturning @AfterThrowing @Around @Aspect @Order
3.tx 声明式事务管理 @EnableTransactionManagement：1.对应的事务管理器实现 [TransactionManager DatatSource,Hibernate,Jpa]
                                                2.开启事务注解支持 @Transactional
 */
@Configuration
@EnableAspectJAutoProxy
@EnableTransactionManagement
@ComponentScan("org.example.service")
public class ServiceJavaConfig {
    //注入连接池 一种是直接调用Bean方法，另一种是在形参列表
    @Bean
    public TransactionManager transactionManager(DataSource dataSource){
        DataSourceTransactionManager dataSourceTransactionManager = new DataSourceTransactionManager();
        dataSourceTransactionManager.setDataSource(dataSource);
        return dataSourceTransactionManager;

    }
}
