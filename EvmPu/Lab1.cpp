#include <iostream>
#include <cmath>
#include <random>
#include <chrono>
using namespace std;

class pi{
 private:
  static float getNumber(){
    return (rand() / (float)RAND_MAX) * (rand() % 2 == 0 ? 1 : (-1));
  }
 public:
  static float printPi(unsigned long long N){
    unsigned long long inCircle = 0;
    for (int i = 0; i < N; i++){
      if ((powf(getNumber(), 2) + powf(getNumber(), 2)) <= 1){
        inCircle++;
      }
    }
    return (4 * inCircle)/ (float)N;
  }
};

int main(int argc, char **argv){
  auto start = std::chrono::system_clock::now();
  cout << pi::printPi(atoi(argv[1])) << endl;
  auto end = std::chrono::system_clock::now();
  std::chrono::duration<double> elapsed_seconds = end - start;
  cout << elapsed_seconds.count() << 's' << endl;
  return 0;
}
