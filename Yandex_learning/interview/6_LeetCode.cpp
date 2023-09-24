#include <iostream>
#include <string>

using namespace std;

class Solution {
 public:
  bool isPalindrome(string s) {
    int left = 0, right = s.size() - 1;
    while (left < right) {
      while (!isalnum(s[left]) && left < right) {
        left++;
      }
      while (!isalnum(s[right]) && left < right) {
        right--;
      }

      if (std::tolower(s[left]) != std::tolower(s[right])) {
        return false;
      }
      left++;
      right--;
    }
    return true;
  }
};

int main() {
  string s;
  getline(cin, s);
  //   cin >> s;

  cout << s << "\n";

  Solution solv;

  std::cout << solv.isPalindrome(s) << endl;
}