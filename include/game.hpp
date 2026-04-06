/**
 * @file game.hpp
 * @brief Абстрактный базовый класс для всех игр.
 */

#pragma once

/**
 * @class Game
 * @brief Интерфейс, который должна реализовать каждая игра.
 *
 * Содержит жизненный цикл игры: инициализация, запуск, очистка.
 */

class Game {
public:
  virtual ~Game() = default;
  virtual void init() = 0;
  virtual void run() = 0;
  virtual void cleanup() = 0;
  virtual const char *getName() const = 0;
};