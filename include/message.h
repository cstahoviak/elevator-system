#pragma once
/**
 * @file message.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2024-07-28
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include "system.h"

#include <iostream>

enum class UserMessageType {
  ADD,
  CALL,
  STATUS,
  ENTER,
  EXIT,
  CONTINUE,
  INVALID
};

class UserMessage
{
  private:
    // The input message from the user
    std::string _msg{""};
    // The message base command, e.g. "add", "call", "status"
    std::string _cmd{""};
    // The elevator ID
    std::string _eid{""};
    // The value associated with the specific command
    std::string _value;

    // A non-owning reference to the system (TODO: Convert to weak pointer)
    ElevatorSystem* _system;

    UserMessageType _type;

  public:

    UserMessage(std::string msg, ElevatorSystem* system);

    UserMessageType resolve_command();

    const std::string& eid() const { return _eid; }
    const std::string& value() const { return _value; }

    const UserMessageType& type() const { return _type; }


    bool is_valid() const {
      if (_type == UserMessageType::CONTINUE) { return false; }
      if (_type == UserMessageType::INVALID) { return false; }

      return true;
    }

};