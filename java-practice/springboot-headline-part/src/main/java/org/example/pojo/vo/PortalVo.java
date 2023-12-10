package org.example.pojo.vo;

import lombok.Data;

@Data
public class PortalVo {
    //搜索标题关键字
    private String keyWords;
    //新闻类型
    private int type=0;
    //页码数
    private int pageNum=1;
    //页大小
    private int pageSize=10;

}
