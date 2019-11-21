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
    while (true) {
      if (state == Players::Player1) {
        std::string attempt = player1.generateNumber();
        system("cls");
        if (player1.check(attempt, player2->getNumber())) {
          game::printLogo();
          std::cout << player1.getName() << " wins." << std::endl;
          break;
        }
        state = Players::Player2;
      } else {
        std::string attempt = player2->generateNumber();
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
    char ans;
    std::cin >> ans;
    return tolower(ans) != 'n';
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
            << "3) Player vs AdvancedAI" << std::endl;
}

IPlayer* game::makeChoice() {
  char choice = 0;
  while (true) {
    std::cin >> choice;
    if (choice >= '1' && choice <= '3') {
      break;
    }
    std::cout << "Wrong game mode. Try again." << std::endl;
  }
  switch (choice) {
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