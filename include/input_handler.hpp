/**
 * @file input_handler.hpp
 * @brief Асинхронный ввод с консоли (отдельный поток, очередь строк).
 */

#pragma once
#include <atomic>
#include <condition_variable>
#include <mutex>
#include <queue>
#include <string>
#include <thread>

/**
 * @interface IInputHandler
 * @brief Интерфейс для получения ввода от пользователя.
 */
class IInputHandler {
public:
  virtual ~IInputHandler() = default;

  /// Запустить фоновый поток чтения ввода.
  virtual void start() = 0;

  /// Остановить поток и освободить ресурсы.
  virtual void stop() = 0;

  /**
   * @brief Ожидать следующую строку ввода (блокирующий вызов).
   * @return Введённая строка (без символа новой строки).
   */
  virtual std::string waitForInput() = 0;

  /// @return true, если в очереди есть хотя бы одна непрочитанная строка.
  virtual bool hasInput() const = 0;
};

/**
 * @class ConsoleAsyncInputHandler
 * @brief Реализация через отдельный поток и std::getline.
 */
class ConsoleAsyncInputHandler : public IInputHandler {
public:
  ConsoleAsyncInputHandler();
  ~ConsoleAsyncInputHandler();

  void start() override;
  void stop() override;
  std::string waitForInput() override;
  bool hasInput() const override;

private:
  void inputLoop();

  std::queue<std::string> m_queue;
  mutable std::mutex m_mutex;
  std::condition_variable m_cv;
  std::thread m_thread;
  std::atomic<bool> m_running;
};