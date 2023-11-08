package org.example.service;

import org.example.pojo.Student;

import java.util.List;

public interface StudentService {
    //查询全部学员业务
    List<Student> findAll();
}
