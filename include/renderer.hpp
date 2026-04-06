/**
 * @file renderer.hpp
 * @brief Абстракция для вывода в консоль (рендеринг).
 */

#pragma once
#include <string>

/**
 * @interface IRenderer
 * @brief Интерфейс для всех реализаций рендерера.
 */
class IRenderer {
public:
  virtual ~IRenderer() = default;

  /// Очистить экран (использует системную команду clear/cls).
  virtual void clearScreen() = 0;

  /**
   * @brief Вывести текст в заданной позиции (использует ANSI-escape коды).
   * @param row Строка (1‑индексация).
   * @param col Столбец (1‑индексация).
   * @param text Выводимый текст.
   */
  virtual void printAt(int row, int col, const std::string &text) = 0;

  /// Нарисовать рамку из символов '+' и '-'.
  virtual void drawFrame(int width) = 0;

  /// Вывести текст без перевода строки.
  virtual void print(const std::string &text) = 0;

  /// Вывести текст с переводом строки.
  virtual void println(const std::string &text) = 0;
};

/**
 * @class ConsoleRenderer
 * @brief Реализация IRenderer для обычного терминала (Linux/Windows).
 */
class ConsoleRenderer : public IRenderer {
public:
  void clearScreen() override;
  void printAt(int row, int col, const std::string &text) override;
  void drawFrame(int width) override;
  void print(const std::string &text) override;
  void println(const std::string &text) override;
};