//
// Created by Gomer on 24.09.2019.
//

#include "tritset.h"
//Получить значение трита
static trit GetTrit(unsigned char currentChar, const size_t index, const int numberOfTrits) {
  if (index > numberOfTrits) {
    return trit::Unknown;
  }
  unsigned int maskFirst = 1u << (7 - 2 * (index % 4));
  unsigned int maskSecond = 1u << (6 - 2 * (index % 4));
  return ((currentChar & maskFirst) == 0) ? ((currentChar & maskSecond) == 0 ? trit::Unknown : trit::True)
                                          : trit::False;
}

//Назначить определенный трит в тритсете
static void SetTrit(unsigned char &currentChar, const trit value, const size_t index) {
  unsigned int maskFirst = 1u << (7 - 2 * (index % 4));
  unsigned int maskSecond = 1u << (6 - 2 * (index % 4));
  if (value == trit::Unknown) {
    currentChar &= ~(maskFirst | maskSecond);
  } else if (value == trit::True) {
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

tritset::tritset(const std::initializer_list<trit> &list) : tritset(list.size()) {
  size_t i = 0;
  for (const auto &el : list){
    (*this)[i] = el;
    i++;
  }
}

//Конструктор копирования
tritset::tritset(const tritset &oldTritset) {
  numberOfChars = oldTritset.numberOfChars;
  numberOfTrits = oldTritset.numberOfTrits;
  set = oldTritset.set;
}

//Конструктор прокти-класса reference
tritset::reference::reference(tritset *os, const size_t ind)
    : index(ind), tSet(os) {
}

//Оператор индексацмм
tritset::reference tritset::operator[](const int ind) {
  if (ind < 0) {
    throw std::invalid_argument("Index can not be negative.");
  }
  return reference(this, ind);
}

//Присваивание значению
tritset::reference &tritset::reference::operator=(const trit value) {
  if ((index > tSet->numberOfTrits) && (value != trit::Unknown)) {
    tSet->numberOfChars = index / 4 + 1;
    tSet->set.resize(tSet->numberOfChars);
    tSet->numberOfTrits = index + 1;
  }
  SetTrit(tSet->set[index / 4], value, index);
  return *this;
}

//Присваивание значению из другого тритсета
tritset::reference &tritset::reference::operator=(const tritset::reference &ref) {
  *this = (trit) ref;
  return *this;
}

//Приведение типов
tritset::reference::operator trit() const {
  return GetTrit(tSet->set[index / 4], index, tSet->numberOfTrits);
}

trit tritset::operator[](int ind) const {
  if (ind < 0) {
    throw std::invalid_argument("Index can not be negative.");
  }
  return GetTrit(this->set[ind / 4], ind, this->numberOfTrits);
}

//Операции между тритсетами
tritset operator|(const tritset &left, const tritset &right) {
  size_t maxSize = std::max(left.capacity(), right.capacity());
  tritset A(maxSize);
  for (size_t i = 0; i < maxSize; i++) {
    A[i] = left[i] | right[i];
  }
  return A;
}

tritset operator&(const tritset &left, const tritset &right) {
  size_t maxSize = std::max(left.capacity(), right.capacity());
  tritset A(maxSize);
  for (size_t i = 0; i < maxSize; i++) {
    A[i] = left[i] & right[i];
  }
  return A;
}

tritset operator!(const tritset &current) {
  size_t max_size = current.capacity();
  tritset A(max_size);
  for (size_t i = 0; i < max_size; i++) {
    A[i] = !current[i];
  }
  return A;
}

tritset &tritset::operator=(const tritset &right) {
  size_t newSize = right.capacity();
  numberOfTrits = newSize;
  numberOfChars = right.size();
  this->set.resize(newSize);
  for (size_t i = 0; i < newSize; i++) {
    (*this)[i] = right[i];
  }
  return *this;
}

tritset &tritset::operator|=(const tritset &right) {
  *this = *this | right;
  return *this;
}

tritset &tritset::operator&=(const tritset &right) {
  *this = *this & right;
  return *this;
}

tritset &tritset::operator!=(const tritset &right) {
  *this = !right;
  return *this;
}

bool operator==(const tritset &left, const tritset &right) {
  if (left.capacity() != right.capacity()) {
    return false;
  }
  size_t capacity = left.capacity();
  for (size_t i = 0; i < capacity; i++) {
    if (left[i] != right[i]) {
      return false;
    }
  }
  return true;
}

//Утилиты для тритсета
//Сжимание до последнего значащего трита
void tritset::shrink() {
  size_t length = logicalLength();
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
size_t tritset::capacity() const {
  return numberOfTrits;
}

//Количество char-ов для хранения тритов
size_t tritset::size() const {
  return set.size();
}

//забыть все с lastIndex-того элемента
void tritset::trim(const int lastIndex) {
  if (lastIndex < 0) {
    throw std::invalid_argument("Last index must be >= 0");
  }
  for (size_t i = lastIndex; i < numberOfTrits + 1; i++) {
    (*this)[i] = trit::Unknown;
  }
}

//Подсчет вхождений значения в тритсет
size_t tritset::cardinality(const trit val) {
  size_t stat = 0;
  for (size_t i = 0; i < numberOfTrits; i++) {
    if ((*this)[i] == val) {
      stat++;
    }
  }
  return stat;
}

std::map<trit, size_t> tritset::cardinality() {
  std::map<trit, size_t> stat;
  for (size_t i = 0; i < numberOfTrits; i++) {
    switch ((*this)[i]) {
      case trit::Unknown: {
        stat[trit::Unknown]++;
        break;
      }
      case trit::True: {
        stat[trit::True]++;
        break;
      }
      default: {
        stat[trit::False]++;
        break;
      }
    }
  }
  return stat;
}

size_t tritset::logicalLength() {
  size_t lastIndex = 0;
  for (size_t i = 0; i < numberOfTrits; i++) {
    if ((*this)[i] != trit::Unknown) {
      lastIndex = i;
    }
  }
  if (lastIndex == 0) {
    return 0;
  } else {
    return lastIndex + 1;
  }
}
