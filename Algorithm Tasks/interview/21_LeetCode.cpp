#include <iostream>
#include <queue>

using namespace std;

/*
Реализовать HitCounter класс:

1)  HitCounter() Инициализирует объект системы счетчика попаданий.
2)  void hit(int timestamp)
    Записывает попадание, которое произошло за timestamp (в секундах).
    Одновременно может произойти несколько попаданий timestamp.
3)  int getHits(int timestamp)
    Возвращает количество посещений за последние 5 минут timestamp (т.е. за
    последние 300 секунды).
*/

class HitCounter {
 public:
  HitCounter() {}

  void hit(int timestamp) { times.push(timestamp); }
  int getHits(int timestamp) {
    while (times.front() <= timestamp - 300) {
      times.pop();
    }
    return times.size();
  }

 private:
  queue<int> times;
};

int main() {
  HitCounter count;

  count.hit(1);
  count.hit(2);
  count.hit(3);
  cout << count.getHits(4) << endl;
  count.hit(300);
  cout << count.getHits(300) << endl;
  cout << count.getHits(301) << endl;

  return 0;
}
