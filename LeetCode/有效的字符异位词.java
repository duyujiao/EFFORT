class Solution {
    public boolean isAnagram(String s, String t) {
        char ss[]=s.toCharArray();
        char tt[]=t.toCharArray();
        int[] m=new int[26];
        int[] n=new int[26];
        int i=0;
        int j=0;
        for(i=0;i<s.length();i++)
        {
            m[ss[i]-'a']++;
        }
        for(j=0;j<t.length();j++)
        {
            n[tt[j]-'a']++;
        }
        if(Arrays.equals(m,n))
            return true;
        else
            return false;
    }
}