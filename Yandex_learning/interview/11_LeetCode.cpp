#include <iostream>
#include <random>
#include <unordered_map>
#include <vector>

using namespace std;

/*
insert delete getrandom O(1)
*/

class RandomizedSet {
 public:
  RandomizedSet() {}

  bool insert(int val) {
    if (!val_to_ind.contains(val)) {
      values.push_back(val);
      val_to_ind[val] = values_size;
      values_size++;
      return true;
    }
    return false;
  }

  bool remove(int val) {
    if (val_to_ind.contains(val)) {
      int del_ind = val_to_ind[val];
      int last_val = values[values_size - 1];
      int last_ind = val_to_ind[last_val];
      swap(values[del_ind], values[last_ind]);
      values.pop_back();
      values_size--;
      val_to_ind[last_val] = del_ind;
      val_to_ind.erase(val);
      return true;
    }
    return false;
  }

  int getRandom() { return values[rand() % values_size]; }

  size_t values_size = 0;
  vector<int> values;
  unordered_map<int, int> val_to_ind;
};
