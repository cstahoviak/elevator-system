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
#include <sstream>

/**
 * @brief The public interface to the ElevatorSystem class.
 * 
 */
void ElevatorSystem::run() {
    while ( true ) {
      // Store the full user message and the command keyword
        std::string msg{""}, cmd{""};

      do {
        // Get a new line of input from the user
        std::cout << "User Input: ";
        std::getline(std::cin, msg);

        // Convert to stream and pull the first word off the input stream
        std::istringstream stream(msg);
        stream >> cmd;

        // Add user massage to the system queue (calls the UserMessage ctor)
        _msgs.emplace(msg);

        // Add messages to System queue until a "continue" message is received.
      } while(_msgs.back().type() != UserMessageType::CONTINUE);
      std::cout << "\n";

    // Route valid massages to individual elevators via the "task manager".
    _task_manager();
  }
}

/**
 * @brief Parse the user message queue.
 * 
 */
void ElevatorSystem::_parse_message_queue() {
  while (!_msgs.empty()) {
    // Get the message off the front of the queue
    UserMessage& msg = _msgs.front();

    if (msg.type() == UserMessageType::ADD) {
      // If ADD command, add elevator to system.
      const auto& pair = _elevators.try_emplace(msg.eid(), std::stod(msg.value()));
      std::cout << (pair.second ? "-> success\n" : "-> failure\n");

    }
    else if (msg.is_valid() && _elevators.find(msg.eid()) != _elevators.end()) {
      // If valid, dispatch the message to the corresponding elevator.
      _elevators[msg.eid()].create_command(msg);
    }

    // Remove the first message from the queue
    _msgs.pop();
  }
}

void ElevatorSystem::_task_manager() {
  // First, parse the message queue
  _parse_message_queue();

  // Then, call the task manager for each elevator
  for (auto& [eid, elevator] : _elevators) {
    elevator.task_manager();
  }
}