[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-22041afd0340ce965d47ae6ef1cefeee28c7c493a6346c4f15d667ab976d596c.svg)](https://classroom.github.com/a/T-oguugN)
# Master-Worker

In this project, you will implement a simple master and worker thread pool, a pattern that occurs
in many real life applications. The master threads produce numbers continuously and place them in
a buffer, and worker threads will consume them, i.e., print these numbers to the screen. This simple
program is an example of a master-worker thread pool pattern that is commonly found in several reallife
application servers. For example, in the commonly used multi-threaded architecture for web servers,
the server has one or more master threads and a pool of worker threads. When a new connection arrives
from a web client, the master accepts the request and hands it over to one of the workers. The worker
then reads the web request from the network socket and writes a response back to the client. Your simple
master-worker program is similar in structure to such applications, albeit with much simpler request
processing logic at the application layer.

You are given a skeleton program master-worker-skeleton.c. This program takes 4 command
line arguments: how many numbers to “produce” (M), the maximum size of the buffer in which
the produced numbers should be stored (N), the number of worker threads to consume these numbers
(C), and the number of master threads to produce numbers (P). The skeleton code spawns P master
threads, that produce the specified number of integers from 0 to M − 1 into a shared buffer array. The
main program waits for these threads to join, and then terminates. The skeleton code given to you does
not have any logic for synchronization.

You must write your solution in the file master-worker.c. You must modify this skeleton code
in the following ways. You must add code to spawn the required number of worker threads, and write the
function to be run by these threads. This function will remove/consume items from the shared buffer and
print them to screen. Further, you must add logic to correctly synchronize the producer and consumer
threads in such a way that every number is produced and consumed exactly once. Further, producers
must not try to produce when the buffer is full, and consumers should not consume from an empty
buffer. While you need to ensure that all C workers are involved in consuming the integers, it is not
necessary to ensure perfect load balancing between the workers. Once allM integers (from 0 toM −1)
have been produced and consumed, all threads must exit. The main thread must call pthread join
on the master and worker threads, and terminate itself once all threads have joined. Your solution must
only use pthreads condition variables for waiting and signaling: busy waiting is not allowed.
Your code can be compiled as shown below: <br>
`gcc master-worker.c -lpthread` <br>
To run your code: <br>
`./master-worker #total_items #max_buf_size #num_workers #masters` <br>
Example: <br>
`./master-worker 100 10 4 3`

If your code is written correctly, every integer from 0 to M −1 will be produced exactly once by the
master producer thread, and consumed exactly once by the worker consumer threads. And all master threads and worker threads should join as below <br>
<img width="223" alt="image" src="https://github.com/user-attachments/assets/55f7c557-1f8f-4c4a-b76e-938c00c67324" />

We have provided you with a simple testing script (test-master-worker.sh which invokes the script check.awk)
that checks this above invariant on the output produced by your program. The script relies on the two
print functions that must be invoked by the producer and consumer threads: the master thread must call
the function print produced when it produces an integer into the buffer, and the worker threads
must call the function print consumed when it removes an integer from the buffer to consume. You
must invoke these functions suitably in your solution. Please do not modify these print functions, as their
output will be parsed by the testing script. <br>
To run test script: <br>
`./test-master-worker.sh 100 10 4 3`

Please ensure that you test your case carefully, as tricky race conditions can pop up unexpectedly.
You must test with up to a few million items produced, and with a few hundreds of master/worker threads.
Test for various corner cases like a single master or a single worker thread or for a very small buffer size
as well. Also test for cases when the number of items produced is not a multiple of the buffer size or the
number of master/worker threads, as such cases can uncover some tricky bugs. Increasing the number
of threads to large values beyond a few hundred will cause your system to slow down considerably, so
exercise caution. 

If you pass all tess cases, the output should look like below <br>
<img width="486" alt="image" src="https://github.com/user-attachments/assets/30470731-9e78-424c-927e-6346eaa7d2eb" /> <br>
Test case with 1 and 3 million items produced <br>
<img width="478" alt="image" src="https://github.com/user-attachments/assets/97036f97-4f6a-4c23-ab1d-55142d7a02c5" />

Source https://www.cse.iitb.ac.in/~mythili/os/






Here is the output <br>
adrianaviviano@Jims-MacBook-Pro-3 project-3-master-and-worker-thread-pool-noel543235 % ./<br>master-worker 100 10 4 3        <br>      
Produced 0 by master 1<br>
Consumed 0 by worker 2<br>
Produced 1 by master 0<br>
Consumed 1 by worker 1<br>
Produced 2 by master 1<br>
Produced 3 by master 0<br>
Consumed 3 by worker 2<br>
Produced 4 by master 2<br>
Produced 5 by master 1<br>
Consumed 5 by worker 1<br>
Consumed 4 by worker 4<br>
Produced 6 by master 0<br>
Produced 7 by master 1<br>
Produced 8 by master 2<br>
Consumed 8 by worker 1<br>
Produced 9 by master 0<br>
Produced 10 by master 1<br>
Consumed 10 by worker 4<br>
Produced 11 by master 1<br>
Consumed 11 by worker 1<br>
Produced 12 by master 2<br>
Produced 13 by master 1<br>
Consumed 13 by worker 1<br>
Produced 14 by master 0<br>
Consumed 14 by worker 1<br>
Consumed 12 by worker 3<br>
Consumed 9 by worker 2<br>
Produced 15 by master 0<br>
Consumed 15 by worker 3<br>
Consumed 7 by worker 4<br>
Consumed 6 by worker 2<br>
Consumed 2 by worker 1<br>
Produced 16 by master 0<br>
Consumed 16 by worker 4<br>
Produced 17 by master 2<br>
Produced 18 by master 1<br>
Consumed 18 by worker 2<br>
Produced 19 by master 0<br>
Consumed 19 by worker 1<br>
Consumed 17 by worker 4<br>
Produced 20 by master 0<br>
Consumed 20 by worker 3<br>
Produced 21 by master 2<br>
Produced 22 by master 0<br>
Consumed 22 by worker 3<br>
Produced 23 by master 1<br>
Consumed 23 by worker 2<br>
Consumed 21 by worker 1<br>
Produced 24 by master 0<br>
Consumed 24 by worker 4<br>
Produced 25 by master 1<br>
Consumed 25 by worker 4<br>
Produced 26 by master 2<br>
Produced 27 by master 0<br>
Consumed 27 by worker 4<br>
Consumed 26 by worker 2<br>
Produced 28 by master 2<br>
Consumed 28 by worker 2<br>
Produced 29 by master 1<br>
Produced 30 by master 2<br>
Consumed 30 by worker 2<br>
Consumed 29 by worker 1<br>
Produced 31 by master 2<br>
Produced 32 by master 0<br>
Consumed 32 by worker 4<br>
Produced 33 by master 1<br>
Consumed 33 by worker 4<br>
Consumed 31 by worker 2<br>
Produced 34 by master 2<br>
Consumed 34 by worker 4<br>
Produced 35 by master 0<br>
Consumed 35 by worker 2<br>
Produced 36 by master 1<br>
Consumed 36 by worker 2<br>
Produced 37 by master 2<br>
Consumed 37 by worker 4<br>
Produced 38 by master 0<br>
Produced 39 by master 2<br>
Consumed 39 by worker 4<br>
Consumed 38 by worker 1<br>
Produced 40 by master 1<br>
Consumed 40 by worker 1<br>
Produced 41 by master 1<br>
Consumed 41 by worker 2<br>
Produced 42 by master 0<br>
Produced 43 by master 2<br>
Consumed 43 by worker 1<br>
Produced 44 by master 0<br>
Consumed 44 by worker 1<br>
Consumed 42 by worker 2<br>
Produced 45 by master 2<br>
Consumed 45 by worker 4<br>
Produced 46 by master 0<br>
Produced 47 by master 1<br>
Consumed 47 by worker 4<br>
Consumed 46 by worker 2<br>
Produced 48 by master 0<br>
Produced 49 by master 1<br>
Consumed 49 by worker 4<br>
Produced 50 by master 2<br>
Produced 51 by master 0<br>
Produced 52 by master 1<br>
Consumed 52 by worker 3<br>
Consumed 51 by worker 4<br>
Consumed 50 by worker 1<br>
Consumed 48 by worker 4<br>
Produced 53 by master 1<br>
Consumed 53 by worker 2<br>
Produced 54 by master 2<br>
Produced 55 by master 0<br>
Consumed 55 by worker 2<br>
Consumed 54 by worker 4<br>
Produced 56 by master 1<br>
Consumed 56 by worker 1<br>
Produced 57 by master 1<br>
Consumed 57 by worker 3<br>
Produced 58 by master 0<br>
Consumed 58 by worker 1<br>
Produced 59 by master 0<br>
Produced 60 by master 2<br>
Consumed 60 by worker 4<br>
Produced 61 by master 2<br>
Consumed 61 by worker 2<br>
Consumed 59 by worker 4<br>
Produced 62 by master 2<br>
Consumed 62 by worker 1<br>
Produced 63 by master 2<br>
Consumed 63 by worker 4<br>
Produced 64 by master 0<br>
Consumed 64 by worker 1<br>
Produced 65 by master 2<br>
Consumed 65 by worker 3<br>
Produced 66 by master 0<br>
Produced 67 by master 2<br>
Produced 68 by master 1<br>
Produced 69 by master 0<br>
Consumed 69 by worker 4<br>
Consumed 68 by worker 2<br>
Consumed 67 by worker 3<br>
Consumed 66 by worker 1<br>
Produced 70 by master 0<br>
Consumed 70 by worker 1<br>
Produced 71 by master 1<br>
Produced 72 by master 0<br>
Consumed 72 by worker 1<br>
Produced 73 by master 1<br>
Produced 74 by master 0<br>
Consumed 74 by worker 1<br>
Consumed 73 by worker 2<br>
Consumed 71 by worker 3<br>
Produced 75 by master 1<br>
Consumed 75 by worker 4<br>
Produced 76 by master 1<br>
Consumed 76 by worker 3<br>
Produced 77 by master 1<br>
Consumed 77 by worker 3<br>
Produced 78 by master 1<br>
Produced 79 by master 0<br>
Consumed 79 by worker 3<br>
Produced 80 by master 1<br>
Produced 81 by master 0<br>
Consumed 81 by worker 1<br>
Consumed 80 by worker 3<br>
Produced 82 by master 0<br>
Produced 83 by master 2<br>
Consumed 83 by worker 4<br>
Consumed 82 by worker 2<br>
Produced 84 by master 2<br>
Consumed 84 by worker 1<br>
Consumed 78 by worker 4<br>
Produced 85 by master 0<br>
Produced 86 by master 2<br>
Consumed 86 by worker 4<br>
Produced 87 by master 1<br>
Consumed 87 by worker 2<br>
Consumed 85 by worker 3<br>
Produced 88 by master 2<br>
Consumed 88 by worker 1<br>
Produced 89 by master 0<br>
Consumed 89 by worker 4<br>
Produced 90 by master 1<br>
Consumed 90 by worker 3<br>
Produced 91 by master 2<br>
Produced 92 by master 1<br>
Consumed 92 by worker 4<br>
Consumed 91 by worker 1<br>
Produced 93 by master 1<br>
Produced 94 by master 0<br>
Consumed 94 by worker 1<br>
Consumed 93 by worker 4<br>
Produced 95 by master 2<br>
Consumed 95 by worker 4<br>
Produced 96 by master 2<br>
Consumed 96 by worker 3<br>
Produced 97 by master 0<br>
Produced 98 by master 2<br>
Produced 99 by master 1<br>
Consumed 99 by worker 1<br>
Consumed 98 by worker 3<br>
Consumed 97 by worker 1<br>
master 0 joined<br>
master 1 joined<br>
master 2 joined<br>
worker 0 joined<br>
worker 1 joinedv<br>
worker 2 joined<br>
worker 3 joined<br>
adrianaviviano@Jims-MacBook-Pro-3 project-3-master-and-worker-thread-pool-noel543235 % <br>

Here is the screenshot of the working test cases
![test cases](img/testcasespasses.png "test cases")