#ifndef SYSTEM_H_
#define SYSTEM_H_

#include <vector>
#include <queue>

#include "elevator.h"
#include "user_message.h"

/* Q: Is there a more appropriate STL container type for _elevators and _floors?

* _elevators can be added to, but not removed from, and the member variables of
* the Elevator elements will be changed during operation, e'g. the _currentFloor
* _currentLoad will vary. I also need to be able to iterate through the elements of
* _elevators, e.g. for call the ElevatorTaskManager() for each elevator.
*
* _floors is set when the System object is instantiated and never changes - elements
* will not be added or removed (ever). I need to be able to check whether or not a
* spcific value exists in _floors to know if a given "call" command is valid - see
* the _call case of the switch statement in UserMessage::IsValid() for an example of
* how this is currently done.
*/

class System {
  private:
    std::queue<UserMessage> _msgs;      // incoming messages from user (FIFO)
    std::vector<Elevator> _elevators;   // is there a more approp. STL container?

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
    void SystemTaskManager();                     // call ElevatorTaskManager() for each elevator
    void SendMessageToElevator(UserMessage msg);  // send valid messages to elevators

  public:
    void Init();
    void Test();

    // getter functions
    /* NOTE: the "const" keyword before the return type indicates that the method
    *  will return a const reference to type T (std::vector<std::string> in this
    *  case). The "const" keyword after the method name indicates that the member
    *  function will NOT modify the object on which it's called.
    */
    const std::vector<std::string>& GetFloors() const { return _floors; }
    const std::vector<Elevator>& GetElevators() const { return _elevators; }

    void AddElevator(std::string name, double payload);   // true -> request successful
                                                          // false -> request failed

};

#endif