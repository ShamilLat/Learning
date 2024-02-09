#include <iostream>
#include <vector>

using namespace std;

/*
Merge Sorted array
*/

class Solution {
 public:
  void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
    int i1 = m - 1, i2 = n - 1, i3 = n + m - 1;
    while (i1 >= 0 && i2 >= 0) {
      if (nums1[i1] > nums2[i2]) {
        nums1[i3] = nums1[i1];
        i1--;
        i3--;
      } else if (nums1[i1] < nums2[i2]) {
        nums1[i3] = nums2[i2];
        i2--;
        i3--;
      } else {
        nums1[i3] = nums1[i1];
        nums1[i3 - 1] = nums2[i2];
        i1--;
        i2--;
        i3 -= 2;
      }
    }
    while (i2 >= 0) {
      nums1[i3] = nums2[i2];
      i2--;
      i3--;
    }
  }
};

int main() {
  vector<int> a, b;

  a = {1, 2, 3, 0, 0, 0, 0, 0};
  b = {2, 2, 3, 4, 5};

  Solution solv;
  solv.merge(a, 3, b, 5);

  for (auto& i : a) {
    cout << i << " ";
  }
  cout << "\n";
}