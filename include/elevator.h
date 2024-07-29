
#pragma once
/**
 * @file elevator.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2024-07-28
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include "command.h"
#include "message.h"

#include <queue>
#include <string>

enum class ElevatorStatus {
  MOVING_UP,
  MOVING_DOWN,
  STATIONARY
};


class Elevator
{
  private:
    std::string _id;
    double _max_weight;
    double _current_weight;
    std::string _current_floor;
    ElevatorStatus _status;

    std::queue<ElevatorCommand> _commands;

    ElevatorStatus _status();
    bool _call(std::string floor);

  public:
    Elevator(std::string id, double max_weight) : 
      _id(id), _max_weight(max_weight) {}

    void create_command(const UserMessage& msg);
    void task_manager();

    
};