#include <stdint.h>
#include <iostream>

class TreeNode {
 public:
  int64_t val;
  TreeNode* left;
  TreeNode* right;
  TreeNode() : val(0), left(nullptr), right(nullptr) {}
  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
  TreeNode(int x, TreeNode* left, TreeNode* right)
      : val(x), left(left), right(right) {}
};

class Solution {
  bool isPossible(TreeNode* root, int64_t l, int64_t r) {
    if (root == nullptr)
      return true;
    if (root->val < r and root->val > l)
      return isPossible(root->left, l, root->val) and
             isPossible(root->right, root->val, r);
    else
      return false;
  }

 public:
  bool isValidBST(TreeNode* root) {
    int64_t min = 0x7fffffffffffffff, max = 0x8000000000000000;
    return isPossible(root, min, max);
  }
};