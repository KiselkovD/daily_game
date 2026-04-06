/**
 * @file storage.cpp
 * @brief
 *
 */
#include "storage.hpp"
#include <fstream>
#include <iostream>

bool FileStorage::save(const std::string &key, const std::string &data) {
  std::ofstream file(key, std::ios::trunc);
  if (!file.is_open()) {
    return false;
  }
  file << data;
  file.close();
  return true;
}

bool FileStorage::load(const std::string &key, std::string &data) {
  std::ifstream file(key);
  if (!file.is_open()) {
    return false;
  }
  std::string line;
  data.clear();
  while (std::getline(file, line)) {
    if (!data.empty())
      data += "\n";
    data += line;
  }
  file.close();
  return true;
}