//
// Created by Gomer on 25.09.2019.
//

#ifndef LAB2_1_TRIT_H
#define LAB2_1_TRIT_H
#include <iostream>
#include <cmath>

enum class trit {
  Unknown = 0, True, False
};

std::ostream &operator<<(std::ostream &out, trit value);
trit operator|(trit left, trit right);
trit operator&(trit left, trit right);
trit operator~(trit currentTrit);

#endif //LAB2_1_TRIT_H
