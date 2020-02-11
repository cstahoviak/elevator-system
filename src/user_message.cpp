#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>    // std::find

#include "user_message.h"
#include "system.h"

void UserMessage::ParseUserMessage() {
  // parse incoming user message 
  std::istringstream stream(_msg);
  stream >> _cmd >> _eid >> _value;
}

UserMessage::ValidCommands UserMessage::ResolveCommand() {
  if( _cmd.compare("status") == 0 )   return _status;
  if( _cmd.compare("continue") == 0 ) return _continue;
  if( _cmd.compare("add") == 0 )      return _add;
  if( _cmd.compare("call") == 0 )     return _call;
  if( _cmd.compare("enter") == 0 )    return _enter;
  if( _cmd.compare("exit") == 0 )     return _exit;

  return _invalid;
}

bool UserMessage::IsValid() {

  // parse incoming message
  ParseUserMessage();

  // is a valid base command issued?
  if( ResolveCommand() == _invalid ) {
    return false;
  }
  // a valid base command has been issued 
  else {
    
    // search existing elevators for matching ID
    for( auto it = _system->GetElevators().begin(); it != _system->GetElevators().end(); it++) {
      if( (*it).GetID().compare(_eid) == 0 ) {
        // input elevator ID matches valid elevator ID
        switch( ResolveCommand() ) {
          // value parameter invalid with "status" base command
          case _status: { return _value.empty(); }

          // value parameter invalid with "continue" base command
          case _continue: { return _value.empty(); }

          case _call: {
            /* NOTE: System::GetFloors() must return a **reference** to the _floors
            * vector, otherwise the search below (find) will not be properly
            * evaluated. Still not sure exactly why this is...? Probably has
            * something to do with a copy of _floors being returned instead of a
            * reference to _floors.
            */

            // true if _value is a valid floor
            return std::find(_system->GetFloors().begin(),
              _system->GetFloors().end(), _value) != _system->GetFloors().end();
          }

          // not yet setup to handle the "enter" command
          case _enter: { return false; }

          // not yet setup to handle the "exit" command
          case _exit: { return false; }
          
          default: { return false; }
        }
      }
    }

    // finished iterating through existing elevators - add new elevator?
    if( ResolveCommand() == _add && !_value.empty() ) {
      std::cout << "Adding Elevator " << _eid << " to system" << std::endl;
      _system->AddElevator(_eid, std::stod(_value));
      return false;   // do not send an "add elevator" command to elevator
    }

    return false;
  } /* end valid base command check */
} /* end IsValid() */

void UserMessage::Test() {

  std::cout << "\nUserMessage::Test()" << std::endl;

  std::cout << "\tUserMessage::Test(): &_system->GetElevators()\t" <<
    &_system->GetElevators() << std::endl;

  auto begin = _system->GetElevators().begin();
  auto end = _system->GetElevators().end();

  std::cout << "\tbegin:\t" << &(*begin) << std::endl;
  std::cout << "\tend:\t" << &(*end) << std::endl;

  std::cout << "\trange-based for loop" << std:: endl;
  for( auto elevator : _system->GetElevators() ) {
    std::cout << "\televator " << elevator.GetID() << " at\t"
      << &elevator << std::endl;
  }

  std::cout << "\n\titerator for loop" << std::endl;
  for( auto it = _system->GetElevators().begin(); it != _system->GetElevators().end(); it++) {
    std::cout << "\televator " << (*it).GetID() << " at\t" << &(*it) << std::endl;
  }
}