#include <fstream>
#include <iostream>
#include <istream>
#include <random>

const std::string TEST_FOLDER = "\\tests\\";
unsigned int xorShift(unsigned int seed, int r1, int r2);
unsigned int mersenneTwister(unsigned int& seed, int r1, int r2);
unsigned int middleSquareMethod(unsigned int seed, int r1, int r2);

int main(){
  unsigned int seed, N, min, max;
  std::cin >> seed >> N >> min >> max;

  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> distr(1, 3);

  switch (distr(gen)) {
    case 1:
      std::cout << "Xorshift" << std::endl;
      for (unsigned int i = 0; i < N; i++) {
        unsigned int randomNumber = xorShift(seed, min, max);
        std::cout << randomNumber << std::endl;
        seed = randomNumber;
      }
    break;
    case 2:
      std::cout << "Mersenne Twister" << std::endl;
      for (unsigned int i = 0; i < N; i++) {
        unsigned int randomNumber = mersenneTwister(seed, min, max);
        std::cout << randomNumber << std::endl;
      }
    break;
    case 3:
      std::cout << "Middle Square Method" << std::endl;
      for (unsigned int i = 0; i < N; i++) {
        unsigned int randomNumber = middleSquareMethod(seed, min, max);
        std::cout << randomNumber << std::endl;
      }
    break;
  }

  return 0;
}

unsigned int xorShift(unsigned int seed, int r1, int r2) {
  seed ^= (seed << 13);
  seed ^= (seed >> 17);
  seed ^= (seed << 5);

  int min_value = std::min(r1, r2);
  int max_value = std::max(r1, r2);

  unsigned int result = min_value + (seed % (max_value - min_value + 1));

  return result;
}

unsigned int mersenneTwister(unsigned int& seed, int r1, int r2) {
  static const unsigned int N = 624;
  static const unsigned int M = 397;
  static const unsigned int MATRIX_A = 0x9908b0df;
  static const unsigned int UM = 0x80000000;
  static const unsigned int LM = 0x7fffffff;

  static unsigned int mt[N];
  static unsigned int mti = N + 1;

  if (mti == N + 1) {
    mt[0] = seed;
    for (mti = 1; mti < N; mti++) {
      mt[mti] = (1812433253UL * (mt[mti - 1] ^ (mt[mti - 1] >> 30)) + mti);
      mt[mti] &= LM;
    }
  }

  unsigned int y;
  unsigned int kk;

  if (mti >= N) {
    for (kk = 0; kk < N - M; kk++) {
      y = (mt[kk] & UM) | (mt[kk + 1] & LM);
      mt[kk] = mt[kk + M] ^ (y >> 1) ^ ((y % 2) * MATRIX_A);
    }
    for (; kk < N - 1; kk++) {
      y = (mt[kk] & UM) | (mt[kk + 1] & LM);
      mt[kk] = mt[kk + (M - N)] ^ (y >> 1) ^ ((y % 2) * MATRIX_A);
    }
    y = (mt[N - 1] & UM) | (mt[0] & LM);
    mt[N - 1] = mt[M - 1] ^ (y >> 1) ^ ((y % 2) * MATRIX_A);
    mti = 0;
  }

  y = mt[mti++];
  y ^= (y >> 11);
  y ^= (y << 7) & 0x9d2c5680;
  y ^= (y << 15) & 0xefc60000;
  y ^= (y >> 18);

  int min_value = std::min(r1, r2);
  int max_value = std::max(r1, r2);
  unsigned int result = min_value + (y % (max_value - min_value + 1));

  return result;
}


unsigned int middleSquareMethod(unsigned int seed, int r1, int r2) {
  return 0;
}
