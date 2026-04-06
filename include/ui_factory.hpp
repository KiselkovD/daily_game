/**
 * @file ui_factory.hpp
 * @brief Абстрактная фабрика для создания объектов ввода/вывода.
 */

#pragma once
#include "input_handler.hpp"
#include "renderer.hpp"
#include <memory>

/**
 * @class UIFactory
 * @brief Интерфейс фабрики, создающей пару "рендерер + обработчик ввода".
 */
class UIFactory {
public:
  virtual ~UIFactory() = default;

  /// @return Указатель на новый объект IRenderer.
  virtual std::unique_ptr<IRenderer> createRenderer() = 0;

  /// @return Указатель на новый объект IInputHandler.
  virtual std::unique_ptr<IInputHandler> createInputHandler() = 0;
};

/**
 * @class ConsoleUIFactory
 * @brief Фабрика для консольной версии (ConsoleRenderer +
 * ConsoleAsyncInputHandler).
 */
class ConsoleUIFactory : public UIFactory {
public:
  std::unique_ptr<IRenderer> createRenderer() override;
  std::unique_ptr<IInputHandler> createInputHandler() override;
};