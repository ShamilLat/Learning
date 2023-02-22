#include "functions.hpp"
#include <fstream>
#include <string>
#include <vector>
#include "log_string.hpp"

namespace {

void reading_process(std::vector<LogString>& log_strings,
                     std::ifstream& input) {
  int day = 0, month = 0, year = 0, hour = 0, minute = 0, second = 0, ms = 0;
  LogString tmp;

  std::string str;
  char t;
  while (input >> str) {
    std::string stop_mark = "[**]";
    std::stringstream time_str(str);
    time_str >> month >> t >> day >> t >> year >> t >> hour >> t >> minute >>
        t >> second >> t >> ms;
    // Date
    time_t time_tmp = ((((year - 1970) * 365 + (year / 4 - 1970 / 4) +
                         days_sum(month) + day - 1) *
                            24 +
                        hour) *
                           60 +
                       minute) *
                          60 +
                      second;
    tmp.set_time(time_tmp, ms);

    // test = *(localtime(&time_tmp));

    // Id
    input >> str >> str;
    std::stringstream ss(str);
    int a, b, c;
    ss >> t >> a >> t >> b >> t >> c;
    tmp.id = Id(a, b, c);

    // Classification
    while (str != stop_mark) {
      input >> str;
    }

    std::string classification = "";
    bool check = true;
    input >> str;
    classification = str;
    while (str[str.length() - 1] != ']') {
      input >> str;
      classification = classification + " " + str;
    }
    // classification[classification.size() - 1] = '\0';
    tmp.classification = classification;

    // Priority
    input >> str >> str;
    ss.str(str);
    ss >> tmp.priority;

    // IPs
    Ip ip;
    input >> str;

    tmp.communication_type = str;

    input >> tmp.ip_sender;
    input >> str;
    input >> tmp.ip_receiver;

    log_strings.push_back(tmp);
  }
}

}  // namespace

int days_sum(int number) {
  int day_in_months[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
  int sum = 0;
  for (int i = 0; i < number - 1; i++) {
    sum += day_in_months[i];
  }
  return sum;
}

void read_file(std::vector<LogString>& log_strings, int argc, char* argv[]) {
  std::ifstream input;
  for (int i = 1; i < argc; i++) {
    input.open(argv[i]);
    reading_process(log_strings, input);
    input.close();
  }
  std::cout << "Input files' name or write Stop\n";
  std::string str;
  while (std::cin >> str && str != "Stop" && str != "stop") {
    input.open(str);
    reading_process(log_strings, input);
    input.close();
  }
}

void output_massive_in_file(int* mas, int mas_size, std::string file_name) {
  std::ofstream ccout(file_name);
  for (int i = 0; i < mas_size; i++) {
    ccout << mas[i] << " ";
  }
  ccout << "\n";
  ccout.close();
}

void output_vector_in_file(std::vector<LogString> vector,
                           std::string file_name) {
  std::ofstream ccout(file_name);
  for (const auto& i : vector) {
    ccout << i;
  }
  ccout.close();
}

void output_log_strings(std::vector<LogString>& a) {
  for (const auto& i : a) {
    std::cout << i;
  }
}