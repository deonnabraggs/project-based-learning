#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <mqueue.h>

#include "ipc.h"

int main()
{
    mqd_t logger_queue;
    LogMessage message;

    struct mq_attr attr;

    attr.mq_flags = 0;
    attr.mq_maxmsg = 10;
    attr.mq_msgsize = sizeof(LogMessage);
    attr.mq_curmsgs = 0;

    printf("\n");
    printf("====================================\n");
    printf("       LOGGER PROCESS STARTED       \n");
    printf("====================================\n");

    printf("\n[LOGGER] Opening message queue...\n");
    printf("[LOGGER] Queue: /core_to_logger\n");

    logger_queue = mq_open(
        CORE_TO_LOGGER,
        O_CREAT | O_RDONLY,
        0666,
        &attr
    );

    if (logger_queue == (mqd_t)-1)
    {
        perror("[LOGGER] mq_open");
        exit(EXIT_FAILURE);
    }

    printf("[LOGGER] Message queue opened successfully\n");

    printf("\n[LOGGER] Waiting for messages from Core...\n");

    ssize_t bytes_received;

    bytes_received = mq_receive(
        logger_queue,
        (char *)&message,
        sizeof(LogMessage),
        NULL
    );

    if (bytes_received == -1)
    {
        perror("[LOGGER] mq_receive");

        mq_close(logger_queue);

        exit(EXIT_FAILURE);
    }

    printf("\n[LOGGER] Message received from Core!\n");

    printf("\n");
    printf("====================================\n");
    printf("           LOGGER OUTPUT            \n");
    printf("====================================\n");

    if (message.status == 0)
    {
        printf("Status   : SUCCESS\n");
    }
    else
    {
        printf("Status   : ERROR\n");
    }

    printf("Message  : %s\n", message.message);
    printf("Result   : %d\n", message.result);

    printf("====================================\n");

    mq_close(logger_queue);

    printf("\n[LOGGER] Process terminated\n");

    return 0;
}