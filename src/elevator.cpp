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
#include "system.h"

#include <iostream>
#include <sstream>
#include <thread>     // std::this_thread

void Elevator::task_manager() {
  // Execute all elevator tasks in the queue
  while ( !_commands.empty() ) {
    // Get the first command (explicityly move the unique_ptr out of the queue)
    std::unique_ptr<ElevatorCommand> cmd = std::move(_commands.front());

    // Execute the command and display the result string
    auto [success, result_str] = cmd.get()->execute();
    std::cout << cmd.get()->msg() << " -> "  << result_str << std::endl;

    // Remove the command from the front of the queue.
    // NOTE: After the move, the top element in the queue is a unique_ptr equal
    // to nullptr. The pop is needed to remove this "empty" unique_ptr from the
    // queue.
    _commands.pop();
  }
}

void Elevator::_update_status() {
  if ( _current_floor == _destination_floor ) {
    _status = Status::STATIONARY;
  }
  else if ( _current_floor < _destination_floor ) {
    _status = Status::MOVING_UP;
  }
  else {
    _status = Status::MOVING_DOWN;
  }

  // Status has been updated (no longer stale)
  _status_stale = false;
}

void Elevator::add_command(std::unique_ptr<ElevatorCommand> cmd) {
  _commands.push(std::move(cmd));
}

std::tuple<bool, std::string> Elevator::status() {
  // Update the elevator's status if it's stale
  if ( _status_stale ) {
    _update_status();
  }

  // Display the elevator status.
  std::ostringstream result;
  result << status_to_str.at(_status);
  switch ( _status ) {
    case Status::MOVING_UP:
      result << " " << _current_floor << " " << _destination_floor << " "
        <<  _current_weight;
      
    case Status::MOVING_DOWN:
      result << " " << _current_floor << " " << _destination_floor << " "
        << _current_weight;

    case Status::STATIONARY:
      result << " " << _current_floor;

    default:
      break;
  }

  return {true, result.str()};
}

std::tuple<bool, std::string> Elevator::call(std::string& destination) {
  // Set the destination floor
  _destination_floor = _system->floors().str_to_floor(destination);

  // Update the elevator's status if it's stale
  if ( _status_stale ) {
    _update_status();
  }
  
  // Define the return values
  bool success = false;
  std::ostringstream result;

  if ( _destination_floor == _current_floor ) {
    // Do nothing - the elevator is already on the floor it's been called to
    result << "success.";
    return {true, result.str()};
  }

  // Compute the distance between floors
  int current = static_cast<int>(_current_floor);
  int dest = static_cast<int>(_destination_floor);
  int dist = dest - current;

  // Move the elevator to the destination floor
  // TODO: This check may not be necessary if the UserMessage already validates
  // that the floor must exist for a valid "CALL" command to be issued.
  if ( _system->floors().names().find(destination) != _system->floors().names().end() )
  {
    switch( _status )
    {
      case Status::MOVING_UP:
        for ( int floor = current; floor <= dest; floor++ ) {
          // Moving the elevator causes its status to be come stale
          _status_stale = true;

          // Update the current floor
          _current_floor = Floors::Name{floor};

          // TODO: Convert Floor to string
          std::cout << _id << ": " << _current_floor << std::endl; 

          // Traversing a floor will take 1 sec
          std::this_thread::sleep_for(_floor_traverse_time_ms);
        }
        break;

      case Status::MOVING_DOWN:
        for ( int floor = current; floor >= dest; floor-- ) {
            // Moving the elevator causes its status to be come stale
            _status_stale = true;

            // Update the current floor
            _current_floor = Floors::Name{floor};

            // TODO: Convert Floor to string
            std::cout << _id << ": " << _current_floor << std::endl; 

            // Traversing a floor will take 1 sec
            std::this_thread::sleep_for(_floor_traverse_time_ms);
          }
        break;

      default:
        std::cout << "Elevator::call error: shouldn't get here." << std::endl; 
        break;
    }

    success = true;
    result << "success.";
  }
  else {
    // The elevator was called to a floor that doesn't exist.
    result << ".failure. Elevator called to non-existent floor: "
      << destination;
  }

  // Set the elevator's status to stale.
  _status_stale = true;

  return {success, result.str()};
}