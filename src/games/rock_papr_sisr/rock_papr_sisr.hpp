/**
 * @file rock_papr_sisr.hpp
 * @brief Реализация игры "Камень, ножницы, бумага".
 */

#pragma once
#include "game.hpp"
#include "input_handler.hpp"
#include "player.hpp"
#include "renderer.hpp"
#include "scoreboard.hpp"
#include "storage.hpp"
#include <memory>

/**
 * @class RockPaperScissors
 * @brief Игра "Камень, ножницы, бумага".
 *
 * Реализует интерфейс Game. Использует переданные зависимости:
 * IRenderer, IInputHandler, Player, Scoreboard, Storage.
 */
class RockPaperScissors : public Game {
public:
  /**
   * @brief Конструктор.
   * @param renderer     Рендерер для вывода в консоль.
   * @param inputHandler Обработчик ввода.
   * @param player       Игрок (глобальный счёт).
   * @param scoreboard   Таблица результатов (сохраняет статистику этой игры).
   * @param storage      Хранилище (не используется в данной игре, но передаётся
   * для единообразия).
   */
  RockPaperScissors(std::unique_ptr<IRenderer> renderer,
                    std::unique_ptr<IInputHandler> inputHandler, Player &player,
                    Scoreboard &scoreboard, Storage &storage);

  void init() override;
  void run() override;
  void cleanup() override;
  const char *getName() const override;

private:
  enum class Move { ROCK, PAPER, SCISSORS };
  enum class Result { WIN, LOSE, TIE };

  Move getPlayerMove();
  Move getComputerMove();
  Result judge(Move player, Move computer);
  void updateStatistics(Result res);
  void showFinalStats();

  std::unique_ptr<IRenderer> m_renderer;
  std::unique_ptr<IInputHandler> m_inputHandler;
  Player &m_player;
  Scoreboard &m_scoreboard;
  Storage &m_storage;
  const int m_gameId = 0;
  int m_roundsPlayed = 0;
  int m_wins = 0, m_losses = 0, m_ties = 0;
  bool m_quitRequested = false;
};