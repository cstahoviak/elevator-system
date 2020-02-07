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
  if( _cmd.compare("status") )   return _status;
  if( _cmd.compare("continue") ) return _continue;
  if( _cmd.compare("add") )      return _add;
  if( _cmd.compare("call") )     return _call;
  if( _cmd.compare("enter") )    return _enter;
  if( _cmd.compare("exit") )     return _exit;

  return _invalid;
}

bool UserMessage::IsValid() {
  // parse incoming message
  ParseUserMessage();

  // is a valid base command issued?
  if( std::find(_valid_cmds.begin(), _valid_cmds.end(), _cmd) == _valid_cmds.end() ) {
    // base command not a valid command
    return false;
  }
  // if adding a new elevator to an empty vector of elevators
  else if( _system->GetElevators().empty() && _cmd.compare("call") == 0 ) {
    _system->AddElevator(_eid, std::stod(_value));
    return false;   // do not send an "add elevator" command to another elevator
  }
  // a valid base command has been issued 
  else {
    // does the elevator ID correspond to a valid elevator?
    for( auto it =_system->GetElevators().begin(); it != _system->GetElevators().end(); ++it ) {
      if( (*it).GetID().compare(_eid) == 0 ) {
        // input elevator ID matches valid elevator ID
        switch( ResolveCommand() ) {
          // value parameter invalid with "status" base command
          case _status: { return _value.empty(); }

          // value parameter invalid with "continue" base command
          case _continue: { return _value.empty(); }

          case _call:
            // true if _value is a valid floor
            return std::find(_system->GetFloors().begin(), _system->GetFloors().end(), _value) != _system->GetFloors().end();

          // not yet setup to handle the "enter" command
          case _enter: { return false; }

          // not yet setup to handle the "exit" command
          case _exit: { return false; }
          
          default: {return false; }
        }
      }
      // reached end of elevators vector without finding the input eid
      else if( it == _system->GetElevators().end() ) {
        // if adding a new elevator
        if( _cmd.compare("add") == 0 ) {
          _system->AddElevator(_eid, std::stod(_value));
          return false;   // do not send an "add elevator" command to another elevator
        }
      }
      else {
        return false;
      }
    } /* end eid check */ 
  } /* end for() */
} /* end IsValid() */