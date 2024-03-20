/**
 * Definition for a binary tree node.
 * public class TreeNode {
 *     int val;
 *     TreeNode left;
 *     TreeNode right;
 *     TreeNode() {}
 *     TreeNode(int val) { this.val = val; }
 *     TreeNode(int val, TreeNode left, TreeNode right) {
 *         this.val = val;
 *         this.left = left;
 *         this.right = right;
 *     }
 * }
 */
class Solution {
    public TreeNode sortedArrayToBST(int[] nums) {
        return Balance(nums,0,nums.length-1);

    }
    public TreeNode Balance(int[] nums,int left,int right)
    {
        if(left>right)
        {
            return null;
        }
        //中间的左边数作为根节点
        int mid=(left+right)>>1;
        TreeNode root=new TreeNode(nums[mid]);
        root.left=Balance(nums,left,mid-1);
        root.right=Balance(nums,mid+1,right);
        return root;

    }
}