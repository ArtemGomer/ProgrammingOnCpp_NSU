//
// Created by Gomer on 24.09.2019.
//

#ifndef LAB2_1_TRITSET_H
#define LAB2_1_TRITSET_H
#include "onetrit.h"
#include <vector>
#include <unordered_map>

class tritset {
 public:
  class reference {
   private:
    tritset *ourset;
    std::vector<unsigned char> newset;
    int index;
    bool overflow, newmem;
   public:
    reference(tritset *os, std::vector<unsigned char> &s, int ind, bool over);
    ~reference();
    operator TritValue();
    reference &operator=(TritValue value);
    reference &operator=(const reference &ref);
    friend std::ostream &operator<<(std::ostream &out, const tritset::reference &ref);
  };
  explicit tritset(int reservedTrits);
  tritset(tritset &oldTritset);
  tritset::reference operator[](int ind);
  tritset operator|(tritset &right);
  tritset operator&(tritset &right);
  tritset operator~();
  void Shrink();
  int Capacity();
  int Size();
  void Trim(int lastIndex);
  int Cardinality(TritValue val);
  int logicalLength();
  std::unordered_map<TritValue, int> Cardinality();
 private:
  std::vector<unsigned char> set;
  int numberOfChars;
  int numberOfTrits;
};

#endif //LAB2_1_TRITSET_H
