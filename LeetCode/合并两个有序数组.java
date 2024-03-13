class Solution {
    public void merge(int[] nums1, int m, int[] nums2, int n) {
        int i=m-1;
        int j=n-1;
        int k=m+n-1;
        while(i>=0&&j>=0)
        {
            if(nums1[i]>nums2[j])
            {
            nums1[k]=nums1[i];
            i--;
            k--;
            }
            else
            {
            nums1[k]=nums2[j];
            j--;
            k--;
            }
            
        }
        /*arraycopy的使用，实现数组的复制
第一个参数:源数组

第二个参数：在源数组中，被复制的数字开始复制的下标

第三个参数：目标数组

第四个参数：从目标数组中，从第几个下标开始放入复制的数据

第五个参数：从源数组中，一共拿几个数值放到目标数组中

System.arraycopy(result, 0, str, 0, 0);
*/
        if(j>=0)
        System.arraycopy(nums2,0,nums1,0,j+1);

    }
}