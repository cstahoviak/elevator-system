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

#include <string>

// TODO: Place the elevator commands within the Elevator:: namespace

enum class ElevatorCommandType {
  CALL,
  STATUS,
  ENTER,
  EXIT
};

class ElevatorCommand {
  private:
    std::string _eid{""};
    ElevatorCommandType _type;

  public:
    const std::string& eid() const { return _eid; }
    const std::string& type() const { return _type; }

    
};

class ElevatorStatusCommand : ElevatorCommand {
  private
}

class ElevatorCallCommand : ElevatorCommand {
  private:
    

};