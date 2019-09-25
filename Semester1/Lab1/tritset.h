//
// Created by Gomer on 24.09.2019.
//

#ifndef LAB2_1_TRITSET_H
#define LAB2_1_TRITSET_H
#include "onetrit.h"

class tritset {
 private:
  unsigned char *set;
  int numberOfChars;
  int numberOfTrits;
 public:
  explicit tritset(int reservedTrits);
  tritset(tritset &oldTritset);
  ~tritset();
  friend class reference;
  TritValue operator[](int index) const;
};



#endif //LAB2_1_TRITSET_H
