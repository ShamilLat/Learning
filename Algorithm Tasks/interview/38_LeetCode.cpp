#include <iostream>

using namespace std;

/*
Merge two sorted list
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
  ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
    ListNode *res = nullptr, *head = nullptr;

    while (list1 != nullptr && list2 != nullptr) {
      if (res == nullptr) {
        res = new ListNode();
        head = res;
      } else {
        res->next = new ListNode();
        res = res->next;
      }

      if (list1->val > list2->val) {
        res->val = list2->val;
        list2 = list2->next;
      } else {
        res->val = list1->val;
        list1 = list1->next;
      }
    }

    if (list1 != nullptr) {
      if (res == nullptr) {
        head = list1;
      } else {
        res->next = list1;
      }
    } else if (list2 != nullptr) {
      if (res == nullptr) {
        head = list2;
      } else {
        res->next = list2;
      }
    }
    return head;
  }
};

int main() {
  Solution solv;

  ListNode *a = nullptr, *b = nullptr;
  ListNode *head_a, *head_b;

  int num = 1;
  while (num) {
    cin >> num;
    if (a == nullptr) {
      a = new ListNode(num);
      head_a = a;
    } else if (num != 0) {
      a->next = new ListNode(num);
      a = a->next;
    }
  }
  num = 1;
  while (num) {
    cin >> num;
    if (b == nullptr) {
      b = new ListNode(num);
      head_b = b;
    } else if (num != 0) {
      b->next = new ListNode(num);
      b = b->next;
    }
  }

  auto new_l = solv.mergeTwoLists(head_a, head_b);

  while (new_l != nullptr) {
    cout << new_l->val << " ";
    new_l = new_l->next;
  }
  cout << endl;
}