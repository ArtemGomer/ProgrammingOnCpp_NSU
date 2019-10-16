//
// Created by Gomer on 24.09.2019.
//

#ifndef LAB2_1_tritset_H
#define LAB2_1_tritset_H

#include "trit.h"
#include <vector>
#include <map>

class tritset {
 public:
  class reference {
   private:
    tritset *tSet;
    size_t index;
   public:
    reference(tritset *os, size_t ind);
    operator trit() const;
    reference &operator=(trit value);
    reference &operator=(const reference &ref);
  };
  explicit tritset(int reservedTrits);
  tritset(const tritset &oldTritset);
  tritset::reference operator[](int ind);
  friend tritset operator|(tritset &left, tritset &right);
  friend tritset operator&(tritset &left, tritset &right);
  friend tritset operator~(tritset &current);
  void shrink();
  size_t capacity();
  size_t size();
  void trim(int lastIndex);
  size_t cardinality(trit val);
  size_t logicalLength();
  std::map<trit, size_t> cardinality();
 private:
  std::vector<unsigned char> set;
  size_t numberOfChars;
  size_t numberOfTrits;
};

#endif //LAB2_1_tritset_H
