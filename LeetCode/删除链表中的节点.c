/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
void deleteNode(struct ListNode* node) {
    //通过指针访问属性需要使用箭头运算符 -> 而不是点运算符 .
    node->val=node->next->val;
    node->next=node->next->next;
    
}