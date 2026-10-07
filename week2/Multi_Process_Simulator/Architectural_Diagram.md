````markdown
# Multi-Process Simulator - Architectural Diagram

## 1. System Architecture

The simulator consists of three independent processes:

- **UI Process** – accepts user commands and displays results.
- **Core Process** – performs CPU, Memory, Stack and Queue operations.
- **Logger Process** – receives and displays execution information.

The processes communicate using **POSIX Message Queues**.

## 2. Architectural Diagram

```text
                         USER
                          |
                          v
                 +------------------+
                 |    UI PROCESS    |
                 |------------------|
                 | User Input       |
                 | Command Selection|
                 +--------+---------+
                          |
                          | UI_TO_CORE
                          | CoreMessage
                          v
                 +------------------+
                 |   CORE PROCESS   |
                 |------------------|
                 | CPU              |
                 | Memory           |
                 | Stack            |
                 | Queue            |
                 +----+--------+----+
                      |        |
          CORE_TO_UI  |        | CORE_TO_LOGGER
          LogMessage  |        | LogMessage
                      v        v
              +--------+--+  +------------------+
              | UI PROCESS |  | LOGGER PROCESS  |
              |------------|  |-----------------|
              | Display    |  | Status / Result |
              | Result     |  | Execution Log   |
              +------------+  +------------------+
````

## 3. IPC Communication

| Message Queue    | Direction     | Purpose                             |
| ---------------- | ------------- | ----------------------------------- |
| `UI_TO_CORE`     | UI → Core     | Sends commands and input values     |
| `CORE_TO_UI`     | Core → UI     | Sends operation results             |
| `CORE_TO_LOGGER` | Core → Logger | Sends status and result information |

### Communication Flow

1. The **UI Process** receives a command from the user.
2. The command is sent to the **Core Process** using `UI_TO_CORE`.
3. The **Core Process** performs the required CPU, Memory, Stack or Queue operation.
4. The result is sent back to the **UI Process** using `CORE_TO_UI`.
5. The Core also sends execution information to the **Logger Process** using `CORE_TO_LOGGER`.

## 4. Core Components

* **CPU:** ADD, SUBTRACT, MULTIPLY, DIVIDE
* **Memory:** STORE, LOAD
* **Stack:** PUSH, POP, PEEK
* **Queue:** ENQUEUE, DEQUEUE, QUEUE PEEK

**IPC Technique:** POSIX Message Queues

```
```

