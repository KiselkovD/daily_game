// src/games/rock_papr_sisr/rock_papr_sisr.cpp
#include "rock_papr_sisr.hpp"
#include <cstdlib>
#include <ctime>
#include <iostream>
RockPaperScissors::RockPaperScissors() : Game() {}

void RockPaperScissors::init() {
  std::srand((unsigned)std::time(nullptr));
  std::cout << "Rock Paper Scissors game initialized." << std::endl;
}

const char *RockPaperScissors::getName() const { return "Rock Paper Scissors"; }

void RockPaperScissors::run() {
  std::cout << "\nPlaying Rock Paper Scissors!" << std::endl;
  int choice;
  while (true) {
    std::cout << "\nYour turn: ";
    Move player = getPlayerMove();
    Move computer = getComputerMove();
    Result res = judge(player, computer);
    std::cout << "Computer turn: "
              << (computer == Move::ROCK    ? "Rock"
                  : computer == Move::PAPER ? "Paper"
                                            : "Scissors")
              << "\n";

    switch (res) {
    case Result::WIN:
      std::cout << "you win" << std::endl;
      break;
    case Result::LOSE:
      std::cout << "you lose" << std::endl;
      break;
    default:
      std::cout << "its tie" << std::endl;
    }

    std::cout << "End the game? (0 - no, 1 - true)" << std::endl;
    std::cin >> choice;
    if (choice)
      break;
  }
}

void RockPaperScissors::cleanup() {
  std::cout << "Rock Paper Scissors exited.\n";
}

Move RockPaperScissors::getPlayerMove() {
  int choice;
  while (true) {
    std::cout << "Enter 1 (Rock), 2 (Paper), 3 (Scissors): ";
    std::cin >> choice;
    if (choice == 1)
      return Move::ROCK;
    if (choice == 2)
      return Move::PAPER;
    if (choice == 3)
      return Move::SCISSORS;
  }
}

Move RockPaperScissors::getComputerMove() {
  int r = std::rand() % 3;
  if (r == 0)
    return Move::ROCK;
  if (r == 1)
    return Move::PAPER;
  return Move::SCISSORS;
}

Result RockPaperScissors::judge(Move player, Move computer) {
  if (player == computer)
    return Result::TIE;
  if ((((int)player + 1) == 4 ? 0 : ((int)player + 1)) == (int)computer)
    return Result::LOSE;
  return Result::WIN;
}