Inter-Process Communication (IPC) – Techniques (PART-2)

5. Sockets

A socket is a communication endpoint that allows two processes to exchange data. It can be used for communication between processes on the same computer or between different computers through a network.

How It Works:

The server creates a socket and waits for a connection.

The client creates a socket and connects to the server.

After the connection is established, both processes can send and receive data.

TCP or UDP can be used for communication.


Where It Is Used:

Client-server applications

Web applications

Chat applications

Online gaming

Network services

Distributed systems


Example:
A web browser communicates with a web server using sockets. The browser sends a request, and the server sends the requested webpage or data.


---

6. Process Synchronization

Process synchronization is a mechanism used to coordinate multiple processes when they access shared resources or data. It ensures that processes operate in a controlled and orderly manner.

How It Works:

Processes are coordinated when accessing shared resources.

A process may wait while another process is using the resource.

It prevents conflicts and inconsistent data.

Semaphores, mutexes, and locks can be used for synchronization.


Where It Is Used:

Operating systems

Database systems

Multithreaded applications

Concurrent programs

Shared-resource applications


Example:
If two processes update the same bank account, synchronization ensures that they do not modify the account balance simultaneously, preventing an incorrect balance.


---

7. Remote Procedure Call (RPC)

Remote Procedure Call (RPC) is a technique that allows a program to execute a procedure or function on a remote computer or process as if it were a local function call.

How It Works:

The client sends a request to the remote server.

The RPC system transfers the request to the server.

The server executes the requested procedure.

The result is returned to the client.


Where It Is Used:

Distributed systems

Client-server applications

Cloud applications

Microservices

Network services


Example:
A banking application can use RPC to request account information from a remote banking server. The server processes the request and returns the information to the application.


---

8. Memory Mapping

Memory mapping is a technique in which a file or memory region is mapped into a process's address space, allowing processes to access shared data efficiently.

How It Works:

A file or memory region is mapped into the virtual address space of a process.

Multiple processes can map the same memory region.

The processes can directly access the shared data.

It reduces the need for repeated copying of data.


Where It Is Used:

Operating systems

Database systems

Large-data applications

High-performance applications

Shared-memory applications


Example:
Two processes can use a memory-mapped file to share a large amount of data. Both processes can access the mapped region directly.
