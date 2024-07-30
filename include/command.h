
#pragma once
/**
 * @file command.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2024-07-29
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include <iostream>
#include <string>

// TODO: Maybe place the elevator commands within the Elevator:: namespace?
enum class ElevatorCommandType {
  STATUS,
  CALL,
  ENTER,
  EXIT
};

/**
 * @brief The Elevator command base type. This type should:
 * 
 * 1. Serve as the base type for all other ElevatorCommand types.
 * 2. Not be able to to instantiated itself.
 * 3. (Maybe) Define a virtual method call "execute" which executes the command.
 */
class ElevatorCommand {
  protected:
    std::string _eid{""};
    ElevatorCommandType _type;

    // A non-owning reference to the elevator (TODO: convert to std::weak_ptr)
    Elevator* _elevator;

  public:
      ElevatorCommand(std::string& eid, ElevatorCommandType type, Elevator* elevator) : 
        _eid{eid}, _type{type}, _elevator{elevator} {};

      // A pure virtual method should prevent an ElevatorCommand object from
      // being instantiated.
      virtual bool execute();

    // Elevator ID (eid) getter.
    const std::string& eid() const { return _eid; }

    // Elevator Command Type getter.
    const ElevatorCommandType& type() const { return _type; }

    // Elevator getter (a const pointer to a const Elevator)
    const Elevator* const elevator() const { return _elevator; }

};

class ElevatorStatusCommand : protected ElevatorCommand {
  public:
    ElevatorStatusCommand(std::string& eid, Elevator* elevator) :
      ElevatorCommand(eid, ElevatorCommandType::STATUS, elevator) {}
    
    bool execute() {
      std::string& result = this->elevator().status();
      std::cout << result; }
};

class ElevatorCallCommand : protected ElevatorCommand {
  public:
    ElevatorCallCommand(std::string& eid, Elevator* elevator) :
      ElevatorCommand(eid, ElevatorCommandType::CALL, elevator) {}
    
    bool execute() { this->elevator().call(); }
};