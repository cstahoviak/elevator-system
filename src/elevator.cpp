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
  while( !_tasks.empty() ) {
    // get a reference to the next message off the top of the queue
    UserMessage &task = _tasks.front();

    UserMessage::ValidCommands cmd = task.ResolveCommand();

    switch( task.ResolveCommand() ) {

      // STOPPED HERE: switch statement executing more than one case??

      case UserMessage::_status: {
        GetStatus();
        break;
      }

      case UserMessage::_continue: { /* do nothing */ break; }

      case UserMessage::_call: {
        CallToFloor( task.GetValue() );
        break;
      }
      case UserMessage::_enter: {
        std::cout << "Ignoring ENTER elevator command" << std::endl;
        break;
      }

      case UserMessage::_exit: {
        std::cout << "Ignoring EXIT elevator command" << std::endl;
        break;
      }

      default: {
        std::cout << "ERROR: SHOULD NOT GET HERE" << std::endl;
        break;
      }
    }

    // remove element from front of queue
    _tasks.pop();
  }
}

void Elevator::GetStatus() {

  if( _currentFloor.compare(_destinationFloor) == 0 ) {
    // elevator at its destination floor - not in motion
    std::cout << "stationary " + _id << std::endl;
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
      std::cout << _id + " moving-up " + _currentFloor + " " + _destinationFloor +
        " " + std::to_string(_currentLoad) << std::endl;
    }
    else {
      std::cout << _id + " moving-down " + _currentFloor + " " + _destinationFloor +
        " " + std::to_string(_currentLoad) << std::endl;
    }
  }

}

void Elevator::CallToFloor( std::string floor ) {

  std::cout << "Moving elevator " << _id << " to floor " << floor << std::endl;

  _destinationFloor = floor;  // set destination floor

  GetStatus();      // get current status
  MoveElevator();   // move elevator to destination floor
  GetStatus();      // get current status
}

void Elevator::MoveElevator() {

  // NEXT: Print current floor as elevator is moving

  auto current = std::find(_system->GetFloors().begin(), _system->GetFloors().end(), _currentFloor);
  auto dest = std::find(_system->GetFloors().begin(), _system->GetFloors().end(), _destinationFloor);

  size_t dist = std::distance(current, dest);

  // it takes two seconds to traverse a single floor
  for (size_t i = 0; i <= dist; i++) {
    // TODO: update current floor as elevator is moving
    std::cout << _id << " <current floor here>" << std::endl;

    std::this_thread::sleep_for(std::chrono::seconds(1));
  }

  // update elevators current location - might do this in loop instead
  _currentFloor = _destinationFloor;
}