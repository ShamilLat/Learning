#include <time.h>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

int main() {
  ofstream ccout("all.eml");
  ifstream ccin;
  for (int file_number = 1; file_number < 24; file_number++) {
    std::string file_format = ".eml";
    std::string file_name = std::to_string(file_number) + file_format;
    ccin.open(file_name);
    std::string str;
    getline(ccin, str);
    do {
      ccout << str << "\n";
    } while (getline(ccin, str));
    ccin.close();
  }
}