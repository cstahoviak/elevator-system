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

    std::queue<UserMessage> _tasks;   // tasks assigned to this elevator
    bool _busy{false};                // elevator will continue to next task when not busy

    System* _system;  // non-owning reference to the System object

    enum Status {
      _stationary,
      _up,
      _down
    };

    Status _status{_stationary};

    void UpdateStatus();                  // updates elevator status
    void GetStatus();                     // displays elevator status
    void CallToFloor(std::string floor);  // calls elevator to specific floor
    void MoveElevator();                  // moves elevator from _currentFloor to _destination Floor
    bool Continue();                      // unused

  public:
    Elevator(std::string id, double payload, System* system) : _id(id),
                                                              _maxLoad(payload),
                                                              _system(system) {}

    void ElevatorTaskManager();

    // getter/ setter functions
    // NOTE: the "const" keyword indicates that the member function will NOT modify
    // the object on which it's called
    std::string GetID() const { return _id; }
    double GetMaxLoad() const { return _maxLoad; }
    double GetCurrentLoad() const { return _currentLoad; }
    void AddTask(UserMessage msg) { _tasks.emplace(msg); }

    // Bonus
    bool Enter();   // will likely need to set _currentLoad
    bool Exit();    
};

#endif