#include "rock_papr_sisr.hpp"
#include "game_metadata.hpp"
#include <cstdlib>
#include <ctime>
#include <stdexcept>

RockPaperScissors::RockPaperScissors(
    const GameMetadata &meta, std::unique_ptr<IRenderer> renderer,
    std::unique_ptr<IInputHandler> inputHandler, Player &player,
    Scoreboard &scoreboard, Storage &storage)
    : Game(meta), m_renderer(std::move(renderer)),
      m_inputHandler(std::move(inputHandler)), m_player(player),
      m_scoreboard(scoreboard), m_storage(storage) {}

void RockPaperScissors::init() {
  std::srand(static_cast<unsigned>(std::time(nullptr)));
  auto stats = m_scoreboard.getStats(getGameId());
  m_wins = stats.wins;
  m_losses = stats.losses;
  m_ties = stats.ties;
  m_roundsPlayed = m_wins + m_losses + m_ties;
  m_renderer->clearScreen();
  m_renderer->println((std::string)getName() + " game initialized.");
}

void RockPaperScissors::run() {
  m_renderer->println("\n=== " + (std::string)getName() + " ===");
  m_renderer->println("Enter your move: 1=Rock, 2=Paper, 3=Scissors");
  m_renderer->println("Type 'q' to finish the game.");

  while (!m_quitRequested) {
    m_renderer->print("\nYour choice: ");
    Move playerMove;
    try {
      playerMove = getPlayerMove();
    } catch (const std::runtime_error &) {
      m_quitRequested = true;
      break;
    }
    Move computerMove = getComputerMove();
    Result res = judge(playerMove, computerMove);

    auto moveToStr = [](Move m) -> std::string {
      switch (m) {
      case Move::ROCK:
        return "Rock";
      case Move::PAPER:
        return "Paper";
      case Move::SCISSORS:
        return "Scissors";
      }
      return "";
    };
    m_renderer->print("Computer: ");
    m_renderer->println(moveToStr(computerMove));

    switch (res) {
    case Result::WIN:
      m_renderer->println("You win this round!");
      m_player.addToGeneralScore(10);
      m_wins++;
      break;
    case Result::LOSE:
      m_renderer->println("You lose this round.");
      m_losses++;
      break;
    case Result::TIE:
      m_renderer->println("It's a tie.");
      m_ties++;
      break;
    }
    m_roundsPlayed++;
    updateStatistics(res);
  }
  showFinalStats();
  m_scoreboard.setStats(getGameId(), {m_wins, m_losses, m_ties});
}

void RockPaperScissors::cleanup() {
  m_renderer->println((std::string)getName() + " finished. Goodbye!");
  m_inputHandler->stop();
}

RockPaperScissors::Move RockPaperScissors::getPlayerMove() {
  while (true) {
    std::string input = m_inputHandler->waitForInput();
    if (input == "1")
      return Move::ROCK;
    if (input == "2")
      return Move::PAPER;
    if (input == "3")
      return Move::SCISSORS;
    if (input == "q")
      throw std::runtime_error("quit");
    m_renderer->print("Invalid input. Enter 1,2,3 or 'q': ");
  }
}

RockPaperScissors::Move RockPaperScissors::getComputerMove() {
  int r = std::rand() % 3;
  return static_cast<Move>(r);
}

RockPaperScissors::Result
RockPaperScissors::judge(RockPaperScissors::Move player,
                         RockPaperScissors::Move computer) {
  if (player == computer)
    return Result::TIE;
  if ((player == Move::ROCK && computer == Move::SCISSORS) ||
      (player == Move::PAPER && computer == Move::ROCK) ||
      (player == Move::SCISSORS && computer == Move::PAPER))
    return Result::WIN;
  return Result::LOSE;
}

void RockPaperScissors::updateStatistics(Result res) {
  bool win = (res == Result::WIN);
  bool tie = (res == Result::TIE);
  m_scoreboard.recordResult(getGameId(), win, tie);
}

void RockPaperScissors::showFinalStats() {
  m_renderer->println("\n=== Game Statistics ===");
  m_renderer->println("Total rounds: " + std::to_string(m_roundsPlayed));
  m_renderer->println("Wins : " + std::to_string(m_wins));
  m_renderer->println("Losses: " + std::to_string(m_losses));
  m_renderer->println("Ties : " + std::to_string(m_ties));
  m_renderer->println("Your general score: " +
                      std::to_string(m_player.getGeneralScore()));
}