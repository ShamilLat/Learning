#include <iostream>

using namespace std;

/*
Сложить два числа, записанных в виде списков

Пример
2 -> 4 -> 3
5 -> 6 -> 4

Ответ:
7 -> 0 -> 8
(342 + 465 = 807)
*/

struct ListNode {
  int val;
  ListNode* next;
  ListNode() : val(0), next(nullptr) {}
  ListNode(int x) : val(x), next(nullptr) {}
  ListNode(int x, ListNode* next) : val(x), next(next) {}
};

class Solution {
 public:
  ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
    int ten = 0;
    ListNode *head = l1, *last_l1 = l1;
    while (l1 != nullptr && l2 != nullptr) {
      int sum = l1->val + l2->val + ten;
      l1->val = sum % 10;
      ten = sum / 10;
      last_l1 = l1;
      l1 = l1->next;
      l2 = l2->next;
    }
    while (l2 != nullptr) {
      last_l1->next = l2;
      l1 = l2;
      if (ten != 0) {
        int sum = l1->val + ten;
        l1->val = sum % 10;
        ten = sum / 10;

        last_l1 = l1;
        l1 = l1->next;
        l2 = l2->next;
      } else {
        break;
      }
    }
    while (l1 != nullptr && ten != 0) {
      int sum = l1->val + ten;
      l1->val = sum % 10;
      ten = sum / 10;

      last_l1 = l1;
      l1 = l1->next;
    }
    if (ten) {
      last_l1->next = new ListNode(ten);
    }
    return head;
  }
};

int main() {}