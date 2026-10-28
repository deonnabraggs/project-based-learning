# IPC TESTING REPORT

## 1. Objective

The objective of IPC testing is to verify that the UI, Core, and Logger processes communicate correctly using three IPC mechanisms: Unix Domain Socket, POSIX Message Queue, and FIFO (Named Pipe).

## 2. IPC Mechanisms Used

| IPC Mechanism       | Communication | File                 |
| ------------------- | ------------- | -------------------- |
| Unix Domain Socket  | UI → Core     | `ui.c`, `core.c`     |
| POSIX Message Queue | Core → UI     | `core.c`, `ui.c`     |
| FIFO (Named Pipe)   | Core → Logger | `core.c`, `logger.c` |

## 3. IPC Test Cases and Results

| Option | Test Case  | Test Input                    | Expected Output                      | Status |
| ------ | ---------- | ----------------------------- | ------------------------------------ | ------ |
| 1      | Add        | 12, 13                        | Result: 25                           | Pass   |
| 2      | Subtract   | 12, 3                         | Result: 9                            | Pass   |
| 3      | Multiply   | 12, 3                         | Result: 36                           | Pass   |
| 4      | Divide     | 12, 3                         | Result: 4                            | Pass   |
| 5      | Store      | Memory location: 0, Value: 50 | Value 50 stored in memory location 0 | Pass   |
| 6      | Load       | Memory location: 0            | Loaded value: 50                     | Pass   |
| 7      | Push       | Value: 25                     | Value 25 pushed onto the stack       | Pass   |
| 8      | Pop        | Remove the top stack value    | Value 25 popped from the stack       | Pass   |
| 9      | Peek       | Push 30, then peek            | Top stack value: 30                  | Pass   |
| 10     | Enqueue    | Value: 40                     | Value 40 added to the queue          | Pass   |
| 11     | Dequeue    | Remove the front queue value  | Value 40 removed from the queue      | Pass   |
| 12     | Queue Peek | Enqueue 50, then peek         | Front queue value: 50                | Pass   |
| 13     | Exit       | Select option 13              | Simulator exits successfully         | Pass   |

## 4. IPC Communication Tests

| Test                | Expected Behaviour                                                              | Status |
| ------------------- | ------------------------------------------------------------------------------- | ------ |
| UI → Core           | UI sends the selected operation and input values through the Unix Domain Socket | Pass   |
| Core → UI           | Core sends the operation result through the POSIX Message Queue                 | Pass   |
| Core → Logger       | Core sends operation logs through the FIFO                                      | Pass   |
| Process Termination | UI, Core, and Logger terminate correctly after the exit operation               | Pass   |

## 5. Test Summary

- Total test cases: 13
- Passed: 13
- Failed: 0

## 6. Conclusion

The Multi-Process Simulator uses three IPC mechanisms to communicate between the UI, Core, and Logger processes. The test cases cover arithmetic operations, memory storage and loading, stack operations, queue operations, and process termination. The expected results demonstrate how each operation should behave when the corresponding inputs and data-structure states are correct.
