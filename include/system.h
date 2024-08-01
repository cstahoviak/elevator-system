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
#include <mutex>
#include <queue>
#include <string>
#include <unordered_map>

/**
 * @brief The elevator system class. This serves as the top-level entity of our
 * system.
 * 
 * TODO: Should this class be a singleton?
 */
class ElevatorSystem
{
  public:
    ElevatorSystem() = default;
    void run();

    // Getters
    // TODO: Should this be const? See link below on C++ getters and setters
    // https://stackoverflow.com/questions/51615363/how-to-write-c-getters-and-setters
    const std::unordered_map<std::string, Elevator>& elevators() {
      return _elevators;
    }
    const Floors& floors() const { return _floors; }
    std::mutex& mutex() { return _mutex; } 

  private:
    // Store a queue of input messages from the user (use as FIFO)
    std::queue<UserMessage> _msgs;
    // TODO: Maybe the value should be a unique pointer instead of an Elevator obj?
    std::unordered_map<std::string, Elevator> _elevators;
    // Store a Floors instance
    const Floors _floors;

    // Mutex used for thread-safe console logging
    std::mutex _mutex;

    void _parse_message_queue();
    void _task_manager();
    void _show_instructions();
};