#include <fstream>
#include <iostream>
#include <istream>
#include <random>

const std::string TEST_FOLDER = "\\tests\\";
unsigned int xorShift(unsigned int seed, int r1, int r2);
unsigned int mersenneTwister(unsigned int& seed, int r1, int r2);
unsigned int middleSquareMethod(unsigned int seed, int r1, int r2);

int main(){
  // Assigns variables for seed, quantity of numbers, minimum value, and maximum value
  unsigned int seed, N, min, max;
  std::cin >> seed >> N >> min >> max;

  // Creates a random number generator between 1 and 3
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> distr(1, 3);

  // Chooses an PRNG based on the random number assigned
  switch (distr(gen)) {
    case 1:
      // Runs Xorshift with user input
      std::cout << "Xorshift" << std::endl;
      for (unsigned int i = 0; i < N; i++)
      {
        unsigned int randomNumber = xorShift(seed, min, max);
        std::cout << randomNumber << std::endl;
        seed = randomNumber;
      }
    break;
    case 2:
      // Runs Mersenne Twister with user input
      std::cout << "Mersenne Twister" << std::endl;
      for (unsigned int i = 0; i < N; i++)
      {
        unsigned int randomNumber = mersenneTwister(seed, min, max);
        std::cout << randomNumber << std::endl;
      }
    break;
    case 3:
      // Runs Middle Square Method with user input
      std::cout << "Middle Square Method" << std::endl;
      for (unsigned int i = 0; i < N; i++)
      {
        unsigned int randomNumber = middleSquareMethod(seed, min, max);
        std::cout << randomNumber << std::endl;
        seed = randomNumber;
      }
    break;
  }

  return 0;
}

// Xorshift function that uses Xorshift to randomly generate a number
unsigned int xorShift(unsigned int seed, int r1, int r2) {
  // Takes the seed and shifts it accordingly for Xorshift
  seed ^= (seed << 13);
  seed ^= (seed >> 17);
  seed ^= (seed << 5);

  // Sets the minimum and maximum values for the randomly generated number
  int min_value = std::min(r1, r2);
  int max_value = std::max(r1, r2);

  // Gives the result using the decimal from the seed shift using minimum and maximum values
  unsigned int result = min_value + (seed % (max_value - min_value + 1));

  return result;
}

// Mersenne Twister function that uses Mersenne Twister to randomly generate a number
unsigned int mersenneTwister(unsigned int& seed, int r1, int r2) {
  // Variables used to generate random numbers effectively
  static const unsigned int N = 624;
  static const unsigned int M = 397;
  static const unsigned int MATRIX_A = 0x9908b0df;
  static const unsigned int UM = 0x80000000;
  static const unsigned int LM = 0x7fffffff;

  static unsigned int mt[N];
  static unsigned int mti = N + 1;

  // Initializes vector if it's the first use
  if (mti == N + 1) {
    mt[0] = seed;
    for (mti = 1; mti < N; mti++) {
      mt[mti] = (1812433253UL * (mt[mti - 1] ^ (mt[mti - 1] >> 30)) + mti);
      mt[mti] &= LM;
    }
  }

  // Variables to hold value of generated number
  unsigned int y;
  unsigned int kk;

  // Generates numbers
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

  // Extracts the next value
  y = mt[mti++];
  y ^= (y >> 11);
  y ^= (y << 7) & 0x9d2c5680;
  y ^= (y << 15) & 0xefc60000;
  y ^= (y >> 18);

  // Gets the minimum and maximum values and then calculates the result
  int min_value = std::min(r1, r2);
  int max_value = std::max(r1, r2);
  unsigned int result = min_value + (y % (max_value - min_value + 1));

  return result;
}

// Middle Square Method function that uses Middle Square Method to randomly generate a number
unsigned int middleSquareMethod(unsigned int seed, int r1, int r2) {
  // Variables that are used to help generate random numbers
  // Squares the seed and then converts it to a string
  const int numDigits = 4;
  const int totalDigits = 8;
  unsigned long long squared = static_cast<unsigned long long>(seed) * seed;
  std::string squaredStr = std::to_string(squared);

  // Checks to see if the string has the right number of digits in it
  if (squaredStr.length() < totalDigits) {
    squaredStr.insert(0, totalDigits - squaredStr.length(), '0');
  }

  // Gets the middle digits
  int start = (squaredStr.length() - numDigits) / 2;
  std::string middleDigits = squaredStr.substr(start, numDigits);
  seed = std::stoul(middleDigits);

  // Finds the minimum and maximum values and then calculates the result
  int min_value = std::min(r1, r2);
  int max_value = std::max(r1, r2);
  unsigned int finalResult = min_value + (seed % (max_value - min_value + 1));

  return finalResult;
}
