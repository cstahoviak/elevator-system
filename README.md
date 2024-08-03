# elevator-system

A Zoox technical interview question from Spring 2020.

## Problem Statement
Time limit: 1.5 hours.

Build an application that simulates an elevator system.
- User should be able to add elevators to the system.
- User should be able to see the status of an elevator.
- User should be able to call an elevator to a certain floor.
- The total number of floors and floor names should be hardcoded.
- All elevators by default start from the lowest floor.

Bonuses:
1. Add support for people getting in the elevators and requesting specific floors.
2. Add support for multiple elevators working in a coordinated manner to minimize passenger wait time.

Expectations:
- Modeling
- Definition of entities
- Clean, modular code for future extensibility

## Example Output

### Simple Example 1
```
add-elevator <elevator-id> <max-weight-supported-in-kgs>
status <elevator>
call-elevator <elevator-id> <floor-name>
enter-elevator <elevator-id> <total-weigh-in-kgs-entering> <space-separated-floor-names-requested>
exit-elevator <elevator-id> <weight-exiting>
continue <elevator-id>
```

### Detailed Example 1
The user should be able to add elevators.

__Commmand__: `add-elevator <elevator-id> <max-weight-supported-in-kgs>`\
__Example__: `add-elevator E1 200`\
__Response__: `success` if the request succeeds, `failure` if the request fails.

### Detailed Example 2
The user should be able to request the real-time status of an elevator.

__Commmand__: `status <elevator-id>`\
__Example__: `status E1 200`\
__Response__:
  - `moving-down 6 B1 0` - The elevator is moving down, is currently on the 6th floor, headed for B1 and has 0kg of weight on board.
  - `moving-up L 1 23` - The elevator is moving up, is on floor L, headed for the 1st floor and has 23kg of weight on board.
  - `stationary B1` - The elevator is at rest on floor B1.


### Detailed Example 3
The user should be able to call an elevator for a specific floor.

__Command__: `call-elevator <elevator-id> <floor-name>`\
__Example__: `call-elevator E1 B1`\
__Response(s)__: `success` if the request succeeds, `failure` if the request fails.

__Example Sequence of Commands__:
```
status E1 -> stationary 6
call-elevator E1 B1 -> success
call-elevator E1 B2 -> success
status E1 -> moving-down 6 B1 0
```

### Detailed Example 4
Do the next action for the elevator.

__Command__: continue <elevator-id>\
__Example__: `continue E1`

__Example Sequence of Commands__:
```
status E1 -> stationary 6
status E1 -> stationary 6
call-elevator E1 2 -> success
call-elevator E1 1 -> success
call-elevator E1 UB -> success
call-elevator E1 B1 -> success
status E1 -> moving-down 6 2 0
continue E1 (The current floor the elevator is at, should be 2 now)
status E1 -> stationary 2 (current floor is 2)
continue E1
status E1 -> moving down 2 1 0
continue E1 (The current floor the elevator is at, should be 1 now)
status E1 -> stationary 1 (current floor is 1)
continue E1
status E1 -> moving down 1 UB 0
continue E1 (The current floor the elevator is at, should be UB now)
status E1 -> stationary UB (current floor is UB)
continue E1
status E1 -> moving down UB B1 0
continue E1
status E1 -> stationary B1
```

### Detailed Example 5: Bonus
TODo: Add support for people getting in/out of the elevators and requesting floors.

## Building & Running the `elevator_system` Application

Clone the `elevator-system` repository locally.
  ```
  git clone https://github.com/cstahoviak/elevator-system.git
  ```

Build the `elevator_system application.
  ```
  cd elevator-system
  mkdir build
  cd build
  cmake ..
  make
  ```

Finally, run the `elevator_system` executable.
  ```
  ./elevator_system
  ```

The following instructions will be printed to the terminal, and the application will wait for user input to begin.

  ```
  The Elevator System Application.

  Valid commands are:
    add <elevator-id> <max-weight-kgs>
    status <elevator-id>
    call <elevator-id> <floor>
    continue

  Note that one or more 'add' commands must first be followed by a
  'continue' command before 'status' or 'call' commands can be issued
  for the added elevator(s).

  The Elevator System will accept messages from the user until a
  'continue' message is received. Once a 'continue' message is
  received, the Elevator System will dispatch all user messages to the
  corresponding elevator for each command to be executed.

  Example:
    add E1 125
    continue
    status E1
    call E1 1
    call E1 P
    status E1
    status E2 (expect to fail)
    continue

  Note that commands given to the system may not execute in the order
  in which they're received. Commands are routed to each elevator, and
  dispatch of those commands is handled asynchronously.

  User Input: 
  ```

