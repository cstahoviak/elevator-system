/**
 * @file command.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2024-07-30
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include "command.h"
#include "elevator.h"

std::tuple<bool, std::string> ElevatorStatusCommand::execute() {
  return this->elevator()->status();
}

std::tuple<bool, std::string> ElevatorCallCommand::execute() {
  return this->elevator()->call(_destination);
}