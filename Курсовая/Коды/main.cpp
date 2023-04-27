#include <stdlib.h>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <map>
#include <sstream>
#include <unordered_map>
#include <vector>
#include "functions.hpp"
#include "id.hpp"
#include "ip.hpp"
#include "log_string.hpp"

int main(int argc, char* argv[]) {
  std::vector<LogString> log_strings;

  read_file(log_strings, argc, argv);

  std::unordered_map<Ip, std::vector<struct tm>>
      sender_ips_compatibility_with_time;
  std::unordered_map<Ip, std::vector<struct tm>>
      receiver_ips_compatibility_with_time;

  int attack_density_week[7] = {};
  int attack_density_60[24] = {};
  int attack_density_30[48] = {};
  int attack_density_15[96] = {};

  std::vector<LogString> first_priority;
  for (auto& i : log_strings) {
    if (i.priority == 1) {
      first_priority.push_back(i);
    }
    sender_ips_compatibility_with_time[i.ip_sender].push_back(i.time);
    receiver_ips_compatibility_with_time[i.ip_receiver].push_back(i.time);
    attack_density_week[i.time.tm_wday]++;
    attack_density_60[i.time.tm_hour]++;
    attack_density_30[i.time.tm_hour * 2 + i.time.tm_min / 30]++;
    attack_density_15[i.time.tm_hour * 4 + i.time.tm_min / 15]++;
  }

  output_massive_in_file(attack_density_week, 7, "week_density.txt");
  output_massive_in_file(attack_density_60, 24, "1_hour_density.txt");
  output_massive_in_file(attack_density_30, 48, "30_min_density.txt");
  output_massive_in_file(attack_density_15, 96, "15_min_density.txt");

  output_vector_in_file(first_priority, "first_priority_logs.txt");

  char time_buf[26];
  for (const auto& i : sender_ips_compatibility_with_time) {
    // for (const auto& i : receiver_ips_compatibility_with_time) {
    std::cout << i.first << ":\n";
    for (const auto& j : i.second) {
      strftime(time_buf, 26, "%Y/%m/%d %H:%M:%S", &j);
      std::cout << time_buf << "\n";
    }
    std::cout << "\n";
  }

  system("python3 graph_printer_1.py");
  system("python3 graph_printer_2.py");
  system("python3 graph_printer_3.py");

  // output_log_strings(log_strings);

  // output_vector(log_strings);

  /* int cmd = 1;
  std::cout << "    1 - help - Output help board\n";
  std::cout << "    2 - output - Output data from logs\n";
  std::cout << "    3 - end - Stop programm\n";
  do {
    std::cout << "Enter command\n";
    std::cin >> cmd;
    if (cmd == 1) {
      std::cout << "    1 - help - Output help board\n";
      std::cout << "    2 - output - Output data from logs\n";
      std::cout << "    3 - end - Stop programm\n";
    } else if (cmd == 2) {
      tmp.set_null();
      do {
        std::cout << "data mean:\n"
                  << "1 - id\n2 - priority\n3 - sender\n"
                     "4 - receiver\n";

        // std::string data;
        int data = 0;
        std::cin >> data;
        while (data < 1 || data > 5) {
          std::cout << "Incorrect data input\nMust be 1 <= data <= 5\n";
          std::cout << "Input data number\n";
          std::cin >> data;
        }
        switch (data) {
          case 1: {
            std::cout << "Input 3 numbers of id\n";
            int a, b, c;
            std::cin >> a >> b >> c;
            tmp.id = {a, b, c};
          } break;
          case 2: {
            std::cout << "Input priority\n";
            std::cin >> tmp.priority;
          } break;
          case 3: {
            std::cout << "Input sender IP\n";
            int b1, b2, b3, b4, p;
            std::cin >> b1 >> b2 >> b3 >> b4 >> p;
            tmp.sender = {b1, b2, b3, b4, p};
          } break;
          case 4: {
            std::cout << "Input receiver IP\n";
            int b1, b2, b3, b4, p;
            std::cin >> b1 >> b2 >> b3 >> b4 >> p;
            tmp.receiver = {b1, b2, b3, b4, p};
          } break;
        }

        std::cout << "If you want to add data, input 1, or any other number "
                     "to output your set\n";
        std::cin >> cmd;
      } while (cmd == 1);

      std::vector<LogString> tmp_vector;
      for (auto& i : log_strings) {
        if (i == tmp) {
          tmp_vector.push_back(i);
        }
      }

      output_vector(tmp_vector);
      cmd = 1;
    } else if (cmd != 3) {
      std::cout << "Incorrect number\n";
    }
  } while (cmd != 3); */
}