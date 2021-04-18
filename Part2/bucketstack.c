/***
 * CMPUT 201 Assignment License
 * Version 2.0
 *
 * Copyright 2021 Chang Liu
 
 * Unauthorized redistribution is forbidden under all circumstances. Use of this
 * software without explicit authorization from the author **and** the CMPUT 201
 * Instructor is prohibited.
 
 * This software was produced as part of an assignment in the course
 * CMPUT 201 - Practical Programming Methodology at the University of
 * Alberta, Canada. This code is confidential and remains confidential
 * after it is submitted for grading. The course staff has the right to
 * run plagiarism-detection tools on any code developed under this license,
 * even beyond the duration of the course.
 *
 * Copying any part of this code without including this copyright notice
 * is illegal.
 *
 * If any portion of this software is included in a solution submitted for
 * grading at an educational institution, the submitter will be subject to
 * the plagiarism sanctions at that institution.
 *
 * This software cannot be publicly posted under any circumstances, whether by
 * the original student or by a third party.
 * If this software is found in any public website or public repository, the
 * person finding it is kindly requested to immediately report, including
 * the URL or other repository locating information, to the following email
 * address:
 *
 *          nadi@ualberta.ca
 ***/
#include "bucketstack.h"
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

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

    
   */
  
