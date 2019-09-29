//
// Created by Gomer on 25.09.2019.
//

#include "onetrit.h"

onetrit &onetrit::operator=(TritValue value) {
  val = value;
  return *this;
}

onetrit::onetrit(TritValue value) : val(value) {}

//Операции между тритами
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

//получить значение трита в тритсете
TritValue GetTrit(unsigned char currentChar, int index) {
  auto maskFirst = (unsigned int) pow(2, 6 - 2 * (index % 4) + 1);
  auto maskSecond = (unsigned int) pow(2, 6 - 2 * (index % 4));
  return ((currentChar & maskFirst) == 0) ? ((currentChar & maskSecond) == 0 ? Unknown : True) : False;
}

//Назначить определенный трит в тритсете
void SetTrit(unsigned char &currentChar, TritValue value, int index) {
  auto maskFirst = (unsigned int) pow(2, 6 - 2 * (index % 4) + 1);
  auto maskSecond = (unsigned int) pow(2, 6 - 2 * (index % 4));
  if (value == Unknown) {
    currentChar &= ~(maskFirst | maskSecond);
  } else if (value == True) {
    currentChar &= ~maskFirst;
    currentChar |= maskSecond;
  } else {
    currentChar |= maskFirst;
    currentChar &= ~maskSecond;
  }
}

//Вернуть значение трита
TritValue onetrit::GetValue() {
  return val;
}

//Удобный вывод значения трита
std::ostream &operator<<(std::ostream &out, TritValue value) {
  switch (value) {
    case Unknown: {
      out << "Unknown";
      break;
    }
    case True: {
      out << "True";
      break;
    }
    default: {
      out << "False";
      break;
    }
  }
  return out;
}