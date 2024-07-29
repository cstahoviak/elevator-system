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

    UserMessageType _type;

  public:
    UserMessage(std::string msg) : _msg(msg) {};
    UserMessageType type() { return _type; }

};