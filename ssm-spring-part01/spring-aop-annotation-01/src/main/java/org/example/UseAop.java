package org.example;

import org.example.statics.StaticProxyCalculator;

public class UseAop {
    public static void main(String[] args) {
        //房东 目标
        Calculator target=new CalculatorPureImpl();
        //中介 代理
        Calculator proxy=new StaticProxyCalculator(target);
        //调用
        int add= proxy.add(1,1);
        System.out.println("add="+add);
    }
}
