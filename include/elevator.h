
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

#include <string>

enum class ElevatorStatus {
  MOVING_UP,
  MOVING_DOWN,
  STATIONARY
};


class Elevator
{
  private:
    int id_;
    double max_weight_;
    double current_weight_;
    std::string current_floor_;
    ElevatorStatus status_;

    std::queue<UserMessage> tasks_;

  public:
    Elevator(int id, double max_weight) : id_(id), max_weight_(max_weight) {}

    ElevatorStatus status();
    bool call(std::string floor);
};