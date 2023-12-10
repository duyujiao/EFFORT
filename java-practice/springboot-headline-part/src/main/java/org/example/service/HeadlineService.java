package org.example.service;

import org.example.pojo.Headline;
import com.baomidou.mybatisplus.extension.service.IService;
import org.example.pojo.vo.PortalVo;
import org.example.utils.Result;

/**
* @author dyj
* @description 针对表【news_headline】的数据库操作Service
* @createDate 2023-12-08 13:23:01
*/
public interface HeadlineService extends IService<Headline> {

    //首页数据查询
    Result findNewsPage(PortalVo portalVo);

    //根据id查询详情
    Result showHeadlineDetail(Integer hid);

    //发布头条方法-插入
    Result publish(Headline headline,String token);

    //修改头条数据
    Result updateData(Headline headline);
}
