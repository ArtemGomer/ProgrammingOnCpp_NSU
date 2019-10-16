//
// Created by Gomer on 24.09.2019.
//

#ifndef LAB2_1_tritset_H
#define LAB2_1_tritset_H

#include "onetrit.h"
#include <vector>
#include <map>

class tritset {
 public:
  class reference {
   private:
    tritset *ourset;
    int index;
   public:
    reference(tritset *os, int ind);
    operator TritValue() const;
    reference &operator=(TritValue value);
    reference &operator=(const reference &ref);
  };
  explicit tritset(int reservedTrits);
  tritset(const tritset &oldTritset);
  tritset::reference operator[](int ind);
  friend tritset operator|(tritset &left, tritset &right);
  friend tritset operator&(tritset &left, tritset &right);
  friend tritset operator~(tritset &current);
  void Shrink();
  int Capacity();
  int Size();
  void Trim(int lastIndex);
  int Cardinality(TritValue val);
  int logicalLength();
  std::map<TritValue, int> Cardinality();
 private:
  std::vector<unsigned char> set;
  int numberOfChars;
  int numberOfTrits;
};

#endif //LAB2_1_tritset_H
