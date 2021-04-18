#define _CRT_SECURE_NO_WARNINGS
#include <stdbool.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

struct NodeBucket {
    char** val;
    struct NodeBucket* next;
};

typedef struct {
    struct NodeBucket* firstBucket;
    int topElt;
    int bucketSize;
} Stack;

void initStack(int bucketSize, Stack** stack);
bool isEmpty(const Stack* stack);
void push(char* val, Stack* stack);
void pop(Stack* stack);
int size(const Stack* stack);
char* top(const Stack* stack);
void swap(Stack* stack);
void print(const Stack* stack);
void clear(Stack* stack);
void destroyStack(Stack** stack);

void initStack(int bucketSize, Stack** stack)
{
    *stack = (Stack*)malloc(sizeof(Stack));
    (*stack)->topElt = bucketSize - 1;
    (*stack)->bucketSize = bucketSize;
    (*stack)->firstBucket = NULL;
}

bool isEmpty(const Stack* stack)
{
    return stack == NULL || stack->firstBucket == NULL;
}

void push(char* val, Stack* stack)
{
    assert(stack != NULL);

    if (stack->topElt == stack->bucketSize - 1) {
        struct NodeBucket* p = (struct NodeBucket*)malloc(sizeof(struct NodeBucket));
        p->val = (char**)malloc(stack->bucketSize * sizeof(char*));
        p->next = stack->firstBucket;
        p->val[0] = (char*)malloc(strlen(val) + 1);
        strcpy(p->val[0], val);
        stack->firstBucket = p;
        stack->topElt = 0;
        return;
    }
    stack->topElt++;
    stack->firstBucket->val[stack->topElt] = (char*)malloc(strlen(val) + 1);
    strcpy(stack->firstBucket->val[stack->topElt], val);
    
}

void pop(Stack* stack)
{
    assert(isEmpty(stack) == false);
    if (stack->topElt == 0) {
        struct NodeBucket* p = stack->firstBucket;
        stack->firstBucket = p->next;
        free(p->val[0]);
        free(p->val);
        free(p);
        stack->topElt = stack->bucketSize - 1;
        return;
    }
    free(stack->firstBucket->val[stack->topElt]);
    stack->topElt--;
}

int size(const Stack* stack)
{
    if (isEmpty(stack))
        return 0;
    int cnt = 0;
    struct NodeBucket* p;
    for (p = stack->firstBucket->next; p; p = p->next)
        cnt++;
    return cnt * stack->bucketSize + (stack->topElt + 1);
}

char* top(const Stack* stack)
{
    assert(isEmpty(stack) == false);
    return stack->firstBucket->val[stack->topElt];
}

void swap(Stack* stack)
{
    assert(isEmpty(stack) == false);
    assert(!(stack->firstBucket->next == NULL && stack->topElt == 0));

    char* first = stack->firstBucket->val[stack->topElt];
    char* second = NULL;
    if (stack->topElt == 0) {
        second = stack->firstBucket->next->val[stack->bucketSize - 1];
    }
    else
        second = stack->firstBucket->val[stack->topElt - 1];
    
    char* temp = (char*)malloc(strlen(first) + 1);

    strcpy(temp, first);
    
    free(first);
    first = (char*)malloc(strlen(second) + 1);
    strcpy(first, second);
    free(second);
    second = (char*)malloc(strlen(temp));
    strcpy(second, temp);
    
    free(temp);
}

void print(const Stack* stack)
{
    printf("stack is:\n");
    if (isEmpty(stack))
        return;
    int i;
    for (i = stack->topElt; i >= 0; i--)
        printf("\t%s\n", stack->firstBucket->val[i]);
    
    struct NodeBucket* p;
    for (p = stack->firstBucket->next; p; p = p->next) {
        for (i = stack->bucketSize - 1; i >= 0; i--)
            printf("\t%s\n", p->val[i]);
    }
}

void clear(Stack* stack)
{
    if (isEmpty(stack))
        return;
    int i;
    for (i = stack->topElt; i >= 0; i--)
        free(stack->firstBucket->val[i]);
    free(stack->firstBucket->val);
    struct NodeBucket* p = stack->firstBucket;
    stack->firstBucket = p->next;
    free(p);
    p = stack->firstBucket;
    while(p) {
        for (i = stack->bucketSize - 1; i >= 0; i--)
            free(p->val[i]);
        free(p->val);
        struct NodeBucket* q = p;
        p = p->next;
        free(q);
    }
    stack->firstBucket = NULL;
    stack->topElt = stack->bucketSize - 1;
}

void destroyStack(Stack **stack)
{
    clear(*stack);
    free(*stack);
    *stack = NULL;
}
/*
int main()
{
    //We will have two stacks
    Stack* s1 = NULL;
    Stack* s2 = NULL;
    initStack(5, &s1);
    initStack(3, &s2);
    push("uno", s1);
    push("dos", s1);
    //s1 now has "dos" and "uno" in that order
    assert(strcmp("dos", top(s1)) == 0);
    //s2 is empty at this moment
    assert(isEmpty(s2));
    push("tres", s2);
    //We just added "tres" in s2
    assert(strcmp("tres", top(s2)) == 0);
    assert(size(s1) == 2);
    assert(size(s2) == 1);
    //Time to swap "dos" and "uno"
    swap(s1);
    //s1 now has "uno" and "dos" in that order
    assert(strcmp("uno", top(s1)) == 0);
    //Let's add 3 elements to each stack
    //after this for loop, s1 will have "hola", "hola", "hola", "uno",
    //"dos" in that order
    //after this for loop, s2 will have "mundo!", "mundo!", "mundo!", "tres"
    //in that order
    for (int i = 0; i < 3; i++) {
        push("hola", s1);
        push("mundo!", s2);
    }
    print(s1);
    print(s2);

    //let's add 97 elements to each stack
    for (int i = 0; i < 97; i++) {
        push("hola", s1);
        push("mundo!", s2);
    }

    assert(size(s1) == 102);
    assert(size(s2) == 101);
    //s1 should have "hola" at the top
    assert(strcmp(top(s1), "hola") == 0);
    //s2 should have "mundo!" at the top
    assert(strcmp(top(s2), "mundo!") == 0);

    //at this point, s1 has 100 "hola" at the top so let's pop them
    //at this point, s2 has 100 "mundo!" at the top so let's pop them
    for (int i = 0; i < 100; i++) {
        assert(strcmp(top(s1), "hola") == 0);
        pop(s1);
        assert(strcmp(top(s2), "mundo!") == 0);
        pop(s2);
    }

    //s1 still has the uno and dos at the top and s2 still
    //has tres at the top. Let's use clear to clear all remaining
    //elements on each stack
    clear(s1);
    clear(s2);

    //both stacks must be empty after clear
    assert(isEmpty(s1));
    assert(isEmpty(s2));

    destroyStack(&s1);
    assert(s1 == NULL);

    destroyStack(&s2);
    assert(s2 == NULL);
    return 0;
}
*/
int main(int argc, char* argv[]) {
    Stack* s = NULL;
    initStack(3, &s);
    push("alpha", s);
    printf("This prints \"alpha\":\n");
    printf("%s\n", top(s));
    push("beta", s);
    printf("This prints \"beta\":\n");
    printf("%s\n", top(s));
    push("gamma", s);
    printf("This prints \"gamma\":\n");
    printf("%s\n", top(s));
    push("delta", s);
    printf("This prints \"delta\":\n");
    printf("%s\n", top(s));
    printf("This will print the whole stack with a tab beforeeach element : \"delta gamma beta alpha\" across 4 lines, preceded by \"stack is:\" on a line on its own line\n");
    print(s);
    clear(s);
    printf("This will print an empty stack so just \"stack is:\"\n");
    print(s);
    push("alice", s);
    printf("This will print a stack that only contains \"alice\" preceded by stack is on its own line\n");
    print(s);
    pop(s);
    printf("This will print an empty stack so just \"stack is:\"\n");
    print(s);
    push("bob", s);
    push("bob", s);
    printf("This will print the whole stack with a tab before each element : \"bob bob\" across 2 lines, preceded by \"stack is:\" on a line on its own\n");

    print(s);
    push("mike", s);
    printf("This will print the whole stack with a tab before each element : \"mike bob bob\" across 3 lines, preceded by \"stack is:\" on a line on its own\n");
    print(s);
    swap(s);
    printf("This will print the whole stack after swapping first two with a tab before each element : \"bob mike bob\" across 3 lines, preceded by \"stack is:\" on a line on its own\n");

    print(s);
    clear(s);
    printf("This will print an empty stack so just \"stack is:\"\n");
    print(s);
    //we will always call this for any stack we test with so
    //make sure it is implemented correctly to free any allocated memory
    destroyStack(&s);
    return 0;
}