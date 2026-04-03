#pragma once
#include <string>
class Player {
public:
  int getName();
  int getGeneralScore();
  void setGeneralScore(int);

private:
  std::string name;
  int generalScore;
};