#include <iostream>
#include <vector>

using namespace std;

/*
Merge k sorted lists
*/

struct ListNode {
  int val;
  ListNode* next;
  ListNode() : val(0), next(nullptr) {}
  ListNode(int x) : val(x), next(nullptr) {}
  ListNode(int x, ListNode* next) : val(x), next(next) {}

  friend ostream& operator<<(ostream& out, ListNode* list) {
    out << "val = " << list->val << ", next = ";
    if (list->next != nullptr) {
      out << list->next->val;
    } else {
      out << "nullptr";
    }
    out << "\n";
    return out;
  }
};

class Solution {
 public:
  ListNode* mergeKLists(vector<ListNode*>& lists) {
    if (lists.size() == 0) {
      return nullptr;
    }

    ListNode* begin_result = nullptr;

    for (int i = 0; i < lists.size(); i++) {
      ListNode* last_list = begin_result;
      ListNode* last_node = nullptr;
      ListNode* curr_list = lists[i];
      while (last_list != nullptr && curr_list != nullptr) {
        if (last_list->val > curr_list->val) {
          auto tmp = curr_list;
          curr_list = curr_list->next;
          tmp->next = last_list;

          if (last_node == nullptr) {
            begin_result = tmp;
          } else {
            last_node->next = tmp;
          }

          last_node = tmp;
        } else {
          last_node = last_list;
          last_list = last_list->next;
        }
      }
      if (curr_list != nullptr) {
        if (last_node != nullptr) {
          last_node->next = curr_list;
        } else {
          begin_result = curr_list;
        }
      }
    }
    return begin_result;
  }
};
