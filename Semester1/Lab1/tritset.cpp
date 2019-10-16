//
// Created by Gomer on 24.09.2019.
//

#include "tritset.h"

//Получить значение трита
static TritValue GetTrit(unsigned char currentChar, const int index, const int numberOfTrits) {
  if (index > numberOfTrits) {
    return TritValue::Unknown;
  }
  auto maskFirst = (unsigned int) pow(2, 6 - 2 * (index % 4) + 1);
  auto maskSecond = (unsigned int) pow(2, 6 - 2 * (index % 4));
  return ((currentChar & maskFirst) == 0) ? ((currentChar & maskSecond) == 0 ? TritValue::Unknown : TritValue::True)
                                          : TritValue::False;
}

//Назначить определенный трит в тритсете
static void SetTrit(unsigned char &currentChar, const TritValue value, const int index) {
  auto maskFirst = (unsigned int) pow(2, 6 - 2 * (index % 4) + 1);
  auto maskSecond = (unsigned int) pow(2, 6 - 2 * (index % 4));
  if (value == TritValue::Unknown) {
    currentChar &= ~(maskFirst | maskSecond);
  } else if (value == TritValue::True) {
    currentChar &= ~maskFirst;
    currentChar |= maskSecond;
  } else {
    currentChar |= maskFirst;
    currentChar &= ~maskSecond;
  }
}

//Конструктор
tritset::tritset(const int reservedTrits) {
  if (reservedTrits < 0) {
    throw std::invalid_argument("The size of a tritset can not be negative.");
  }
  numberOfTrits = reservedTrits;
  numberOfChars = reservedTrits == 0 ? 0 : (reservedTrits / 4) + 1;
  set.resize(numberOfChars);
}

//Конструктор копирования
tritset::tritset(const tritset &oldTritset) {
  numberOfChars = oldTritset.numberOfChars;
  numberOfTrits = oldTritset.numberOfTrits;
  set = oldTritset.set;
}

//Конструктор прокти-класса reference
tritset::reference::reference(tritset *os, const int ind)
    : index(ind), ourset(os) {
}

//Оператор индексацмм
tritset::reference tritset::operator[](const int ind) {
  if (ind < 0) {
    throw std::invalid_argument("Index can not be negative.");
  }
  return reference(this, ind);
}

//Присваивание значению
tritset::reference &tritset::reference::operator=(const TritValue value) {
  if ((index > ourset->numberOfTrits) && (value != TritValue::Unknown)) {
    ourset->numberOfChars = index / 4 + 1;
    ourset->set.resize(ourset->numberOfChars);
    ourset->numberOfTrits = index + 1;
  }
  SetTrit(ourset->set[index / 4], value, index);
  return *this;
}

//Присваивание значению из другого тритсета
tritset::reference &tritset::reference::operator=(const tritset::reference &ref) {
  *this = (TritValue) ref;
  return *this;
}

//Приведение типов
tritset::reference::operator TritValue() const {
  return GetTrit(ourset->set[index / 4], index, ourset->numberOfTrits);
}

//Операции между тритсетами
tritset operator|(tritset &left, tritset &right) {
  int max_size = (left.numberOfTrits > right.numberOfTrits ? left.numberOfTrits : right.numberOfTrits);
  tritset A(max_size);
  for (int i = 0; i < max_size; i++) {
    A[i] = left[i] | right[i];
  }
  return A;
}

tritset operator&(tritset &left, tritset &right) {
  int max_size = (left.numberOfTrits > right.numberOfTrits ? left.numberOfTrits : right.numberOfTrits);
  tritset A(max_size);
  for (int i = 0; i < max_size; i++) {
    A[i] = left[i] & right[i];
  }
  return A;
}

tritset operator~(tritset &current) {
  int max_size = current.numberOfTrits;
  tritset A(max_size);
  for (int i = 0; i < max_size; i++) {
    A[i] = ~current[i];
  }
  return A;
}

//Утилиты для тритсета
//Сжимание до последнего значащего трита
void tritset::Shrink() {
  int length = logicalLength();
  if (length != 0) {
    numberOfChars = (length - 1) / 4 + 1;
    numberOfTrits = length;
    set.resize(numberOfChars);
  } else {
    numberOfChars = 0;
    numberOfTrits = 0;
    set.resize(0);
  }
}

//Вместимость тритов
int tritset::Capacity() {
  return numberOfTrits;
}

//Количество char-ов для хранения тритов
int tritset::Size() {
  return numberOfChars;
}

//забыть все с lastIndex-того элемента
void tritset::Trim(const int lastIndex) {
  if (lastIndex < 0) {
    throw std::invalid_argument("Last index must be >= 0");
  }
  for (int i = lastIndex; i < numberOfTrits + 1; i++) {
    (*this)[i] = TritValue::Unknown;
  }
}

//Подсчет вхождений значения в тритсет
int tritset::Cardinality(const TritValue val) {
  int stat = 0;
  for (int i = 0; i < numberOfTrits; i++) {
    if ((*this)[i] == val) {
      stat++;
    }
  }
  return stat;
}

std::map<TritValue, int> tritset::Cardinality() {
  std::map<TritValue, int> stat;
  for (int i = 0; i < numberOfTrits; i++) {
    switch ((*this)[i]) {
      case TritValue::Unknown: {
        stat[TritValue::Unknown]++;
        break;
      }
      case TritValue::True: {
        stat[TritValue::True]++;
        break;
      }
      default: {
        stat[TritValue::False]++;
        break;
      }
    }
  }
  return stat;
}

int tritset::logicalLength() {
  int lastIndex = 0;
  for (int i = 0; i < numberOfTrits; i++) {
    if ((*this)[i] != TritValue::Unknown) {
      lastIndex = i;
    }
  }
  if (lastIndex == 0) {
    return 0;
  } else {
    return lastIndex + 1;
  }
}
