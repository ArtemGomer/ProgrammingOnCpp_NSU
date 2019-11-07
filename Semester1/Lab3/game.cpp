//
// Created by Gomer on 06.11.2019.
//

#include "game.h"
void game::start(IPlayer *player2) {
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
        game::drawLogo();
        std::cout << player1.getName() << " wins." << std::endl;
        break;
      }
      state = Players::Player2;
    } else {
      std::string attempt = player2->generateNumber();
      system("cls");
      if (player2->check(attempt, player1.getNumber())) {
        game::drawLogo();
        std::cout << player2->getName() << " wins." << std::endl;
        break;
      }
      state = Players::Player1;
    }
  }
}

void game::drawLogo() {
  std::string field;
  field += (char) 201u;
  for (size_t i = 1; i < 15; i++) {
    field += (char) 205u;
  }
  field += (char) 187u;
  std::cout << field << std::endl;
  field[0] = (char) 200u;
  field[15] = (char) 188u;
  std::cout << (char) 186u << "Bulls and cows" << (char) 186u << std::endl
            << field << std::endl;
}