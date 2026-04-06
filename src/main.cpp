/**
 * @file main.cpp
 * @brief Точка входа в программу.
 *
 * Загружает данные игрока и таблицу результатов, запускает игру "Камень,
 * ножницы, бумага", сохраняет изменения после завершения.
 */

#include "games/rock_papr_sisr/rock_papr_sisr.hpp"
#include "player.hpp"
#include "scoreboard.hpp"
#include "storage.hpp"
#include "ui_factory.hpp"
#include <iostream>
#include <memory>
#include <sstream>

/**
 * @brief Загрузить таблицу результатов из файла.
 * @param scoreboard Объект Scoreboard, который будет заполнен.
 * @param storage    Хранилище (файловая система).
 */
void loadScoreboard(Scoreboard &scoreboard, Storage &storage) {
  std::string data;
  if (storage.load("data/scoreboard.dat", data)) {
    std::istringstream iss(data);
    int gameId, wins, losses, ties;
    while (iss >> gameId >> wins >> losses >> ties) {
      scoreboard.setStats(gameId, {wins, losses, ties});
    }
  }
}

/**
 * @brief Сохранить таблицу результатов (только для игры с id=0).
 * @param scoreboard Объект Scoreboard.
 * @param storage    Хранилище.
 */
void saveScoreboard(const Scoreboard &scoreboard, Storage &storage) {
  auto stats = scoreboard.getStats(0);
  std::ostringstream oss;
  oss << "0 " << stats.wins << " " << stats.losses << " " << stats.ties << "\n";
  storage.save("data/scoreboard.dat", oss.str());
}

/**
 * @brief Главная функция.
 * @return 0 при успешном завершении.
 */
int main() {
  ConsoleUIFactory factory;
  auto renderer = factory.createRenderer();
  auto inputHandler = factory.createInputHandler();

  FileStorage storage;
  Player player;
  Scoreboard scoreboard;

  // Загрузка данных игрока
  std::string playerData;
  if (storage.load("data/player.dat", playerData)) {
    size_t pos = playerData.find('\n');
    if (pos != std::string::npos) {
      player.setName(playerData.substr(0, pos));
      player.setGeneralScore(std::stoi(playerData.substr(pos + 1)));
    }
  } else {
    player.setName("Guest");
    player.setGeneralScore(0);
  }

  loadScoreboard(scoreboard, storage);

  inputHandler->start();

  RockPaperScissors game(std::move(renderer), std::move(inputHandler), player,
                         scoreboard, storage);
  try {
    game.init();
    game.run();
    game.cleanup();
  } catch (const std::exception &e) {
    std::cerr << "Game error: " << e.what() << std::endl;
  }

  // Сохранение данных
  std::stringstream ss;
  ss << player.getName() << "\n" << player.getGeneralScore();
  storage.save("data/player.dat", ss.str());
  saveScoreboard(scoreboard, storage);

  return 0;
}