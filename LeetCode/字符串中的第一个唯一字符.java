class Solution {
    public int firstUniqChar(String s) {
        char[] MyChar=s.toCharArray();
        int c[]=new int[26];
        int i=0;
        for(i=0;i<s.length();i++)
        {
            c[MyChar[i]-'a']++;
        }
        for(int j=0;j<s.length();j++)
        {
            if(c[MyChar[j]-'a']==1)
                return j;
        }
        return -1;

    }
}