#include <algorithm>
#include <iomanip>
#include <iostream>
#include <vector>

/*
Говно из жопы а не задача
*/

std::ostream& operator<<(std::ostream& out, std::vector<int>& a) {
  for (int i = 0; i < a.size(); i++) {
    out << a[i] << " ";
  }
  return out;
}

int main() {
  int n;
  std::cin >> n;
  std::vector<int> numbers(n);
  std::vector<int> numbers_pos(n), numbers_half(n);
  int pos_n, pos_1, half = 0, min_left = n, max_right = 0;
  const int one_num = 0, n_num = n - 1;
  int input;
  for (int i = 0; i < n; i++) {
    std::cin >> input;
    numbers[i] = input - 1;
    if (numbers[i] == one_num) {
      half = 1;
      pos_1 = i;
    } else if (numbers[i] == n_num) {
      pos_n = i;
    }
    if (half) {
      if (numbers[i] > max_right) {
        max_right = numbers[i];
      }
    } else {
      if (numbers[i] < min_left) {
        min_left = numbers[i];
      }
    }
    numbers_pos[numbers[i]] = i;
    numbers_half[numbers[i]] = half;
  }

  int true_max_right = max_right;
  // if (max_right == 0) {
  max_right = n - 1;
  // }
  if (min_left == n) {
    min_left = 0;
  }

  std::cout << "A Here" << std::endl;

  std::vector<int> inv_before(n, 0);
  for (int i = 0; i < n; i++) {
    for (int j = i + 1; j < n; j++) {
      if (numbers[i] >= min_left && numbers[j] >= min_left &&
          numbers[i] > numbers[j]) {
        inv_before[numbers[j]]++;
      }
    }
  }

  std::cout << "B Here" << std::endl;

  int total_transposes = 0, total_after_transposes = 0;
  std::vector<int> inv_after(n, 0);
  for (int i = 0; i < n; i++) {
    for (int j = i + 1; j < n; j++) {
      if (numbers[i] > numbers[j]) {
        inv_after[numbers[i]]++;
        if (numbers[i] <= true_max_right && numbers[j] <= true_max_right) {
          total_after_transposes++;
        }
        if (numbers[i] >= min_left && numbers[j] >= min_left) {
          total_transposes++;
        }
      }
    }
  }

  std::cout << "C Here" << std::endl;

  std::vector<int> right_numbers_cnt(
      n, 0);  // количество чисел, расположенных справа от i, слева от 1 и лежат
              // в диапазоне [min_left, number[i]]
  for (int i = 0; i < pos_1; i++) {
    for (int j = i + 1; j < pos_1; j++) {
      std::cout << "In for" << std::endl;
      if (numbers[i] <= max_right && numbers[j] >= min_left &&
          numbers[j] <= numbers[i]) {
        right_numbers_cnt[numbers[i]]++;
      }
    }
  }
  std::cout << "D Here" << std::endl;
  // для чисел после 1 это числа, лежащие между 1 и i, которые лежат в диапазоне
  // [numbers[i], max_right]
  for (int i = pos_1 + 1; i < n; i++) {
    for (int j = pos_1; j < i; j++) {
      if (numbers[i] >= min_left && numbers[j] >= numbers[i] &&
          numbers[j] <= max_right) {
        right_numbers_cnt[numbers[i]]++;
      }
    }
  }
  std::cout << "E Here" << std::endl;

  std::vector<int> right_numbers_cnt2(
      n, 0);  // То же самое, только теперь числа слева от i
  for (int i = 1; i < pos_1; i++) {
    for (int j = 0; j < i; j++) {
      if (numbers[i] <= max_right && numbers[j] >= min_left &&
          numbers[j] <= numbers[i]) {
        right_numbers_cnt2[numbers[i]]++;
      }
    }
  }
  std::cout << "F Here" << std::endl;
  // соответственно для чисел после 1, числа лежащие справа от i, в диапазоне
  // [numbers[i], max_right]
  for (int i = pos_1; i < n; i++) {
    for (int j = i + 1; j < n; j++) {
      if (numbers[i] >= min_left && numbers[j] >= numbers[i] &&
          numbers[j] <= max_right) {
        right_numbers_cnt2[numbers[i]]++;
      }
    }
  }
  std::cout << "G Here" << std::endl;

  std::vector<int> count_transposes(
      n, 0);  // сколько нужно транспозиций, чтобы перевести число из одной
  // половины в другую
  int last_right_number = -1, last_left_number = -1;
  for (int i = min_left; i <= max_right; i++) {
    if (numbers_half[i] == 0) {
      count_transposes[i] =
          pos_1 - numbers_pos[i] - right_numbers_cnt[i] - 1 +
          ((last_left_number != -1) ? count_transposes[last_left_number] : 0);

      count_transposes[i] -= right_numbers_cnt2[i];
      last_left_number = i;
    }
  }
  std::cout << "H Here" << std::endl;
  for (int i = max_right; i >= min_left; i--) {
    if (numbers_half[i] == 1) {
      count_transposes[i] =
          numbers_pos[i] - pos_1 - right_numbers_cnt[i] +
          ((last_right_number != -1) ? count_transposes[last_right_number] : 0);

      count_transposes[i] -= right_numbers_cnt2[i];
      last_right_number = i;
    }
  }
  std::cout << "I Here" << std::endl;

  std::vector<int> movable_rl_numbers;
  for (int i = min_left; i < n; i++) {
    if (numbers_half[i] == 1) {
      movable_rl_numbers.push_back(i);
    }
  }
  movable_rl_numbers.push_back(0);

  int current_rl_move = right_numbers_cnt2[movable_rl_numbers[0]] +
                        right_numbers_cnt[movable_rl_numbers[0]] +
                        (movable_rl_numbers[0] > min_left ? 1 : 0);
  int current_lr_move = 0;
  std::cout << "movable rl vector:";
  for (int i = 0; i < movable_rl_numbers.size(); i++) {
    std::cout << " " << movable_rl_numbers[i] << "  ";
  }
  std::cout << std::endl;

  int vector_pos = 0;
  std::cout << "J Here" << std::endl;

  int min_count_transpose = std::max(
      total_transposes + count_transposes[movable_rl_numbers[vector_pos]],
      total_after_transposes);
  int left_numbers_t = 0, right_numbers_t = 0;
  int last_lr_moves = 0, last_lr_number = 0;
  for (int i = min_left; i < n; i++) {
    if (numbers_half[i] == 0) {
      left_numbers_t += inv_after[i];
      left_numbers_t -= inv_before[i];
      current_lr_move++;
      int tmp = current_lr_move * current_rl_move +
                count_transposes[movable_rl_numbers[vector_pos]] +
                count_transposes[i] + left_numbers_t + right_numbers_t;
      if (min_count_transpose > tmp + total_transposes) {
        min_count_transpose = tmp + total_transposes;
      }
      std::cout << "A: " << tmp + total_transposes << std::endl;
      last_lr_number = i;
    } else {
      // Сначала считаю, что только перекидываю число из правой части в левую.
      int tmp = last_lr_moves +
                count_transposes[movable_rl_numbers[vector_pos]] +
                right_numbers_t;

      if (min_count_transpose > tmp + total_transposes) {
        min_count_transpose = tmp + total_transposes;
      }
      std::cout << "B: " << tmp + total_transposes << std::endl;

      current_rl_move--;
      last_lr_moves = current_lr_move * current_rl_move +
                      count_transposes[last_lr_number] + left_numbers_t;

      vector_pos++;
      right_numbers_t += inv_after[i];
      right_numbers_t -= inv_before[i];

      // Считаю, что перекидываю из левой части до правой, выкидывая всё что
      // выше
      tmp = current_lr_move * current_rl_move +
            count_transposes[movable_rl_numbers[vector_pos]] +
            count_transposes[last_lr_number] + left_numbers_t + right_numbers_t;

      if (min_count_transpose > tmp + total_transposes) {
        min_count_transpose = tmp + total_transposes;
      }
      std::cout << "C: " << tmp + total_transposes << std::endl;
    }
  }

  // for (int i = min_left; i < n; i++) {
  //   if (numbers_half[i] == 1) {
  //     inv_after_sum -= inv_before[i];
  //     int tmp = current_left_move * current_right_move + count_transposes[i]
  //     +
  //               count_transposes[movable_right_numbers[vector_pos]] +
  //               inv_after_sum + inv_before_sum;
  //   } else if (numbers_half[i] == 0) {
  //     int tmp = count_transposes[movable_right_numbers[vector_pos]];
  //     inv_before_sum -= inv_before[i];
  //   }
  // }

  std::cout << std::setw(13) << "numbers: ";
  for (int i = 0; i < n; i++) {
    std::cout << "[" << i + 1 << "] ";
  }
  std::cout << "\n";
  std::cout << std::setw(13) << "inv_after:";
  for (int i = 0; i < n; i++) {
    std::cout << " " << inv_after[i] << "  ";
  }
  std::cout << "\n";
  std::cout << std::setw(13) << "inv_before:";
  for (int i = 0; i < n; i++) {
    std::cout << " " << inv_before[i] << "  ";
  }
  std::cout << "\n";
  std::cout << std::setw(13) << "right_num:";
  for (int i = 0; i < n; i++) {
    std::cout << " " << right_numbers_cnt[i] << "  ";
  }
  std::cout << "\n";
  std::cout << std::setw(13) << "right_num2:";
  for (int i = 0; i < n; i++) {
    std::cout << " " << right_numbers_cnt2[i] << "  ";
  }
  std::cout << "\n";
  std::cout << std::setw(13) << "cnt_t:";
  for (int i = 0; i < n; i++) {
    std::cout << " " << count_transposes[i] << "  ";
  }
  std::cout << "\n";

  std::cout << "pos_n = " << pos_n << "\n";
  std::cout << "pos_1 = " << pos_1 << "\n";
  std::cout << "min_left = " << min_left << "\n";
  std::cout << "max_right = " << max_right << "\n";
  std::cout << "halfs " << numbers_half << "\n";
  std::cout << "positions " << numbers_pos << "\n";
  std::cout << "total = " << total_transposes << "\n";

  std::cout << "\n\nAnswer is: " << min_count_transpose << "\n";

  return 0;
}