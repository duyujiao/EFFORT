package org.example.service.impl;

import com.alibaba.druid.util.StringUtils;
import com.baomidou.mybatisplus.core.conditions.query.LambdaQueryWrapper;
import com.baomidou.mybatisplus.extension.service.impl.ServiceImpl;
import org.example.pojo.User;
import org.example.service.UserService;
import org.example.mapper.UserMapper;
import org.example.utils.JwtHelper;
import org.example.utils.MD5Util;
import org.example.utils.Result;
import org.example.utils.ResultCodeEnum;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import java.util.HashMap;
import java.util.Map;




/**
* @author dyj
* @description 针对表【news_user】的数据库操作Service实现
* @createDate 2023-12-08 13:23:01
*/

//登录就是数据库查询
@Service
public class UserServiceImpl extends ServiceImpl<UserMapper, User>
    implements UserService{
    @Autowired
    private UserMapper userMapper;
    @Autowired
    private JwtHelper jwtHelper;

    /*
        登录业务
        1.根据账号，查询用户对象- loginUser
        2.如果用户对象为null,查询失败，账号错误！501
        3.然后对比，密码，失败，返回503的错误
        4.根据用户id生成一个token,token->result返回
     */

    @Override
    public Result login(User user) {

        //根据账号查询数据
        LambdaQueryWrapper<User> lambdaQueryWrapper = new LambdaQueryWrapper<>();
        lambdaQueryWrapper.eq(User::getUsername,user.getUsername());
        User loginUser=userMapper.selectOne(lambdaQueryWrapper);
        if(loginUser==null)
        {
            return Result.build(null, ResultCodeEnum.USERNAME_ERROR);
        }

        //对比密码
        if(!StringUtils.isEmpty(user.getUserPwd())&& MD5Util.encrypt(user.getUserPwd()).equals(loginUser.getUserPwd())){
            //登录成功
            //根据用户id生成token(jwt),将token封装到result返回
            String token = jwtHelper.createToken(Long.valueOf(loginUser.getUid()));
            Map data=new HashMap();
            data.put("token",token);
            return Result.ok(data);

        }
        //密码错误
        else
        return Result.build(null,ResultCodeEnum.PASSWORD_ERROR);
    }

    /*
        根据token获取用户数据
        1.token是否在有效期
        2.根据token解析用户userId
        3.根据id查询数据
        4.去掉密码，封装result结果返回即可
     */
    @Override
    public Result getUserInfo(String token) {
        //判断token是否过期，true过期，false没过期
        boolean expiration = jwtHelper.isExpiration(token);
        if(expiration)
        {
            //失效，未登录看待
            return Result.build(null,ResultCodeEnum.NOTLOGIN);
        }
        int userId = jwtHelper.getUserId(token).intValue();
        User user=userMapper.selectById(userId);
        user.setUserPwd("");
        Map data=new HashMap<>();
        data.put("loginUser",user);

        return Result.ok(data);
    }

    /*
        检查账号是否可用
        1.根据账号进行count查询
        2.count==0 可用
        3.count>0 不可用
     */

    @Override
    public Result checkUserName(String username) {
        LambdaQueryWrapper<User> lambdaQueryWrapper=new LambdaQueryWrapper<>();
        lambdaQueryWrapper.eq(User::getUsername,username);
        Long count = userMapper.selectCount(lambdaQueryWrapper);
        if(count==0)
        {
            return Result.ok(null);
        }
        return Result.build(null,ResultCodeEnum.USERNAME_USED);
    }

    /*
        注册业务
        1.依然检查账号是否已经被注册
        2.密码加密处理
        3.账号数据保存
        4.返回结果
     */
    @Override
    public Result regist(User user) {
        LambdaQueryWrapper<User> lambdaQueryWrapper=new LambdaQueryWrapper<>();
        lambdaQueryWrapper.eq(User::getUsername,user.getUsername());
        Long count = userMapper.selectCount(lambdaQueryWrapper);
        if(count>0)
        {
            return Result.build(null,ResultCodeEnum.USERNAME_USED);
        }
        //密码加密
        user.setUserPwd(MD5Util.encrypt(user.getUserPwd()));
        userMapper.insert(user);
        return Result.ok(null);
    }
}




