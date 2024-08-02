/**
 * @file test_message.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2024-08-01
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include <gtest/gtest.h>

// I don't think this is recommended, but it works for accessing private
// members of a class for the purpose of unit testing (do this only after
// including from STL and other dependencies).
#define private public

#include "system.h"
#include "message.h"

/**
 * @brief The UserMessage test fixture.
 * 
 */
class UserMessageTest : public testing::Test
{
  protected:
    void SetUp() override {
      // Add a default elevator to system
      std::string eid{"E0"};
      double max_weight{100};
      const auto& pair = 
        system._elevators.try_emplace(eid, eid, max_weight, &system);
    }

    // A UserMessage requires a reference to the system
    ElevatorSystem system;
};

TEST_F(UserMessageTest, TestContinueMessage) {
  std::string user_input{"continue"};
  UserMessage msg{user_input, &system};
  EXPECT_TRUE(msg.is_valid());
}

TEST_F(UserMessageTest, TestAddMessage) {
  std::string user_input1{"add E1"};
  std::string user_input2{"add E1 100"};

  UserMessage msg1{user_input1, &system};
  UserMessage msg2{user_input2, &system};

  // A valid "add" command requires both an elevator ID and a max weight
  EXPECT_FALSE(msg1.is_valid());
  EXPECT_TRUE(msg2.is_valid());
}

TEST_F(UserMessageTest, TestStatusMessage) {
  std::string user_input1{"status E0"};
  std::string user_input2{"add E1"};

  UserMessage msg1{user_input1, &system};
  UserMessage msg2{user_input2, &system};

  // Expect message 2 to fail because elevator "E1" hasn't added to the system
  EXPECT_TRUE(msg1.is_valid());
  EXPECT_FALSE(msg2.is_valid());
}

TEST_F(UserMessageTest, TestCallMessage) {
  // Call existing elevator E0 to a valid floor
  std::string user_input1{"call E0 P"};
  // Call existing elevator E0 to an invalid floor
  std::string user_input2{"call E0 4"};
  // Call non-existent elevator E0 to a valid floor
  std::string user_input3{"call E1 1"};

  UserMessage msg1{user_input1, &system};
  UserMessage msg2{user_input2, &system};
  UserMessage msg3{user_input3, &system};

  // Expect message 2 to fail because elevator "E1" hasn't added to the system
  EXPECT_TRUE(msg1.is_valid());
  EXPECT_FALSE(msg2.is_valid());
  EXPECT_FALSE(msg3.is_valid());
}