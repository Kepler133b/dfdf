# assignment3-asgmt3_team17

Group:Team17

# Purpose of program

Part1 finishes the function in squeue.c. It supports some operations,the function name are initSqueue ,
isEmpty , addFront , leaveFront , mergeFront , peekFront , addBack , leaveBack , peekBack , mergeBack , 
print , and nuke . initSqueue and isEmpty.
Part2 finishes the function in bucketstack.c. It supports the operations,the function name are 
itStack, isEmpty, push, pop, int size,top,swap, print, clear, destroyStack.

# Exact commands needed to run code
For part1:
./squeue
For part2:
./bucketstack

# Files in assignment (structure and what they do):

* Part1:
squeue.h, squeue.c, squeue_client.c, Makefile
* Part2:
bucketstack.h, bucketstack.c, bucketstack_client.c, Makefile

How they are structured:
* part1: 
squeue.h is a header file and contains all implementation code.
squeue.c contains the definitions of all the functions declared in squeue.h. 
squeue_client.c contains only the main function and #include <stdio.h> , #include <assert.h> ,
#include <stdlib.h> , and #include "squeue.h".
Makefile contains the gcc command which connects the above files.
* part2:
bucketstack.h is a header file and contains all implementation code.
bucketstack.c contains the definitions of all the functions declared in bucketstack.h.
bucketstack_client.c contains only a main function and #include <stdio.h> , #include <assert.h> ,
#include <stdlib.h> , and #include "bucketstack.h" .
Makefile contains the gcc command which connects the above files.

How they do:
For part1:
We store the functions in the squeue.h, which is useful for us to modify the program. The file of squeue.c includes the defintions of the functions, the function name are initSqueue , isEmpty , addFront , leaveFront , mergeFront , peekFront , addBack , leaveBack , peekBack , mergeBack , 
print , and nuke . initSqueue and isEmpty. In addition, squeue_client.c contains the main function. 
For part2:
We store the functions in the bucketstack.h, which is useful for us to modify the program. The file of bucketstack.c includes the defintions of the functions, the function name are initSqueue , isEmpty , addFront , leaveFront , mergeFront , peekFront , addBack , leaveBack , peekBack , mergeBack , 
print , and nuke . initSqueue and isEmpty. In addition, bucketstack_client.c contains the main function. 

# References
1.https://blog.csdn.net/likunkun__/article/details/81713796
