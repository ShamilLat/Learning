#include <unordered_map>

using namespace std;

class LinkedList {
 public:
  int key;
  int val;
  LinkedList* prev;
  LinkedList* next;

  LinkedList(int key, int val) {
    this->key = key;
    this->val = val;
    prev = nullptr;
    next = nullptr;
  }
};

class LRUCache {
  unordered_map<int, LinkedList*> cache;
  LinkedList* left;
  LinkedList* right;
  int capacity;
  int size;

 public:
  LRUCache(int capacity) {
    this->capacity = capacity;
    size = 0;
    left = new LinkedList(0, 0);
    right = new LinkedList(0, 0);
    left->next = right;
    right->prev = left;
  }

  void remove(LinkedList* node) {
    LinkedList* p_node = node->prev;
    LinkedList* n_node = node->next;
    p_node->next = n_node;
    n_node->prev = p_node;
  }

  void insert(LinkedList* node) {
    LinkedList* p_node = right->prev;
    p_node->next = node;
    right->prev = node;
    node->next = right;
    node->prev = p_node;
  }

  int get(int key) {
    if (cache.find(key) == cache.end())
      return -1;
    LinkedList* node = cache[key];
    remove(node);
    insert(node);
    return cache[key]->val;
  }

  void put(int key, int value) {
    if (cache.find(key) != cache.end()) {
      LinkedList* node = cache[key];
      node->val = value;
      remove(node);
      insert(node);
      return;
    }

    if (capacity == size) {
      LinkedList* tmp = left->next;
      remove(tmp);
      cache.erase(tmp->key);
      delete tmp;
      size--;
    }
    LinkedList* node = new LinkedList(key, value);
    cache[key] = node;
    insert(node);
    size++;
  }
};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */