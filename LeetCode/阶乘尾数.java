class Solution {
    public int trailingZeroes(int n) {
        //尾随零是*10；10是5*2；5比2的个数多；所有计算能被5整除的，每隔5个数有一个5出现，25个数2个5，。。。。
        int count=0;
        while(n>=5)
        {
            n=n/5;
            count+=n;
        }
        return count;
    }
        
}