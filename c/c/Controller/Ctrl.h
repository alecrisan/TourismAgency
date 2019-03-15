//
//  Ctrl.h
//  c
//
//  Created by Crisan Alexandra on 10/03/2018.
//  Copyright © 2018 Crisan Alexandra. All rights reserved.
//

#ifndef Ctrl_h
#define Ctrl_h

#include <stdio.h>
#include "Repo.h"
#include "OperationsStack.h"

typedef struct
{
    OfferRepo* repo;
    Stack* undoS;
    Stack* redoS;
}Ctrller;

/*
 Creates a controller
 Input: repo - pointer to the repo
 Output: a Ctrller
 */
Ctrller* createController(OfferRepo* repo, Stack* undoS, Stack* redoS);


/*
 Destroys the controller
 Input: c - pointer to the controller
 Output: None
 */
void destroyController(Ctrller* c);


/*
 Adds an offer - first it creates an offer with the given information and then
 calls the add function in the repo
 Input: c - pointer to the controller
        type - a string
        destination - a string
        departureDate - a string
        price - an integer
        UndoOrRedo - an integer, 1 if the operation can be recorded for Undo, 0 for Redo
 Output: 0 if the given offer is already in the repo
        -1 if the given type is not one of: seaside/mountain/citybreak
        1 if the offer was added
 */
int addOffer(Ctrller* c, char* type, char* destination, char* departureDate, int price, int UndoOrRedo);



/*
 Deletes an offer if it exists -  calls the delete function in the repo
 An offer is uniquely identified by its destination and departureDate
 Input: c - pointer to the controller
        destination - a string
        departureDate - a string
        UndoOrRedo - an integer, 1 if the operation can be recorded for Undo, 0 for Redo
 Output: 0 if the given offer doesn't exist
        1 if it was deleted successfully
 */
int delOffer(Ctrller* c, char* destination, char* departureDate, int UndoOrRedo);



/*
 Updates an offer if it exists - first it creates an offer with the new information and then
 An offer is uniquely identified by its destination and departureDate
 Input: c - pointer to the controller
        destination - a string
        departureDate - a string
        newType - a string
        newDestination - a string
        newDepartureDate - a string
        newPrice - an integer
        UndoOrRedo - an integer, 1 if the operation can be recorded for Undo, 0 for Redo
 Output: 0 if the given offer doesn't exist/the new type entered is not valid
        1 if it was updated successfully
 */
int updateOffer(Ctrller* c, char* destination, char* departureDate, char* newType, char* newDestination, char* newDepartureDate, int newPrice, int UndoOrRedo);


/*
 Gets the repository from the controller
 Input: c - pointer to the controller
 Output: pointer to the repo
 */
OfferRepo* getRepo(Ctrller* c);


/*
 Performs an undo on the last operation
 Input: c - pointer to the controller
 Output: 1 if the undo was successful, 0 otherwise
 */
int undo(Ctrller* c);


/*
 Performs an redo on the last operation
 Input: c - pointer to the controller
 Output: 1 if the redo was successful, 0 otherwise
 */
int redo(Ctrller* c);

 /*
  Initialises the controller with some data
  Input: c - pointer to the controller
  Output: None
  */
void initCtrller(Ctrller* c);
 
 /*
 Contains some tests for the implemented functionalities
 Input: None
 Output: None
 */
void testsController(void);

#endif /* Ctrl_h */
