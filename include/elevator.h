
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
#include "floor.h"

#include <chrono>
#include <map>
#include <memory>
#include <queue>
#include <string>

// Forward declarations
// class ElevatorSystem;


class Elevator
{
  public:
    enum class Status {
      MOVING_UP,
      MOVING_DOWN,
      STATIONARY
    };
    
    // Elevator constructor
    Elevator(std::string& id, double max_weight) : 
      _id(id), _max_weight(max_weight) {}

    // The essential functions of an elevator (both return a result bool and a
    // result string)
    std::tuple<bool, std::string> status();
    std::tuple<bool, std::string> call(std::string& destination);

    void add_command(std::unique_ptr<ElevatorCommand> cmd);
    void task_manager();

    // Getters
    const Floors::Name& current_floor() const { return _current_floor; }
    const Floors::Name& destination_floor() const { return _destination_floor; }

    const std::map<Status, std::string> status_to_str {
      {Status::MOVING_UP, "moving-up"},
      {Status::MOVING_DOWN, "moving-down"},
      {Status::STATIONARY, "stationary"},
    };
  
  private:
    std::string _id;
    double _max_weight;
    double _current_weight;

    // Store the floors of the elevator system
    Floors _floors;

    // All elevators start at the lowest level.
    Floors::Name _current_floor{Floors::Name::B2};
    Floors::Name _destination_floor;
    Status _status{Status::STATIONARY};
    bool _status_stale = true;

    // How long (in ms) it takes an elevator to traverse a single floor.
    std::chrono::milliseconds _floor_traverse_time_ms{1000};

    // Store a queue of current commands (FIFO)
    std::queue<std::unique_ptr<ElevatorCommand>> _commands;

    void _update_status();
};