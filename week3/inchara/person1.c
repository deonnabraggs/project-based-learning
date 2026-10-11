#include <stdio.h>

#ifndef SCHEDULER_H
#define SCHEDULER_H

#define MAX_PROCESSES 100
#define MAX_EVENTS 10000

/* Information about each process */
typedef struct {
    int pid;
    int arrival_time;
    int burst_time;
    int priority;

    int waiting_time;
    int turnaround_time;
    int response_time;
    int completion_time;
} Process;

/* CPU execution interval; pid = -1 means idle */
typedef struct {
    int pid;
    int start_time;
    int end_time;
} Event;

/* Person 1: Non-preemptive algorithms */
void fcfs(Process p[], int n, Event events[], int *event_count);
void sjf(Process p[], int n, Event events[], int *event_count);
void priority_nonpreemptive(
    Process p[], int n, Event events[], int *event_count);

/* Person 2: Preemptive algorithms */
void srtf(Process p[], int n, Event events[], int *event_count);
void priority_preemptive(
    Process p[], int n, Event events[], int *event_count);
void round_robin(
    Process p[], int n, int quantum,
    Event events[], int *event_count);

/* Person 3: Output and calculations */
void display_gantt_chart(Event events[], int event_count);
void display_results(Process p[], int n);
void calculate_averages(Process p[], int n);
void calculate_cpu_utilization(
    Event events[], int event_count, int total_time);
void compare_algorithms(Process input[], int n, int quantum);

#endif

/* Record CPU execution intervals */
static void add_event(Event events[], int *count,
                      int pid, int start, int end)
{
    if (start >= end || *count >= MAX_EVENTS)
        return;

    if (*count > 0 &&
        events[*count - 1].pid == pid &&
        events[*count - 1].end_time == start) {
        events[*count - 1].end_time = end;
        return;
    }

    events[*count].pid = pid;
    events[*count].start_time = start;
    events[*count].end_time = end;
    (*count)++;
}

/* Select the next available process */
static int select_process(Process p[], int n, int time,
                          int completed[], int mode)
{
    int i, best = -1;

    for (i = 0; i < n; i++) {
        if (completed[i] || p[i].arrival_time > time)
            continue;

        if (best == -1) {
            best = i;
            continue;
        }

        if (mode == 0) {
            /* FCFS: earliest arrival */
            if (p[i].arrival_time < p[best].arrival_time)
                best = i;
        }
        else if (mode == 1) {
            /* SJF: shortest burst */
            if (p[i].burst_time < p[best].burst_time ||
                (p[i].burst_time == p[best].burst_time &&
                 p[i].arrival_time < p[best].arrival_time))
                best = i;
        }
        else {
            /* Priority: smaller number means higher priority */
            if (p[i].priority < p[best].priority ||
                (p[i].priority == p[best].priority &&
                 p[i].arrival_time < p[best].arrival_time))
                best = i;
        }
    }

    return best;
}

/* Common implementation for non-preemptive algorithms */
static void run_nonpreemptive(Process p[], int n,
                              Event events[], int *event_count,
                              int mode)
{
    int completed[MAX_PROCESSES] = {0};
    int time = 0;
    int finished = 0;
    int i;

    *event_count = 0;

    if (n <= 0 || n > MAX_PROCESSES)
        return;

    for (i = 0; i < n; i++) {
        p[i].waiting_time = 0;
        p[i].turnaround_time = 0;
        p[i].response_time = 0;
        p[i].completion_time = 0;
    }

    while (finished < n) {
        int selected = select_process(
            p, n, time, completed, mode);

        /* CPU idle until the next process arrives */
        if (selected == -1) {
            int next_arrival = -1;

            for (i = 0; i < n; i++) {
                if (!completed[i] &&
                    (next_arrival == -1 ||
                     p[i].arrival_time < next_arrival)) {
                    next_arrival = p[i].arrival_time;
                }
            }

            if (next_arrival > time) {
                add_event(events, event_count, -1,
                          time, next_arrival);
                time = next_arrival;
            }

            continue;
        }

        int start = time;
        int end = start + p[selected].burst_time;

        /* Record execution */
        add_event(events, event_count, p[selected].pid,
                  start, end);

        /* Calculate process metrics */
        p[selected].completion_time = end;

        p[selected].turnaround_time =
            end - p[selected].arrival_time;

        p[selected].waiting_time =
            p[selected].turnaround_time - p[selected].burst_time;

        p[selected].response_time =
            start - p[selected].arrival_time;

        completed[selected] = 1;
        finished++;
        time = end;
    }
}

/* FCFS: First-Come, First-Served */
void fcfs(Process p[], int n,
          Event events[], int *event_count)
{
    run_nonpreemptive(p, n, events, event_count, 0);
}

/* SJF: Shortest Job First, Non-Preemptive */
void sjf(Process p[], int n,
         Event events[], int *event_count)
{
    run_nonpreemptive(p, n, events, event_count, 1);
}

/* Priority Scheduling, Non-Preemptive */
void priority_nonpreemptive(Process p[], int n,
                            Event events[], int *event_count)
{
    run_nonpreemptive(p, n, events, event_count, 2);
}

/* Test program for Person 1 */
int main(void)
{
    Process p[MAX_PROCESSES] = {
        {1, 0, 4, 2, 0, 0, 0, 0},
        {2, 1, 3, 1, 0, 0, 0, 0},
        {3, 2, 2, 3, 0, 0, 0, 0}
    };

    Event events[MAX_EVENTS];
    int event_count;
    int i;
    int choice;

    printf("CPU Scheduling Simulator - Person 1\n");
    printf("1. FCFS\n");
    printf("2. SJF Non-Preemptive\n");
    printf("3. Priority Non-Preemptive\n");
    printf("Enter your choice: ");

    if (scanf("%d", &choice) != 1 ||
        choice < 1 || choice > 3) {
        printf("Invalid choice.\n");
        return 1;
    }

    switch (choice) {
        case 1:
            fcfs(p, 3, events, &event_count);
            break;
        case 2:
            sjf(p, 3, events, &event_count);
            break;
        case 3:
            priority_nonpreemptive(
                p, 3, events, &event_count);
            break;
    }

    printf("\nGantt Chart:\n");

    for (i = 0; i < event_count; i++) {
        if (events[i].pid == -1)
            printf("| IDLE (%d-%d) ",
                   events[i].start_time,
                   events[i].end_time);
        else
            printf("| P%d (%d-%d) ",
                   events[i].pid,
                   events[i].start_time,
                   events[i].end_time);
    }
    printf("|\n");

    printf("\nPID\tAT\tBT\tPriority\tCT\tTAT\tWT\tRT\n");

    for (i = 0; i < 3; i++) {
        printf("P%d\t%d\t%d\t%d\t\t%d\t%d\t%d\t%d\n",
               p[i].pid,
               p[i].arrival_time,
               p[i].burst_time,
               p[i].priority,
               p[i].completion_time,
               p[i].turnaround_time,
               p[i].waiting_time,
               p[i].response_time);
    }

    return 0;
}