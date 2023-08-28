#include <sys/time.h>
#include <time.h>
#include <chrono>
#include <cmath>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <random>
#include <sstream>
#include <string>
#include <vector>

int main() {
  double a, t1, b;
  char t;
  double speed[6];

  for (int k = 0; k < 3; k++) {
    for (int i = 0; i < 6; i++) {
      std::cin >> t >> a >> t >> b >> t;
      speed[i] = b;
    }

    int st = 1;
    for (int i = 0; i < 6; i++) {
      std::cin >> t >> a >> t >> b >> t;
      std::cout << "(" << st << "," << speed[i] / b<< ")\n";
      st *= 2;
    }
    std::cout << "\n";
  }
}