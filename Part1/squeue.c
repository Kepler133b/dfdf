#include <stdio.h>
#include <string.h>

/*Reference:https://blog.csdn.net/likunkun__/article/details/81713796, Queue*/

/*initSqueue initializes the given squeue to an empty squeue. 
After calling initSqueue on a given squeue , we should be able 
to add elements to that squeue by calling addFront or addBack*/
void initSqueue (Squeue **squeue)
{
    squeue->first = (Node*)malloc(length * sizeof(Node));
	if (!squeue->first)
	{
		exit(0);
	}
	squeue->last = squeue->first;
	squeue->first->next = NULL;
}

/*isEmpty checks if the given squeue is empty. Returns true if it is empty and false if not.*/
bool isEmpty (const Squeue *squeue)
{
	return squeue->first == squeue->last;
}

/*addFront adds the given string (i.e., val ) to the front of the given squeue. Make sure you
adjust all pointers of the squeue appropriately.*/
void addFront (Squeue *squeue, char *val)
{
    assert(&q); // apply memeory spaces
	Node* newNode;
	newNode = (Node*)malloc(sizeof(Node));
 
	if (NULL == newNode)
	{
		exit(0);
	}
 
	newNode->*val = x;
	newNode->next = NULL;
	squeue->last->next = newNode;
	squeue->last = newNode;
	return;
}

/* addBack adds the given string (i.e., val) to the back of the given squeue. Make sure you
adjust all pointers of the squeue appropriately. You need to dynamically allocate memory
for the new string. You cannot assume any maximum size for the string.*/
void addBack (Squeue *squeue, char *val)
{
    assert(&squeue); // apply memeory spaces
	Node* newNode;
	newNode = (Node*)malloc(sizeof(Node));
 
	if (NULL == newNode)
	{
		exit(0);
	}
 
	newNode->*val = ;
	newNode->prev = NULL;
	squeue->first->prev = newNode;
	squeue->first = newNode;
	return;
}


DataType QueueFront(Queue* q){
	assert(q);
	if (QueueEmpty(q))
	{
		return NULL;
	}
	return squeue->_head->_next->_data;
}
 
DataType QueueBack(Queue* q){
	assert(q);
	if (QueueEmpty(q))
	{
		return NULL;
	}
	return squeue->_tail->_data;
}

void leaveFront (Squeue *squeue)
/*leaveFront deletes the first element from the front of the given squeue. Make sure you
adjust all pointers of the squeue appropriately and delete any unneeded struct instances.
The first line of the function should be: assert (!isEmpty(s)); to ensure that you don't
try accessing elements from an empty squeue.*/
{
    assert (!isEmpty(s));
}

void leaveBack (Squeue *squeue)
/* leaveBack deletes the last element at the back of the given squeue. Make sure you adjust
all pointers appropriately and delete any unneeded struct instances. The first line of the function
should be: assert (!isEmpty(s)); to ensure that you don't try accessing elements from
an empty squeue. */
{
    assert (!isEmpty(s));
}

char* peekFront (const Squeue * squeue)
/* peekFront returns the value of the first element from the front of the squeue without
changing the squeue. The first line of the function should be: assert (!isEmpty(s)); to
ensure that you don't try accessing elements from an empty squeue. */
{
    assert(!isEmpty(s));
}

char* peekBack (const Squeue *squeue);
/* peekBack returns the value of the last element from the back of the squeue without
changing the squeue. The first line of the function should be: assert (!isEmpty(s)); to
ensure that you don't try accessing elements from an empty squeue. */
{
    assert(!isEmpty(s));
}


void print (const Squeue * squeue, char direction);
/*print takes a Squeue and a single char that represents the direction, f for forward
and r for reverse, and then prints the squeue in the desired direction. If the direction passed
in is not 'f' or 'r', then print the following message to stderr:
Error, illegal direction <entered direction> . Note that
<entered direction> must be replaced by the direction passed in as an arugment. For
example, if the function was called with direction b , the message printed to stderr will be
Error, illegal direction b . If an illegal direction is detected, just print that
message; do not try to print the contents of squeue , and do not exit the program or make an assertion that could cause the program to abort. To output elements of the stack,
the function prints squeue is: on a line, followed by each element on its own line. Each
element is preceded with a tab. See example code.*/



void nuke (Squeue * squeue);
/* nuke takes a Squeue , deletes all of the internal Nodes, and sets the first and last pointers
of the Squeue instance to NULL .*/

void mergeFront(Squeue* squeue, char direction);
/* mergeFront takes a Squeue and a single char that represents the direction, f for
forward and r for reverse. It concatenates the two strings contained in the first two nodes of
the squeue in the desired direction, stores the concatenated string in the first node, and then
deletes the second node. See the provided main function example above to understand what
mergeFront does. Note that it is an error if you call mergeFront on a squeue with
less than 2 nodes. You should have an assert to check for this. If the direction passed in is
not 'f' or 'r', then print the following message to stderr:
Error, illegal direction <entered direction> . Note that
<entered direction> must be replaced by the direction passed in as an arugment. For
example, if the function was called with direction b , the message printed to stderr will be
Error, illegal direction b . If an illegal direction is detected, just print that
message; do not try to do the merge, and do not exit the program or make an assertion
that could cause the program to abort.*/

void mergeBack(Squeue* squeue, char direction);
/*It concatenates the two strings contained in the last two nodes of
the squeue in the desired direction, stores the concatenated string in the node before last, and
then deletes the last node. */

void reverse(Squeue* squeue);
/* reverses the elements in the given squeue. If the squeue was a->b->c->d , where first
points to a and last points to d , calling reverse would change the squeue contents to
d->c->b->a , and make first point to d and last point to a .*/

void destroySqueue(Squeue **squeue);

/* destroySqueue safely deletes all members of the given squeue as well as any memory
allocated for squeue. After calling destroySqueue on a given squeue , that squeue
would point to NULL*/