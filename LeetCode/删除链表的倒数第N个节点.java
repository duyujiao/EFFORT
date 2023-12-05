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
    public ListNode removeNthFromEnd(ListNode head, int n) {
        //在Java代码中，对象赋值时通过引用赋给了pre,指向相同的地址，而不是值
//当通过 pre 修改节点的属性或指针时，head 也会体现出相同的更改，因为它们引用的是同一个对象。
        ListNode pre=head;
        ListNode cout=head;
        int len=0;
        while(cout!=null)
        {
            len++;
            cout=cout.next;

        }
        if(n==len)
        return head.next;
        for(int i=0;i<len-n-1;i++)
        {
            pre=pre.next;
        }
        pre.next=pre.next.next;        
        return head;

    }
}