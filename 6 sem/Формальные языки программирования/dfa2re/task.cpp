#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>
#include "api.hpp"

bool contains_map(std::map<std::string, std::string>& s, std::string c) {
  for (auto& i : s) {
    if (i.first == c) {
      return true;
    }
  }
  return false;
}

struct State {
  State() {}
  State(std::string name_) : number(name_) {}

  void check_self_ways() {
    for (auto& i : input) {
      if (i.first == number) {
        if (self_connection.size()) {
          self_connection = self_connection + "|" + i.second;
        } else {
          self_connection = i.second;
        }
        input.erase(number);
        output.erase(number);
        break;
      }
    }
  }

  std::string number = "";
  bool is_final = false;
  std::string self_connection = "";
  std::map<std::string, std::string> input;
  std::map<std::string, std::string> output;
};

bool myfunctionsort(State& s1, State& s2) {
  return s1.input.size() + s1.output.size() + !s1.self_connection.empty() >
         s2.input.size() + s2.output.size() + !s2.self_connection.empty();
}

std::string dfa2re(DFA& d) {
  std::stringstream infile(d.to_string());

  int states_count = d.size();
  auto final_states_names = d.get_final_states();
  auto states_names = d.get_states();

  std::map<std::string, State> states_map;
  for (auto& i : states_names) {
    states_map.emplace(std::make_pair(i, State(i)));
  }

  std::string str = "";
  std::getline(infile, str);

  for (int i = 0; i < states_count; i++) {
    std::getline(infile, str);
  }

  while (std::getline(infile, str)) {
    std::stringstream ss(str);
    std::string name1, name2;
    char t;
    ss >> t >> name1;
    name1.erase(name1.size() - 1);
    ss >> t;
    name2 = d.get_trans(name1, t);
    if (name1 == name2) {
      if (states_map[name1].self_connection.empty()) {
        states_map[name1].self_connection = std::string(1, t);
      } else {
        states_map[name1].self_connection =
            states_map[name1].self_connection + '|' + std::string(1, t);
      }
    } else {
      if (contains_map(states_map[name1].output, name2)) {
        states_map[name1].output[name2] =
            states_map[name1].output[name2] + '|' + t;
      } else {
        states_map[name1].output[name2] = std::string(1, t);
      }
      states_map[name1].number = name1;
      if (contains_map(states_map[name2].input, name1)) {
        states_map[name2].input[name1] =
            states_map[name2].input[name1] + '|' + t;
      } else {
        states_map[name2].input[name1] = std::string(1, t);
      }
      states_map[name2].number = name2;
    }
  }

  for (auto& i : final_states_names) {
    states_map[i].is_final = true;
  }

  State new_begin_state("new_begin_state");
  new_begin_state.output[d.get_initial_state()] = "$";
  states_map[d.get_initial_state()].input[new_begin_state.number] = "$";

  State new_end_state("new_end_state");
  for (auto& i : states_map) {
    if (i.second.is_final) {
      new_end_state.input[i.second.number] = "$";
      i.second.output[new_end_state.number] = "$";
    }
  }

  states_map.emplace(std::make_pair(new_begin_state.number, new_begin_state));
  states_map.emplace(std::make_pair(new_end_state.number, new_end_state));

  std::vector<std::string> names_for_sorting;
  for (auto& i : states_names) {
    names_for_sorting.push_back(i);
  }
  auto size = d.size();
  for (int i = 0; i < size; i++) {
    for (int j = i + 1; j < size; j++) {
      if (myfunctionsort(states_map[names_for_sorting[i]],
                         states_map[names_for_sorting[j]])) {
        std::swap(names_for_sorting[i], names_for_sorting[j]);
      }
    }
  }

  // Deleting States
  for (auto& i : names_for_sorting) {
    std::string self_state = states_map[i].self_connection;
    std::map<std::string, std::string> input_con;
    std::map<std::string, std::string> output_con;
    for (auto& j : states_map[i].input) {
      input_con.insert({j.first, j.second});
      states_map[j.first].output.erase(states_map[i].number);
    }
    for (auto& j : states_map[i].output) {
      output_con.insert({j.first, j.second});
      states_map[j.first].input.erase(states_map[i].number);
    }

    for (auto& in : input_con) {
      for (auto& out : output_con) {
        std::string way = "";
        if (in.second == "$") {
          in.second = "";
        } else if (in.second.size() > 1) {
          in.second = '(' + in.second + ')';
        }
        if (out.second == "$") {
          out.second = "";
        } else if (out.second.size() > 1) {
          out.second = '(' + out.second + ')';
        }
        if (self_state.empty()) {
          way = in.second + out.second;
        } else {
          way = in.second + "(" + self_state + ")*" + out.second;
        }
        if (contains_map(states_map[in.first].output, out.first)) {
          way = states_map[in.first].output[out.first] + '|' + way;
          states_map[in.first].output[out.first].clear();
          states_map[out.first].input[in.first].clear();
        }
        states_map[in.first].output[out.first] = way;
        states_map[out.first].input[in.first] = way;

        states_map[in.first].check_self_ways();
        states_map[out.first].check_self_ways();
      }
    }
  }


  std::string rt_string =
      states_map[new_begin_state.number].output[new_end_state.number];
  rt_string.erase(std::remove(rt_string.begin(), rt_string.end(), '$'),
                  rt_string.end());
  return rt_string;
}