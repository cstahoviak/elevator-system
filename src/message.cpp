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

#include <iostream>
#include <sstream>
#include <string>

UserMessage::UserMessage(std::string msg, ElevatorSystem* system) :
    _msg(msg), _system(system)
{
  // Extract the "command", "eid" and message "value" from the message
  std::istringstream stream(_msg);
  std::string args_str;
  stream >> _cmd >> _eid >> args_str;

  // Unpack args string into vector
  // TODO: Does this work as expected?
  std::string arg;
  while(std::getline(std::stringstream(args_str), arg, ' ')) {
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

ElevatorCommand UserMessage::create_command() const
{
  switch (_type)
  {
  case (UserMessageType::ADD):
    std::cout << "Cannot create Elevator command from 'ADD' message."
      << std::endl;
    break;

  case (UserMessageType::STATUS):
    ElevatorStatusCommand cmd{_eid, _elevator};
    break;

  case (UserMessageType::CALL):
    /* code */
    break;

  case (UserMessageType::ENTER):
    /* code */
    break;

  case (UserMessageType::EXIT):
    /* code */
    break;

  case (UserMessageType::CONTINUE):
    std::cout << "Cannot create Elevator command from 'CONTINUE' message."
      << std::endl;
    break;
  
  default:
    break;
  }
}

bool UserMessage::is_valid() const
{
  bool is_valid = false;

  switch (_type)
  {
    case (UserMessageType::ADD):
      
      break;

    case (UserMessageType::CALL):
      /* code */
      break;

    case (UserMessageType::STATUS):
      /* code */
      break;

    case (UserMessageType::ENTER):
      // "enter" command not implemented yet.
      is_valid = false;
      break;

    case (UserMessageType::EXIT):
      // "enter" command not implemented yet.
      is_valid = false;
      break;

    case (UserMessageType::CONTINUE):
      is_valid = true;
      break;
    
    default:
    is_valid = false;
      break;
  }

  return is_valid;
}
