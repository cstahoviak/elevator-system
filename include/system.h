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

// NOTE: It's not sufficient to forward-declare the Elevator type to be able to
// use it in a collection (std::unordered_map). We must provide the type
// definition so that the compiler understands how much memory, etc. to use for
// each object in the collection.
// https://stackoverflow.com/questions/60141413/field-has-incomplete-type-error-during-stdunordered-map-type-object-declarat
#include "elevator.h"
#include "floor.h"
#include "message.h"

#include <map>
#include <queue>
#include <string>
#include <unordered_map>

// Forward-delcare some classes.
// class Elevator;
class UserMessage;

class ElevatorSystem
{
  public:
    ElevatorSystem() = default;
    void run();

    // Getters
    const std::unordered_map<std::string, Elevator>& elevators() {
      return _elevators;
    }

  private:
    // Store a queue of input messages from the user (FIFO)
    std::queue<UserMessage> _msgs;
    // TODO: Maybe the value should be a unique pointer instead of an Elevator obj?
    std::unordered_map<std::string, Elevator> _elevators;

    void _parse_message_queue();
    void _task_manager();
};