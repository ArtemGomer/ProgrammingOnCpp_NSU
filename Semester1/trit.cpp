//
// Created by Gomer on 20.09.2019.
//

#include "trit.h"
trit::trit() { value = Unknown; }
trit::trit(int N) : value(N) {}
trit &trit::operator=(trit const &right) {
  *this = right;
  return *this;
}
int trit::GetValue() {
  return value;
}
void trit::SetValue(int val) {
  value = val;
}
trit &operator&(trit &left, trit &right) {
  switch (left.GetValue()) {
    case (True): return right;
    case (False): return left;
    default: return right.GetValue() == False ? right : left;
  }
}

trit &operator|(trit &left, trit &right) {
  switch (left.GetValue()) {
    case (True): return left;
    case (False): return right;
    default: return right.GetValue() == True ? right : left;
  }
}

std::ostream &operator<<(std::ostream &out, trit &t) {
  switch (t.GetValue()) {
    case (True): {
      std::cout << "True";
      return out;
    }
    case (False): {
      std::cout << "False";
      return out;
    }
    default: {
      std::cout << "Unknown";
      return out;
    }
  }
}
