class Solution {
    public boolean isPalindrome(String s) {
        String str=s.toLowerCase();
        char ss[]=str.toCharArray();
        int l=str.length();
        int i=0;
        int m=0;
        for(i=0;i<l;i++)
        {
           if(!Character.isLetterOrDigit(ss[i]))
           {
               for(int j=i;j<l-1;j++)
                {
                    ss[j]=ss[j+1]; 
                }
                l--;
                i--;   
            }
        }
        for(int left=m,right=l-1;left<right;left++,right--)
        {
            if(ss[left]!=ss[right])
                return false;
        }
        return true;
    }
}