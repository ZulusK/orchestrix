#include "Controller.h"
#include <cstdlib>
Controller::Controller() {}

bool *Controller::getInput() {
  bool *input =new bool[4];
  input[0] = rand() % 2;
  input[1] = rand() % 2;
  input[2] = rand() % 2;
  input[3] = rand() % 2;
  return input;
}
