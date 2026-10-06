#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <mqueue.h>

#include "ipc.h"

int main()
{
    mqd_t ui_queue;
    CoreMessage request;

    struct mq_attr attr;

    attr.mq_flags = 0;
    attr.mq_maxmsg = 10;
    attr.mq_msgsize = sizeof(CoreMessage);
    attr.mq_curmsgs = 0;

    printf("\n");
    printf("====================================\n");
    printf("          UI PROCESS STARTED        \n");
    printf("====================================\n");

    ui_queue = mq_open(
        UI_TO_CORE,
        O_CREAT | O_WRONLY,
        0666,
        &attr
    );

    if (ui_queue == (mqd_t)-1)
    {
        perror("[UI] mq_open");
        exit(EXIT_FAILURE);
    }

    printf("[UI] Message queue opened successfully\n");

    printf("\nEnter instruction (ADD/SUB/MUL/DIV): ");
    scanf("%255s", request.instruction);

    printf("Enter value 1: ");
    scanf("%d", &request.value1);

    printf("Enter value 2: ");
    scanf("%d", &request.value2);

    request.command = 1;

    printf("\n====================================\n");
    printf("             UI COMMAND             \n");
    printf("====================================\n");

    printf("Instruction : %s\n", request.instruction);
    printf("Value 1     : %d\n", request.value1);
    printf("Value 2     : %d\n", request.value2);

    if (mq_send(
            ui_queue,
            (char *)&request,
            sizeof(CoreMessage),
            0) == -1)
    {
        perror("[UI] mq_send");
        mq_close(ui_queue);
        exit(EXIT_FAILURE);
    }

    printf("\n[UI] Command sent to Core successfully\n");

    mq_close(ui_queue);

    printf("[UI] Process terminated\n");

    return 0;
}
