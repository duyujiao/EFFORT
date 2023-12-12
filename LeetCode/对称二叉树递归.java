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
    public boolean isSymmetric(TreeNode root) {

            boolean result=isequal(root.left,root.right);
            return result;

    }
    boolean isequal(TreeNode left,TreeNode right)
    {
        if(left==null&&right==null)
        return true;
        else if(left==null&&right!=null||left!=null&&right==null)
        return false;
        if(left.val!=right.val)
        return false;

        boolean a=isequal(left.left,right.right);
        boolean b=isequal(left.right,right.left);
        boolean c=a&&b;
        return c;
    }
}