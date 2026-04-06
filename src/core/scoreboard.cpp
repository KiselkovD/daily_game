/**
 * @file scoreboard.cpp
 * @brief
 *
 */
#include "scoreboard.hpp"
#include <sstream>

void Scoreboard::recordResult(int gameId, bool win, bool tie) {
  auto &stats = m_stats[gameId];
  if (win) {
    stats.wins++;
  } else if (tie) {
    stats.ties++;
  } else {
    stats.losses++;
  }
}

GameStats Scoreboard::getStats(int gameId) const {
  auto it = m_stats.find(gameId);
  if (it != m_stats.end()) {
    return it->second;
  }
  return GameStats{0, 0, 0};
}

void Scoreboard::setStats(int gameId, const GameStats &stats) {
  m_stats[gameId] = stats;
}

std::string Scoreboard::getStatsString(int gameId) const {
  auto stats = getStats(gameId);
  std::ostringstream oss;
  oss << "Wins: " << stats.wins << " Losses: " << stats.losses
      << " Ties: " << stats.ties;
  return oss.str();
}

void Scoreboard::clear() { m_stats.clear(); }