Inter-Process Communication (IPC) - Methods

1. Pipes

A pipe is an IPC method that allows one process to send data to another process. Pipes are commonly used for communication between related processes, such as a parent and child process.

How It Works:

One process writes data into the pipe.

Another process reads the data from the pipe.

Pipes are usually unidirectional, meaning data flows in one direction.


Advantages:

Pipes are simple and easy to use.

They provide fast communication between processes.

They are supported by most operating systems.

They are useful for communication between related processes.


Disadvantages:

Pipes usually support communication in only one direction.

They are mainly useful between related processes.

The communication is normally available only while the processes and pipe are active.


Example:

A parent process creates a pipe and sends a message such as "Hello Child" to the child process.


2. Named Pipes (FIFO)

A Named Pipe, also called a FIFO (First In, First Out), is an IPC method that allows processes to communicate through a special file created by the operating system.


How It Works:

The operating system creates a special file called a FIFO.

One process writes data to the FIFO.

Another process reads the data from the FIFO.

Unlike normal pipes, named pipes can be used by unrelated processes.


Advantages:

Named pipes can be used by unrelated processes.

They are simple to implement.

Data is transferred in FIFO order.

They are useful for communication between separate programs.


Disadvantages:

Named pipes usually provide one-way communication.

Both processes need access to the FIFO.

They are less flexible than sockets for communication across different computers.


Example:

A server process writes "Data received" to a FIFO, and a client process reads the message from the same FIFO.


3. Message Queues

A message queue is an IPC method that allows processes to exchange messages through a queue managed by the operating system.


How It Works:

A process creates or accesses a message queue.

The sender places a message into the queue.

The operating system stores the message until another process receives it.

The receiving process retrieves the message from the queue.

Messages can be assigned different types or priorities.


Advantages:

Processes do not need to communicate at exactly the same time.

Messages can be organized by type or priority.

Multiple processes can use the same queue.

They provide more structured communication than simple pipes.


Disadvantages:

Message queues have limited system capacity.

Managing queues can be more complicated than pipes.

Messages may have size limitations.

They require operating system resources.


Example:

A client process sends a request such as "Print document" to a message queue. A printer process receives the request and processes it.


4. Shared Memory

Shared memory is an IPC method where two or more processes access the same region of memory to exchange data.


How It Works:

The operating system creates a shared memory area.

Multiple processes attach to the shared memory.

One process writes data into the shared memory.

Other processes can read the data directly.

Synchronization mechanisms such as semaphores or mutexes may be needed to prevent conflicts when multiple processes access the memory.


Advantages:

Shared memory provides very fast communication.

It is suitable for transferring large amounts of data.

It reduces the need to copy data between processes.

It is efficient for high-performance applications.


Disadvantages:

It requires synchronization to avoid data conflicts.

It can be more difficult to program correctly.

Race conditions can occur when processes access the memory at the same time.

Incorrect synchronization can lead to inconsistent data.


Example:

A producer process writes sensor data into shared memory, while another process reads and processes the sensor data.
