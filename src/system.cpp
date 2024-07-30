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
#include "message.h"

#include <cstdlib>
#include <iostream>
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
        // std::istringstream stream(msg);
        // stream >> cmd;

        // Add user massage to the system queue (calls the UserMessage ctor)
        _msgs.emplace(msg);

        // Add messages to System queue until a "continue" message is received.
      } while( _msgs.back().type() != UserMessageType::CONTINUE );
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
  while ( !_msgs.empty() ) {
    // Get the message off the front of the queue
    UserMessage& msg = _msgs.front();

    if ( msg.is_valid() ) {
      // If ADD command, add elevator to system.
      if ( msg.type() == UserMessageType::ADD ) {
        // Assume that the first element of thr args vector is the max weight
        const auto& pair = _elevators.try_emplace(
          msg.eid(), std::stod(msg.args()[0]), this);
        std::cout << (pair.second ? "-> success.\n" : "-> failure.\n");
      }

      if ( _elevators.find(msg.eid()) != _elevators.end() ) {
        // If valid, and elevator ID matches an existing elevator, create
        // ElevatorCommand from the user message.
        std::unique_ptr<ElevatorCommand> cmd = 
          msg.create_command(&_elevators[msg.eid()]);

        if ( cmd.get() ) {
          // If the command is valid (not nullptr), dispatch the command to the
          // elevator.
          _elevators[msg.eid()].add_command(std::move(cmd));
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

/**
 * @brief Overloads the string stream operator for an ElevatorSystem::Floor obj.
 * 
 * Takes a ostream reference and returns an ostream reference. Passing and
 * returning by value will cause errors.
 * 
 * @param stream 
 * @param floor 
 * @return std::ostream& 
 */
std::ostream& operator<<(std::ostream& stream, const ElevatorSystem::Floor& floor)
{
  switch ( floor ) {
    case (ElevatorSystem::Floor::B2):
      stream << "B2";
      break;

    case (ElevatorSystem::Floor::B1):
      stream << "B1";
      break;

    case (ElevatorSystem::Floor::UB):
      stream << "UB";
      break;

    case (ElevatorSystem::Floor::L):
      stream << "L";
      break;

    case (ElevatorSystem::Floor::ONE):
      stream << "ONE";
      break;

    case (ElevatorSystem::Floor::TWO):
      stream << "TWO";
      break;

    case (ElevatorSystem::Floor::THREE):
      stream << "THREE";
      break;

    case (ElevatorSystem::Floor::P):
      stream << "P";
      break;
    
    default:
      stream << "invalid floor";
      break;
  }

  return stream;
}