PERSON 3 – IPC TECHNIQUES (PART 1)
1. Signals
Definition
A signal is a notification sent by the operating system or one process to another process to inform it that a particular event has occurred.
How It Works
When an event occurs, the operating system sends a signal to a process. The process receives the signal and performs a predefined action or uses a signal handler to respond to it.
Where It Is Used
Signals are mainly used in operating systems to notify processes about events such as interruptions, termination, or other system events.
Example
When a program is running in a terminal and the user presses Ctrl + C, the operating system sends an interrupt signal to the program. The program can then stop its execution.
________________________________________
2. Semaphores
Definition
A semaphore is a synchronization tool used to control access to shared resources by multiple processes or threads.
How It Works
A semaphore maintains a value that represents the availability of a resource. A process performs a wait operation before accessing the resource and a signal operation after finishing its work.
Where It Is Used
Semaphores are used in operating systems and multithreaded programs when multiple processes or threads need to share resources such as files, memory, printers, or databases.
Example
Suppose there is one printer shared by several processes. A semaphore can make sure that only one process uses the printer at a time. Other processes wait until the printer becomes available.
________________________________________
3. Synchronization
Definition
Synchronization is the process of coordinating multiple processes or threads so that they work together correctly without interfering with each other.
How It Works
Synchronization controls when processes or threads can access shared data or resources. It ensures that operations happen in the correct order and prevents conflicts.
Where It Is Used
Synchronization is used in operating systems, databases, banking applications, and multithreaded programs where multiple processes or threads work with shared resources.
Example
Consider a bank account shared by two transactions. If both transactions try to update the account balance at the same time, synchronization ensures that the operations are performed properly so that the balance remains correct.
________________________________________
4. Mutual Exclusion
Definition
Mutual exclusion is a technique that ensures only one process or thread can access a shared resource or critical section at a time.
How It Works
Before entering a critical section, a process obtains permission to use the shared resource. While it is using the resource, other processes must wait. After the process finishes, another process can access the resource.
Where It Is Used
Mutual exclusion is used in operating systems, databases, banking systems, and multithreaded programs where multiple processes or threads access the same resource.
Example
Suppose two threads want to update the same bank account balance. Mutual exclusion allows only one thread to update the balance at a time. The second thread waits until the first thread finishes.
________________________________________
