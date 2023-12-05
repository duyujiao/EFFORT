class Solution {
    public String longestCommonPrefix(String[] strs) {
        int i=0;
        int j=0;
        int rows=strs.length;//行
        int cols=strs[0].length();//列
        char[][] str=new char[rows][cols];
        //String s="";
        StringBuilder sb = new StringBuilder();
        for(int m=0;m<rows;m++)
        {
            str[m]=strs[m].toCharArray();
            //最后加上这条语句成功，输入["ab", "a"]的时候，会出现数组越界，问题就出现在了cols计算上
            //“ab”两个字符，“a”一个字符，应该是最小的长度作为列数
            cols = Math.min(cols, str[m].length);
        }
        
        for(j=0;j<cols;j++)
        {
            for(i=0;i<rows-1;i++)
            {
                if(str[i][j]!=str[i+1][j])
               break;
            }
             if (i == rows - 1) 
            {
               // s +=str[0][j];
                 sb.append(str[0][j]);
            } 
            else {
                break;
            }
        }
       return sb.toString();
    }
}