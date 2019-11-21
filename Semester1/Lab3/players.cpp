//
// Created by Gomer on 06.11.2019.
//

#include "players.h"

std::string IPlayer::getName() const {
  return name;
}

std::string IPlayer::getNumber() const {
  return number;
}

void HumanPlayer::playerGenerator() {
  system("cls");
  std::cout << "Choose your name." << std::endl;
  std::cin >> name;
  while (true) {
    bool flag = true;
    system("cls");
    std::cout << name << ", please, make a 4-digit number." << std::endl;
    std::cin >> number;
    if (number.length() == 4) {
      for (const auto letter : number){
        if (!isdigit(letter)){
          flag = false;
          break;
        }
      }
      if (flag) {
        return;
      }
    }
  }
}

std::string HumanPlayer::generateNumber() {
  std::string attempt;
  while (true) {
    bool flag = true;
    system("cls");
    std::cout << getName() << ", try to guess a number. Type 'show' to show your steps" << std::endl;
    std::cin >> attempt;
    if (attempt == "show"){
      system("cls");
      for (const auto &step : steps){
        std::cout << step.first << " " << step.second.first << " " << step.second.second << std::endl;
      }
      system("pause");
    }
    else if (attempt.length() == 4) {
      for (const auto letter : attempt){
        if (!isdigit(letter)){
          flag = false;
          break;
        }
      }
      if (flag) {
        return attempt;
      }
    }
  }
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
  steps[atp].first = bull;
  steps[atp].second = cow;
  system("pause");
  system("cls");
  return false;
}

void AdvancedAI::playerGenerator() {
  name = "AdvancedAI";
  number = std::to_string(1000 + (rand() % 9000));
}


std::string AdvancedAI::generateNumber() {
  std::string buffer;
  if (state < 10){
    buffer.clear();
    for (size_t i = 0; i < 4; i++){
      buffer += std::to_string(state);
    }
    state++;
  }
  else {
    if (state == 10) {
      state++;
      return bulls;
    }
    for (int i = 2; i >= 0; i--){
      if (bulls[i] < bulls[i + 1]){
        for (int j = 3; j > i; j--){
          if (bulls[i] < bulls[j]){
            std::swap(bulls[j], bulls[i]);
            std::sort(bulls.begin() + (i + 1), bulls.end());
            return bulls;
          }
        }
      }
    }
  }
  return buffer;
}

bool AdvancedAI::check(const std::string &atp, const std::string &opNumber) {
  if (state < 10){
    for (size_t i = 0; i < 4; i++){
      if (opNumber[i] == (state - 1) + 48){
        bulls += std::to_string(state - 1);
        if (bulls.length() == 4){
          state = 10;
        }
      }
    }
  }
  return !(atp != opNumber);
}

void PrimitiveAI::playerGenerator() {
  name = "PrimitiveAI";
  number = std::to_string(1000 + (rand() % 9000));
}

std::string PrimitiveAI::generateNumber() {
  std::string buffer;
  if (state < 10){
    for (size_t i = 0; i < 4; i++){
      buffer += std::to_string(state);
    }
    state++;
  } else {
    for (size_t i = 4; i > 0; i--){
      size_t pos = rand() % i;
      buffer += bulls[pos];
      std::swap(bulls[pos], bulls[i - 1]);
    }
  }
  return buffer;
}

bool PrimitiveAI::check(const std::string &atp, const std::string &opNumber) {
  if (state < 10){
    for (size_t i = 0; i < 4; i++){
      if (opNumber[i] == (state - 1) + 48){
        bulls += std::to_string(state - 1);
      }
    }
  }
  return !(atp != opNumber);
}