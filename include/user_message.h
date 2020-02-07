#ifndef USER_MESSAGE_H_
#define USER_MESSAGE_H_

#include <string>
#include <vector>

class System;   // forward declaration

class UserMessage {
  private:
    std::string _msg{""};     // input message from user
    std::string _cmd{""};     // message base command
    std::string _eid{""};     // elevator ID
    std::string _value{""};   // value associated with specific command

    // std::vector<std::string> _valid_cmds {
    //   "status",
    //   "continue",
    //   "add",        // add-elevator
    //   "call"        // call-elevator
    //   "enter"       // enter-elevator
    //   "exit"        // exit-elevator
    // };

    System* _system;    // non-owning reference to System object

  public:
    enum ValidCommands {
      _status,
      _continue,
      _add,
      _call,
      _enter,
      _exit,
      _invalid
    };

    UserMessage(std::string msg, System* system) : _msg(msg), _system(system) {}

    // getter / setter functions
    // std::vector<std::string> GetValidCmds() { return _valid_cmds; }
    std::string GetEID() { return _eid; }

    void ParseUserMessage();
    ValidCommands ResolveCommand();
    bool IsValid();
};

#endif