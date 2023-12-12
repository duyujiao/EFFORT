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
    public List<List<Integer>> levelOrder(TreeNode root) {
       List<List<Integer>> list=new ArrayList<>();
        if(root==null)
        return list;
       Queue<TreeNode> queue=new LinkedList<>();
       queue.add(root);
    
       while(!queue.isEmpty())
       {   List<Integer> list1=new ArrayList<>();   
        int nums=queue.size();
        for(int i=0;i<nums;i++){
           TreeNode a=queue.poll();
           list1.add(a.val);        
           if(a.left!=null)
           queue.add(a.left);
           if(a.right!=null)
           queue.add(a.right);          
        }
           list.add(list1);
       }     
       return list;

    }
}