#include <iostream>

using namespace std;

/*
Максимальная сумма val в узлах при каком то из путей
https://leetcode.com/problems/binary-tree-maximum-path-sum/
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
  int maxPathSum(TreeNode* root) {
    int cnt = INT_MIN;
    chk(root, cnt);
    return cnt;
  }
  int chk(TreeNode* root, int& cnt) {
    if (root == NULL) {
      return 0;
    }
    int l = max(0, chk(root->left, cnt));
    int r = max(0, chk(root->right, cnt));
    cnt = max(cnt, l + r + root->val);
    return root->val + max(l, r);
  }
};