//
//  OperationsStack.c
//  c
//
//  Created by Crisan Alexandra on 19/03/2018.
//  Copyright © 2018 Crisan Alexandra. All rights reserved.
//

#include "OperationsStack.h"
#include <stdlib.h>
#include <string.h>
#include <assert.h>

Operation* createOp(Offer* o, char* opType)
{
    Operation* op = (Operation*)malloc(sizeof(Operation));
    op->o = copyOffer(o);
    
    if (opType != NULL)
    {
        op->opType = (char*)malloc(sizeof(char) * (strlen(opType) + 1));
        strcpy(op->opType, opType);
    }
    else
        op->opType = NULL;
    return op;
}

void destroyOp(Operation* op)
{
    destroyOffer(op->o);
    free(op->opType);
    free(op);
}

Operation* copyOp(Operation* op)
{
    Operation* new = createOp(op->o, op->opType);
    return new;
}

char* getOpType(Operation* op)
{
    return op->opType;
}

Offer* getO(Operation* op)
{
    return op->o;
}





Stack* createStack()
{
    Stack* s = (Stack*)malloc(sizeof(Stack));
    s->len = 0;
    return s;
}


void destroyStack(Stack* s)
{
    for(int i = 0; i < s->len; i++)
        destroyOp(s->operations[i]);
    free(s);
}

int isFull(Stack* s)
{
    if (s->len == 100)
        return 1;
    return 0;
}

int isEmpty(Stack* s)
{
    if (s->len == 0)
        return 1;
    return 0;
}

void pushOp(Stack* s, Operation* op)
{
    if (isFull(s))
        return;
    
    s->operations[s->len++] = copyOp(op);
}

Operation* popOp(Stack* s)
{
    if(isEmpty(s))
        return NULL;
    
    s->len--;
    return s->operations[s->len];
}

// Tests
void testsStack()
{
    Stack* s = createStack();
    
    Offer* o1 = createOffer("mountain", "Milan", "22.07.2019", 270);
    Offer* o2 = createOffer("seaside", "Pisa", "16.03.2019", 600);
    Operation* op1 = createOp(o1, "add");
    Operation* op2 = createOp(o2, "add");
    Operation* op3 = createOp(o1, "delete");
    
    destroyOffer(o1);
    destroyOffer(o2);
    
    pushOp(s, op1);
    pushOp(s, op2);
    pushOp(s, op3);
    
    destroyOp(op1);
    destroyOp(op2);
    destroyOp(op3);
    
    assert(isFull(s) == 0);
    assert(isEmpty(s) == 0);
    
    Operation* op = popOp(s);
    assert(strcmp(getOpType(op), "delete") == 0);
    destroyOp(op);
    
    op = popOp(s);
    assert(strcmp(getOpType(op), "add") == 0);
    destroyOp(op);
    
    op = popOp(s);
    assert(strcmp(getOpType(op), "add") == 0);
    destroyOp(op);
    
    assert(isEmpty(s) == 1);
    
    destroyStack(s);
}


