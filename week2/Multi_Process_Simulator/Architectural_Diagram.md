Markdown

# Multi-Process Simulator – Architectural Diagram

## Architecture Overview

The Multi-Process Simulator consists of three independent processes: UI, Core, and Logger. These processes communicate using Unix Domain Sockets, POSIX Message Queues, and FIFOs (Named Pipes).

- **UI Process:** Accepts user input, sends operation requests to Core, and displays the results received from Core.
- **Core Process:** Processes requests and manages CPU operations, memory, stack, and queue.
- **Logger Process:** Receives and displays execution log messages from Core.

## Architecture Diagram

```text
                              USER
                                |
                                v
                   +--------------------------+
                   |        UI PROCESS        |
                   |--------------------------|
                   | Accept User Input        |
                   | Select Operation         |
                   | Send Operation Request   |
                   +------------+-------------+
                                |
                                | Unix Domain Socket
                                | UI --> Core
                                v
                   +--------------------------+
                   |       CORE PROCESS       |
                   |--------------------------|
                   | Process Requests         |
                   | CPU / Arithmetic         |
                   | Memory Management        |
                   | Stack Management         |
                   | Queue Management         |
                   +------------+-------------+
                                |
                    +-----------+-----------+
                    |                       |
                    | POSIX Message Queue   | FIFO / Named Pipe
                    | Core --> UI           | Core --> Logger
                    |                       |
                    v                       v
       +--------------------------+  +--------------------------+
       |        UI PROCESS        |  |      LOGGER PROCESS      |
       |       (Same UI)          |  |--------------------------|
       |--------------------------|  | Receive Log Messages     |
       | Receive Response         |  | Display Operation Logs   |
       | Display Status           |  | Display Results/Details  |
       | Display Result           |  |                          |
       +--------------------------+  +--------------------------+

```

**Note:** The UI Process appears twice in the diagram to show the two communication paths. Both UI boxes represent the same process.

## Working Flow

1. The user selects an operation and enters the required input through the UI.
2. The UI sends the operation request to Core through a Unix Domain Socket.
3. Core processes the request and performs the required arithmetic, memory, stack, or queue operation.
4. Core sends the response to the UI through a POSIX Message Queue.
5. Core sends execution log messages to Logger through a FIFO (Named Pipe).
6. The UI displays the operation status and result, while Logger displays execution log messages.

## IPC Mechanisms

| IPC Mechanism | Communication | Purpose |
|---|---|---|
| Unix Domain Socket | UI → Core | Transfers operation requests |
| POSIX Message Queue | Core → UI | Transfers responses and results |
| FIFO (Named Pipe) | Core → Logger | Transfers execution log messages |

## Conclusion

The Multi-Process Simulator uses three IPC mechanisms to enable communication between the UI, Core, and Logger processes. Unix Domain Sockets transfer requests, POSIX Message Queues return responses, and FIFOs transfer execution logs.
