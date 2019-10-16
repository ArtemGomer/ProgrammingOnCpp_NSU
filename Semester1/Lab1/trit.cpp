#include "trit.h"

//Операции между тритами
trit operator|(trit left, trit right) {
  if ((left == trit::True) || (right == trit::True))
    return trit::True;
  else if ((left == trit::Unknown) || (right == trit::Unknown))
    return trit::Unknown;
  else
    return trit::False;
}

trit operator&(trit left, trit right) {
  if ((left == trit::False) || (right == trit::False))
    return trit::False;
  else if ((left == trit::Unknown) || (right == trit::Unknown))
    return trit::Unknown;
  else
    return trit::True;
}

trit operator~(trit currentTrit) {
  if (currentTrit == trit::True)
    return trit::False;
  else if (currentTrit == trit::False)
    return trit::True;
  else
    return trit::Unknown;
}

//Удобный вывод значения трита
std::ostream &operator<<(std::ostream &out, trit value) {
  switch (value) {
    case trit::Unknown: {
      out << "Unknown";
      break;
    }
    case trit::True: {
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
