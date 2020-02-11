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
    UserMessage& task = _tasks.front();

    switch( task.ResolveCommand() ) {

      // STOPPED HERE: switch statement executing more than one case??

      case UserMessage::_status: {
        UpdateStatus();   // first, update elevator status
        GetStatus();      // then display current status
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
        std::cout << "ElevatorTaskManager() ERROR: SHOULD NOT GET HERE" << std::endl;
        break;
      }
    }

    // remove element from front of queue
    _tasks.pop();
  }
}

void Elevator::GetStatus() {

  switch( _status ) {
    
    case _stationary: {
      std::cout << "stationary " + _id << std::endl;
      break;
    }

    case _up: {
      std::cout << _id + " moving-up " + _currentFloor + " " + _destinationFloor +
        " " + std::to_string(_currentLoad) << std::endl;
      break;
    }

    case _down: {
      std::cout << _id + " moving-down " + _currentFloor + " " + _destinationFloor +
        " " + std::to_string(_currentLoad) << std::endl;
      break;
    }
  }

}

void Elevator::UpdateStatus() {

  if( _currentFloor.compare(_destinationFloor) == 0 ) {
    // elevator at its destination floor - not in motion
    _status = _stationary;
  }
  else {
    int idx     = 0;
    int current = 0;
    int dest    = 0;

    // TODO: Problem evaluating up vs down

    for( auto it = _system->GetFloors().begin(); it != _system->GetFloors().end(); it++ ) {
      if( (*it).compare(_currentFloor) == 0 ) {
        current = idx;
      }
      if( (*it).compare(_destinationFloor) == 0 ) {
        dest = idx;
      }
      idx++;
    }

    if( (dest - current) > 0) {
      _status = _up;
    }
    else {
      _status = _down;
    }
  }

}

void Elevator::CallToFloor( std::string floor ) {

  std::cout  << _id << " -> " << floor << std::endl;

  _destinationFloor = floor;  // set destination floor

  UpdateStatus();   // update elevator status
  GetStatus();      // displace updated status
  MoveElevator();   // move elevator to destination floor
  GetStatus();      // get current status
}

void Elevator::MoveElevator() {

  auto current = std::find(_system->GetFloors().begin(), _system->GetFloors().end(), _currentFloor);
  auto dest = std::find(_system->GetFloors().begin(), _system->GetFloors().end(), _destinationFloor);

  // size_t dist = std::distance(current, dest);

  switch (_status) {
    case _up:
      // iterate "upawards" through floors
      for (auto it = current; it != dest+1; it++) {
        _currentFloor = (*it);
        std::cout << _id << ": " << _currentFloor << std::endl;

        std::this_thread::sleep_for(std::chrono::seconds(1));
      }
      break;

    case _down:
      // iterate "downwards" through floors
      for (auto it = current; it != dest-1; it--) {
        _currentFloor = (*it);
        std::cout << _id << ": " << _currentFloor << std::endl;

        std::this_thread::sleep_for(std::chrono::seconds(1));
      }
      break;
  
    default:
      std::cout << "MoveElevator() ERROR: SHOULD NOT GET HERE" << std::endl;
      break;
  }

  // update elevator status
  _status = _stationary;
}