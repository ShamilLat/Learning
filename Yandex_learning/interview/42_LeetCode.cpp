#include <iostream>
#include <queue>
#include <stack>

using namespace std;

/*
Найти самый нижний общий узел двух узлов дерева
*/

struct TreeNode {
  int val;
  TreeNode* left;
  TreeNode* right;
  TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
 public:
  TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
    if (root == nullptr || root == p || root == q)
      return root;

    TreeNode *left = nullptr, *right = nullptr;
    if (root->left) {
      left = lowestCommonAncestor(root->left, p, q);
    }
    if (root->right) {
      right = lowestCommonAncestor(root->right, p, q);
    }

    if (left && right)
      return root;
    else if (left)
      return left;
    else
      return right;

    return root;
  }
};

int main() {}