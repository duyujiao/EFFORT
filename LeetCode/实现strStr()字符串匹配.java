class Solution {
    public int strStr(String haystack, String needle) {
        int l1=haystack.length();
        int l2=needle.length();
        char[] n=needle.toCharArray();
        char[] h=haystack.toCharArray();
        int i=0;
        int j=0;
        //i<=l1-l2为了确保haystack中的字符串长度不小于needle
        for(i=0;i<=l1-l2;i++)
        {
            for(j=0;j<l2;j++)
            {
                //不能改变i的值，后面要返回下标
                if(n[j]!=h[i+j])
                break;
            }
            if(j==l2)
        return i;
        }
        return -1;

    }
}