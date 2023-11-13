package org.example.mapper;
//规定数据库方法即可

import org.example.pojo.Employee;

public interface EmployeeMapper {
    //根据id查询员工信息
    Employee queryById(Integer id);

    int deleteById(Integer id);

}
