/**
 * @file elevator_system.cpp
 * @author carlcstahoviak@gmail.com
 * @brief The elevator system application.
 * @version 0.1
 * @date 2024-07-28
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include "message.h"
#include "system.h"

#include <iostream>

int main () {
  std::cout << "The Elevator System Application." << std::endl;
  std::cout << "Valid commands are: " << std::endl;

  ElevatorSystem system;
  system.run();
}