//
// Created by Gomer on 25.09.2019.
//

#ifndef LAB2_1_ONETRIT_H
#define LAB2_1_ONETRIT_H
#include <iostream>
#include <cstring>
#include <cmath>

enum TritValue {
  Unknown = 0, True, False
};
class onetrit {
 private:
  TritValue val;
 public:
  explicit onetrit(TritValue value);
  TritValue GetValue();
  onetrit &operator=(TritValue value);
};
std::ostream &operator<<(std::ostream &out, TritValue value);
TritValue operator|(onetrit &left, onetrit &right);
TritValue operator&(onetrit &left, onetrit &right);
TritValue operator~(onetrit &currentTrit);

#endif //LAB2_1_ONETRIT_H
