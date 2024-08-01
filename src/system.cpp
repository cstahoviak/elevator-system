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
#include <future>
#include <iostream>
#include <sstream>
#include <thread>
#include <vector>

/**
 * @brief The public interface to the ElevatorSystem class.
 */
void ElevatorSystem::run() {
    _show_instructions();

    while ( true ) {
      // Store the full user message and the command keyword
        std::string msg{""}, cmd{""};

      do {
        // Get a new line of input from the user
        std::cout << "User Input: ";
        std::getline(std::cin, msg);

        // Add user message to the system queue (calls the UserMessage ctor)
        _msgs.emplace(msg, this);

        // Add messages to System queue until a "continue" message is received.
      } while( _msgs.back().type() != UserMessageType::CONTINUE );

      std::cout << "\n";

    // Route valid massages to individual elevators via the "task manager".
    _task_manager();
    std::cout << "\n";
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
          eid, eid, std::stod(msg.args()[0]), this);
        std::cout << msg.msg() << 
          (pair.second ? " -> success.\n" : " -> failure.\n");
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
      std::cout << msg.msg() <<  " -> failure.\n";
    }

    // Dequeue the message.
    _msgs.pop();
  }
}

void ElevatorSystem::_task_manager() {
  // First, parse the message queue
  _parse_message_queue();

  // Then, call the task manager for each elevator.
  std::vector<std::future<void>> futures;
  // std::vector<std::thread> threads;
  for (auto& [eid, elevator] : _elevators) {
    // Dispatch elevators synchronously
    // elevator.task_manager();

    // Dispatch elevators synchronously via std::async
    futures.push_back(
      std::async(std::launch::async, &Elevator::task_manager, &elevator));

    // Dispatch elevators synchronously via std::thread
    // threads.emplace_back(&Elevator::task_manager, &elevator);
  }

  // Join all threads
  // for (std::thread& thread : threads) {
  //   thread.join();
  // }
}

void ElevatorSystem::_show_instructions() {
  std::ostringstream out;

  out << "The Elevator System Application.\n" <<
    "\nValid commands are:\n" <<
    "\tadd <elevator-id> <max-weight-kgs>\n" <<
    "\tstatus <elevator-id>\n" <<
    "\tcall <elevator-id> <floor>\n" <<
    "\tcontinue\n" <<
    "\nNote that one or more 'add' commands must first be followed by a\n" <<
    "'continue' command before 'status' or 'call' commands can be issued\n" <<
    "for the added elevator(s).\n" <<
    "\nExample:\n" <<
    "\tadd E1 125\n" <<
    "\tcontinue\n" <<
    "\tstatus E1\n" <<
    "\tcall E1 1\n" <<
    "\tcall E1 P\n" <<
    "\tstatus E1\n" <<
    "\tstatus E2 (expect to fail)\n"
    "\tcontinue\n" <<
    "\nNote that commands given to the system may not execute in the order\n" <<
    "in which they're received. Commands are routed to each elevator, and\n" <<
    "dispatch of those commands is handled asynchronously (TODO).\n\n";

    std::cout << out.str();
}