#include "wordCounter.h"

int main(int argc, char **argv) {
  wordCounter f;
  try {
    f.countFrequency(argv[1]);
    f.printFrequency(argv[2]);
  }
  catch (std::invalid_argument &ex) {
    std::cout << ex.what() << std::endl;
  }
  return 0;
}