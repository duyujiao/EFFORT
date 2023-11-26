package org.example.config;

import com.github.pagehelper.PageInterceptor;
import org.apache.ibatis.logging.slf4j.Slf4jImpl;
import org.apache.ibatis.session.AutoMappingBehavior;
import org.mybatis.spring.SqlSessionFactoryBean;
import org.mybatis.spring.mapper.MapperScannerConfigurer;
import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.ComponentScan;
import org.springframework.context.annotation.Configuration;

import javax.sql.DataSource;
import java.util.Properties;

@Configuration
public class MapperJavaConfigNew {
    //sqlSessionFactory加入到ioc容器
    //mybatis->sqlSessionFactory[ioc]->getObject()->sqlSessionFactory
    //方式一:外部指定mybatis-config.xml[mybatis的配置 除了连接池，mapper指定]
    //方式二：采用方式二
    @Bean
    public SqlSessionFactoryBean sqlSessionFactory(DataSource dataSource){
        SqlSessionFactoryBean sqlSessionFactoryBean = new SqlSessionFactoryBean();
        //指定配置文件等信息
        //指定数据库连接池对象
        sqlSessionFactoryBean.setDataSource(dataSource);
        //指定mybatis配置文件的功能，使用代码的形式
        org.apache.ibatis.session.Configuration configuration=new org.apache.ibatis.session.Configuration();
        //<setting name="mapUnderscoreToCamelCase" value="true">
        //开启驼峰式
        configuration.setMapUnderscoreToCamelCase(true);
        //开启logback日志输出
        configuration.setLogImpl(Slf4jImpl.class);
        //开启resultMap自动映射
        configuration.setAutoMappingBehavior(AutoMappingBehavior.FULL);
        sqlSessionFactoryBean.setConfiguration(configuration);

        //给实体类起别名
        sqlSessionFactoryBean.setTypeAliasesPackage("org.example.pojo");

        PageInterceptor pageInterceptor=new PageInterceptor();
        Properties properties=new Properties();
        properties.setProperty("helperDialect","mysql");
        pageInterceptor.setProperties(properties);
        sqlSessionFactoryBean.addPlugins(pageInterceptor);

        return sqlSessionFactoryBean;

    }
    @Bean
    public MapperScannerConfigurer mapperScannerConfigurer(){
        //Mapper代理兑现的factoryBean-》指定一个包-》mapper接口-》sqlSessionFactory->sqlSession->getMapper-》mapper代理对象->ioc
        MapperScannerConfigurer mapperScannerConfigurer = new MapperScannerConfigurer();
        mapperScannerConfigurer.setBasePackage("org.example.mapper");//mapper接口和mapperxml所在的共同包
        return mapperScannerConfigurer;

    }
}
