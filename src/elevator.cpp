#include <iostream>
#include <algorithm>  // std::find
#include <iterator>   // std::distance

#include <thread>     // std::this_thread
#include <chrono>     // std::chrono

#include "elevator.h"
#include "system.h"
#include "user_message.h"

void Elevator::ElevatorTaskManager() {
  // de-queue all messages in elevator task queue
  while( !_task_queue.empty() ) {
    // get next message off the top of the queue
    UserMessage task = _task_queue.front();

    switch( task.ResolveCommand() ) {

      // STOPPED HERE: deal eith enum tomorrow

      case UserMessage::ValidCommands::_status: { GetStatus(); }
      case UserMessage::ValidCommands::_continue: { /* do nothing */ }
      case UserMessage::ValidCommands::_call: { MoveElevator(); }
      case UserMessage::ValidCommands::_enter: {
        std::cout << "Ignoring ENTER elevator command" << std::endl;
       }
      case UserMessage::ValidCommands::_exit: {
        std::cout << "Ignoring EXIT elevator command" << std::endl;
       }
      default: {
        std::cout << "ERROR: SHOULD NOT GET HERE" << std::endl;
       }
    }

    // remove element from front of queue
    _task_queue.pop();
  }
}

std::string Elevator::GetStatus() {
  if( _currentFloor.compare(_destinationFloor) == 0 ) {
    // elevator at its destination floor - not in motion
    return "stationary " + _id + "\n";
  }
  else {
    int idx     = 0;
    int current = 0;
    int dest    = 0;

    for(auto it = _system->GetFloors().begin(); it != _system->GetFloors().end(); ++it) {
      if( (*it).compare(_currentFloor)) {
        current = idx;
      }
      if( (*it).compare(_destinationFloor)) {
        dest = idx;
      }
      idx++;
    }

    if( (current - dest) > 0) {
      return "moving-up " + _currentFloor + " " + _id + " " +
        std::to_string(_currentLoad) + "\n";
    }
    else {
      return "moving-down " + _currentFloor + " " + _id + " " +
        std::to_string(_currentLoad) + "\n";
    }
  }

}

bool Elevator::CallToFloor( std::string floor ) {
  if( std::find(_system->GetFloors().begin(), _system->GetFloors().end(), floor) == _system->GetFloors().end()) {
    // don't think it should be possible to get here
    std::cout << "Cannot call " << _id << " to non-existent floor " << floor << std::endl;
    return false;
  }
  else {
    std::cout << "Moving elevator " << _id << " to floor " << floor << std::endl;
    _destinationFloor = floor;
    MoveElevator();   // move elevator to the destination floor
    return true;
  }
}

void Elevator::MoveElevator() {
  auto current = std::find(_system->GetFloors().begin(), _system->GetFloors().end(), _currentFloor);
  auto dest = std::find(_system->GetFloors().begin(), _system->GetFloors().end(), _destinationFloor);

  size_t dist = std::distance(current, dest);

  // it takes two seconds to traverse a single floor
  for (size_t i=0; i <= dist; i++) {
    // update current floor as elevator is moving

    std::this_thread::sleep_for(std::chrono::seconds(2));
  }

  // update elevators current location - might do this in loop instead
  _currentFloor = _destinationFloor;
}