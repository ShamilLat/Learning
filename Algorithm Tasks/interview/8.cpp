#include <iostream>
#include <unordered_map>
#include <vector>

int countSubarraysWithSum(std::vector<int>& arr, int targetSum) {
  int count = 0;
  int currentSum = 0;

  // Используем unordered_map для отслеживания количества встреч сумм
  std::unordered_map<int, int> sumCounts;

  sumCounts[0] = 1;  // Начальное значение суммы равно 0

  for (int num : arr) {
    currentSum += num;

    // Проверяем, есть ли разница между текущей суммой и целевой суммой в
    // sumCounts
    if (sumCounts.find(currentSum - targetSum) != sumCounts.end()) {
      count += sumCounts[currentSum - targetSum];
    }

    sumCounts[currentSum]++;
  }

  return count;
}

int main() {
  std::vector<int> arr = {1, 2, 3, 4, 5, 2};
  int targetSum = 7;
  int result = countSubarraysWithSum(arr, targetSum);
  std::cout << "Количество подмассивов с суммой " << targetSum << ": " << result
            << std::endl;
  return 0;
}
