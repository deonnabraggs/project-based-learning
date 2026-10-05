<<<<<<< HEAD
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <mqueue.h>
=======
ipc.h
#ifndef IPC_H
#define IPC_H

#define UI_TO_CORE "/ui_to_core"
#define CORE_TO_LOGGER "/core_to_logger"

#define MAX_MESSAGE 256

typedef struct
{
    int command;
    int value1;
    int value2;
    char instruction[MAX_MESSAGE];
} CoreMessage;

typedef struct
{
    int status;
    int result;
    char message[MAX_MESSAGE];
} LogMessage;

#endif
cpu.h
#ifndef CPU_H
#define CPU_H

int execute_instruction(const char *instruction,
                        int value1,
                        int value2);

#endif
cpu.c
#include <stdio.h>
#include <string.h>
#include "cpu.h"

int execute_instruction(const char *instruction,
                        int value1,
                        int value2)
{
    if (strcmp(instruction, "ADD") == 0)
        return value1 + value2;

    if (strcmp(instruction, "SUB") == 0)
        return value1 - value2;

    if (strcmp(instruction, "MUL") == 0)
        return value1 * value2;

    if (strcmp(instruction, "DIV") == 0)
    {
        if (value2 == 0)
        {
            printf("[CPU] Error: Division by zero\n");
            return -1;
        }

        return value1 / value2;
    }

    printf("[CPU] Unknown instruction: %s\n", instruction);
    return -1;
}
memory.h
#ifndef MEMORY_H
#define MEMORY_H

#define MEMORY_SIZE 100

void initialize_memory(void);
void write_memory(int address, int value);
int read_memory(int address);

#endif
memory.c
#include <stdio.h>
#include "memory.h"

static int memory[MEMORY_SIZE];

void initialize_memory(void)
{
    for (int i = 0; i < MEMORY_SIZE; i++)
        memory[i] = 0;

    printf("[MEMORY] Initialized\n");
}

void write_memory(int address, int value)
{
    if (address < 0 || address >= MEMORY_SIZE)
    {
        printf("[MEMORY] Invalid address\n");
        return;
    }

    memory[address] = value;
    printf("[MEMORY] memory[%d] = %d\n", address, value);
}

int read_memory(int address)
{
    if (address < 0 || address >= MEMORY_SIZE)
    {
        printf("[MEMORY] Invalid address\n");
        return -1;
    }

    return memory[address];
}
stack.h
#ifndef STACK_H
#define STACK_H

#define STACK_SIZE 50

void initialize_stack(void);
int push(int value);
int pop(void);
int peek(void);

#endif
stack.c
#include <stdio.h>
#include "stack.h"

static int stack[STACK_SIZE];
static int top = -1;

void initialize_stack(void)
{
    top = -1;
    printf("[STACK] Initialized\n");
}

int push(int value)
{
    if (top >= STACK_SIZE - 1)
    {
        printf("[STACK] Overflow\n");
        return -1;
    }

    stack[++top] = value;
    printf("[STACK] PUSH %d\n", value);
    return 0;
}

int pop(void)
{
    if (top < 0)
    {
        printf("[STACK] Underflow\n");
        return -1;
    }

    int value = stack[top--];
    printf("[STACK] POP %d\n", value);
    return value;
}

int peek(void)
{
    if (top < 0)
        return -1;

    return stack[top];
}
queue.h
#ifndef QUEUE_H
#define QUEUE_H

#define QUEUE_SIZE 50

void initialize_queue(void);
int enqueue(int value);
int dequeue(void);
int queue_empty(void);

#endif
queue.c
#include <stdio.h>
#include "queue.h"

static int queue[QUEUE_SIZE];
static int front = 0;
static int rear = -1;

void initialize_queue(void)
{
    front = 0;
    rear = -1;
    printf("[QUEUE] Initialized\n");
}

int enqueue(int value)
{
    if (rear >= QUEUE_SIZE - 1)
    {
        printf("[QUEUE] Overflow\n");
        return -1;
    }

    queue[++rear] = value;
    printf("[QUEUE] ENQUEUE %d\n", value);
    return 0;
}

int dequeue(void)
{
    if (front > rear)
    {
        printf("[QUEUE] Empty\n");
        return -1;
    }

    int value = queue[front++];
    printf("[QUEUE] DEQUEUE %d\n", value);
    return value;
}

int queue_empty(void)
{
    return front > rear;
}
core.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <fcntl.h>
#include <sys/stat.h>
#include <mqueue.h>

>>>>>>> 7442c904b0954d6d28a4facacaa29be82173f9d9
#include "ipc.h"
#include "cpu.h"
#include "memory.h"
#include "stack.h"
#include "queue.h"
<<<<<<< HEAD
int main()
{
 mqd_t ui_queue;
 mqd_t logger_queue;
 CoreMessage request;
 LogMessage response;
 struct mq_attr attr;
 attr.mq_flags = 0;
 attr.mq_maxmsg = 10;
 attr.mq_msgsize = sizeof(CoreMessage);
 attr.mq_curmsgs = 0;
 printf("\n");
 printf("====================================\n");
 printf(" CORE PROCESS STARTED \n");
 printf("====================================\n");
 ui_queue = mq_open(
 UI_TO_CORE,
 O_CREAT | O_RDONLY,
 0666,
 &attr
 );
 if (ui_queue == (mqd_t)-1)
 {
 perror("[CORE] mq_open UI_TO_CORE");
 exit(EXIT_FAILURE);
 }
 struct mq_attr logger_attr;
 logger_attr.mq_flags = 0;
 logger_attr.mq_maxmsg = 10;
 logger_attr.mq_msgsize = sizeof(LogMessage);
 logger_attr.mq_curmsgs = 0;
 logger_queue = mq_open(
 CORE_TO_LOGGER,
 O_CREAT | O_WRONLY,
 0666,
 &logger_attr
 );
 if (logger_queue == (mqd_t)-1)
 {
 perror("[CORE] mq_open CORE_TO_LOGGER");
 mq_close(ui_queue);
 exit(EXIT_FAILURE);
 }
 initialize_memory();
 initialize_stack();
 initialize_queue();
 printf("\n[CORE] Waiting for command from UI...\n");
 ssize_t bytes_received;
 bytes_received = mq_receive(
 ui_queue,
 (char *)&request,
 sizeof(CoreMessage),
 NULL
 );
 if (bytes_received == -1)
 {
 perror("[CORE] mq_receive"); mq_close(ui_queue);
 mq_close(logger_queue);
 exit(EXIT_FAILURE);
 }
 printf("\n[CORE] Message received\n");
 printf("[CORE] Instruction: %s\n", request.instruction);
 printf("[CORE] Value 1: %d\n", request.value1);
 printf("[CORE] Value 2: %d\n", request.value2);
 int result;
 result = execute_instruction(
 request.instruction,
 request.value1,
 request.value2
 );
 if (result != -1)
 {
 write_memory(0, result);
 push(result);
 enqueue(result);
 }
 if (result == -1)
 {
 response.status = 1;
 }
 else
 {
 response.status = 0;
 }
 response.result = result;
 snprintf(
 response.message,
 MAX_MESSAGE,
 "Instruction %s executed: result = %d",
 request.instruction,
 result
 );
 if (mq_send(
 logger_queue,
 (char *)&response,
 sizeof(LogMessage),
 0) == -1)
 {
 perror("[CORE] mq_send");
 }
 else
 {
 printf("[CORE] Result sent to Logger\n");
 }
 printf("\n[CORE] Execution completed\n");
 mq_close(ui_queue);
 mq_close(logger_queue);
 printf("[CORE] Process terminated\n");
 return 0;
}
=======

int main()
{
    mqd_t ui_queue;
    mqd_t logger_queue;

    CoreMessage request;
    LogMessage response;

    struct mq_attr attr;

    attr.mq_flags = 0;
    attr.mq_maxmsg = 10;
    attr.mq_msgsize = sizeof(CoreMessage);
    attr.mq_curmsgs = 0;

    printf("\n");
    printf("====================================\n");
    printf("       CORE PROCESS STARTED         \n");
    printf("====================================\n");

    ui_queue = mq_open(
        UI_TO_CORE,
        O_CREAT | O_RDONLY,
        0666,
        &attr
    );

    if (ui_queue == (mqd_t)-1)
    {
        perror("mq_open UI_TO_CORE");
        exit(EXIT_FAILURE);
    }

    struct mq_attr logger_attr;

    logger_attr.mq_flags = 0;
    logger_attr.mq_maxmsg = 10;
    logger_attr.mq_msgsize = sizeof(LogMessage);
    logger_attr.mq_curmsgs = 0;

    logger_queue = mq_open(
        CORE_TO_LOGGER,
        O_CREAT | O_WRONLY,
        0666,
        &logger_attr
    );

    if (logger_queue == (mqd_t)-1)
    {
        perror("mq_open CORE_TO_LOGGER");

        mq_close(ui_queue);

        exit(EXIT_FAILURE);
    }

    initialize_memory();
    initialize_stack();
    initialize_queue();

    printf("\n");
    printf("[CORE] Waiting for command from UI...\n");

    ssize_t bytes_received;

    bytes_received = mq_receive(
        ui_queue,
        (char *)&request,
        sizeof(CoreMessage),
        NULL
    );

    if (bytes_received == -1)
    {
        perror("mq_receive");

        mq_close(ui_queue);
        mq_close(logger_queue);

        exit(EXIT_FAILURE);
    }

    printf("\n");
    printf("[CORE] Message received\n");
    printf("[CORE] Instruction: %s\n",
           request.instruction);
    printf("[CORE] Value 1: %d\n",
           request.value1);
    printf("[CORE] Value 2: %d\n",
           request.value2);

    int result;

    result = execute_instruction(
        request.instruction,
        request.value1,
        request.value2
    );

    write_memory(0, result);
    push(result);
    enqueue(result);

    response.status = 0;
    response.result = result;

    snprintf(
        response.message,
        MAX_MESSAGE,
        "Instruction %s executed: result = %d",
        request.instruction,
        result
    );

    if (mq_send(
            logger_queue,
            (char *)&response,
            sizeof(LogMessage),
            0) == -1)
    {
        perror("mq_send");
    }
    else
    {
        printf("[CORE] Result sent to Logger\n");
    }

    printf("\n");
    printf("[CORE] Execution completed\n");

    mq_close(ui_queue);
    mq_close(logger_queue);

    printf("[CORE] Process terminated\n");

    return 0;
}
>>>>>>> 7442c904b0954d6d28a4facacaa29be82173f9d9
