/**
 * @file main.cpp
 * @brief Точка входа в программу.
 *
 * Загружает данные игрока и таблицу результатов, запускает игру "Камень,
 * ножницы, бумага", сохраняет изменения после завершения.
 */

#include "game_metadata.hpp"
#include "games/guess_number/guess_number.hpp"
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
 * @brief Сохранить ВСЮ таблицу результатов в файл.
 * @param scoreboard Объект Scoreboard.
 * @param storage    Хранилище.
 *
 * Изменение: теперь сохраняются все игры из списка ALL_GAMES,
 * а не только одна. Это предотвращает затирание статистики других игр.
 */
void saveAllScoreboards(const Scoreboard &scoreboard, Storage &storage) {
  std::ostringstream oss;
  for (GameId id : ALL_GAMES) {
    int gid = static_cast<int>(id);
    auto stats = scoreboard.getStats(gid);
    // Сохраняем только если были результаты (иначе не пишем нули)
    if (stats.wins == 0 && stats.losses == 0 && stats.ties == 0)
      continue;
    oss << gid << " " << stats.wins << " " << stats.losses << " " << stats.ties
        << "\n";
  }
  storage.save("data/scoreboard.dat", oss.str());
}

std::unique_ptr<Game> createGame(GameId id, std::unique_ptr<IRenderer> renderer,
                                 std::unique_ptr<IInputHandler> inputHandler,
                                 Player &player, Scoreboard &scoreboard,
                                 Storage &storage) {
  const auto &meta = getGameMetadata(id);
  switch (id) {
  case GameId::ROCK_PAPER_SCISSORS:
    return std::make_unique<RockPaperScissors>(meta, std::move(renderer),
                                               std::move(inputHandler), player,
                                               scoreboard, storage);
  case GameId::GUESS_NUMBER:
    return std::make_unique<GuessNumber>(meta, std::move(renderer),
                                         std::move(inputHandler), player,
                                         scoreboard, storage);
  default:
    return nullptr;
  }
}

void showMenu(IRenderer &renderer, IInputHandler &input) {
  renderer.clearScreen();
  renderer.println("=== Game Menu ===");
  for (size_t i = 0; i < ALL_GAMES.size(); ++i) {
    const auto &meta = getGameMetadata(ALL_GAMES[i]);
    renderer.println(std::to_string(i + 1) + ". " + meta.name);
  }
  renderer.println("0. Exit");
  renderer.print("Your choice: ");
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

  auto menuRenderer = factory.createRenderer();
  auto menuInput = factory.createInputHandler();
  menuInput->start();

  bool exitRequested = false;
  while (!exitRequested) {
    showMenu(*menuRenderer, *menuInput);
    std::string choiceStr = menuInput->waitForInput();
    int choice;
    try {
      choice = std::stoi(choiceStr);
    } catch (...) {
      menuRenderer->println("Invalid input. Enter a number.");
      continue;
    }

    if (choice == 0) {
      exitRequested = true;
      break;
    }
    if (choice < 1 || choice > static_cast<int>(ALL_GAMES.size())) {
      menuRenderer->println("Invalid choice. Try again.");
      continue;
    }

    GameId selectedId = ALL_GAMES[choice - 1];

    // Для каждой игры создаём свежие UI-объекты
    auto gameRenderer = factory.createRenderer();
    auto gameInput = factory.createInputHandler();
    gameInput->start(); // запускаем фоновый поток ввода для игры

    auto game = createGame(selectedId, std::move(gameRenderer),
                           std::move(gameInput), player, scoreboard, storage);
    if (!game) {
      menuRenderer->println("Game not implemented yet.");
      continue;
    }
    try {
      game->init();
      game->run();
      game->cleanup();
    } catch (const std::exception &e) {
      std::cerr << "Game error: " << e.what() << std::endl;
    }

    // Сохраняем данные игрока и таблицу результатов ПОСЛЕ КАЖДОЙ игры
    std::stringstream ss;
    ss << player.getName() << "\n" << player.getGeneralScore();
    storage.save("data/player.dat", ss.str());
    saveAllScoreboards(scoreboard, storage);
  }

  menuInput->stop();
  return 0;
}