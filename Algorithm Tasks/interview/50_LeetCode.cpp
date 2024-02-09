/*
Удалить n-ый узел из конца списка
*/


/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
 public:
  ListNode* removeNthFromEnd(ListNode* head, int n) {
    ListNode *it1 = head, *it2 = head, *res = head;
    int cnt = 0;
    while (it2 != nullptr) {
      if (cnt > n) {
        it1 = it1->next;
      } else {
        cnt++;
      }
      it2 = it2->next;
    }
    if (it1 == head && cnt <= n) {
      res = it1->next;
    } else
      it1->next = it1->next->next;

    return res;
  }
};