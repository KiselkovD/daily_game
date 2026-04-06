/**
 * @file player.hpp
 * @brief Класс игрока (имя и глобальный счёт).
 */

#pragma once
#include <string>

/**
 * @class Player
 * @brief Хранит имя пользователя и его общий счёт (суммируется по всем играм).
 */
class Player {
public:
  /**
   * @brief Конструктор.
   * @param name Имя игрока (по умолчанию "Player").
   */
  explicit Player(const std::string &name = "Player");

  /// @return Имя игрока.
  std::string getName() const;

  /// @return Общий счёт.
  int getGeneralScore() const;

  /**
   * @brief Добавить очки к общему счёту.
   * @param points Количество очков (может быть отрицательным).
   */
  void addToGeneralScore(int points);

  /// Установить общий счёт напрямую (используется при загрузке из файла).
  void setGeneralScore(int score);

  /// Установить новое имя.
  void setName(const std::string &name);

private:
  std::string m_name;
  int m_generalScore;
};