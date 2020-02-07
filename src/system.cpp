#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>  // std::find

#include "system.h"
#include "elevator.h"
#include "user_message.h"

System::System() {
  OnInit();
}

void System::OnInit() {
  std::string user_msg{""}, cmd{""};

  // main loop
  while( true ) {

    // take input from user until "continue" command is given
    while( cmd.compare("continue") != 0 ) {
      
      // take input from user
      std::cout << "User Input: ";
      getline(std::cin, user_msg);
      std::istringstream stream(user_msg);
      stream >> cmd;    // pull first word off input stream

      if( cmd.compare("continue") != 0 ) {
        _msg_queue.emplace( user_msg, this );   // calls UserMessage Constructor
      }
    }
    // parse all incoming messages (up to "continue" statement )
    ParseMessageQueue();

    // do individual elevator tasks
    SystemTaskManager();
  }

}

void System::ParseMessageQueue() {

  // de-queue all messages in system message queue
  while( !_msg_queue.empty() ) {
    // get next message off the top of the queue
    UserMessage msg = _msg_queue.front();

    // check to see if message syntax is valid
    if( msg.IsValid() ) {
      // message syntax is valid - send message to elevator
      SendMessageToElevator(msg);
    }

    // remove element from front of queue
    _msg_queue.pop();
  }
}

void System::SendMessageToElevator(UserMessage msg) {
  for( auto it = _elevators.begin(); it != _elevators.end(); ++it ) {
    if( (*it).GetID().compare( msg.GetEID() ) == 0 ) {
      (*it).AddTask( msg ); // send message / task to elevator
    }
  }
}

bool System::AddElevator(std::string name, double payload) {
  
  // all this below might not be necessary..
  // already accomplished by UserMessage::IsValid()

  for( auto iter =_elevators.begin(); iter != _elevators.end(); ++iter ) {
    if( (*iter).GetID().compare(name) == 0 ) {
      // elevator with this name already exists - failed to add elevator to _elevators
      std::cout << "Elevator " << name << " already exists with max payload "
        << std::to_string( (*iter).GetMaxLoad() ) << " kgs" << std::endl;
      return false;
    }
    else if( iter == _elevators.end() && payload >= 0.0 ) {
      // reached end of _elevators vector and none with _id "name" found
      _elevators.emplace_back(name, payload, this);
      // SetElevatorSystemHandle();
      return true;
    }
  }
}

void System::SystemTaskManager() {

  for( auto elevator : _elevators ) {
    elevator.ElevatorTaskManager();
  }

}

// void System::SetElevatorSystemHandle() {
//   auto it = _elevators.end();
//   (*it)._system = this;
// }