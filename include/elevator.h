#ifndef ELEVATOR_H_
#define ELEVATOR_H_

#include <string>
#include <vector>

class System;   // forward delcaration

class Elevator {
  private:
    std::string _id{""};
    double      _maxLoad{0.0};
    double      _currentLoad{0.0};

    std::string _currentFloor{0};     // all elevators start at the lowest floor by default
    std::string _destinationFloor{0};

    std::vector<std::string> _task_queue;
    bool _busy{false};                // elevator will continue to next task when not busy

    System* _system;  // non-owning reference to the System object

  public:
    Elevator(std::string id, double payload) : _id(id), _maxLoad(payload) {}
    std::string GetStatus();
    bool CallToFloor(std::string floor);
    bool Enter();
    bool Exit();
    bool Continue();

    void MoveElevator();
};

#endif