/**
 * @file floor.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2024-07-31
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include "floor.h"

/**
 * @brief Overloads the string stream operator for an Floors::Name enum.
 * 
 * Takes a ostream reference and returns an ostream reference. Passing and
 * returning by value will cause errors.
 * 
 * @param stream 
 * @param floor 
 * @return std::ostream& 
 */
std::ostream& operator<<(std::ostream& stream, const Floors::Name& floor)
{
  switch ( floor ) {
    case (Floors::Name::B2):
      stream << "B2";
      break;

    case (Floors::Name::B1):
      stream << "B1";
      break;

    case (Floors::Name::UB):
      stream << "UB";
      break;

    case (Floors::Name::L):
      stream << "L";
      break;

    case (Floors::Name::ONE):
      stream << "ONE";
      break;

    case (Floors::Name::TWO):
      stream << "TWO";
      break;

    case (Floors::Name::THREE):
      stream << "THREE";
      break;

    case (Floors::Name::P):
      stream << "P";
      break;
    
    default:
      stream << "invalid floor";
      break;
  }

  return stream;
}