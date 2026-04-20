// game_id.hpp
#pragma once

#include <string>
#include <vector>
struct GameMetadata {
  int id;           // идентификатор игры (из GameId)
  std::string name; // название игры
  // при необходимости можно добавить другие поля: версия, автор и т.п.
};

enum class GameId : int {
  ROCK_PAPER_SCISSORS = 0,
  GUESS_NUMBER,
  WORDLE,
  MINI_RPG,
  SNAKE,
  TETRIS,
  ARITHMETIC_TEST,
  MAZE,
  TODO_LIST,
  BANK,
  STORY_GEN,
  CROSS_ROAD,
  PING_PONG,
  SEA_BATTLE,
  PACMAN,
  PAINT,
  SELL_BUY
};

inline const GameMetadata &getGameMetadata(GameId id) {
  static const std::vector<GameMetadata> metadata = {
      {static_cast<int>(GameId::ROCK_PAPER_SCISSORS), "Rock Paper Scissors"},
      {static_cast<int>(GameId::GUESS_NUMBER), "Guess Number"}
      // добавьте новые игры сюда же
  };
  return metadata[static_cast<int>(id)];
}

inline const std::vector<GameId> ALL_GAMES = {GameId::ROCK_PAPER_SCISSORS,
                                              GameId::GUESS_NUMBER};