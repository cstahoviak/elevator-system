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

    System* _system;    // non-owning reference to System object

    void ParseUserMessage();

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
    void Test();

    // getter / setter functions
    std::string GetMsg() const { return _msg; }
    std::string GetEID() const { return _eid; }
    std::string GetValue() const { return _value; }

    ValidCommands ResolveCommand();
    bool IsValid();
};

#endif