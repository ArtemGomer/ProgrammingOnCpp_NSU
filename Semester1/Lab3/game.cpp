//
// Created by Gomer on 08.12.2019.
//

#include "game.h"
#include <iostream>
#include <ctime>
game::game() {
  printLogo();
  makeChoice();
}

game::~game() {
  delete(p1);
  delete(p2);
}

void game::makeChoice() {
  std::string choice;
  while (true) {
    game::printMods();
    std::cin >> choice;
    if (choice == "rules") {
      system("cls");
      game::printRules();
      system("pause");
      system("cls");
    } else if (choice == "exit") {
      p1 = nullptr;
      p2 = nullptr;
      return;
    } else if (choice != "1" && choice != "2" && choice != "3" && choice != "4") {
      std::cout << "Wrong game mode. Try again." << std::endl;
    } else {
      break;
    }
  }
  switch (choice[0]) {
    case '1': {
      p1 = new HumanPlayer;
      p2 = new HumanPlayer;
      break;
    }
    case '2': {
      p1 = new HumanPlayer;
      p2 = new PrimitiveAI;
      break;
    }
    case '3': {
      p1 = new HumanPlayer;
      p2 = new AdvancedAI;
      break;
    }
    default: {
      p1 = new PrimitiveAI;
      p2 = new AdvancedAI;
      break;
    }
  }
}

void game::printRules() {
  std::cout << "You and your opponent makes a number." << std::endl
            << "Your goal is to guess opponent`s number." << std::endl
            << "If one of your digits is in opponent`s number on the same place - you have a bull" << std::endl
            << "If one of your digits is in opponent`s number on another place - you have a cow" << std::endl;
}
void game::printMods() {
  std::cout << "Please, choose game mode:" << std::endl
            << "1) Player vs Player" << std::endl
            << "2) Player vs PrimitiveAI" << std::endl
            << "3) Player vs AdvancedAI" << std::endl
            << "4) PrimitiveAI vs AdvancedAI" << std::endl
            << "Type 'rules' to see rules" << std::endl
            << "Type 'exit' to exit the game" << std::endl;
}
void game::printLogo() {
  std::string field;
  field += (unsigned char) 201;
  for (size_t i = 1; i < 15; i++) {
    field += (unsigned char) 205;
  }
  field += (unsigned char) 187;
  std::cout << field << std::endl;
  field[0] = (unsigned char) 200;
  field[15] = (unsigned char) 188;
  std::cout << (unsigned char) 186 << "Bulls and cows" << (unsigned char) 186 << std::endl
            << field << std::endl;
}

bool game::gameStart() {
  if (p1 == nullptr && p2 == nullptr){
    return false;
  }
  srand((unsigned int) time(nullptr));
  for (size_t i = 0; i < 5; i++) {
    rand();
  }
  while (true) {
    system("cls");
    p1->playerGenerator();
    p2->playerGenerator();
    system("cls");
    Players state = Players::player1;
    while (true) { // Главный цикл игры
      if (state == Players::player1) {
        std::string attempt = p1->generateNumber();
        if (attempt == "exit") {
          system("cls");
          return false;
        }
        system("cls");
        if (p1->check(attempt, p2->getNumber())) {
          game::printLogo();
          std::cout << p1->getName() << " wins." << std::endl;
          break;
        }
        state = Players::player2;
      } else {
        std::string attempt = p2->generateNumber();
        if (attempt == "exit") {
          system("cls");
          return false;
        }
        system("cls");
        if (p2->check(attempt, p1->getNumber())) {
          game::printLogo();
          std::cout << p2->getName() << " wins." << std::endl;
          break;
        }
        state = Players::player1;
      }
    }
    std::cout << "Do you want to play again? y/n" << std::endl;
    std::string ans;
    while (true) {
      std::cin >> ans;
      if (ans == "y" || ans == "n") {
        break;
      } else {
        std::cout << "Just choose y/n. What is your problem?" << std::endl;
      }
    }
    return ans != "n";
  }
}