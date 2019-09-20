#include <iostream>
#include <cmath>
#include <random>
#include <time.h>
using namespace std;

class pi {
 private:
  static float getNumber() {
    return (rand() / (float) RAND_MAX) * (rand() % 2 == 0 ? 1 : (-1));
  }
 public:
  static float printPi(int N) {
    unsigned long long inCircle = 0;
    for (int i = 0; i < N; i++) {
      if ((powf(getNumber(), 2) + powf(getNumber(), 2)) <= 1) {
        inCircle++;
      }
    }
    return (4 * inCircle) / (float) N;
  }
};

int main(int argc, char **argv) {
  struct timespec start, end;
  clock_gettime(CLOCK_MONOTONIC_RAW, &start);
  cout << pi::printPi(atoi(argv[1])) << endl;
  clock_gettime(CLOCK_MONOTONIC_RAW, &end);
  cout << "Time taken: " << to_string(end.tv_sec - start.tv_sec + 0.000000001 * (end.tv_nsec - start.tv_nsec)) << endl;
  return 0;
}
