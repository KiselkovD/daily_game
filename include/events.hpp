/**
 * @file events.hpp
 * @brief Вспомогательные структуры для обработки событий ввода (в текущей
 * версии не используются).
 */

#pragma once
#include <string>

/**
 * @enum InputKey
 * @brief Возможные клавиши ввода (зарезервировано для будущего расширения).
 */
enum class InputKey {
  NONE,
  QUIT,
  UP,
  DOWN,
  LEFT,
  RIGHT,
  ENTER,
  ESCAPE,
  ACTION
};

/**
 * @struct InputEvent
 * @brief Событие ввода (клавиша + текст).
 */
struct InputEvent {
  InputKey key = InputKey::NONE; ///< Виртуальный код клавиши.
  std::string text; ///< Введённая строка (например, для текстовых полей).
};