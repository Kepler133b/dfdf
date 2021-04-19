/***
* CMPUT 201 Student Submission License
* Version 2.0
* 
* Copyright 2019 Sarah Nadi and \<student name\>

* Unauthorized redistribution is forbidden under all circumstances. Use of this
* software without explicit authorization from the author **and** the CMPUT 201
* Instructor is prohibited.

* This software was produced as a solution for an assignment or lab in the course
* CMPUT 201 - Practical Programming Methodology at the University of
* Alberta, Canada. This solution is confidential and remains confidential 
* after it is submitted for grading. The course staff has the right to 
* run plagiarism-detection tools on any code developed under this license, 
* even beyond the duration of the course.

* Copying any part of this solution without including this copyright notice
* is illegal.

* If any portion of this software is included in a solution submitted for
* grading at an educational institution, the submitter will be subject to
* the plagiarism sanctions at that institution.

* This software cannot be publicly posted under any circumstances, whether by
* the original student or by a third party.
* If this software is found in any public website or public repository, the
* person finding it is kindly requested to immediately report, including 
* the URL or other repository locating information, to the following email
* address:
* 
*           nadi@ualberta.ca


***/
#include <stdbool.h>
#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "squeue.h"

typedef struct Node Node;

void initSqueue(Squeue** squeue)
{
    *squeue = (Squeue*)malloc(sizeof(Squeue));
    (*squeue)->first = NULL;
    (*squeue)->last = NULL;
}

bool isEmpty(const Squeue* squeue)
{
    return squeue->first == NULL;
}

void addFront(Squeue* squeue, char* val)
{
    Node* p = (Node*)malloc(sizeof(Node));
    p->val = (char*)malloc(strlen(val) + 1);
    strcpy(p->val, val);
    p->prev = NULL;
    if (squeue->first == NULL) {
        p->next = NULL;
        squeue->first = squeue->last = p;
    }
    else {
        p->next = squeue->first;
        squeue->first->prev = p;
        squeue->first = p;
    }    
}

void addBack(Squeue* squeue, char* val)
{
    Node* p = (Node*)malloc(sizeof(Node));
    p->val = (char*)malloc(strlen(val) + 1);
    strcpy(p->val, val);
    p->next = NULL;
    if (squeue->first == NULL) {
        p->prev = NULL;
        squeue->first = squeue->last = p;
    }
    else {
        p->prev = squeue->last;
        squeue->last->next = p;
        squeue->last = p;
    }
}

void leaveFront(Squeue* squeue)
{
    assert(!isEmpty(squeue));
    if (squeue->first == squeue->last)
    {
        free(squeue->first->val);
        free(squeue->first);
        squeue->first = squeue->last = NULL;
    }
    else
    {
        Node* p = squeue->first->next;
        free(squeue->first->val);
        free(squeue->first);
        squeue->first = p;
    }
}

void leaveBack(Squeue* squeue)
{
    assert(!isEmpty(squeue));
    if (squeue->first == squeue->last)
    {
        free(squeue->first->val);
        free(squeue->first);
        squeue->first = squeue->last = NULL;
    }
    else
    {
        Node* p = squeue->last->prev;
        free(squeue->last->val);
        free(squeue->last);
        squeue->last = p;
    }
}

char* peekFront(const Squeue* squeue)
{
    assert(!isEmpty(squeue));
    return squeue->first->val;
}

char* peekBack(const Squeue* squeue)
{
    assert(!isEmpty(squeue));
    return squeue->last->val;
}

void print(const Squeue* squeue, char direction)
{
    Node* p;
    switch (direction) {
    case 'f':
        printf("squeue is:\n");
        for (p = squeue->first; p; p = p->next)
            printf("\t%s\n", p->val);
        break;
    case 'r':
        printf("squeue is:\n");
        for (p = squeue->last; p; p = p->prev)
            printf("\t%s\n", p->val);
        break;
    default:
        fprintf(stderr, "Error, illegal direction %c\n", direction);
        break;
    }
}

void nuke(Squeue* squeue)
{
    Node* p = squeue->first;
    while(p)
    {
        Node* q = p->next;
        free(p->val);
        free(p);
        p = q;
    }
    squeue->first = squeue->last = NULL;
}

void mergeFront(Squeue* squeue, char direction)
{
    assert(!isEmpty(squeue));
    assert(squeue->first != squeue->last);

    if (direction != 'f' && direction != 'r') {
        fprintf(stderr, "Error, illegal direction %c\n", direction);
        return;
    }

    Node* p = (Node*)malloc(sizeof(Node));
    p->val = (char*)malloc(
        strlen(squeue->first->val) + strlen(squeue->first->next->val) + 1
    );
    if (direction == 'f') {
        strcpy(p->val, squeue->first->val);
        strcat(p->val, squeue->first->next->val);
    }
    else {
        strcpy(p->val, squeue->first->next->val);
        strcat(p->val, squeue->first->val);
    }
    p->prev = NULL;

    if (squeue->first->next == squeue->last) {
        p->next = NULL;
        free(squeue->first->val);
        free(squeue->last->val);
        free(squeue->first);
        free(squeue->last);
        squeue->first = squeue->last = p;
    }
    else {
        p->next = squeue->first->next->next;
        p->next->prev = p;
        free(squeue->first->val);
        free(squeue->first->next->val);
        free(squeue->first->next);
        free(squeue->first);
        squeue->first = p;
    }    
}

void mergeBack(Squeue* squeue, char direction)
{
    assert(!isEmpty(squeue));
    assert(squeue->first != squeue->last);

    if (direction != 'f' && direction != 'r') {
        fprintf(stderr, "Error, illegal direction %c\n", direction);
        return;
    }

    Node* p = (Node*)malloc(sizeof(Node));
    p->val = (char*)malloc(
        strlen(squeue->last->val) + strlen(squeue->last->prev->val) + 1
    );
    if (direction == 'f') {
        strcpy(p->val, squeue->last->prev->val);
        strcat(p->val, squeue->last->val);
    }
    else {
        strcpy(p->val, squeue->last->val);
        strcat(p->val, squeue->last->prev->val);
    }
    p->next = NULL;

    if (squeue->first->next == squeue->last) {
        p->prev = NULL;
        free(squeue->first->val);
        free(squeue->last->val);
        free(squeue->first);
        free(squeue->last);
        squeue->first = squeue->last = p;
    }
    else {
        p->prev = squeue->last->prev->prev;
        p->prev->next = p;
        free(squeue->last->val);
        free(squeue->last->prev->val);
        free(squeue->last->prev);
        free(squeue->last);
        squeue->last = p;
    }
}

void reverse(Squeue* squeue)
{
    Node* p = squeue->first;
    while(p)
    {
        Node* q = p->next;
        p->next = p->prev;
        p->prev = q;
        p = q;
    }
    Node* q = squeue->first;
    squeue->first = squeue->last;
    squeue->last = q;
}

void destroySqueue(Squeue** squeue)
{
    Node* p = (*squeue)->first;
    while (p)
    {
        Node* q = p->next;
        free(p->val);
        free(p);
        p = q;
    }
    (*squeue)->first = (*squeue)->last = NULL;
    free(*squeue);
    *squeue = NULL;
}
