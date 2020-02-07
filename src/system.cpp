#include <iostream>
#include <algorithm>  // std::find

#include "system.h"
#include "elevator.h"

System::System() {
  OnInit();
}

void System::OnInit() {
  while( true ) {
    // take input from user 
  }

}

bool System::AddElevator(std::string name, double payload) {
  
  // this won't work
  // auto iter = std::find(_elevators.begin(), _elevators.end(), name);

  for( auto iter =_elevators.begin(); iter != _elevators.end(); ++iter ) {
    if( (*iter).GetID().compare(name) == 0 ) {
      // elevator with this name already exists - failed to add elevator to _elevators
      std::cout << "Elevator " << name << " already exists with max payload "
        << std::to_string( (*iter).GetMaxLoad() ) << " kgs" << std::endl;
      return false;
    }
    else if( iter == _elevators.end() ) {
      // reached end of _elevators and none with id "name" found
      _elevators.emplace_back(name, payload, this);
      // SetElevatorSystemHandle();
      return true;
    }
  }
}

// void System::SetElevatorSystemHandle() {
//   auto it = _elevators.end();
//   (*it)._system = this;
// }