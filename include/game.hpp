/**
 * @file game.hpp
 * @brief Абстрактный базовый класс для всех игр.
 */

#pragma once
#include "game_metadata.hpp"
/**
 * @class Game
 * @brief Интерфейс, который должна реализовать каждая игра.
 *
 * Содержит жизненный цикл игры: инициализация, запуск, очистка.
 */

class Game {
public:
  explicit Game(const GameMetadata &meta) : m_metadata(meta) {}
  virtual ~Game() = default;
  virtual void init() = 0;
  virtual void run() = 0;
  virtual void cleanup() = 0;
  const GameMetadata &getMetadata() const { return m_metadata; }
  virtual const char *getName() const { return m_metadata.name.c_str(); }
  virtual int getGameId() const { return m_metadata.id; }

protected:
  GameMetadata m_metadata; // защищённые данные, доступны наследникам
};