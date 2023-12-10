package org.example.service;

import org.example.pojo.Type;
import com.baomidou.mybatisplus.extension.service.IService;
import org.example.utils.Result;

/**
* @author dyj
* @description 针对表【news_type】的数据库操作Service
* @createDate 2023-12-08 13:23:01
*/
public interface TypeService extends IService<Type> {

    //查询所有类别数据
    Result findAllTypes();
}
