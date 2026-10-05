MULTI-PROCESS CPU SIMULATOR & IPC
                         ARCHITECTURE

                              START
                                │
                                ▼
                     ┌───────────────────┐
                     │    UI PROCESS     │
                     │      ui.c         │
                     │                   │
                     │ Get User Input    │
                     │ Instruction +     │
                     │ Value 1 + Value 2 │
                     └─────────┬─────────┘
                               │
                               │ POSIX
                               │ MESSAGE QUEUE
                               ▼
                     ┌───────────────────┐
                     │    CORE PROCESS   │
                     │      core.c       │
                     │                   │
                     │ Receive Message   │
                     │        │          │
                     │        ▼          │
                     │   CPU (cpu.c)     │
                     │ ADD/SUB/MUL/DIV   │
                     └─────────┬─────────┘
                               │
                    ┌──────────┼──────────┐
                    │          │          │
                    ▼          ▼          ▼
              ┌─────────┐ ┌─────────┐ ┌─────────┐
              │ MEMORY  │ │  STACK  │ │  QUEUE  │
              │memory.c │ │ stack.c │ │ queue.c │
              │ Store   │ │  Push   │ │ Enqueue │
              │ Result  │ │ Result  │ │ Result  │
              └─────────┘ └─────────┘ └─────────┘
                    │          │          │
                    └──────────┼──────────┘
                               │
                               ▼
                     ┌───────────────────┐
                     │  CREATE LOG       │
                     │     MESSAGE       │
                     │ Status + Result + │
                     │     Message       │
                     └─────────┬─────────┘
                               │
                               │ POSIX
                               │ MESSAGE QUEUE
                               ▼
                     ┌───────────────────┐
                     │  LOGGER PROCESS   │
                     │     logger.c      │
                     │                   │
                     │ Receive Message   │
                     │        │          │
                     │        ▼          │
                     │ Display Output    │
                     └─────────┬─────────┘
                               │
                               ▼
                     ┌───────────────────┐
                     │   FINAL RESULT    │
                     │ SUCCESS / ERROR   │
                     │ Message + Result  │
                     └─────────┬─────────┘
                               │
                               ▼
                              END



      The UI Process accepts the instruction and input values from the user and sends them to the Core Process using POSIX Message Queues. The Core Process receives the message and executes the instruction using the CPU module. The calculated result is then handled by the Memory, Stack, and Queue modules. After execution, the Core creates a LogMessage containing the status, result, and message, and sends it to the Logger Process through another POSIX Message Queue. Finally, the Logger displays the execution status and result.
IPC technique used: POSIX Message Queues (mq_open(), mq_send(), mq_receive(), mq_close()).
