/**
 * Definition for singly-linked list.
 * public class ListNode {
 *     int val;
 *     ListNode next;
 *     ListNode() {}
 *     ListNode(int val) { this.val = val; }
 *     ListNode(int val, ListNode next) { this.val = val; this.next = next; }
 * }
 */
class Solution {
    public ListNode mergeTwoLists(ListNode list1, ListNode list2) {   
        ListNode a=list1;
        ListNode b=list2;
        ListNode c=new ListNode();
        ListNode d=c;
        
            while(a!=null&&b!=null)
            {
                if(a.val>=b.val)
                {
             
                 d.next=b;
                b=b.next;
                }
                else
                {                 
                    d.next=a;
                    a=a.next;
                }
                d=d.next;
            }
             if(a==null)
            {
                
               d.next=b;
            }
             if(b==null)
            {
                d.next=a;
            }
        
        return c.next;

    }
}