#include "game.h"

int main() {
//  system("color 17");
  std::cout << "Please, choose game mode:" << std::endl
            << "1) PvP" << std::endl
            << "2) PvPrimitiveAI" << std::endl
            << "3) PvAdvancedAI" << std::endl;
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
  delete(player);
  return 0;
}