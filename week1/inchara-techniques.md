# Inter-Process Communication (IPC) – Techniques

## 1. Signals

### Definition

A signal is a notification sent to a process to inform it that an event has occurred. It is mainly used to control or notify a process.

### How It Works

* A process or the operating system sends a signal.
* The receiving process gets the signal.
* The process responds to the signal based on how it is programmed.
* Some common signals are `SIGINT`, `SIGTERM`, and `SIGKILL`.

### Where It Is Used

* Process control
* Interrupt handling
* Error handling
* Process termination

### Example

When **Ctrl+C** is pressed in a terminal, the operating system sends a `SIGINT` signal to the running process. The process can then stop or handle the signal.

---

## 2. Semaphores

### Definition

A semaphore is a synchronization tool used to control the access of multiple processes or threads to a shared resource.

### How It Works

* A semaphore has a value that indicates whether a resource is available.
* A process checks the semaphore before using the resource.
* If the resource is available, the process can access it.
* After using the resource, the process releases it for other processes.

### Where It Is Used

* Operating systems
* Process synchronization
* Shared resources
* Multithreaded applications

### Example

If several processes need to use one printer, a semaphore can make sure that only one process uses the printer at a time.

---

## 3. Process Synchronization

### Definition

Process synchronization is used to coordinate multiple processes when they work with shared resources or data.

### How It Works

* Processes are controlled when accessing a shared resource.
* A process may have to wait if another process is using the resource.
* Once the resource is free, the waiting process can continue.
* This helps avoid conflicts between processes.

### Where It Is Used

* Operating systems
* Database systems
* Concurrent programs
* Multithreaded applications
* Shared-resource applications

### Example

If two processes need to update the same bank account, synchronization controls their access so that the account balance is updated correctly.

---

## 4. Mutual Exclusion

### Definition

Mutual exclusion is a technique that allows only one process or thread to access a shared resource or critical section at a time.

### How It Works

* A process requests access to the shared resource.
* If another process is using it, the process waits.
* After the first process finishes, it releases the resource.
* The next waiting process can then use the resource.

### Where It Is Used

* Operating systems
* Shared memory
* Database systems
* Multithreaded programs
* Critical sections

### Example

If two processes try to write to the same file at the same time, mutual exclusion allows one process to write first. The other process waits until the file is available.

---
