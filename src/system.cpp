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

  std::cout << "System::OnInit():" << std::endl;
  
  // std::cout << "\t_elevators:\t" << &_elevators << std::endl;

  // auto begin = _elevators.begin();
  // auto end = _elevators.end();

  // std::cout << "\tbegin:\t" << &(*begin) << std::endl;
  // std::cout << "\tend:\t" << &(*end) << std::endl;

  // Test();

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
        _msgs.emplace( user_msg, this );   // calls UserMessage Constructor
      }
    }
    cmd = "";   // reset input command

    // parse all incoming messages (up to "continue" statement )
    ParseMessageQueue();

    // do individual elevator tasks
    SystemTaskManager();
    std::cout << "\n";
  }
}

void System::ParseMessageQueue() {

  // de-queue all messages in system message queue
  while( !_msgs.empty() ) {
    // get next message off the top of the queue
    UserMessage& msg = _msgs.front();
    std::cout << "msg received: " << msg.GetMsg() << std::endl;

    // check to see if message syntax is valid
    if( msg.IsValid() ) {
      std::cout << "message valid" << std::endl;

      // message syntax is valid - send message to elevator
      SendMessageToElevator(msg);
    }
    else {
      std::cout << "message invalid" << std::endl;
    }

    // remove element from front of queue
    _msgs.pop();
  }
  std::cout << "\n";
}

void System::SendMessageToElevator(UserMessage msg) {
  
  for( auto it = _elevators.begin(); it != _elevators.end(); it++ ) {
    if( (*it).GetID().compare( msg.GetEID() ) == 0 ) {
      (*it).AddTask( msg ); // send message / task to elevator
    }
  }
}

bool System::AddElevator(std::string name, double payload) {

  if( payload >= 0.0 ) {
    _elevators.emplace_back(name, payload, this);
    return true;
  }
  else {
    std::cout << "Cannot add new elevator with negative max load" << std::endl;
    return false;
  }
}

void System::SystemTaskManager() {

  for( auto it = _elevators.begin(); it != _elevators.end(); it++ ) {
    (*it).ElevatorTaskManager();
  }

}

void System::Test() {

  std::cout << "\nSystem::Test()" << std::endl;

  std::vector<std::string> names{"E1", "E2", "E3"};

  int i = 0;
  for( auto name : names ) {
    _elevators.emplace_back(name, i*100.0, this);
    i++;
  }

  /* RANGE-BASED FOR LOOPS:
  * The range-based for loop creates an object of type Elevator as a
  * place-holder for each element of _elevators. As _elevators is iterated
  * through, that address of elevator never changes.
  */

  std::cout << "\trange-based for loop" << std:: endl;
  for( auto elevator : _elevators ) {
    std::cout << "\televator " << elevator.GetID() << " at\t"
      << &elevator << std::endl;
  }

  auto begin = _elevators.begin();
  auto end = _elevators.end();

  std::cout << "\n\tbegin:\t" << &(*begin) << std::endl;
  std::cout << "\tend:\t" << &(*end) << std::endl;

  /* ITERATOR-BASED FOR LOOPS:
  * The iterator based for loop uses an iterator object to loop through the
  * **actual** elements of _elevators without creating a temporary Elevator
  * object as in the range-based for loop case. In this case, the actual address
  * of each element of _elevators is printed.
  */

  // Q: Why does end (see above) not match the address of the last Elevator ebject
  //in  _elevators printed below?

  std::cout << "\n\titerator for loop" << std::endl;
  for( auto it = _elevators.begin(); it != _elevators.end(); it++) {
    std::cout << "\televator " << (*it).GetID() << " at\t" << &(*it) << std::endl;
  }

  UserMessage msg("message", this);
  msg.Test();
}