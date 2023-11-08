package org.example.dao.Impl;

import org.example.dao.StudentDao;
import org.example.pojo.Student;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.jdbc.core.BeanPropertyRowMapper;
import org.springframework.jdbc.core.JdbcTemplate;
import org.springframework.stereotype.Component;
import org.springframework.stereotype.Repository;

import java.util.List;
@Repository
public class StudentDaoImpl implements StudentDao {

    @Autowired
    private JdbcTemplate jdbcTemplate;
    @Override
    public List<Student> queryAll() {
        String sql="select id,name,age,gender,class as classes from students;";
        //query可以返回集合
        List<Student> studentList=jdbcTemplate.query(sql,new BeanPropertyRowMapper<>(Student.class));
        return studentList;
    }
}
