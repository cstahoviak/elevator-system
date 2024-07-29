/**
 * @file elevator.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2024-07-28
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include "elevator.h"
#include "command.h"

void Elevator::create_command(const UserMessage& msg) {
  // TODO: Create the elevator Command from the user message

}

void Elevator::task_manager() {
  // Execute all elevator tasks in the queue
  while (!_tasks.empty()) {}
    UserMessage& cmd = _commands.front();

    switch (cmd.type())
    {
    case (ElevatorCommandType::CALL):
      // Call elevator to specific floor
      _call();
      break;

    case (ElevatorCommandType::STATUS):
      // Get status of elevator
      _status();
      break;

    case (ElevatorCommandType::ENTER):
      // TODO: not implemented.
      break;

    case (UserMessageType::EXIT):
      // TODO: not implemented.
      break;
    
    default:
      break;
    }
}