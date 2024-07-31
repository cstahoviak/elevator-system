#pragma once
/**
 * @file floor.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2024-07-31
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include <map>
#include <ostream>

class Floors
{
  public:
    enum class Name {
      B2,     // basement 2
      B1,     // basement 1
      UB,     // not sure what this is supposed to stand for
      L,      // lobby
      ONE,
      TWO,
      THREE,
      P       // penthouse
    };

    // Getters
    const std::map<std::string, Floors::Name>& floors() const { return _floors; }

    // Utility Function
    Floors::Name str_to_floor(std::string& floor) { return _floors[floor]; }

  private:
    // Store a mapping between floors as strings and floor as Floors
    std::map<std::string, Floors::Name> _floors {
      {"B2", Floors::Name::B2},
      {"B1", Floors::Name::B1},
      {"UB", Floors::Name::UB},
      {"L", Floors::Name::L},
      {"1", Floors::Name::ONE},
      {"2", Floors::Name::TWO},
      {"3", Floors::Name::THREE},
      {"P", Floors::Name::P}
    };
};

// Utility function
// friend Floors::Name str_to_floor(std::string& floor);
  
// Cannot extend the << operator as a member-function of a class - it has to be
// a seperate function. The implementation of this function MUST be in
// system.cpp otherwise I'll get a "multiple definition of operator<<" error
// because the implementation gets included in multiple translation units.
std::ostream& operator<<(std::ostream& stream, const Floors::Name& floor);