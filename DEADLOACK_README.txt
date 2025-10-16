Deadlock Detection using Wait-For Graph in C++

Description

This program implements a deadlock detection algorithm using a Wait-For Graph (WFG).

Each process is represented as a node.

An edge Pi -> Pj means process Pi is waiting for Pj.

The program uses Depth-First Search (DFS) to detect cycles in the graph.

If a cycle exists, it reports a deadlock and lists the processes involved.

How to Compile and Run

Save the source file as deadlock_detection.cpp.

Compile using:

g++ deadlock_detection.cpp -o deadlock


Run the program:

./deadlock

Input Format

First, enter the number of processes.

Then, enter the number of edges.

Finally, enter each edge in the format:

P1 -> P2


(meaning P1 is waiting for P2).

Sample Input
Enter the number of processes: 4
Enter the number of edges: 3
Enter edges (format: P1 -> P2):
P1 -> P2
P2 -> P3
P3 -> P1

Sample Output
Deadlock detected involving processes: P1 P2 P3

Parameter Passing Explanation

By Value: Simple integers (n, e) are passed by value to functions.

By Reference (via STL containers): Vectors (adj, visited, etc.) are internally passed by reference inside the WaitForGraph class, avoiding unnecessary copies.

Encapsulation: The class WaitForGraph keeps the graph and detection logic inside, and methods operate on the same object instance.