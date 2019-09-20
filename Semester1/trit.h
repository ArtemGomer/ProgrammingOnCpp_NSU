//
// Created by Gomer on 20.09.2019.
//

#ifndef LAB2_TRIT_H
#define LAB2_TRIT_H
#include <iostream>
#include <fstream>

enum Trit{
  True, False, Unknown
};

class trit {
 private:
  int value;
 public:
  trit();
  explicit trit(int N);
  trit &operator=(trit const &right);
  int GetValue();
  void SetValue(int val);
};
trit &operator&(trit &left, trit &right);
trit &operator|(trit &left, trit &right);
std::ostream &operator<<(std::ostream &out, trit &t);

#endif //LAB2_TRIT_H
