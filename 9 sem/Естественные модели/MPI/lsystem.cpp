#include <fstream>
#include <map>
#include <string>

using namespace std;

string update_data(string& data, map<char, string>& R) {
  string buf = "";

  for (auto& i : data) {
    buf += R[i];
  }

  return buf;
}

void run_lsystem(int T) {
  // аксиома
  string data = "a";
  
  // система правил
  map<char, string> R;
  R['a'] = "b";
  R['b'] = "ab";
  
  // основной цикл
  for (int t = 0; t < T; t++)
    data = update_data(data, R);
  
  // сохранение результатов расчета
  ofstream f("output.dat");
  f << data << endl;
  f.close();
}

int main(int argc, char** argv) {
  int T = atoi(argv[1]);  // число итераций алгоритма

  run_lsystem(T);

  return 0;
}