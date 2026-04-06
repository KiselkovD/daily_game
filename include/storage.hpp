/**
 * @file storage.hpp
 * @brief Абстракция для сохранения/загрузки данных (файловая реализация).
 */

#pragma once
#include <string>

/**
 * @interface Storage
 * @brief Интерфейс для постоянного хранения пар "ключ → данные".
 */
class Storage {
public:
  virtual ~Storage() = default;

  /**
   * @brief Сохранить данные по ключу.
   * @param key  Имя файла (или другой идентификатор).
   * @param data Строка с данными.
   * @return true в случае успеха, false при ошибке.
   */
  virtual bool save(const std::string &key, const std::string &data) = 0;

  /**
   * @brief Загрузить данные по ключу.
   * @param key  Имя файла.
   * @param data Выходной параметр – загруженная строка.
   * @return true если файл прочитан, false если файл не существует или ошибка.
   */
  virtual bool load(const std::string &key, std::string &data) = 0;
};

/**
 * @class FileStorage
 * @brief Реализация Storage через файловую систему.
 *
 * Каждый ключ интерпретируется как путь к файлу.
 */
class FileStorage : public Storage {
public:
  bool save(const std::string &key, const std::string &data) override;
  bool load(const std::string &key, std::string &data) override;
};