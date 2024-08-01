/**
 * @file message.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2024-07-29
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include "message.h"
#include "system.h"

#include <iostream>
#include <sstream>
#include <string>

UserMessage::UserMessage(std::string msg, ElevatorSystem* system) :
    _msg{msg}, _system{system}
{
  // Extract the "command", "eid" and command "args" from the message
  std::istringstream stream(_msg);

  // Pull off the command from of the user message
  stream >> _cmd;

  // Deal the with continue command up front
  if ( !_cmd.compare("continue") ) {
    _type = UserMessageType::CONTINUE;
  }
  else {
    // All valid commands begin with an elevator ID
    stream >> _eid;

    // Unpack the remaining args into the _args vector
    std::string arg;
    while ( stream.rdbuf()->in_avail() ) {
      // std::getline(stream, arg);
      stream >> arg;
      _args.push_back(arg);
    }

    // Define the message type
    if ( !_cmd.compare("add") ) {
      _type = UserMessageType::ADD;
    }
    else if ( !_cmd.compare("status") ) {
      _type = UserMessageType::STATUS;
    }
    else if ( !_cmd.compare("call") ) {
      _type = UserMessageType::CALL;
    }
    else if ( !_cmd.compare("enter") ) { 
      _type = UserMessageType::ENTER;
    }
    else if ( !_cmd.compare("exit") ) {
      _type = UserMessageType::EXIT;
    }
    else {
      _type = UserMessageType::INVALID;
    }
  }

  // Determine if the message is valid, i.e. do the number of args meet the
  // requirements of the command?
  _is_valid = _validate_message();
}

/**
 * @brief 
 * 
 * Note that I wanted to use std::optional<ElevatorCommand> for the return type,
 * but std::optional doesn't work with polymorphic (derived) types. So I think
 * the solution is to return a pointer to the command instead
 * 
 * @param elevator 
 * @return std::optional<ElevatorCommand*> 
 */
std::unique_ptr<ElevatorCommand> UserMessage::create_command(Elevator* elevator) const
{
  std::unique_ptr<ElevatorCommand> cmd = nullptr;
  // The line below throw an "error: invalid new-expression of abstract class 
  // type ‘ElevatorCommand’. Note: because the following virtual functions are 
  // pure within ‘ElevatorCommand’" 
  // std::unique_ptr<ElevatorCommand> cmd = 
  //   std::make_unique<ElevatorCommand>(nullptr);

  switch ( _type )
  {
  case UserMessageType::ADD:
    std::cout << "Cannot create Elevator command from 'ADD' message."
      << std::endl;
    break;

  case UserMessageType::STATUS:
    cmd = std::make_unique<ElevatorStatusCommand>(_eid, _msg, elevator);
    break;

  case UserMessageType::CALL:
    cmd = std::make_unique<ElevatorCallCommand>(_eid, _msg, elevator, _args[0]);
    break;

  case UserMessageType::ENTER:
    // "enter" command not implemented yet.
    break;

  case UserMessageType::EXIT:
    // "exit" command not implemented yet.
    break;

  case UserMessageType::CONTINUE:
    std::cout << "Cannot create Elevator command from 'CONTINUE' message."
      << std::endl;
    break;
  
  default:
    break;
  }

  return cmd;
}

bool UserMessage::_validate_message() {
  // NOTE: Cannot redeclare variables of the same name and type in multiple
  // switch blocks. Need to create them outside of the switch block.
  bool valid_msg = false;
  bool valid_args = false;
  bool valid_elevator = false;
  bool valid_floor = false;

  switch ( _type )
  {
    case ( UserMessageType::ADD ):
      // Require only a single string arg1 (weight) for a valid "ADD" command.
      valid_msg = _args.size() == 1;

      // Note that if the elevator already exists in the system, this is handled
      // by ElevatorSystem::_parse_message_queue.
      break;

    case UserMessageType::STATUS:
      // No additional args beyond the elevator ID are required
      valid_args = _args.size() == 0;

      // Require that the elevator exists
      valid_elevator = 
        _system->elevators().find(_eid) != _system->elevators().end();

      valid_msg = valid_args && valid_elevator;
      break;

    case UserMessageType::CALL:
      // Require only a single arg (a valid floor)
      valid_args = _args.size() == 1;

      // Require that the elevator exists
      valid_elevator = 
        _system->elevators().find(_eid) != _system->elevators().end();

      // Require that the called-to floor exists
      valid_floor = 
        _system->floors().names().find(_args[0]) != _system->floors().names().end();

      valid_msg = valid_args && valid_elevator && valid_floor;
      break;

    case UserMessageType::ENTER:
      // "enter" command not implemented yet.
      break;

    case UserMessageType::EXIT:
      // "exit" command not implemented yet.
      break;

    case UserMessageType::CONTINUE:
    valid_msg = true;
      break;
    
    default:
      break;
  }

  return valid_msg;
}