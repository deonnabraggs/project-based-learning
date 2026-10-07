
# IPC Techniques

## 1. Overview

The Multi-Process Simulator uses **Inter-Process Communication (IPC)** to enable communication between three independent processes:

- **UI Process**
- **Core Process**
- **Logger Process**

The IPC technique implemented in this project is **POSIX Message Queues**.

---

## 2. POSIX Message Queues

POSIX Message Queues are used to exchange commands, results and execution information between the processes.

The implementation uses:

```c
#include <mqueue.h>
````

The project uses three message queues:

| Message Queue    | Communication | Purpose                               |
| ---------------- | ------------- | ------------------------------------- |
| `UI_TO_CORE`     | UI → Core     | Sends commands and input values       |
| `CORE_TO_UI`     | Core → UI     | Sends operation results to UI         |
| `CORE_TO_LOGGER` | Core → Logger | Sends execution information to Logger |

---

## 3. IPC Communication Flow

```text
                 UI PROCESS
                     |
                     | UI_TO_CORE
                     v
                CORE PROCESS
                 /         \
                /           \
               v             v
         CORE_TO_UI    CORE_TO_LOGGER
              |              |
              v              v
         UI PROCESS    LOGGER PROCESS
```

The UI Process sends commands to the Core Process.

The Core Process performs the requested CPU, Memory, Stack or Queue operation.

The Core Process sends the result back to the UI and sends execution information to the Logger.

---

## 4. Message Structures

### CoreMessage

`CoreMessage` is used to send commands and input values from the UI Process to the Core Process.

```c
typedef struct
{
    int command;
    int value1;
    int value2;
    char instruction[MAX_MESSAGE];
} CoreMessage;
```

### LogMessage

`LogMessage` is used by the Core Process to send status and result information.

```c
typedef struct
{
    int status;
    int result;
    char message[MAX_MESSAGE];
} LogMessage;
```

---

## 5. IPC Functions Used

| Function       | Purpose                          |
| -------------- | -------------------------------- |
| `mq_open()`    | Opens or creates a message queue |
| `mq_send()`    | Sends a message                  |
| `mq_receive()` | Receives a message               |
| `mq_close()`   | Closes a message queue           |
| `mq_unlink()`  | Removes a named message queue    |

---

## 6. Advantages of POSIX Message Queues

POSIX Message Queues were selected because they provide:

* Communication between independent processes
* Structured message-based communication
* Clear process separation
* Reliable transfer of commands and results
* Suitable communication for the multi-process architecture

---

## 7. Conclusion

The Multi-Process Simulator successfully implements **POSIX Message Queues** as its IPC technique.

The implemented communication is:

**UI → Core → UI**

and

**Core → Logger**

This allows the UI, Core and Logger processes to communicate while remaining independent processes.

```
```

