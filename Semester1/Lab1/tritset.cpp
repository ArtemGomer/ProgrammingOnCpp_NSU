//
// Created by Gomer on 21.09.2019.
//

#include "tritset.h"

tritset::tritset(size_t number) {
  capacity = number;
  set = nullptr;
  pos = 0;
  set = new unsigned char(number / 4 + 1);
  for (size_t i = 0; i < number / 4 + 1; i++){
    set[i] = 0;
  }
}

tritset::~tritset() {
  delete[] set;
}

tritset &tritset::operator[](size_t index) {
  pos = index;
  return *this;
}

tritset &tritset::operator=(trit value) {
  size_t place = pos % 4;
  if (value.GetValue() == True){
    if (place == 0){
      set[pos / 4] = (set[pos / 4] & 0x3fu) | 0x40u;
    }
    else if (place == 1){
      set[pos / 4] = (set[pos / 4] & 0xcfu) | 0x10u;
    }
    else if (place == 2){
      set[pos / 4] = (set[pos / 4] & 0xf3u) | 0x04u;
    }
    else if (place == 3){
      set[pos / 4] = (set[pos / 4] & 0xfcu) | 0x01u;
    }
  }
  else if (value.GetValue() == False){
    if (place == 0){
      set[pos / 4] = (set[pos / 4] & 0x3fu) | 0x80u;
    }
    else if (place == 1){
      set[pos / 4] = (set[pos / 4] & 0xcfu) | 0x20u;
    }
    else if (place == 2){
      set[pos / 4] = (set[pos / 4] & 0xf3u) | 0x08u;
    }
    else if (place == 3){
      set[pos / 4] = (set[pos / 4] & 0xfcu) | 0x02u;
    }
  }
  else if (value.GetValue() == Unknown){
    if (place == 0){
      set[pos / 4] &= 0x3fu;
    }
    else if (place == 1){
      set[pos / 4] &= 0xcfu;
    }
    else if (place == 2){
      set[pos / 4] &= 0xf3u;
    }
    else if (place == 3){
      set[pos / 4] &= 0xfcu;
    }
  }
  return *this;
}

//tritset &operator &(tritset &left, tritset &right){
//  trit l, r;
//  for (size_t i = 0; i < left.GetCapacity() * 4; i++){
//
//  }
//  return ;
//}

unsigned int tritset::getChar(size_t index) {
  return set[index];
}

int tritset::GetCapacity() {
  return capacity;
}

