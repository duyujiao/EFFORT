/* The isBadVersion API is defined in the parent class VersionControl.
      boolean isBadVersion(int version); */

      public class Solution extends VersionControl {
        public int firstBadVersion(int n) {
            //二分法
            int left=1;
            int right=n;
             
            while(left<right)
            {
               int mid=(left+right)>>>1;
               if(!isBadVersion(mid))
               left=mid+1;
               else
               right=mid;
    
            }
            return left;
            
        }
    }