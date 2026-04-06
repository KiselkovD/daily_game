/**
 * @file renderer.cpp
 * @brief реализация консольного рендера
 *
 */
#include "renderer.hpp"
#include <cstdlib>
#include <iostream>

#ifdef _WIN32
#define CLEAR "cls"
#else
#define CLEAR "clear"
#endif

void ConsoleRenderer::clearScreen() { std::system(CLEAR); }

void ConsoleRenderer::printAt(int row, int col, const std::string &text) {
  std::cout << "\033[" << row << ";" << col << "H" << text;
  std::cout.flush();
}

void ConsoleRenderer::drawFrame(int width) {
  std::string border = "+" + std::string(width - 2, '-') + "+\n";
  print(border);
}

void ConsoleRenderer::print(const std::string &text) {
  std::cout << text;
  std::cout.flush();
}

void ConsoleRenderer::println(const std::string &text) {
  std::cout << text << std::endl;
}