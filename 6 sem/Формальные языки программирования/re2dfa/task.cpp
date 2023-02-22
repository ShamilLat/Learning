#include <iostream>
#include <map>
#include <sstream>
#include <stack>
#include <string>
#include <vector>
#include "api.hpp"

bool contains(std::map<int, bool>& s, int c) {
  for (auto& i : s) {
    if (i.first == c) {
      return true;
    }
  }
  return false;
}

struct Key {
  Key() {}
  Key(bool op_, bool nullable_, int f, int l) : op(op_), nullable(nullable_) {
    fpos[f] = true;
    lpos[l] = true;
  }
  Key(bool op_, bool nullable_) : op(op_), nullable(nullable_) {}

  std::string to_string() const {
    std::stringstream ss;
    ss << "nullable " << nullable << "\nfposes : ";
    for (auto& i : fpos) {
      ss << i.first << " ";
    }
    ss << "\nlposes : ";
    for (auto& i : lpos) {
      ss << i.first << " ";
    }
    return ss.str();
  }

  bool op = false;
  bool nullable = false;
  std::map<int, bool> fpos;
  std::map<int, bool> lpos;
};

struct Connnection {
  Connnection() {}
  Connnection(char symbol_, int id_, int left_id_, int right_id_)
      : id(id_), left_id(left_id_), right_id(right_id_) {
    if (symbol_ == '>') {
      symbol_ = '.';
    }
    symbol = symbol_;
  }

  std::string flposes() const {
    std::stringstream ss;
    ss << "symbol " << symbol << " id " << id << "\n";
    ss << key.to_string();
    return ss.str();
  }

  Key key;
  char symbol;
  int id;
  int left_id;
  int right_id;
};

int letters_count = 0;

std::string opz(std::string& ss, int* b, Alphabet& tmp) {
  std::string s = ss;
  std::map<char, int> pr;
  pr['('] = 4;
  pr['*'] = 3;
  pr['.'] = 2;
  pr['|'] = 1;
  pr['>'] = 0;
  std::string out = "";
  std::stack<char> st;

  for (int i = 0; i < s.length(); i++) {
    if (tmp.has_char(s[i]) || s[i] == '#' || s[i] == '$') {
      out = out + s[i];
      letters_count++;
    } else {
      if (s[i] == '(') {
        st.push(s[i]);
      } else if (s[i] == ')') {
        while (!st.empty() && st.top() != '(') {
          out = out + st.top();
          st.pop();
        }
        st.pop();
      } else if (s[i] == '*' || s[i] == '|' || s[i] == '.' || s[i] == '>') {
        while (!st.empty() && st.top() != '(' && pr[st.top()] >= pr[s[i]]) {
          out = out + st.top();
          st.pop();
        }
        st.push(s[i]);
      }
    }
    if (b[i] == 1) {
      b[i] = 0;
      s[i] = '>';
      i--;
    }
    if (b[i] == 2) {
      b[i] = 0;
      s[i] = '.';
      i--;
    } else if (b[i] == 3) {
      b[i] = 0;
      s[i] = '$';
      i--;
    }
  }
  while (!st.empty()) {
    out = out + st.top();
    st.pop();
  }
  return out;
}

void labels(std::string& line, int* mul, Alphabet& tmp) {
  auto str_size = line.length();

  for (int i = 0; i < str_size; i++) {
    mul[i] = 0;
  }
  for (int i = 0; i < str_size - 1; i++) {
    if ((tmp.has_char(line[i]) && tmp.has_char(line[i + 1])) ||
        (tmp.has_char(line[i]) && line[i + 1] == '(') ||
        (line[i] == ')' && tmp.has_char(line[i + 1])) ||
        (line[i] == ')' && line[i + 1] == '(') ||
        (line[i] == '*' && (tmp.has_char(line[i + 1]) || line[i + 1] == '('))) {
      mul[i] = 2;
    } else if (line[i + 1] == '#') {
      mul[i] = 1;
    } else if ((line[i] == '(' && line[i + 1] == '|') ||
               (line[i] == '|' && line[i + 1] == ')') ||
               //  line[i] == '(' && line[i + 1] == ')' ||
               (line[i] == '|' && line[i + 1] == '|') ||
               (line[i] == '|' && line[i + 1] == '*')) {
      mul[i] = 3;
    }
  }
}

bool is_operator(char c) {
  return c == '*' || c == '.' || c == '|' || c == '>';
}

int id = 0;
int str_poz = 0;

struct Comp {
  bool operator()(const int& lhs, const int& rhs) const { return lhs > rhs; }
};

int recursion(std::string& s, std::map<int, Connnection, Comp>& v) {
  int rt_id = id;
  char symbol = s[str_poz];
  if (is_operator(s[str_poz])) {
    if (s[str_poz] == '*') {
      id++;
      str_poz--;
      int tmp = recursion(s, v);
      v.emplace(rt_id, Connnection(symbol, rt_id, tmp, -1));
    } else {
      id++;
      str_poz--;
      int tmp1 = recursion(s, v);
      id++;
      str_poz--;
      int tmp2 = recursion(s, v);
      v.emplace(rt_id, Connnection(symbol, rt_id, tmp2, tmp1));
    }
  } else {
    v.emplace(rt_id, Connnection(symbol, id, -1, -1));
    bool tmp_bool = false;
    if (symbol == '$')
      tmp_bool = true;
    v[rt_id].key = {false, tmp_bool, letters_count, letters_count};
    letters_count--;
  }
  return rt_id;
}

DFA re2dfa(const std::string& s) {
  Alphabet tmp(s);
  std::string copy_s = s;
  copy_s = copy_s + "#";
  auto str_size = copy_s.length();
  int bool_label[str_size];

  labels(copy_s, bool_label, tmp);
  std::string opz_str = opz(copy_s, bool_label, tmp);

  std::cout << "POLIZ: " << opz_str << "\n";
  std::cout << "($ = eps; > = .)\n";

  str_poz = opz_str.length() - 1;
  std::map<int, Connnection, Comp> tree;
  std::map<char, std::vector<int>> letters_positions;
  int counter = 1;
  for (int i = 0; i < opz_str.length(); i++) {
    if (!is_operator(opz_str[i])) {
      letters_positions[opz_str[i]].push_back(counter++);
    }
  }

  recursion(opz_str, tree);

  for (auto& i : tree) {
    if (is_operator(i.second.symbol)) {
      if (i.second.symbol == '*') {
        i.second.key = {true, true};
        for (auto& j : tree[i.second.left_id].key.fpos) {
          i.second.key.fpos[j.first] = true;
        }
        for (auto& j : tree[i.second.left_id].key.lpos) {
          i.second.key.lpos[j.first] = true;
        }

      } else if (i.second.symbol == '|') {
        if (tree[i.second.left_id].key.nullable ||
            tree[i.second.right_id].key.nullable) {
          i.second.key = {true, true};
        } else {
          i.second.key = {true, false};
        }
        for (auto& j : tree[i.second.left_id].key.fpos) {
          i.second.key.fpos[j.first] = true;
        }
        for (auto& j : tree[i.second.left_id].key.lpos) {
          i.second.key.lpos[j.first] = true;
        }
        for (auto& j : tree[i.second.right_id].key.fpos) {
          i.second.key.fpos[j.first] = true;
        }
        for (auto& j : tree[i.second.right_id].key.lpos) {
          i.second.key.lpos[j.first] = true;
        }
      } else if (i.second.symbol == '.') {
        if (tree[i.second.left_id].key.nullable &&
            tree[i.second.right_id].key.nullable) {
          i.second.key = {true, true};
        } else {
          i.second.key = {true, false};
        }
        for (auto& j : tree[i.second.left_id].key.fpos) {
          i.second.key.fpos[j.first] = true;
        }
        for (auto& j : tree[i.second.right_id].key.lpos) {
          i.second.key.lpos[j.first] = true;
        }
        if (tree[i.second.left_id].key.nullable) {
          for (auto& j : tree[i.second.right_id].key.fpos) {
            i.second.key.fpos[j.first] = true;
          }
        }
        if (tree[i.second.right_id].key.nullable) {
          for (auto& j : tree[i.second.left_id].key.lpos) {
            i.second.key.lpos[j.first] = true;
          }
        }
      }
    }
  }

  std::map<int, std::map<int, bool>> followpos;
  for (auto& i : tree) {
    if (i.second.symbol == '*') {
      for (auto& j : i.second.key.lpos) {
        for (auto& k : i.second.key.fpos)
          followpos[j.first][k.first] = true;
      }
    } else if (i.second.symbol == '.') {
      for (auto& j : tree[i.second.left_id].key.lpos) {
        for (auto& k : tree[i.second.right_id].key.fpos) {
          followpos[j.first][k.first] = true;
        }
      }
    }
  }

  std::cout << "\n!!!!!!!!!!!!!!!First-Last-POSES";

  for (const auto& i : tree) {
    std::cout << "\n" << i.second.flposes() << "\n////////////\n";
  }

  std::cout << "\n!!!!!!!!!!!!!!!FOLLOWPOS table\n";
  for (auto& i : followpos) {
    std::cout << i.first << ": ";
    for (auto& j : i.second) {
      std::cout << j.first << " ";
    }
    std::cout << "\n";
  }

  DFA res = DFA(Alphabet(s));

  std::map<int, std::map<int, bool>> states;
  int states_count = 0;
  std::string alphabet = tmp.to_string();

  states[0] = tree[0].key.fpos;
  int grid_pos = letters_positions['#'][0];
  res.create_state(std::to_string(0));
  res.set_initial(std::to_string(0));
  if (contains(states[0], grid_pos)) {
    res.make_final(std::to_string(0));
  }

  for (auto& it_current_state : states) {
    for (auto& letter : alphabet) {
      std::map<int, bool> tmp_map;
      for (auto& j : letters_positions[letter]) {
        if (contains(it_current_state.second, j)) {
          for (auto& k : followpos[j]) {
            tmp_map[k.first] = true;
          }
        }
      }
      bool next_for_check = false;
      int found_state = 0;
      for (auto& k : states) {
        if (tmp_map == k.second) {
          next_for_check = true;
          found_state = k.first;
          break;
        }
      }
      if (next_for_check) {
        res.set_trans(std::to_string(it_current_state.first), letter,
                      std::to_string(found_state));
      } else if (!next_for_check && !tmp_map.empty()) {
        states_count++;
        states[states_count] = tmp_map;
        bool final = false;
        if (contains(tmp_map, grid_pos)) {
          final = true;
        }
        res.create_state(std::to_string(states_count), final);
        res.set_trans(std::to_string(it_current_state.first), letter,
                      std::to_string(states_count));
      }
    }
  }
  return res;
}
