#include "game.h"
#include <ctime>


int main() {
  srand((unsigned int) time(nullptr));
  for (size_t i = 0; i < 5; i++) {
    rand();
  }
  BEGIN:
  system("cls");
  game::drawLogo();
  std::cout << "Please, choose game mode:" << std::endl
            << "1) Player vs Player" << std::endl
            << "2) Player vs PrimitiveAI" << std::endl
            << "3) Player vs AdvancedAI" << std::endl;
  char choice = 0;
  IPlayer *player = nullptr;
  while (true) {
    std::cin >> choice;
    if (choice >= '1' && choice <= '3') {
      break;
    }
    std::cout << "Wrong game mode. Try again." << std::endl;
  }
  switch (choice) {
    case '1': {
      player = new HumanPlayer;
      break;
    }
    case '2': {
      player = new PrimitiveAI;
      break;
    }
    default: {
//      player = new AdvancedAI;
      break;
    }
  }
  system("cls");
  game::start(player);
  std::cout << "Do you want to play again? y/n" << std::endl;
  std::string ans;
  std::cin >> ans;
  if (ans == "y") {
    goto BEGIN;
  }
  delete (player);
  return 0;
}