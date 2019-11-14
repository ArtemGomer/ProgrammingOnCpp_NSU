#include "worker.h"

int main(int argc, char **argv) {
  worker w;
  try {
    w.process(argv[1]);
  }
  catch (const std::exception &ex){
    std::cout << ex.what() << std::endl;
    return 1;
  }
  return 0;
}