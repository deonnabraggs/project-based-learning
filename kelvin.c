#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <mqueue.h>
#include "ipc.h"
#include "cpu.h"
#include "memory.h"
#include "stack.h"
#include "queue.h"
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