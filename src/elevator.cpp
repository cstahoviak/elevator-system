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

#include "system.h"

#include <sstream>

/**
 * @brief The public interface to the ElevatorSystem class.
 * 
 */
void ElevatorSystem::run() {
    while ( true ) {

      // Create the user message  
      UserMessage usr_msg;

      // Add messages to System queue until a "continue" message is received.
      while ( usr_msg.type() != UserMessageType::CONTINUE) {
        // Store the full user message and the command keyword
        std::string msg{""}, cmd{""};

        // Get a new line of input
        std::cout << "User Input: ";
        std::getline(std::cin, msg);
        // Convert to stream and pull the first word off the input stream
        std::istringstream stream(msg);
        stream >> cmd;

        // Add user massage to the system queue (calls the UserMessage ctor)
        _msgs.emplace(msg);
      }
      std::cout << "\n";

    // Route valid massages to individual elevators via the "task manager".
    system._task_manager();

  }

}