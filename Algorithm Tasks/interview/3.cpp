#include <iostream>
#include <random>
#include <unordered_map>
#include <vector>

template <typename KeyType, typename ValueType>
class CustomHashMap {
 public:
  CustomHashMap() {}

  // Вставка элемента в хэш-таблицу и массив
  void insert(const KeyType& key, const ValueType& value) {
    if (keyToIndex.find(key) == keyToIndex.end()) {
      keys.push_back(key);
      keyToIndex[key] = keys.size() - 1;
    }
    data[key] = value;
  }

  // Получение элемента по ключу
  ValueType& operator[](const KeyType& key) { return data[key]; }

  // Равновероятное получение одного из элементов
  ValueType getRandomElement() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> distribution(0, keys.size() - 1);
    int randomIndex = distribution(gen);
    return data[keys[randomIndex]];
  }

 private:
  std::vector<KeyType> keys;
  std::unordered_map<KeyType, ValueType> data;
  std::unordered_map<KeyType, int> keyToIndex;
};

int main() {
  CustomHashMap<std::string, int> customMap;
  customMap.insert("apple", 1);
  customMap.insert("banana", 2);
  customMap.insert("cherry", 3);

  // Получение одного из элементов
  int randomValue = customMap.getRandomElement();
  std::cout << "Random value: " << randomValue << std::endl;

  return 0;
}
