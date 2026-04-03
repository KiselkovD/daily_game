#pragma once
#include <string>
#include <vector>

struct ScoreEntry {
  std::string name;
  int score;
  int gameIndex;
};
class Scoreboard {
public:
  void setScore(std::string name, int score, int gameIndex);
  int getScore(std::string name, int gameIndex);
  std::string getScoreTable(int gameIndex);

private:
  std::vector<ScoreEntry> scoreEntryVector;
};