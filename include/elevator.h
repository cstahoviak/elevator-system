#ifndef ELEVATOR_H_
#define ELEVATOR_H_

#include <string>
#include <vector>
#include <queue>

#include "user_message.h"

class System;   // forward delcaration

class Elevator {
  private:
    std::string _id{""};
    double      _maxLoad{0.0};
    double      _currentLoad{0.0};

    std::string _currentFloor{"B2"};      // all elevators start at the lowest floor by default
    std::string _destinationFloor{"B2"};

    std::queue<UserMessage> _task_queue;
    bool _busy{false};                // elevator will continue to next task when not busy

    System* _system;  // non-owning reference to the System object

  public:
    Elevator(std::string id, double payload, System* system) : _id(id),
                                                              _maxLoad(payload),
                                                              _system(system) {}

    void ElevatorTaskManager();

    std::string GetStatus();
    bool CallToFloor(std::string floor);
    void MoveElevator();
    bool Continue();

    // getter/ setter functions
    std::string GetID() {return _id; }
    double GetMaxLoad() { return _maxLoad; }
    double GetCurrentLoad() { return _currentLoad; }
    void AddTask(UserMessage msg) { _task_queue.push(msg); }

    // Bonus
    bool Enter();   // will likely need to set _currentLoad
    bool Exit();    
};

#endif