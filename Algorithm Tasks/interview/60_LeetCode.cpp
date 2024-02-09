#include <iostream>
#include <stack>

using namespace std;

/*
Посчитать сумму элементов в дереве в диапазоне [low, high]  
*/

struct TreeNode {
  int val;
  TreeNode* left;
  TreeNode* right;
  TreeNode() : val(0), left(nullptr), right(nullptr) {}
  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
  TreeNode(int x, TreeNode* left, TreeNode* right)
      : val(x), left(left), right(right) {}
};

class Solution {
 public:
  int rangeSumBST(TreeNode* root, int low, int high) {
    stack<TreeNode*> st;
    st.push(root);
    TreeNode* cur;
    int sum = 0;
    while (!st.empty()) {
      cur = st.top();
      st.pop();
      if (cur->val >= low && cur->val <= high) {
        sum += cur->val;
      }

      if (cur->left != nullptr) {
        st.push(cur->left);
      }
      if (cur->right != nullptr) {
        st.push(cur->right);
      }
    }

    return sum;
  }
};