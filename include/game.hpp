#pragma once
class Game {
public:
  virtual ~Game() = default;
  virtual void init() = 0;
  virtual void run() = 0;
  virtual void cleanup() = 0;
  virtual const char *getName() const = 0;
};