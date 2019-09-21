//
// Created by Gomer on 21.09.2019.
//

#ifndef LAB2_TRITSET_H
#define LAB2_TRITSET_H
#include "trit.h"

class tritset {
 private:
  int capacity;
  size_t pos;
  unsigned char *set;
 public:
  tritset(size_t number);
  ~tritset();
  tritset &operator [](size_t index);
  tritset &operator =(trit value);
  unsigned int getChar(size_t index);
  int GetCapacity();
};
tritset &operator &(tritset &left, tritset &right);


#endif //LAB2_TRITSET_H
