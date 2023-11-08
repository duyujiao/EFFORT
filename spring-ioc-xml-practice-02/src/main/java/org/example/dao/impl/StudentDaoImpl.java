package org.example.dao.impl;

import org.example.dao.StudentDao;
import org.example.pojo.Student;
import org.springframework.jdbc.core.BeanPropertyRowMapper;
import org.springframework.jdbc.core.JdbcOperations;
import org.springframework.jdbc.core.JdbcTemplate;

import java.util.List;

public class StudentDaoImpl implements StudentDao {
    private JdbcTemplate jdbcTemplate;
    //注入我们的jdbcTemplate对象
    public void setJdbcTemplate(JdbcTemplate jdbcTemplate)
    {
        this.jdbcTemplate=jdbcTemplate;
    }

    //查询全部学生数据

    @Override
    public List<Student> queryAll() {
        String sql="select id,name,age,gender,class as classes from students;";

        //query可以返回集合！
        //BeanPropertyRowMapper就是封装好RowMapper的实现，要求属性名和列名相同即可‘
        List<Student> studentList=jdbcTemplate.query(sql,new BeanPropertyRowMapper<>(Student.class));

        return studentList;
    }
}
