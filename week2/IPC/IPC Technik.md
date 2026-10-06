Inter-Process Communication (IPC)

The Multi-Process CPU Simulator uses POSIX Message Queues (mqueue) as its Inter-Process Communication (IPC) mechanism. The message queues enable independent processes to exchange structured data without directly accessing each other's memory.

IPC Architecture
┌─────────────────────────┐
│       UI PROCESS        │
│                         │
│ • Accepts instruction   │
│ • Accepts input values  │
│ • Creates CoreMessage   │
└────────────┬────────────┘
             │
             │ mq_send()
             │ /ui_to_core
             │ CoreMessage
             ▼
┌─────────────────────────┐
│      CORE PROCESS       │
│                         │
│ • Receives command      │
│ • Executes instruction  │
│ • Updates memory        │
│ • Uses stack and queue  │
│ • Creates LogMessage    │
└────────────┬────────────┘
             │
             │ mq_send()
             │ /core_to_logger
             │ LogMessage
             ▼
┌─────────────────────────┐
│     LOGGER PROCESS      │
│                         │
│ • Receives result       │
│ • Displays status       │
│ • Displays result       │
└─────────────────────────┘
Message Queues

Two POSIX message queues are used:

Message Queue	Direction	Purpose
/ui_to_core	UI → Core	Transfers instructions and input values
/core_to_logger	Core → Logger	Transfers execution status and results
Communication Process
The UI Process accepts an instruction such as ADD, SUB, MUL, or DIV, along with two input values.
The UI stores the information in a CoreMessage structure.
mq_send() sends the CoreMessage through /ui_to_core.
The Core Process receives the message using mq_receive().
The Core Process executes the requested instruction and processes the result using its CPU, memory, stack, and queue components.
The execution result and status are stored in a LogMessage structure.
mq_send() sends the LogMessage through /core_to_logger.
The Logger Process receives the message using mq_receive() and displays the execution status and result.
POSIX Message Queue Functions Used
mq_open() – Opens or creates a POSIX message queue.
mq_send() – Sends a message to another process through a message queue.
mq_receive() – Receives a message from a message queue.
mq_close() – Closes the message queue descriptor.
mq_unlink() – Removes the message queue when it is no longer required.
Data Structures Used for IPC
CoreMessage

Used for communication between the UI and Core processes.

typedef struct
{
    int command;
    int value1;
    int value2;
    char instruction[MAX_MESSAGE];
} CoreMessage;
LogMessage

Used for communication between the Core and Logger processes.

typedef struct
{
    int status;
    int result;
    char message[MAX_MESSAGE];
} LogMessage;
IPC Communication Flow
UI Process
    │
    │  CoreMessage
    │  mq_send()
    ▼
/ui_to_core
    │
    │  mq_receive()
    ▼
Core Process
    │
    │  LogMessage
    │  mq_send()
    ▼
/core_to_logger
    │
    │  mq_receive()
    ▼
Logger Process
IPC Technique

POSIX Message Queues (mqueue) are used as the IPC mechanism for communication between the UI, Core, and Logger processes.

