#pragma once
#include <string>
class Storage {
public:
  virtual bool save(const std::string &key, const std::string &data) = 0;

  virtual bool load(const std::string &key, std::string &data) = 0;
};

class FileStorage final : public Storage {
  bool save(const std::string &key, const std::string &data) { return true; }

  bool load(const std::string &key, std::string &data) { return true; }
};