#include <iostream>
#include <stack>
#include <vector>

using namespace std;

/*
Вывести все числа в "гнездовом" массиве

Example 1:
Input: nestedList = [[1,1],2,[1,1]]
Output: [1,1,2,1,1]

Example 2:
Input: nestedList = [1,[4,[6]]]
Output: [1,4,6]

*/

// This is the interface that allows for creating nested lists.
// You should not implement it, or speculate about its implementation
class NestedInteger {
 public:
  // Return true if this NestedInteger holds a single integer, rather than a
  // nested list.
  bool isInteger() const {};

  // Return the single integer that this NestedInteger holds, if it holds a
  // single integer The result is undefined if this NestedInteger holds a nested
  // list
  int getInteger() const {};

  // Return the nested list that this NestedInteger holds, if it holds a nested
  // list The result is undefined if this NestedInteger holds a single integer
  const vector<NestedInteger>& getList() const {};
};

class NestedIterator {
 public:
  NestedIterator(vector<NestedInteger>& nestedList) {
    current_vec = rec(nestedList);
    iter = 0;
  }

  int next() { return current_vec[iter++]; }

  bool hasNext() { return iter < current_vec.size(); }

 private:
  vector<int> current_vec;
  int iter = 0;

  vector<int> rec(const vector<NestedInteger>& vec) {
    vector<int> res;
    for (auto& i : vec) {
      if (i.isInteger()) {
        res.push_back(i.getInteger());
      } else {
        auto new_vec = rec(i.getList());
        res.insert(res.end(), new_vec.begin(), new_vec.end());
      }
    }
    return res;
  }
};
