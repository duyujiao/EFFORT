package org.example.test;

import org.apache.ibatis.io.Resources;
import org.apache.ibatis.session.SqlSession;
import org.apache.ibatis.session.SqlSessionFactory;
import org.apache.ibatis.session.SqlSessionFactoryBuilder;
import org.example.mapper.EmployeeMapper;
import org.example.pojo.Employee;
import org.junit.jupiter.api.Test;

import java.io.IOException;
import java.io.InputStream;

public class MybatisTest {
    //通过mybatis提供的API进行方法的调用
    @Test
    public void test_01() throws IOException {

        //1.读取外部配置文件（mybatis-config.xml）
        InputStream ips= Resources.getResourceAsStream("mybatis-config.xml");
        //2.创建sqlSessionFactory
        SqlSessionFactory sqlSessionFactory=new SqlSessionFactoryBuilder().build(ips);
        //3.根据sqlSessionFactory创建sqlSession(每次业务创建一个用完就释放）
        SqlSession sqlSession = sqlSessionFactory.openSession();
        //4.获取接口的代理对象（代理技术）调用代理对象的方法，就会查找mapper接口的方法
        EmployeeMapper mapper=sqlSession.getMapper(EmployeeMapper.class);
        Employee employee = mapper.queryById(1);
        System.out.println("employee="+employee);
        //5.提交事务（非DQL）和释放资源
        sqlSession.commit();
        sqlSession.close();


    }
}
