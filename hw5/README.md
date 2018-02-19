# Distributed System
With the development of technology, computers can be connected via a network and hence distributed
systems become popular. A distributed system is a software system in which components located on
network-connected computers communicate and coordinate their actions by passing messages. In this 
way, complicated and time-consuming calculation can be divided into smaller tasks which are then
assigned to the computers in the distributed system. In this homework, we would like you to construct
the task queue of every computer in a distributed system using a data structure called the binomial heap.

Each computer in the distributed system has its own task queue. Each task has an unique integer
ID id and a priority value p. The larger the priority value is, the more important the task is. A task
with a larger priority value should be executed first. New tasks can be assigned to any computers in the
system. Also, if the system detects that the workload of the computers is not balanced, it can request
one computer to give all its tasks to another. However, the system sometimes misjudges and asks a
computer with fewer than w tasks to give all its tasks to another computer. Under this circumstance,
the computer will refuse to give its tasks to another computer.

The reason we ask you to implement the binomial heap (http://en.wikipedia.org/wiki/Binomial_
heap) is that it is particularly useful for the \merging" of task queues of two computers. In particular,
only O(log n) time is needed to merge two size-n task queues.
