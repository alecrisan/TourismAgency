//
//  Ctrl.c
//  c
//
//  Created by Crisan Alexandra on 10/03/2018.
//  Copyright © 2018 Crisan Alexandra. All rights reserved.
//

#include "Ctrl.h"
#include "Repo.h"
#include "assert.h"
#include <stdlib.h>
#include <string.h>

Ctrller* createController(OfferRepo* repo, Stack* undoS, Stack* redoS)
{
    Ctrller* c = (Ctrller*)(malloc(sizeof(Ctrller)));
    c->repo = repo;
    c->undoS = undoS;
    c->redoS = redoS;
    return c;
}

void destroyController(Ctrller* c)
{
    destroyRepo(c->repo);
    destroyStack(c->undoS);
    destroyStack(c->redoS);
    free(c);
}

int addOffer(Ctrller* c, char* type, char* destination, char* departureDate, int price, int UndoOrRedo)
{
    Offer* o = createOffer(type, destination, departureDate, price);
    int result = add(c->repo, o);
    
    if (result == 1)
    {
        
        if (UndoOrRedo == 1)
        {
            Operation* op = createOp(o, "add");
            pushOp(c->undoS, op);
            destroyOp(op);
        }
        if (UndoOrRedo == 0)
        {
            Operation* op = createOp(o, "add");
            pushOp(c->redoS, op);
            destroyOp(op);
        }
        
    }
    
    destroyOffer(o);
    
    return result;
    
}

int delOffer(Ctrller* c, char* destination, char* departureDate, int UndoOrRedo)
{
    int poz = findOffer(c->repo, destination, departureDate);
    Offer* o = getOffer(c->repo, poz);
    Offer* copy = copyOffer(o);
    int result = del(c->repo, destination, departureDate);
    
    if (result == 1)
    {

        if (UndoOrRedo == 1)
        {
            Operation* op = createOp(copy, "delete");
            pushOp(c->undoS, op);
            destroyOp(op);
        }
        if (UndoOrRedo == 0)
        {
            Operation* op = createOp(copy, "delete");

            pushOp(c->redoS, op);
            destroyOp(op);
        }
        
    }
    
    destroyOffer(copy);
    return result;
}

int updateOffer(Ctrller* c, char* destination, char* departureDate, char* newType, char* newDestination, char* newDepartureDate, int newPrice, int UndoOrRedo)
{
    Offer* o = createOffer(newType, newDestination, newDepartureDate, newPrice);
    int poz = findOffer(c->repo, destination, departureDate);
    if(poz == -1)
        return 0;
    Offer* old = getOffer(c->repo, poz);
    Offer* copy = copyOffer(old);
    int result = update(c->repo, destination, departureDate, o);
    
    if (result == 1)
    {
        if(UndoOrRedo == 1)
        {
            Operation* op = createOp(copy, "delete");
            pushOp(c->undoS, op);
            destroyOp(op);

            Operation* op2 = createOp(o, "add");
            pushOp(c->undoS, op2);
            destroyOp(op2);
        }
        if(UndoOrRedo == 0)
        {
            Operation* op = createOp(copy, "delete");
            pushOp(c->undoS, op);
            destroyOp(op);

            Operation* op2 = createOp(o, "add");
            pushOp(c->undoS, op2);
            destroyOp(op2);
        }
    }
    destroyOffer(old);
    destroyOffer(copy);
    
    return result;
}

OfferRepo* getRepo(Ctrller* c)
{
    return c->repo;
}

int undo(Ctrller* c)
{
    if (isEmpty(c->undoS))
        return 0;
    
    Operation* op = popOp(c->undoS);
    
    if (strcmp(getOpType(op), "add") == 0)
    {
        Offer* o = getO(op);
        char destination[20], departureDate[20];
        strcpy(destination, o->destination);
        strcpy(departureDate, o->departureDate);
        delOffer(c, destination, departureDate, 0);
    }
    else if (strcmp(getOpType(op), "delete") == 0)
    {
        Offer* o = getO(op);
        Offer* copy = copyOffer(o);
        addOffer(c, copy->type, copy->destination, copy->departureDate, copy->price, 0);
    }

    destroyOp(op);
    return 1;
}

int redo(Ctrller* c)
{
    if (isFull(c->redoS))
        return 0;
    if (isEmpty(c->redoS))
        return 0;
    
    Operation* op = popOp(c->redoS);
    
    if (strcmp(getOpType(op), "add") == 0)
    {
        Offer* o = getO(op);
        char destination[20], departureDate[20];
        strcpy(destination, o->destination);
        strcpy(departureDate, o->departureDate);
        delOffer(c, destination, departureDate, 1);
    }
    else if (strcmp(getOpType(op), "delete") == 0)
    {
        Offer* o = getO(op);
        Offer* copy = copyOffer(o);
        addOffer(c, copy->type, copy->destination, copy->departureDate, copy->price, 1);
    }
    return 1;
}

void initCtrller(Ctrller* c)
{
    addOffer(c, "seaside", "Romania", "04.05.2019", 340, 2);
    addOffer(c,"mountain", "Milan", "22.01.2019", 200, 2);
    addOffer(c,"citybreak", "London", "04.12.2018", 50, 2);
    addOffer(c,"seaside", "Constanta", "17.06.2018", 200, 2);
    addOffer(c,"citybreak", "Barcelona", "20.08.2019", 300, 2);
    addOffer(c,"citybreak", "Oradea", "10.05.2018", 110, 2);
    addOffer(c,"mountain", "Nice", "14.03.2017", 100, 2);
    addOffer(c,"seaside", "Lefkada", "13.07.2018", 400, 2);
    addOffer(c,"seaside", "Valencia", "07.06.2019", 350, 2);
    addOffer(c,"mountain", "Paris", "30.11.2018", 270, 2);
}

//Tests

void testAddOffer()
{

    OfferRepo* repo = createRepo();
    Stack* undoS = createStack();
    Stack* redoS = createStack();
    Ctrller* c = createController(repo, undoS, redoS);
    addOffer(c, "seaside", "Pisa", "16.03.2019", 600, 2);
    
    assert(addOffer(c, "mountain", "Milan", "22.07.2019", 270, 2) == 1);
    
    destroyController(c);

}

void testDelOffer()
{

    OfferRepo* repo = createRepo();
    Stack* undoS = createStack();
    Stack* redoS = createStack();
    Ctrller* c = createController(repo, undoS, redoS);
    addOffer(c, "seaside", "Pisa", "16.03.2019", 600, 2);
    
    assert(delOffer(c, "Pisa", "16.03.2019", 2) == 1);
    
    destroyController(c);

}

void testUpdateOffer()
{

    OfferRepo* repo = createRepo();
    Stack* undoS = createStack();
    Stack* redoS = createStack();
    Ctrller* c = createController(repo, undoS, redoS);
    addOffer(c, "seaside", "Pisa", "16.03.2019", 600, 2);

    assert(updateOffer(c, "Pisa", "16.03.2019", "mountain", "Milan", "22.07.2019", 270, 2) == 1);

    destroyController(c);
}


void testsController()
{
    testAddOffer();
    testDelOffer();
    testUpdateOffer();
}

