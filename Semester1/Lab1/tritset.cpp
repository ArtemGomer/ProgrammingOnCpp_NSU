//
// Created by Gomer on 24.09.2019.
//

#include "tritset.h"

//Получить значение трита
static TritValue GetTrit(unsigned char currentChar, int index) {
  auto maskFirst = (unsigned int) pow(2, 6 - 2 * (index % 4) + 1);
  auto maskSecond = (unsigned int) pow(2, 6 - 2 * (index % 4));
  return ((currentChar & maskFirst) == 0) ? ((currentChar & maskSecond) == 0 ? Unknown : True) : False;
}

//Назначить определенный трит в тритсете
static void SetTrit(unsigned char &currentChar, TritValue value, int index) {
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

TritValue tritset::operator[](int ind) const {
  return GetTrit(set[ind / 4], ind);
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
tritset::reference::reference(tritset *os, std::vector<unsigned char> &s, const int ind, const bool over)
    : newset(s), index(ind), overflow(over), newmem(false), ourset(os) {
}

//Деструктор прокти-класса reference
tritset::reference::~reference() {
  if (newmem) {
    ourset->set.resize(newset.size());
    ourset->numberOfTrits = index + 1;
    ourset->numberOfChars = newset.size();
    SetTrit(ourset->set[index / 4], GetTrit(newset[index / 4], index), index);
  }
  SetTrit(ourset->set[index / 4], GetTrit(newset[index / 4], index), index);
}

//Оператор индексацмм
tritset::reference tritset::operator[](const int ind) {
  if (ind < 0){
    throw std::invalid_argument("Index can not be negative.");
  }
  if (ind > numberOfTrits) {
    int newNumberOfChars = ind / 4 + 1;
    return reference(this, set, ind, newNumberOfChars >= numberOfChars);
  } else {
    return reference(this, set, ind, false);
  }
}

//Присваивание значению
tritset::reference &tritset::reference::operator=(const TritValue value) {
  if ((overflow) && (value != Unknown)) {
    newmem = True;
    int newNumberOfChars = index / 4 + 1;
    newset.resize(newNumberOfChars);
    SetTrit(newset[index / 4], value, index);
  } else if (!overflow) {
    SetTrit(newset[index / 4], value, index);
  }
  return *this;
}

//Присваивание значению из другого тритсета
tritset::reference &tritset::reference::operator=(const tritset::reference &ref) {
  TritValue val = GetTrit(ref.newset[index / 4], ref.index);
  SetTrit(newset[index / 4], val, index);
  return *this;
}

//Приведение типов
tritset::reference::operator TritValue() const {
  return GetTrit(newset[index / 4], index);
}

//Операции между тритсетами
tritset operator|(tritset &left, tritset &right) {
  int max_size = (left.numberOfTrits > right.numberOfTrits ? left.numberOfTrits : right.numberOfTrits);
  tritset A(max_size);
  onetrit val1(Unknown), val2(Unknown);
  for (int i = 0; i < max_size; i++) {
    val1 = left[i];
    val2 = right[i];
    A[i] = val1 | val2;
  }
  return A;
}

tritset operator&(tritset &left, tritset &right) {
  int max_size = (left.numberOfTrits > right.numberOfTrits ? left.numberOfTrits : right.numberOfTrits);
  tritset A(max_size);
  onetrit val1(Unknown), val2(Unknown);
  for (int i = 0; i < max_size; i++) {
    val1 = left[i];
    val2 = right[i];
    A[i] = val1 & val2;
  }
  return A;
}

tritset operator~(tritset &current) {
  int max_size = current.numberOfTrits;
  tritset A(max_size);
  onetrit val1(Unknown);
  for (int i = 0; i < max_size; i++) {
    val1 = current[i];
    A[i] = ~val1;
  }
  return A;
}

//Удобный вывод элемента тритсета
std::ostream &operator<<(std::ostream &out, const tritset::reference &ref) {
  TritValue value = GetTrit(ref.newset[ref.index / 4], ref.index);
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

//Утилиты для тритсета
//Сжимание до последнего значащего трита
void tritset::Shrink() {
  int lastIndex = 0;
  for (int i = 0; i < numberOfTrits; i++) {
    if ((*this)[i] != Unknown) {
      lastIndex = i;
    }
  }
  numberOfChars = lastIndex / 4 + 1;
  numberOfTrits = lastIndex + 1;
  set.resize(numberOfChars);
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
    (*this)[i] = Unknown;
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

std::unordered_map<TritValue, int> tritset::Cardinality() {
  std::unordered_map<TritValue, int> stat{};
  for (int i = 0; i < numberOfTrits; i++) {
    switch ((*this)[i]) {
      case Unknown: {
        stat[Unknown]++;
        break;
      }
      case True: {
        stat[True]++;
        break;
      }
      default: {
        stat[False]++;
        break;
      }
    }
  }
  return stat;
}

int tritset::logicalLength() {
  int lastIndex = 0;
  for (int i = 0; i < numberOfTrits; i++) {
    if ((*this)[i] != Unknown) {
      lastIndex = i;
    }
  }
  return lastIndex + 1;
}
