//
// Created by Gomer on 06.11.2019.
//

#include "game.h"
bool game::start(IPlayer *player2) {
  srand((unsigned int) time(nullptr));
  for (size_t i = 0; i < 5; i++) {
    rand();
  }
  while (true) {
    system("cls");
    HumanPlayer player1;
    player1.playerGenerator();
    player2->playerGenerator();
    system("cls");
    Players state = Players::Player1;
    while (true) { // Главный цикл игры
      if (state == Players::Player1) {
        std::string attempt = player1.generateNumber();
        if (attempt == "exit") {
          system("cls");
          return false;
        }
        system("cls");
        if (player1.check(attempt, player2->getNumber())) {
          game::printLogo();
          std::cout << player1.getName() << " wins." << std::endl;
          break;
        }
        state = Players::Player2;
      } else {
        std::string attempt = player2->generateNumber();
        if (attempt == "exit") {
          system("cls");
          return false;
        }
        system("cls");
        if (player2->check(attempt, player1.getNumber())) {
          game::printLogo();
          std::cout << player2->getName() << " wins." << std::endl;
          break;
        }
        state = Players::Player1;
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

void game::printMods() {
  std::cout << "Please, choose game mode:" << std::endl
            << "1) Player vs Player" << std::endl
            << "2) Player vs PrimitiveAI" << std::endl
            << "3) Player vs AdvancedAI" << std::endl
            << "Type 'rules' to see rules" << std::endl
            << "Type 'exit' to exit the game" << std::endl;
}

void game::printRules() {
  std::cout << "You and your opponent makes a number." << std::endl
            << "Your goal is to guess opponent`s number." << std::endl
            << "If one of your digits is in opponent`s number on the same place - you have a bull" << std::endl
            << "If one of your digits is in opponent`s number on another place - you have a cow" << std::endl;
}

IPlayer *game::makeChoice() {
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
      return nullptr;
    } else if (choice != "1" && choice != "2" && choice != "3") {
      std::cout << "Wrong game mode. Try again." << std::endl;
    } else {
      break;
    }
  }
  switch (choice[0]) {
    case '1': {
      return new HumanPlayer;
    }
    case '2': {
      return new PrimitiveAI;
    }
    default: {
      return new AdvancedAI;
    }
  }
}
