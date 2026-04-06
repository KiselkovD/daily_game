/**
 * @file scoreboard.hpp
 * @brief Хранение статистики игр (победы, поражения, ничьи).
 */

#pragma once
#include <string>
#include <unordered_map>

/**
 * @struct GameStats
 * @brief Статистика по одной игре.
 */
struct GameStats {
  int wins = 0;   ///< Количество побед.
  int losses = 0; ///< Количество поражений.
  int ties = 0;   ///< Количество ничьих.
};

/**
 * @class Scoreboard
 * @brief Таблица результатов для нескольких игр (идентифицируются по gameId).
 */
class Scoreboard {
public:
  /**
   * @brief Записать результат одной игры.
   * @param gameId Идентификатор игры.
   * @param win    true – победа, false – поражение (если tie == false).
   * @param tie    true – ничья (приоритет выше, чем win).
   */
  void recordResult(int gameId, bool win, bool tie);

  /// @return Статистика для указанной игры.
  GameStats getStats(int gameId) const;

  /// @return Строковое представление статистики (например, "Wins: 2 Losses: 1
  /// Ties: 0").
  std::string getStatsString(int gameId) const;

  /// Прямая установка статистики (используется при загрузке из файла).
  void setStats(int gameId, const GameStats &stats);

  /// Очистить всю статистику.
  void clear();

private:
  std::unordered_map<int, GameStats>
      m_stats; ///< Хранилище: gameId → статистика.
};