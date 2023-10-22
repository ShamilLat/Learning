#include <algorithm>
#include <iostream>
#include <stack>

using namespace std;

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
  bool isValidBST(TreeNode* v,
                  long long min_v = LONG_LONG_MIN,
                  long long max_v = LONG_LONG_MAX) {
    bool chk = true;
    if (v->left != nullptr) {
      chk &= isValidBST(v->left, min_v, min(max_v, (long long)v->val));
    }
    if (v->right != nullptr) {
      chk &= isValidBST(v->right, max(min_v, (long long)v->val), max_v);
    }

    return (v->val > min_v) & (v->val < max_v) & chk;
  }
};
