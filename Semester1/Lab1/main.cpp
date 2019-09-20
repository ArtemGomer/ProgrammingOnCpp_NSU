#include "trit.h"

int main() {
  trit t(True);
  trit s(Unknown);
  std::cout << (t | s) << " " << (t & s) << std::endl;
  return 0;
}
