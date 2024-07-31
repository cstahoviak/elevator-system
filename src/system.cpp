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
#include <iostream>
#include <sstream>

/**
 * @brief The public interface to the ElevatorSystem class.
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
        // std::istringstream stream(msg);
        // stream >> cmd;

        // Add user massage to the system queue (calls the UserMessage ctor)
        _msgs.emplace(msg, this);

        // Add messages to System queue until a "continue" message is received.
      } while( _msgs.back().type() != UserMessageType::CONTINUE );
      std::cout << "\n";

    // Route valid massages to individual elevators via the "task manager".
    _task_manager();
  }
}

/**
 * @brief Parse the user message queue.
 */
void ElevatorSystem::_parse_message_queue() {
  while ( !_msgs.empty() ) {
    // Get the message off the front of the queue
    UserMessage& msg = _msgs.front();

    if ( msg.is_valid() ) {
      // If ADD command, add elevator to system.
      if ( msg.type() == UserMessageType::ADD ) {
        // TODO: Is there a better way to pass the map key and eid to tr_emplace?
        std::string eid = msg.eid();
        // Assume that the first element of the args vector is the max weight
        const auto& pair = _elevators.try_emplace(
          eid, eid, std::stod(msg.args()[0]));
        std::cout << (pair.second ? "-> success.\n" : "-> failure.\n");
      }
      else if ( _elevators.find(msg.eid()) != _elevators.end() ) {
        // If valid, and elevator ID matches an existing elevator, create
        // ElevatorCommand from the user message.
        std::unique_ptr<ElevatorCommand> cmd = 
          msg.create_command(&_elevators.at(msg.eid()));

        if ( cmd.get() ) {
          // If the command is valid (not nullptr), dispatch the command to the
          // elevator.
          _elevators.at(msg.eid()).add_command(std::move(cmd));
        }
      }
    }
    else {
      // An invalid command was added to the System message queue.
      std::cout << " -> failure.\n";
    }

    // Dequeue the message.
    _msgs.pop();
  }
}

void ElevatorSystem::_task_manager() {
  // First, parse the message queue
  _parse_message_queue();

  // Then, call the task manager for each elevator.
  // TODO: Parallelize elevator dispatch with std::async
  for (auto& [eid, elevator] : _elevators) {
    elevator.task_manager();
  }
}