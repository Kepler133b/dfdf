squeue: squeue.o squeue_client.o
	gcc -Wall -std=c99 -o squeue squeue_client.o squeue.o

squeue_client.o: squeue.h squeue_client.c
	gcc -Wall -std=c99 -c squeue_client.c

squeue.o: squeue.h squeue.c
	gcc -Wall -std=c99 -c squeue.c

clean:
	rm -f *.o
	rm -f squeue


