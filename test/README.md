# elevator-system Tests

## Notes from the GoogleTest Primer
The following are notes from the [GoogleTest Primer](https://google.github.io/googletest/primer.html).

### Creating a Simple Test
1. Both the TestSuiteName and the TestName cannot contain underscores.
2. Tests from different test suites can have the same individual name.
3. GoogleTest groups the test results by test suites, so logically related tests should be in the same test suite

  ```
  TEST(TestSuiteName, TestUserMessage) {
    // ... test body ...
  }
  ```

## Test Fixtures: Using the same data configuration across multiple tests.
If you find yourself writing two or more tests that operate on similar data, you can use a test fixture. This allows you to reuse the same configuration of objects for several different tests.

1. Derive a class from testing::Test
2. Start its body with protected:, as we’ll want to access fixture members from sub-classes.
3. If necessary, write a default constructor or SetUp() function to prepare the objects for each test.
4. If necessary, write a destructor or TearDown() function to release any resources you allocated in SetUp().

  ```
  class TestFixtureClassName : public testing::Test
  {
    protected:
      void SetUp() override;
  }
  ```

### A Simple Test that Uses a Test Fixture
1. When using a fixture, use TEST_F() instead of TEST() as it allows you to access objects and subroutines in the test fixture.
2. No test suite name is specified for this macro.
3. For each test defined with TEST_F(), GoogleTest will create a fresh test fixture at runtime, immediately initialize it via SetUp(), run the test, clean up by calling TearDown(), and then delete the test fixture.
4. GoogleTest does not reuse the same test fixture for multiple tests. Any changes one test makes to the fixture do not affect other tests.

  ```
  TEST_F(TestFixtureClassName, TestName) {
    ... test body ...
  }
  ```
