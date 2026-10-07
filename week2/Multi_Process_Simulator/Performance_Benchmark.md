## Benchmark Objective
 
The purpose of this benchmark is to evaluate the performance of the Multi-Process Simulator and compare it with a Standalone Single-Process Simulator. 
 
The Standalone Simulator performs CPU, Memory, Stack and Queue operations within one process. 
 
The Multi-Process Simulator separates these functions into three independent processes: UI Process, Core Process and Logger Process. 
 
--- 
 
## Experimental Setup
 
* **Operating System:** Ubuntu Linux 
* **Standalone Simulator:** Single-process implementation 
* **Multi-Process Simulator:** UI Process, Core Process and Logger Process 
* **IPC Technique:** POSIX Message Queues 
* **Programming Language:** C 
* **Benchmark Tool:** `/usr/bin/time -v` 
* **CPU Operations:** ADD, SUBTRACT, MULTIPLY, DIVIDE 
* **Memory Operations:** STORE, LOAD 
* **Stack Operations:** PUSH, POP, PEEK 
* **Queue Operations:** ENQUEUE, DEQUEUE, QUEUE PEEK 
 
--- 
 
## Performance Metrics
 
The following performance metrics were considered: 
 
* Execution Time 
* CPU Usage 
* Memory Usage 
* IPC Communication 
* Process Separation 
* Process Management Overhead 
 
--- 
 
## IPC Methods Tested
 
The Multi-Process Simulator uses **POSIX Message Queues** for communication between the UI, Core and Logger processes. 
 
The communication flow is: 
 
**UI Process → Core Process → Logger Process** 
 
The message queues used are: 
 
* `UI_TO_CORE` 
* `CORE_TO_UI` 
* `CORE_TO_LOGGER` 
 
The UI sends commands to the Core process. 
 
The Core process performs the required CPU, Memory, Stack or Queue operation and sends the result back to the UI and Logger. 
 
--- 
 
## Measured Performance
 
### Multi-Process Simulator 
 
The three processes were measured separately using `/usr/bin/time -v`. 
 
| Parameter | UI Process | Core Process | Logger Process | 
|---|---:|---:|---:| 
| Execution Time | **35.31 seconds** | **29.21 seconds** | **23.98 seconds** | 
| CPU Usage | **0%** | **0%** | **0%** | 
| Maximum Memory | **1784 KB** | **1660 KB** | **1656 KB** | 
| User CPU Time | 0.00 s | 0.00 s | 0.00 s | 
| System CPU Time | 0.00 s | 0.00 s | 0.00 s | 
| Exit Status | 0 | 0 | 0 | 
 
### Standalone Single-Process Simulator 
 
The Standalone Simulator was tested using the following operations: 
 
1. `ADD 12 13` 
2. `SUBTRACT 23 12` 
3. `MULTIPLY 12 4` 
4. `DIVIDE 12 2` 
 
The results were: 
 
* ADD = **25** 
* SUBTRACT = **11** 
* MULTIPLY = **48** 
* DIVIDE = **6** 
 
| Parameter | Result | 
|---|---:| 
| Execution Time | **23.99 seconds** | 
| CPU Usage | **0%** | 
| User CPU Time | **0.00 seconds** | 
| System CPU Time | **0.00 seconds** | 
| Maximum Memory | **1912 KB** | 
| Exit Status | **0** | 
 
--- 
 
## Observed Execution
 
The Standalone Simulator successfully executed the following operations: 
 
1. `ADD 12 + 13 = 25` 
2. `SUBTRACT 23 - 12 = 11` 
3. `MULTIPLY 12 × 4 = 48` 
4. `DIVIDE 12 ÷ 2 = 6` 
 
The Multi-Process Simulator uses the same simulator operations through separate UI, Core and Logger processes. 
 
The Core process performs the actual operations and sends the results to the UI and Logger using POSIX Message Queues. 
 
The Logger process successfully receives the results from the Core process and displays the execution information. 
 
--- 
 
## Architecture Comparison
 
| Parameter | Standalone Single-Process Simulator | Multi-Process Simulator | 
|---|---|---| 
| Architecture | Single process | 3 independent processes | 
| UI | Same process | Separate UI process | 
| Core | Same process | Separate Core process | 
| Logger | Same process | Separate Logger process | 
| Execution Time | **23.99 seconds** | UI: **35.31 s** | 
|  |  | Core: **29.21 s** | 
|  |  | Logger: **23.98 s** | 
| CPU Usage | **0%** | **0% for each process** | 
| Maximum Memory | **1912 KB** | UI: **1784 KB** | 
|  |  | Core: **1660 KB** | 
|  |  | Logger: **1656 KB** | 
| IPC | Not required | POSIX Message Queues | 
| Process Independence | Low | High | 
| Modularity | Lower | Higher | 
 
--- 
 
## Communication Overhead
 
The Standalone Simulator does not require IPC because all components execute inside a single process. 
 
The Multi-Process Simulator requires communication between the UI, Core and Logger processes using POSIX Message Queues. 
 
Therefore, the Multi-Process Simulator introduces additional IPC and process-management overhead. 
 
The exact numerical IPC overhead was not calculated because the UI, Core and Logger processes were measured separately. 
 
The three process execution times should not be added together because the processes can execute concurrently and their elapsed times can overlap. 
 
--- 
 
## Final Findings
 
The benchmark demonstrates the difference between the Standalone Single-Process Simulator and the Multi-Process Simulator. 
 
The Standalone Simulator performs all CPU, Memory, Stack and Queue operations inside one process without requiring IPC. It recorded an execution time of **23.99 seconds** and a maximum memory usage of **1912 KB**. 
 
The Multi-Process Simulator separates the system into three independent processes: UI, Core and Logger. The processes communicate using **POSIX Message Queues**. 
 
The measured execution times were: 
 
* **UI Process:** 35.31 seconds 
* **Core Process:** 29.21 seconds 
* **Logger Process:** 23.98 seconds 
 
The Multi-Process Simulator requires additional process coordination and IPC communication, which introduces overhead compared with the Standalone Simulator. 
 
However, the Multi-Process architecture provides better **process separation, modularity, independent operation and practical IPC implementation**. 
 
For the current project, the Multi-Process Simulator successfully achieves the required functionality using **POSIX Message Queues**.
