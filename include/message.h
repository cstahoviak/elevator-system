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

#include <memory>
#include <string>
#include <vector>

// Forward declarations (for non-owning pointers)
class ElevatorCommand;
class ElevatorSystem;
class Elevator;

/**
 * @brief
 * 
 * TODO: Does it make more sense for this to be within the UserMessage class?
 * What design decision are we making when choosing to place it either within
 * or outside of the associated class?
 */
enum class UserMessageType {
  ADD,
  STATUS,
  CALL,
  ENTER,
  EXIT,
  CONTINUE,
  INVALID
};

class UserMessage
{
  public:
    UserMessage(std::string& msg, ElevatorSystem* system);

    std::unique_ptr<ElevatorCommand> create_command(Elevator* elevator) const;
    bool is_valid() const { return _is_valid; };

    // Getters
    const std::string& msg() const { return _msg; }
    const std::string& eid() const { return _eid; }
    const std::vector<std::string>& args() const { return _args; }
    const UserMessageType& type() const { return _type; }

  private:
    // The input message from the user
    std::string _msg{""};
    // The message base command, e.g. "add", "call", "status"
    std::string _cmd{""};
    // The elevator ID
    std::string _eid{""};
    // A vector of string args to pass to the associated command
    std::vector<std::string> _args;
    // Is the command valid?
    bool _is_valid{false};

    UserMessageType _type{UserMessageType::INVALID};

    // A non-owning reference to the system (TODO: Convert to weak pointer)
    ElevatorSystem* _system;

    // Determines if the message is valid (called by the ctor)
    bool _validate_message();
};