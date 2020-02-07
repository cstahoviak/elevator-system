#include <iostream>
#include <algorithm>  // std::find

#include "system.h"

bool System::AddElevator(std::string name, double payload) {

  auto iter = std::find(_elevators.begin(), _elevators.end(), name);

  if( iter == _elevators.end() ) {
    // if elevator name does not already exist, add it to _elevators
    _elevators.emplace_back(name, payload);
    return true;
  }
  else {
    // failed to add elevator to _elevators
    std::cout << "Elevator " << name << " already exists with max payload "
      << std::to_string( (*iter)._maxLoad ) << " kgs" << std::endl;
    return false;
  }
}