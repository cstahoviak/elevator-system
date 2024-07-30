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
#include <unordered_map>

class ElevatorSystem
{
  public:
    enum class Floor {
      B2,   // basement 2
      B1,   // basement 1
      UB,   // not sure what this is supposed to stand for
      L,    // lobby
      ONE,
      TWO,
      THREE,
      P     // penthouse
    };

    ElevatorSystem() = default;
    void run();

    // Getters
    Floor str_to_floor(std::string& floor) { return _floors.at(floor); }

  private:
    // Store a queue of input messages from the user (FIFO)
    std::queue<UserMessage> _msgs;
    // TODO: Maybe the value should be a unique pointer instead of an Elevator obj?
    std::unordered_map<std::string, Elevator> _elevators;

    void _parse_message_queue();
    void _task_manager();

    // Store a mapping between floors as strings and floor as Floors
    std::map<std::string, Floor> _floors {
      {"B2", Floor::B2},
      {"B1", Floor::B1},
      {"UB", Floor::UB},
      {"L", Floor::L},
      {"1", Floor::ONE},
      {"2", Floor::TWO},
      {"3", Floor::THREE},
      {"P", Floor::P}
    };
};