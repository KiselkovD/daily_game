/**
 * @file input_handler.cpp
 * @brief Реализация асинхронного обработчика ввода из консоли.
 */
#include "input_handler.hpp"
#include <iostream>

ConsoleAsyncInputHandler::ConsoleAsyncInputHandler() : m_running(false) {}

ConsoleAsyncInputHandler::~ConsoleAsyncInputHandler() { stop(); }

void ConsoleAsyncInputHandler::start() {
  if (m_running)
    return;
  m_running = true;
  m_thread = std::thread(&ConsoleAsyncInputHandler::inputLoop, this);
}

void ConsoleAsyncInputHandler::stop() {
  if (!m_running)
    return;
  m_running = false;
  m_cv.notify_all();
  if (m_thread.joinable())
    m_thread.join();
}

void ConsoleAsyncInputHandler::inputLoop() {
  std::string line;
  while (m_running) {
    if (std::getline(std::cin, line)) {
      std::lock_guard<std::mutex> lock(m_mutex);
      m_queue.push(line);
      m_cv.notify_one();
    }
  }
}

std::string ConsoleAsyncInputHandler::waitForInput() {
  std::unique_lock<std::mutex> lock(m_mutex);
  m_cv.wait(lock, [this] { return !m_queue.empty() || !m_running; });
  if (!m_running && m_queue.empty())
    return "";
  std::string val = m_queue.front();
  m_queue.pop();
  return val;
}

bool ConsoleAsyncInputHandler::hasInput() const {
  std::lock_guard<std::mutex> lock(m_mutex);
  return !m_queue.empty();
}