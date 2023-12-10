package org.example.service.impl;

import com.baomidou.mybatisplus.core.metadata.IPage;
import com.baomidou.mybatisplus.extension.plugins.pagination.Page;
import com.baomidou.mybatisplus.extension.service.impl.ServiceImpl;
import org.example.pojo.Headline;
import org.example.pojo.vo.PortalVo;
import org.example.service.HeadlineService;
import org.example.mapper.HeadlineMapper;
import org.example.utils.JwtHelper;
import org.example.utils.Result;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import java.util.Date;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

/**
* @author dyj
* @description 针对表【news_headline】的数据库操作Service实现
* @createDate 2023-12-08 13:23:01
*/
@Service
public class HeadlineServiceImpl extends ServiceImpl<HeadlineMapper, Headline>
    implements HeadlineService{
    @Autowired
    private HeadlineMapper headlineMapper;
    @Autowired
    private JwtHelper jwtHelper;

    /*
        首页数据查询
        1.进行分页数据查询
        2.分页数据，拼接到result即可

        注意一：查询需要自定义语句，自定义Mapper的方法，携带分页
        注意二：返回的结果List<Map>
     */
    @Override
    public Result findNewsPage(PortalVo portalVo) {
        //Page->当前页数 页容量 默认 1 10
        IPage<Map> page=new Page<>(portalVo.getPageNum(),portalVo.getPageSize());
        headlineMapper.selectMyPage(page,portalVo);

        List<Map> records = page.getRecords();
        Map data=new HashMap();
        data.put("pageData",records);
        data.put("pageNum",page.getCurrent());//页码数
        data.put("pageSize",page.getSize());//页大小
        data.put("totalpage",page.getPages());//总页数
        data.put("totalSize",page.getTotal());//总记录数

        Map pageInfo=new HashMap();
        pageInfo.put("pageInfo",data);

        return Result.ok(pageInfo);
    }

    /*
        根据id查询详情

        1.查询对应的数据即可【多表查询，头条和用户表，方法需要自定义 返回map即可】
        2.修改阅读量+1【version乐观锁，当前数据对应的版本号】
     */
    @Override
    public Result showHeadlineDetail(Integer hid) {
        Map data=headlineMapper.queryDetailMap(hid);
        Map headline=new HashMap();
        headline.put("headline",data);

        //修改阅读量+1
        Headline headline1=new Headline();
        headline1.setHid((Integer)data.get("hid"));
        headline1.setVersion((Integer) data.get("version"));
        //阅读量+1
        headline1.setPageViews((Integer) data.get("pageViews")+1);
        headlineMapper.updateById(headline1);
        return Result.ok(headline);
    }

    /*
        发布头条的方法
        1.补全数据
     */

    @Override
    public Result publish(Headline headline,String token) {
        //token查询用户id
        int userId=jwtHelper.getUserId(token).intValue();
        //数据装配
        headline.setPublisher(userId);
        headline.setPageViews(0);
        headline.setCreateTime(new Date());
        headline.setUpdateTime(new Date());

        headlineMapper.insert(headline);
        return Result.ok(null);
    }

    /*
        修改头条数据
        1.hid查询数据的最新version
        2.修改数据的修改时间为当前节点

     */

    @Override
    public Result updateData(Headline headline) {
        Integer version=headlineMapper.selectById(headline.getHid()).getVersion();
        headline.setVersion(version);//乐观锁
        headline.setUpdateTime(new Date());
        headlineMapper.updateById(headline);
        return Result.ok(null);
    }
}




