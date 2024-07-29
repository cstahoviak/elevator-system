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

#include <sstream>

UserMessage::UserMessage(std::string msg, ElevatorSystem* system) :
    _msg(msg), _system(system)
{
  // Extract the "command", "eid" and message "value" from the message
  std::istringstream stream(_msg);
  stream >> _cmd >> _eid >> _value;

  switch(_cmd)
  {
    case ("add"):
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
      /* code */
      break;

    case (UserMessageType::EXIT):
      /* code */
      break;

    case (UserMessageType::CONTINUE):
      /* code */
      break;
    
    default:
      break;
  }

  return is_valid;
}
