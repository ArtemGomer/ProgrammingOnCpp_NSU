//
// Created by Gomer on 25.09.2019.
//

#include "onetrit.h"

onetrit &onetrit::operator=(TritValue value) {
  val = value;
  return *this;
}

onetrit::onetrit(TritValue value) : val(value) {}

std::ostream &operator<<(std::ostream &out, TritValue value) {
  switch (value) {
    case Unknown: {
      std::cout << "Unknown";
      break;
    }
    case True: {
      std::cout << "True";
      break;
    }
    default: {
      std::cout << "False";
      break;
    }
  }
  return out;
}

TritValue operator|(onetrit &left, onetrit &right) {
  if ((left.GetValue() == True) || (right.GetValue() == True))
    return True;
  else if ((left.GetValue() == Unknown) || (right.GetValue() == Unknown))
    return Unknown;
  else
    return False;
}

TritValue operator&(onetrit &left, onetrit &right) {
  if ((left.GetValue() == False) || (right.GetValue() == False))
    return False;
  else if ((left.GetValue() == Unknown) || (right.GetValue() == Unknown))
    return Unknown;
  else
    return True;
}

TritValue operator~(onetrit &currentTrit) {
  if (currentTrit.GetValue() == True)
    return False;
  else if (currentTrit.GetValue() == False)
    return True;
  else
    return Unknown;
}

TritValue onetrit::GetValue() {
  return val;
}

TritValue GetTrit(unsigned char &currentChar, int index) {
  auto maskFirst = (unsigned int) pow(2, 6 - 2 * (index % 4) + 1);
  auto maskSecod = (unsigned int) pow(2, 6 - 2 * (index % 4));
  return ((currentChar & maskFirst) != 1) ? False : ((currentChar & maskSecod) == 0 ? Unknown : True);
}

void SetTrit(unsigned char &currentChar, TritValue value, int index){
  auto maskFirst = (unsigned int) pow(2, 6 - 2 * (index % 4) + 1);
  auto maskSecond = (unsigned int) pow(2, 6 - 2 * (index % 4));
  if (value == Unknown){
    currentChar &= ~(maskFirst | maskSecond);
  }
  else if (value == True){
    currentChar &= ~maskFirst;
    currentChar |= maskSecond;
  }
  else{
    currentChar |= maskFirst;
    currentChar &= ~maskSecond;
  }
}