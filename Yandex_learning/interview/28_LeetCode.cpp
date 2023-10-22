#include <iostream>
#include <queue>
#include <stack>
#include <unordered_map>
#include <vector>

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
  bool isSymmetric(TreeNode* root) {
    queue<TreeNode*> q_left, q_right;
    TreeNode *left = root, *right = root;

    int check = code(left, right, 1);
    if (check == 1) {
      left = left->left;
      right = right->right;
    } else if (check == 0) {
      return false;
    }

    q_left.push(left);
    q_right.push(right);

    while (!q_left.empty() && !q_right.empty()) {
      left = q_left.front();
      right = q_right.front();
      if (left->val != right->val) {
        return false;
      }

      check = code(left, right, 1);
      if (check == 1) {
        q_left.push(left->left);
        q_right.push(right->right);
      } else if (check == 0) {
        return false;
      }

      check = code(left, right, 0);
      if (check == 1) {
        q_left.push(left->right);
        q_right.push(right->left);
      } else if (check == 0) {
        return false;
      }

      q_left.pop();
      q_right.pop();
    }

    return true;
  }

 private:
  int code(TreeNode* left, TreeNode* right, int size_code) {
    if (size_code) {
      if (left->left != nullptr && right->right != nullptr) {
        return 1;
      } else if (left->left == nullptr && right->right == nullptr) {
        return 2;
      }
    } else {
      if (left->right != nullptr && right->left != nullptr) {
        return 1;
      } else if (left->right == nullptr && right->left == nullptr) {
        return 2;
      }
    }

    return 0;
  }
};

int main() {
  return 0;
}