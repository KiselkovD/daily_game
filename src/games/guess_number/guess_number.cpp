/**
 * @file guess_number.hpp
 * @brief
 *
 */

#include "guess_number.hpp"
#include "game_metadata.hpp"
#include <charconv>
#include <cstdlib>
#include <ctime>
#include <stdexcept>

/**
 * @class GuessNumber
 * @brief
 *
 */

GuessNumber::GuessNumber(const GameMetadata &meta,
                         std::unique_ptr<IRenderer> renderer,
                         std::unique_ptr<IInputHandler> inputHandler,
                         Player &player, Scoreboard &scoreboard,
                         Storage &storage)
    : Game(meta), m_renderer(std::move(renderer)),
      m_inputHandler(std::move(inputHandler)), m_player(player),
      m_scoreboard(scoreboard), m_storage(storage) {}

void GuessNumber::init() {
  std::srand(static_cast<unsigned>(std::time(nullptr)));
  auto stats = m_scoreboard.getStats(getGameId());
  m_wins = stats.wins;
  generateNumber();
  m_renderer->clearScreen();
  m_renderer->println(getName() + (std::string) " game initialized.");
}
void GuessNumber::run() {
  m_renderer->println("\n=== " + (std::string)getName() + " ===");
  m_renderer->println("Enter your guess: (0 < x < 100)");
  m_renderer->println("Type 'q' to finish the game.");

  while (!m_quitRequested) {
    m_renderer->print("\nYour choice: ");
    int playerGuess;
    try {
      playerGuess = getPlayerGuess();
    } catch (const std::runtime_error &) {
      m_quitRequested = true;
      break;
    }
    Result res = checkGuess(playerGuess);
    switch (res) {
    case Result::LESS:
      m_renderer->println("value smaller");
      break;
    case Result::SAME:
      m_renderer->println("You win!");
      m_player.addToGeneralScore(10);
      m_wins++;
      generateNumber();
      break;
    case Result::MORE:
      m_renderer->println("value grater");
      break;
    }
    updateStatistics(res);
  }
  showFinalStats();
  m_scoreboard.setStats(getGameId(), {m_wins, 0, 0});
}
void GuessNumber::cleanup() {
  m_renderer->println((std::string)getName() + " finished. Goodbye!");
  m_inputHandler->stop();
}
int GuessNumber::getPlayerGuess() {
  while (true) {
    std::string input = m_inputHandler->waitForInput();
    int value; // сюда будет записано число (если парсинг успешен)
    auto [ptr, ec] =
        std::from_chars(input.data(), input.data() + input.size(), value);
    if (ec == std::errc() && ptr == input.data() + input.size())
      return value;
    if (input == "q")
      throw std::runtime_error("quit");
    m_renderer->print("Invalid input. Enter 1,2,3 or 'q': ");
  }
}
GuessNumber::Result GuessNumber::checkGuess(int playerGuess) {
  if (playerGuess > m_number)
    return Result::LESS;
  if (playerGuess < m_number)
    return Result::MORE;
  return Result::SAME;
}
void GuessNumber::updateStatistics(Result res) {
  if (res == Result::SAME)
    m_scoreboard.recordResult(getGameId(), true, false);
}
void GuessNumber::showFinalStats() {
  m_renderer->println("\n=== Game Statistics ===");
  m_renderer->println("Wins : " + std::to_string(m_wins));
  m_renderer->println("Your general score: " +
                      std::to_string(m_player.getGeneralScore()));
}
void GuessNumber::generateNumber() { m_number = std::rand() % 99 + 1; }