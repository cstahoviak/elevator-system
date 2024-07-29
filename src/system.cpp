/**
 * @file system.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2024-07-28
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include "system.h"

#include <cstdlib>
/**
 * @brief Parse the user message queue.
 * 
 */
void ElevatorSystem::_parse_message_queue() {
  while (!_msgs.empty()) {

  }
}

ElevatorSystem::task_manager() {
  // First, parse the message queue
  _parse_message_queue();

  // Then, call the task manager for each elevator
  for (Elevator& elevator : _elevators) {
    elevator.task_manager();
  }

}