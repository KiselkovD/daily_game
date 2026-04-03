#pragma once
#include "../../../include/game.hpp"

enum class Move { ROCK = 0, PAPER, SCISSORS };
enum class Result { WIN, LOSE, TIE };

class RockPaperScissors : public Game {
public:
  RockPaperScissors();
  void init() override;
  void run() override;
  void cleanup() override;
  const char *getName() const override;

private:
  void playRound();
  Move getPlayerMove();
  Move getComputerMove();
  Result judge(Move player, Move computer);
};