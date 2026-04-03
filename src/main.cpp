#include "../include/game.hpp"
#include "../src/games/rock_papr_sisr/rock_papr_sisr.hpp"
#include <iostream>
#include <memory>
#include <vector>
int main() {
  std::vector<std::unique_ptr<Game>> games;
  games.push_back(std::make_unique<RockPaperScissors>());
  std::cout << "\n========== DAILY GAME HUB ==========\n";
  std::cout << "Choose game (0–" << games.size() - 1 << "): ";
  for (size_t i = 0; i < games.size(); ++i) {
    std::cout << std::endl << i << " " << games[i]->getName() << std::endl;
  }
  int choice;
  std::cin >> choice;

  if (choice >= 0 && choice < games.size()) {
    games[choice]->init();
    games[choice]->run();
    games[choice]->cleanup();
  } else {
    std::cout << "Invalid choice.\n";
  }
  return 0;
}