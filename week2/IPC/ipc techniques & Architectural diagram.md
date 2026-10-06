IPC TECHNIQUES USED

POSIX MESSAGE QUEUES

The project uses POSIX Message Queues as the main IPC technique.
They allow separate processes to communicate by sending and receiving messages
without directly sharing their memory.

1. UI TO CORE

Queue Name: /ui_to_core

The UI Process collects the instruction and input values from the user.
It creates a CoreMessage containing the command, instruction, Value 1 and Value 2.

The message is sent to the Core Process using mq_send().
The Core Process receives the message using mq_receive().

This allows the UI Process to pass user input to the Core Process.

2. CORE TO LOGGER

Queue Name: /core_to_logger

After executing the instruction, the Core Process prepares a LogMessage.
It contains the execution status, result and message.

The Core Process sends this information to the Logger Process using mq_send().
The Logger Process receives the message using mq_receive() and displays the result.

This allows the Logger Process to record the execution information
without directly interacting with the Core Process.

IPC FUNCTIONS USED

• mq_open() – Creates or opens a message queue
• mq_send() – Sends a message between processes
• mq_receive() – Receives a message from the queue
• mq_close() – Closes the message queue
• mq_unlink() – Removes the message queue

HEADER USED

mqueue.h



ARCHITECTURAL DIAGRAM

┌───────────────┐
│   UI PROCESS  │
│               │
│ Instruction   │
│ Value 1       │
│ Value 2       │
└───────┬───────┘
        │
        │ /ui_to_core
        │ POSIX Message Queue
        ▼
┌───────────────────────────┐
│       CORE PROCESS        │
│                           │
│  ┌─────────────────────┐  │
│  │        CPU          │  │
│  │ Execute Instruction │  │
│  └─────────────────────┘  │
│                           │
│  ┌─────────────────────┐  │
│  │       MEMORY        │  │
│  │     Store Result    │  │
│  └─────────────────────┘  │
│                           │
│  ┌─────────────────────┐  │
│  │       STACK         │  │
│  │     Push Result     │  │
│  └─────────────────────┘  │
│                           │
│  ┌─────────────────────┐  │
│  │       QUEUE         │  │
│  │   Enqueue Result    │  │
│  └─────────────────────┘  │
└────────────┬──────────────┘
             │
             │ /core_to_logger
             │ POSIX Message Queue
             ▼
┌──────────────────────┐
│    LOGGER PROCESS    │
│                      │
│ Status               │
│ Message              │
│ Result               │
└──────────────────────┘
