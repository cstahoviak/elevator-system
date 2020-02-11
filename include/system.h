#ifndef SYSTEM_H_
#define SYSTEM_H_

#include <vector>
#include <queue>

#include "elevator.h"
#include "user_message.h"

class System {
  private:
    std::queue<UserMessage> _msgs;   // incoming messages from user (FIFO)
    std::vector<Elevator> _elevators;
    
    // floor elements listed from bottom of building to top
    std::vector<std::string> _floors = {
      "B2",   // basement 2
      "B1",   // basement 1
      "UB",   // not sure what this is supposed to stand for
      "L",    // lobby
      "1",
      "2",
      "3",
      "P"     // penthouse
    };

    void ParseMessageQueue();                     // parse incoming user messages
    void SendMessageToElevator(UserMessage msg);  // send valid messages to elevators
    void SystemTaskManager();                     // call ElevatorTaskManager() for each elevator

  public:
    System();
    void OnInit();
    void Test();

    // getter functions
    const std::vector<std::string>& GetFloors() const { return _floors; }
    const std::vector<Elevator>& GetElevators() const { return _elevators; }

    bool AddElevator(std::string name, double payload);   // true -> request successful
                                                          // false -> request failed

};

#endif