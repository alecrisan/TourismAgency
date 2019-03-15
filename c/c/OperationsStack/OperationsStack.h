//
//  OperationsStack.h
//  c
//
//  Created by Crisan Alexandra on 19/03/2018.
//  Copyright © 2018 Crisan Alexandra. All rights reserved.
//

#ifndef OperationsStack_h
#define OperationsStack_h

#include <stdio.h>
#include "OfferEntity.h"

typedef struct
{
    Offer* o;
    char* opType;
}Operation;

/*
 Creates an operation of a given type
 Input: o - pointer to an offer
        opType - string ("add"/"delete")
 Output: pointer to an operation
 */
Operation* createOp(Offer* o, char* opType);

/*
 Destroys an operation
 Input: op - pointer to an operation
 Output: None
 */
void destroyOp(Operation* op);

/*
 Copies an operation
 Input: op - pointer to an operation
 Output: pointer to the new copy
 */
Operation* copyOp(Operation* op);

/*
 Gets the operation type
 Input: op - pointer to an operation
 Output: a string
 */
char* getOpType(Operation* op);

/*
 Gets the offer that the operation worked with
 Input: op - pointer to an operation
 Output: pointer to an offer
 */
Offer* getO(Operation* op);



typedef struct
{
    Operation* operations[100];
    int len;
}Stack;


/*
 Creates a stack
 Input: None
 Output: the created stack
 */
Stack* createStack(void);

/*
 Destroys the stack
 Input: s - pointer to the stack
 Output: None
 */
void destroyStack(Stack* s);

/*
 Checks if the stack is full
 Input: s - pointer to the stack
 Output: 1 if it's full, 0 otherwise
 */
int isFull(Stack* s);

/*
 Checks if the stack is empty
 Input: s - pointer to the stack
 Output: 1 if it's empty, 0 otherwise
 */
int isEmpty(Stack* s);

/*
 Pushes an operation on the stack
 Input: s - pointer to the stack
        op - pointer to the operation
 Output: None
 */
void pushOp(Stack* s, Operation* op);

/*
 Pops the last operation from the stack
 Input: s - pointer to the stack
 Output: pointer to the last operation
 */
Operation* popOp(Stack* s);



 /*
 Contains some tests for the implemented functionalities
 Input: None
 Output: None
 */
void testsStack(void);

#endif /* OperationsStack_h */
