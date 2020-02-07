#ifndef SYSTEM_H_
#define SYSTEM_H_

#include <vector>
#include <queue>

#include "elevator.h"
#include "user_message.h"

class System {
  private:
    std::queue<UserMessage> _msg_queue;   // incoming messages from user (FIFO)
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

  public:
    System();
    void OnInit();

    // getter functions
    std::vector<std::string> GetFloors() { return _floors; }
    std::vector<Elevator> GetElevators() { return _elevators; } 

    bool AddElevator(std::string name, double payload);   // true -> request successful
                                                          // false -> request failed
    // void SetElevatorSystemHandle();

    void ParseMessageQueue();
    void SendMessageToElevator(UserMessage msg);
    void SystemTaskManager();


};

#endif