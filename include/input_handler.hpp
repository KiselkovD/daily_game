#pragma once
enum Direction { UP, LEFT, DOWN, RIGHT };
class InputHandler {
public:
  virtual Direction getDirection();

private:
};