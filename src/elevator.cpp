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

#include <thread>     // std::this_thread
#include <chrono>     // std::chrono

void Elevator::task_manager() {
  // Execute all elevator tasks in the queue
  while ( !_commands.empty() ) {
    // Get the first command
    ElevatorCommand& cmd = _commands.front();

    // Execute the command
    cmd.execute();

    // Remove the command from the front of the queue
    _commands.pop()
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
}

std::string& Elevator::status() {
  // Update the elevator's status if it's stale
  if ( _status_stale ) {
    _update_status();
  }

  // TODO: Display the elevator status.
  switch ( _status ) {
    case Status::MOVING_UP:
      // TODO: Cannot convert Floor enum to string
      return "moving-up " + _current_floor + " " + _destination_floor + " " +
        + _current_weight;
      
    case Status::MOVING_DOWN:
      return "moving-down " + _current_floor + " " + _destination_floor + " " +
        + _current_weight;

    case Status::STATIONARY:
      return "stationary " + _current_floor;
  }

  switch (expression)
  {
  case /* constant-expression */:
    /* code */
    break;
  
  default:
    break;
  }
}

std::string& Elevator::call(std::string& destination) {
  // Convert the destination string to a floor
  ElevatorSystem::Floor destination_floor = _system->str_to_floor(destination);

  if ( destination_floor == _current_floor ) {
    // Do nothing - the elevator is already on the floor it's been called to
    std::string result = "-> success\n";
    return result;
  }

  // Compute the distance between floors
  int current = static_cast<int>(_current_floor);
  int dest = static_cast<int>(destination_floor);
  int dist = dest - current;

  // Move the elevator to the destination floor
  switch( _status )
  {
    case Status::MOVING_UP:
      for ( int floor = current; floor < dest; floor++ ) {
        // Update the current floor
        _current_floor = ElevatorSystem::Floor{floor};

        // TODO: Convert Floor to string
        std::cout << _id << ": " << _current_floor << std::endl; 

        // Traversing a floor will take 1 sec
        std::this_thread::sleep_for(std::chrono::seconds(1));
      }
      break;

    case Status::MOVING_DOWN:
      for ( int floor = current; floor > dest; floor-- ) {
          // Update the current floor
          _current_floor = ElevatorSystem::Floor{floor};

          // TODO: Convert Floor to string
          std::cout << _id << ": " << _current_floor << std::endl; 

          // Traversing a floor will take 1 sec
          std::this_thread::sleep_for(std::chrono::seconds(1));
        }
      break;

    default:
      std::cout << "Elevator::call error: shouldn't get here." << std::endl; 
      break;
  }

  // Set the elevator's status to stale
  _status_stale = true;
}
