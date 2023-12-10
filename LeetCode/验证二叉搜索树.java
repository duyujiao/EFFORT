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
    //基本数据类型的变量在方法内部声明时，会在每次方法调用重新初始化默认值
    //，所以要放在方法体外部，只会初始化一次
    long min=Long.MIN_VALUE;
    public boolean isValidBST(TreeNode root) {
       
        if(root==null)
        return true;
        boolean l=isValidBST(root.left);
        if(min<root.val)
        min=root.val;
        else
        return false;
        boolean r=isValidBST(root.right);
        return l&&r;
    }
}