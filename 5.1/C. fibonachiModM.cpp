#include <iostream>
#include <ostream>
#include <vector>

std::ostream& operator<<(std::ostream& out, std::vector<std::vector<int>>& a) {
  for (auto& i : a) {
    for (auto& j : i) {
      out << j << " ";
    }
    out << std::endl;
  }
  return out;
}

std::vector<std::vector<int>> Multiply2x2Matrices(
    std::vector<std::vector<int>>& A,
    std::vector<std::vector<int>>& B,
    const int64_t& m) {
  //   std::cout << "Multi\n";
  std::vector<std::vector<int>> C = {{0, 0}, {0, 0}};
  C[0][0] = (A[0][0] * B[0][0] + A[0][1] * B[1][0]) % m;
  C[0][1] = (A[0][0] * B[0][1] + A[0][1] * B[1][1]) % m;
  C[1][0] = (A[1][0] * B[0][0] + A[1][1] * B[1][0]) % m;
  C[1][1] = (A[1][0] * B[0][1] + A[1][1] * B[1][1]) % m;
  //   std::cout << "Multi out" << std::endl;
  return C;
}

std::vector<std::vector<int>> FastMatrixExponentiation(
    std::vector<std::vector<int>>& D,
    const int64_t& n,
    const int64_t& m) {
  //   std::cout << "n = " << n << " m = " << m << std::endl;
  //   std::cout << "D:\n" << D;
  if (n == 0) {
    return (std::vector<std::vector<int>>){{1, 0}, {0, 1}};
  }  // единичная 2×2 матрица
  if (n % 2 == 0) {
    auto Y = FastMatrixExponentiation(D, n / 2, m);
    return Multiply2x2Matrices(Y, Y, m);
  } else {
    auto Y = FastMatrixExponentiation(D, (n - 1) / 2, m);
    auto Y2 = Multiply2x2Matrices(Y, Y, m);
    return Multiply2x2Matrices(Y2, D, m);
  }
  return {};
}

int FibonacciModuloM(const int64_t& n, const int64_t& m) {
  std::vector<std::vector<int>> M = {{0, 1}, {1, 1}};
  auto P = FastMatrixExponentiation(M, n, m);
  return P[0][1];
}

int main() {
  int64_t n, m;
  std::cin >> n >> m;

  std::cout << FibonacciModuloM(n, m) << std::endl;
  return 0;
}