package org.example.controller;

import org.example.pojo.Student;
import org.example.service.StudentService;

import java.util.List;

public class StudentController {
    private StudentService studentService;
    public void setStudentService(StudentService studentService)
    {
        this.studentService=studentService;
    }
    public void findAll()
    {
        List<Student> studentList=studentService.findAll();
        System.out.println("studentList="+studentList);
    }
}
