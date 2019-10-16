//
// Created by Gomer on 25.09.2019.
//

#ifndef LAB2_1_ONETRIT_H
#define LAB2_1_ONETRIT_H
#include <iostream>
#include <cmath>

enum class TritValue {
  Unknown = 0, True, False
};

std::ostream &operator<<(std::ostream &out, TritValue value);
TritValue operator|(TritValue left, TritValue right);
TritValue operator&(TritValue left, TritValue right);
TritValue operator~(TritValue currentTrit);

#endif //LAB2_1_ONETRIT_H
