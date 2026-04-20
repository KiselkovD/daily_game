/**
 * @file guess_number.hpp
 * @brief
 *
 */

#pragma once
#include "game.hpp"
#include "game_metadata.hpp"
#include "input_handler.hpp"
#include "player.hpp"
#include "renderer.hpp"
#include "scoreboard.hpp"
#include "storage.hpp"
#include <memory>

/**
 * @class GuessNumber
 * @brief
 *
 */
class GuessNumber : public Game {
public:
  GuessNumber(const GameMetadata &meta, std::unique_ptr<IRenderer> renderer,
              std::unique_ptr<IInputHandler> inputHandler, Player &player,
              Scoreboard &scoreboard, Storage &storage);

  void init() override;
  void run() override;
  void cleanup() override;

private:
  enum class Result { MORE, SAME, LESS };
  int getPlayerGuess();
  Result checkGuess(int);
  void updateStatistics(Result res);
  void showFinalStats();
  void generateNumber();
  std::unique_ptr<IRenderer> m_renderer;
  std::unique_ptr<IInputHandler> m_inputHandler;
  Player &m_player;
  Scoreboard &m_scoreboard;
  Storage &m_storage;
  int m_number = 0;
  int m_attempts = 0;
  int m_wins = 0;
  bool m_quitRequested = false;
};
