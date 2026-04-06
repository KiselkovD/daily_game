/**
 * @file ui_factory.cpp
 * @brief консольная фабрика интерфейсов
 *
 */
#include "ui_factory.hpp"
#include "input_handler.hpp"
#include "renderer.hpp"

std::unique_ptr<IRenderer> ConsoleUIFactory::createRenderer() {
  return std::make_unique<ConsoleRenderer>();
}

std::unique_ptr<IInputHandler> ConsoleUIFactory::createInputHandler() {
  return std::make_unique<ConsoleAsyncInputHandler>();
}