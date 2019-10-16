#include "onetrit.h"

//Операции между тритами
TritValue operator|(TritValue left, TritValue right) {
  if ((left == TritValue::True) || (right == TritValue::True))
    return TritValue::True;
  else if ((left == TritValue::Unknown) || (right == TritValue::Unknown))
    return TritValue::Unknown;
  else
    return TritValue::False;
}

TritValue operator&(TritValue left, TritValue right) {
  if ((left == TritValue::False) || (right == TritValue::False))
    return TritValue::False;
  else if ((left == TritValue::Unknown) || (right == TritValue::Unknown))
    return TritValue::Unknown;
  else
    return TritValue::True;
}

TritValue operator~(TritValue currentTrit) {
  if (currentTrit == TritValue::True)
    return TritValue::False;
  else if (currentTrit == TritValue::False)
    return TritValue::True;
  else
    return TritValue::Unknown;
}

//Удобный вывод значения трита
std::ostream &operator<<(std::ostream &out, TritValue value) {
  switch (value) {
    case TritValue::Unknown: {
      out << "Unknown";
      break;
    }
    case TritValue::True: {
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
