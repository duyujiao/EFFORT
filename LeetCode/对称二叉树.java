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
        Queue<TreeNode> queue=new LinkedList<>();
        if(root==null)
        return true;
        queue.offer(root.left);
        queue.offer(root.right);
        while(!queue.isEmpty())
        {
            TreeNode a=queue.poll();
            TreeNode b=queue.poll();
            if(a==null&&b==null)
            continue;
            else if(a==null||b==null||(a.val!=b.val))
            return false;
            queue.offer(a.left);
            queue.offer(b.right);
            queue.offer(a.right); 
            queue.offer(b.left);
        }
        return true;
    }
}