
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

#include "system.h"

#include <queue>
#include <string>

class Elevator
{
  public:
    enum class Status {
      MOVING_UP,
      MOVING_DOWN,
      STATIONARY
    };
    
    // Elevator constructor
    Elevator(std::string id, double max_weight, ElevatorSystem* system) : 
      _id(id), _max_weight(max_weight), _system(system) {}

    // The essential functions of an elevator (both return a result string)
    std::ostringstream& status();
    std::ostringstream& call(std::string& destination);

    void add_command(std::unique_ptr<ElevatorCommand> cmd) { _commands.push(cmd); };
    void task_manager();

    // Getters
    const ElevatorSystem::Floor& current_floor() const { return _current_floor; }
    const ElevatorSystem::Floor& destination_floor() const { return _destination_floor; }

    std::map<Status, std::string> status_to_str {
      {Status::MOVING_UP, "moving-up"},
      {Status::MOVING_DOWN, "moving-down"},
      {Status::STATIONARY, "stationary"},
      };
  
  private:
    std::string _id;
    double _max_weight;
    double _current_weight;

    // All elevators start at the lowest level.
    ElevatorSystem::Floor _current_floor{ElevatorSystem::Floor::B2};
    ElevatorSystem::Floor _destination_floor;
    Status _status{Status::STATIONARY};
    bool _status_stale = true;

    // How long (in ms) it takes an elevator to traverse a single floor.
    std::chrono::milliseconds _floor_traverse_time_ms{1000};

    // Store a queue of current commands (FIFO)
    std::queue<std::unique_ptr<ElevatorCommand>> _commands;

    // Store a non-owning reference to the System (TODO: make std:weak_ptr)
    // TODO: Do I actually need this (not actually using it yet)?
    ElevatorSystem* _system;

    void _update_status();
};