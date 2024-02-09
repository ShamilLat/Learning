#include <iostream>
#include <stack>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

/*
Реализовать свой стек с возможностью вывода и удаления Max элемента
*/

class MaxStack {
 public:
  stack<int> data;
  stack<int> max_d;

  void push(int x) {
    data.push(x);
    if (!max_d.empty()) {
      max_d.push(max(max_d.top(), x));
    } else {
      max_d.push(x);
    }
  }
  int pop() {
    int tmp = 0;
    if (!data.empty()) {
      max_d.pop();
      tmp = data.top();
      data.pop();
    }
    return tmp;
  }
  int top() { return data.top(); }

  int popMax() {
    stack<int> tmp;
    while (!data.empty() && data.top() != max_d.top()) {
      tmp.push(pop());
    }
    int res = pop();

    while (!tmp.empty()) {
      push(tmp.top());
      tmp.pop();
    }
    return res;
  }

  int peekMax() { return max_d.top(); }
};

int main() {
  MaxStack st;

  st.push(5);
  st.push(1);
  st.push(5);

  cout << st.top() << endl;
  cout << st.popMax() << endl;
  cout << st.top() << endl;
  cout << st.peekMax() << endl;
  cout << st.pop() << endl;
  cout << st.top() << endl;

  return 0;
}