//
// Created by Gomer on 24.09.2019.
//

#include "tritset.h"
tritset::tritset(int reservedTrits) {
  numberOfTrits = reservedTrits;
  numberOfChars = (reservedTrits / 4) + 1;
  set = new unsigned char(numberOfChars);
  memset(set, 170, numberOfChars);
}
tritset::~tritset() {
  delete[] set;
}

tritset::tritset(tritset &oldTritset) {
  numberOfChars = oldTritset.numberOfChars;
  numberOfTrits = oldTritset.numberOfTrits;
  set = new unsigned char(numberOfChars);
  memset(set, 0, numberOfChars);
  memcpy(set, oldTritset.set, numberOfChars);
}

TritValue tritset::operator[](int index) const {
  return GetTrit(set[index], index);
}
