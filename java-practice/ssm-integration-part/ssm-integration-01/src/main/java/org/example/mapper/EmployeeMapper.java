package org.example.mapper;

import org.example.pojo.Employee;

import java.util.List;

public interface EmployeeMapper {
    //查询全部员工信息
    List<Employee> queryList();
}
