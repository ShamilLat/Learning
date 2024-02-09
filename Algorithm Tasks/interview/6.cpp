#include <ctime>
#include <iostream>
#include <unordered_map>
#include <vector>

class RequestCounter {
 public:
  void addRequest(int userId, time_t requestTime) {
    requests[userId].push_back(requestTime);
  }

  int countUsersWith1000Requests() {  // Если все запросы идут по порядку по
                                      // времени
    time_t currentTime = time(nullptr);
    int userCount = 0;

    for (const auto& entry : requests) {
      int recentRequestCount = 0;

      // Находим индекс последнего запроса, который удовлетворяет условию
      int lastIndex = -1;
      for (int i = entry.second.size() - 1; i >= 0; i--) {
        if (currentTime - entry.second[i] <= 300) {
          lastIndex = i;
          break;
        }
      }

      // Если нашли хотя бы 1000 запросов за последние 5 минут, увеличиваем
      // счетчик
      if (lastIndex != -1 && entry.second.size() - lastIndex >= 1000) {
        userCount++;
      }
    }
    return userCount;
  }

  int countUsersWith1000Requests_2() {  // Если запросы могут вноситься не по
                                        // порядку времени
    time_t currentTime = time(nullptr);
    int userCount = 0;

    for (const auto& entry : requests) {
      int recentRequestCount = 0;
      for (const time_t& requestTime : entry.second) {
        if (currentTime - requestTime <= 300) {
          recentRequestCount++;
        }
      }

      if (recentRequestCount >= 1000) {
        userCount++;
      }
    }

    return userCount;
  }

 private:
  std::unordered_map<int, std::vector<time_t>> requests;
};

int main() {
  RequestCounter counter;

  // Пример использования класса (аналогичный предыдущему):
  counter.addRequest(1, std::time(nullptr) - 100);
  counter.addRequest(1, std::time(nullptr) - 200);
  counter.addRequest(1, std::time(nullptr) - 350);
  counter.addRequest(2, std::time(nullptr) - 60);
  counter.addRequest(3, std::time(nullptr) - 280);
  counter.addRequest(3, std::time(nullptr) - 290);
  counter.addRequest(3, std::time(nullptr) - 310);

  int result = counter.countUsersWith1000Requests();
  std::cout << "Пользователей с хотя бы 1000 запросов за последние 5 минут: "
            << result << std::endl;

  return 0;
}
