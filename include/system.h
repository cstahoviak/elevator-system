#pragma once
/**
 * @file system.h
 * @author your name (you@domain.com)
 * @brief The elevator System.
 * @version 0.1
 * @date 2024-07-28
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include "elevator.h"
#include "message.h"

#include <queue>
#include <string>
#include <vector>

class ElevatorSystem
{
  private:
    std::queue<UserMessage> _msgs;
    // TODO: Store vector of unique pointers instead of vector of Elevator objs.
    std::vector<Elevator> _elevators;

    void _parse_message_queue();
    void _task_manager();
    bool _add_message(UserMessage& msg) {_msgs.emplace}


    bool _add_elevator(int id, double max_weight);
    ElevatorStatus _status(int id);
    bool _call(int id, std::string floor);


  public:
    ElevatorSystem() = default;
    void run();    
};