package org.example.controller;

import com.alibaba.druid.util.StringUtils;
import org.example.pojo.User;
import org.example.service.UserService;
import org.example.utils.JwtHelper;
import org.example.utils.Result;
import org.example.utils.ResultCodeEnum;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.context.annotation.Bean;
import org.springframework.web.bind.annotation.*;

//这一次只负责接收和返回结果，具体怎么是业务层干的
@RestController
@RequestMapping("user")
@CrossOrigin//跨域
public class UserController {
    @Autowired
    private UserService userService;
    @Autowired
    private JwtHelper jwtHelper;

    @PostMapping("login")
    public Result login(@RequestBody User user){
        Result result=userService.login(user);
        return result;
    }

    @GetMapping("getUserInfo")
    //@RequestHeader 是一个注解，用于从HTTP请求的头部获取值，并将其绑定到方法参数上。
    public Result getUserInfo(@RequestHeader String token)
    {
        Result result=userService.getUserInfo(token);
        return result;
    }

    @PostMapping("checkUserName")
    public Result checkUserName(String username)
    {
        Result result=userService.checkUserName(username);
        return result;
    }

    @PostMapping("regist")
    public Result regist(@RequestBody User user)
    {
        Result result=userService.regist(user);
        return result;
    }

    @GetMapping("checkLogin")
    public Result checkLogin(@RequestHeader String token)
    {
        boolean expiration = jwtHelper.isExpiration(token);
        if(expiration|| StringUtils.isEmpty(token)){
            //已经过期了
            return Result.build(null, ResultCodeEnum.NOTLOGIN);
        }
        return Result.ok(null);

    }
}
