#include <iostream>
#include <stack>

using namespace std;

/*
Реализовать очередь через 2 стека
*/

class MyQueue {
 public:
  MyQueue() {}

  void push(int x) { first.push(x); }

  int pop() {
    int tmp = peek();
    second.pop();
    return tmp;
  }

  int peek() {
    if (second.empty()) {
      while (!first.empty()) {
        second.push(first.top());
        first.pop();
      }
    }
    return second.top();
  }

  bool empty() { return first.empty() && second.empty(); }

 private:
  stack<int> first, second;
};

int main() {
  MyQueue* obj = new MyQueue();
  obj->push(1);
  obj->push(2);
  cout << obj->peek() << endl;
  cout << obj->pop() << endl;
  cout << obj->empty() << endl;
}

/**
 * Your MyQueue object will be instantiated and called as such:
 * MyQueue* obj = new MyQueue();
 * obj->push(x);
 * int param_2 = obj->pop();
 * int param_3 = obj->peek();
 * bool param_4 = obj->empty();
 */