// #include <complex.h>
#include <math.h>
#include <stdio.h>
#include <complex>
#include <iostream>

const float hW = 100;
const float h = 1;
const float G = 0.0001 * hW;

float prob(std::complex<float> x) {
  return fabs(std::real(x * std::conj(x)));
}

#define MAX(a, b) (((a) > (b)) ? (a) : (b))

struct state {
  char n1;
  char n2;
  char f0u;
  char f0d;
  char f1u;
  char f1d;

  state() {}
  state(char n1_, char n2_, char f0u_, char f0d_, char f1u_, char f1d_)
      : n1(n1_), n2(n2_), f0u(f0u_), f0d(f0d_), f1u(f1u_), f1d(f1d_) {}
};

state states[24] = {
    state(0, 0, 1, 1, 0, 0),  // 0
    state(0, 0, 0, 1, 0, 1),  // 1
    state(0, 0, 1, 0, 1, 0),  // 2
    state(0, 0, 1, 0, 0, 1),  // 3
    state(0, 0, 0, 1, 1, 0),  // 4
    state(0, 0, 0, 0, 1, 1),  // 5

    state(0, 1, 1, 1, 0, 0), state(0, 1, 0, 1, 0, 1), state(0, 1, 1, 0, 1, 0),
    state(0, 1, 1, 0, 0, 1), state(0, 1, 0, 1, 1, 0), state(0, 1, 0, 0, 1, 1),

    state(1, 0, 1, 1, 0, 0), state(1, 0, 0, 1, 0, 1), state(1, 0, 1, 0, 1, 0),
    state(1, 0, 1, 0, 0, 1), state(1, 0, 0, 1, 1, 0), state(1, 0, 0, 0, 1, 1),

    state(1, 1, 1, 1, 0, 0), state(1, 1, 0, 1, 0, 1), state(1, 1, 1, 0, 1, 0),
    state(1, 1, 1, 0, 0, 1), state(1, 1, 0, 1, 1, 0), state(1, 1, 0, 0, 1, 1)};

float H(int i, int j) {
  if (i == j)
    return (states[i].n1 + states[i].n2 + states[i].f1d + states[i].f1u) * hW;
  if (states[i].f0d == states[j].f0d && states[i].f1d == states[j].f1d &&
      states[i].n2 == states[j].n2) {
    if (states[i].f0u - states[j].f0u == 1 &&
        states[j].f1u - states[i].f1u == 1 && states[i].n1 - states[j].n1 == 1)
      return sqrt(MAX(states[i].n1, states[j].n1)) * G;
    if (states[i].f0u - states[j].f0u == -1 &&
        states[j].f1u - states[i].f1u == -1 &&
        states[i].n1 - states[j].n1 == -1)
      return sqrt(MAX(states[i].n1, states[j].n1)) * G;
  } else if (states[i].f0u == states[j].f0u && states[i].f1u == states[j].f1u &&
             states[i].n1 == states[j].n1) {
    if (states[i].f0d - states[j].f0d == 1 &&
        states[j].f1d - states[i].f1d == 1 && states[i].n2 - states[j].n2 == 1)
      return sqrt(MAX(states[i].n2, states[j].n2)) * G;
    if (states[i].f0d - states[j].f0d == -1 &&
        states[j].f1d - states[i].f1d == -1 &&
        states[i].n2 - states[j].n2 == -1)
      return sqrt(MAX(states[i].n2, states[j].n2)) * G;
  }
  return 0;
}

int main(int argc, char* argv[]) {
  if (argc < 3) {
    printf("Need more arguments\n");
    return 0;
  }

  int maxt = atoi(argv[1]);
  int niter = atoi(argv[2]);
  float dt = (float)maxt / niter;
  float t = 0;

  printf("%d\n%d\n", maxt, niter);
  std::complex<float> psi_old[24] = {0};
  std::complex<float> psi_new[24] = {0};

  // psi_old[4] = std::complex<float>((float)0.5, (float)0);
  // psi_old[0] = std::complex<float>((float)-0.5, (float)0);
  // psi_old[5] = std::complex<float>((float)0.5, (float)0);
  // psi_old[3] = std::complex<float>((float)-0.5, (float)0);

  // psi_old[0] = 1;  // первый тест
  psi_old[3] = 1;  // второй тест

  for (int k = 0; k < niter; k++) {
    std::complex<float> sum = 0;
    for (int i = 0; i < 24; i++) {
      psi_new[i] = 0;
      for (int j = 0; j < 24; j++) {
        psi_new[i] +=
            (std::complex<float>((float)(i == j), -(1 / h) * H(i, j) * dt)) *
            psi_old[j];
      }
      sum += psi_new[i] * conj(psi_new[i]);
    }
    float answer = prob(psi_old[0]) + prob(psi_old[6]) + prob(psi_old[12]) +
                   prob(psi_old[18]);

    printf("%f %f\n", t, answer);

    t += dt;
    if (dt < 0.0000000001)
      for (int i = 0; i < 24; i++)
        psi_old[i] = psi_new[i];
    else
      for (int i = 0; i < 24; i++)
        psi_old[i] = psi_new[i] / sqrt(sum);
  }

  return 0;
}