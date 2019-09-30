#include "wordCounter.h"

int main(int argc, char **argv) {
  wordCounter f;
  try {
    f.countFrequency(argv[argc - 2]);
    f.printFrequency(argv[argc - 1]);
  }
  catch (std::invalid_argument &ex) {
    std::cout << ex.what() << argv[argc - 2] << std::endl;
  }
  return 0;
}