package org.example.service.impl;

import com.baomidou.mybatisplus.extension.service.impl.ServiceImpl;
import org.example.pojo.Type;
import org.example.service.TypeService;
import org.example.mapper.TypeMapper;
import org.example.utils.Result;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import java.util.List;

/**
* @author dyj
* @description 针对表【news_type】的数据库操作Service实现
* @createDate 2023-12-08 13:23:01
*/
@Service
public class TypeServiceImpl extends ServiceImpl<TypeMapper, Type>
    implements TypeService{
    @Autowired
    private TypeMapper typeMapper;

    @Override
    public Result findAllTypes() {
        //不传条件就代表查全部
        List<Type> types = typeMapper.selectList(null);
        return Result.ok(types);
    }
}




