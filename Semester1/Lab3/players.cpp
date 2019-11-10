//
// Created by Gomer on 06.11.2019.
//

#include "players.h"
void HumanPlayer::playerGenerator() {
  system("cls");
  std::cout << "Choose your name." << std::endl;
  std::cin >> name;
  std::cout << getName() << ", make your 4-digit number." << std::endl;
  while (true) {
    std::cin >> number;
    if (number.length() == 4) {
      break;
    }
    std::cout << "Please, make a 4-digit number." << std::endl;
  }
}

std::string HumanPlayer::generateNumber() {
  std::cout << getName() << ", try to guess a number." << std::endl;
  std::string attempt;
  while (true) {
    std::cin >> attempt;
    if (attempt.length() == 4) {
      break;
    }
    std::cout << "Please, make a 4-digit number." << std::endl;
  }
  return attempt;
}

bool HumanPlayer::check(const std::string &atp, const std::string &opNumber) {
  int bull = 0, cow = 0;
  bool exceptions[4];
  for (bool &exception : exceptions) {
    exception = false;
  }
  for (size_t i = 0; i < 4; i++){
    if (atp[i] == opNumber[i]){
      bull++;
      exceptions[i] = true;
    }
  }
  for (size_t i = 0; i < 4; i++)
    for (size_t j = 0; j < 4; j++) {
      if (atp[i] == opNumber[j]) {
        if (!exceptions[j]){
          cow++;
          exceptions[j] = true;
        }
      }
    }
  if (bull == 4) {
    return true;
  }
  std::cout << "Bulls = " << bull << std::endl;
  std::cout << "Cows = " << cow << std::endl;
  system("pause");
  system("cls");
  return false;
}

void PrimitiveAI::playerGenerator() {
  name = "PrimitiveAI";
  number = std::to_string(1000 + (rand() % 9000));
}

PrimitiveAI::PrimitiveAI() : state(0){
  for (int &bull : bulls){
    bull = 0;
  }
}

std::string PrimitiveAI::generateNumber() {
  std::string buffer;
  static int accNumbers[4] = {0, 0, 0, 0};
  if (state < 10){
    for (size_t i = 0; i < 4; i++){
      buffer += std::to_string(state);
    }
    state++;
  }
  else {
    if (state == 10) {
      size_t digit = 0;
      for (size_t i = 0; i < 10; i++) {
        while (bulls[i] != 0) {
          accNumbers[digit] = i;
          bulls[i]--;
          digit++;
        }
      }
      state++;
    }
    for (size_t i = 4; i > 0; i--){
      size_t pos = rand() % i;
      buffer += std::to_string(accNumbers[pos]);
      std::swap(accNumbers[pos], accNumbers[i - 1]);
    }
  }
  return buffer;
}

bool PrimitiveAI::check(const std::string &atp, const std::string &opNumber) {
  static int bullsCounter = 0;
  if (state < 10){
    for (size_t i = 0; i < 4; i++){
      if (opNumber[i] == (state - 1) + 48){
        bulls[state - 1]++;
        bullsCounter++;
        if (bullsCounter == 4){
          state = 10;
        }
      }
    }
  }
  return !(atp != opNumber);
}

std::string IPlayer::getName() const {
  return name;
}

std::string IPlayer::getNumber() const {
  return number;
}

//
//void AdvancedAI::playerGenerator() {
//  name = "Bot";
//  number = std::to_string(1000 + rand() % 9000);
//}