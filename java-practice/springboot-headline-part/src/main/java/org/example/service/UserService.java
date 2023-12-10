package org.example.service;

import org.example.pojo.User;
import com.baomidou.mybatisplus.extension.service.IService;
import org.example.utils.Result;

/**
* @author dyj
* @description 针对表【news_user】的数据库操作Service
* @createDate 2023-12-08 13:23:01
*/
public interface UserService extends IService<User> {



    //登陆业务
    Result login(User user);

    //根据token获取用户数据
    Result getUserInfo(String token);

    //检查账号是否可用，被占用
    Result checkUserName(String username);

    //注册业务
    Result regist(User user);

}
