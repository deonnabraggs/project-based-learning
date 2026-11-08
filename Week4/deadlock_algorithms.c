// Include the deadlock header file
#include "deadlock.h"

// Function to check whether the system is in a safe state
int is_safe(int sequence[])
{
    // Check whether the sequence array is NULL and process/resource limits are valid
    if (sequence == NULL ||
    n < 1 || n > MAX_PROCESSES ||
    m < 1 || m > MAX_RESOURCES)
    {
        // Return 0 if the input is invalid
        return 0;
    }

    // Store temporarily available resources
    int work[MAX_RESOURCES] = {0};

    // Track whether each process is completed or not
    int finish[MAX_PROCESSES] = {0};

    // Count the number of completed processes
    int count = 0;

    // Copy available resources into the work array
    for (int j = 0; j < m; j++)
    {
        // Check whether available resources are negative
        if (available[j] < 0)
            return 0;

        // Store available resources in work
        work[j] = available[j];
    }

    // Initially set all positions in the safe sequence to -1
    for (int i = 0; i < n; i++)
        sequence[i] = -1;

    // Repeat until all processes are completed
    while (count < n)
    {
        // Initially assume no process can execute
        int found = 0;

        // Check each process one by one
        for (int i = 0; i < n; i++)
        {
            // Skip inactive or already completed processes
            if (!active[i] || finish[i])
                continue;

            // Assume the process can execute
            int possible = 1;

            // Check the resources needed by the process
            for (int j = 0; j < m; j++)
            {
                // Check whether the required resources are greater than available resources
                if (need[i][j] > work[j])
                {
                    // Mark that the process cannot execute
                    possible = 0;

                    // Stop checking this process
                    break;
                }
            }

            // Skip the process if enough resources are not available
            if (!possible)
                continue;

            // Release the allocated resources after the process finishes
            for (int j = 0; j < m; j++)
                work[j] += allocation[i][j];

            // Store the process number in the safe sequence and increase count
            sequence[count++] = i;

            // Mark the process as completed
            finish[i] = 1;

            // Indicate that a process has been completed
            found = 1;
        }

        // Stop if no process can execute
        if (!found)
            break;
    }

    // Check whether any active process is still unfinished
    for (int i = 0; i < n; i++)
    {
        // Return 0 if an active process is not completed
        if (active[i] && !finish[i])
            return 0;
    }

    // Return 1 if the system is in a safe state
    return 1;
}

// Function to detect deadlocked processes
int detect_deadlock(int deadlocked[])
{
    // Check whether the array is NULL and process/resource limits are valid
    if (deadlocked == NULL ||
    n < 1 || n > MAX_PROCESSES ||
    m < 1 || m > MAX_RESOURCES)
    {
        // Return -1 if the input is invalid
        return -1;
    }

    // Store temporarily available resources
    int work[MAX_RESOURCES] = {0};

    // Track whether each process is completed
    int finish[MAX_PROCESSES] = {0};

    // Count the number of deadlocked processes
    int count = 0;

    // Initially mark all processes as not deadlocked
    for (int i = 0; i < n; i++)
        deadlocked[i] = 0;

    // Copy available resources into the work array
    for (int j = 0; j < m; j++)
    {
        // Check whether available resources are negative
        if (available[j] < 0)
            return -1;

        // Store available resources in work
        work[j] = available[j];
    }

    // Check each process
    for (int i = 0; i < n; i++)
    {
        // Check whether the process is inactive
        if (!active[i])
        {
            // Mark inactive process as completed
            finish[i] = 1;

            // Move to the next process
            continue;
        }

        // Initially assume the process has no allocated resources
        int has_allocation = 0;

        // Check the resources allocated to the process
        for (int j = 0; j < m; j++)
        {
            // Check whether the process has any allocated resource
            if (allocation[i][j] > 0)
            {
                // Mark that the process has allocated resources
                has_allocation = 1;

                // Stop checking further resources
                break;
            }
        }

        // Mark the process as finished if it has no allocated resources
        // Otherwise, mark it as unfinished
        /* Standard detection algorithm initialization. */
        finish[i] = !has_allocation;
    }

    // Variable to check whether any process has completed
    int changed;

    // Repeat the process until no more processes can finish
    do
    {
        // Initially assume no process has completed in this round
        changed = 0;

        // Check each process one by one
        for (int i = 0; i < n; i++)
        {
            // Skip inactive or already completed processes
            if (!active[i] || finish[i])
                continue;

            // Assume the requested resources are available
            int possible = 1;

            // Check the resources requested by the process
            for (int j = 0; j < m; j++)
            {
                // Check whether the requested resources are greater than available resources
                if (request[i][j] > work[j])
                {
                    // Mark that the process cannot continue
                    possible = 0;

                    // Stop checking this process
                    break;
                }
            }

            // Skip the process if enough resources are not available
            if (!possible)
                continue;

            // Release the allocated resources after the process finishes
            for (int j = 0; j < m; j++)
                work[j] += allocation[i][j];

            // Mark the process as completed
            finish[i] = 1;

            // Indicate that progress has been made
            changed = 1;
        }

    // Repeat while at least one process has completed
    } while (changed);

    // Check all processes to find deadlocked processes
    for (int i = 0; i < n; i++)
    {
        // Check whether an active process is still unfinished
        if (active[i] && !finish[i])
        {
            // Mark the process as deadlocked
            deadlocked[i] = 1;

            // Increase the deadlocked process count
            count++;
        }
    }

    // Return the total number of deadlocked processes
    return count;
}
