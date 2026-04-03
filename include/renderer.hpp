#pragma once
#include <string>
class Renderer {
public:
  void clearScreen();
  void printAt(int row, int col, const std::string &text);
  void drawFrame(int width);

private:
  std::string screenContent;
};