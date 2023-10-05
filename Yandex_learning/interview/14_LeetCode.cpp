#include <iostream>
#include <vector>

using namespace std;

/*
ReverseList:
1->2->3->4->5

Answer:
5->4->3->2->1
*/

//  * Definition for singly-linked list.
struct ListNode {
  int val;
  ListNode* next;
  ListNode() : val(0), next(nullptr) {}
  ListNode(int x) : val(x), next(nullptr) {}
  ListNode(int x, ListNode* next) : val(x), next(next) {}
};

class Solution {
 public:
  ListNode* reverseList(ListNode* head) {
    vector<int> values;
    ListNode* end = head;
    int cnt = 0;
    while (end != nullptr) {
      values.push_back(end->val);
      end = end->next;
      cnt++;
    }
    end = head;
    for (int i = 0; i < cnt; i++) {
      end->val = values[values.size() - 1 - i];
      end = end->next;
    }
    return head;
  }
};
