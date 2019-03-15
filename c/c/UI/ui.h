//
//  ui.h
//  c
//
//  Created by Crisan Alexandra on 10/03/2018.
//  Copyright © 2018 Crisan Alexandra. All rights reserved.
//

#ifndef ui_h
#define ui_h

#include <stdio.h>
#include "Ctrl.h"

typedef struct
{
    Ctrller* c;
}UI;

/*
 Creates a UI
 Input: c - pointer to the controller
 Output: a UI
 */
UI* createUI(Ctrller* c);


/*
 Destroys the UI
 Input: ui - pointer to the UI
 Output: None
 */
void destroyUI(UI* ui);

/*
 Prints out the menu
 Input: None
 Output: the menu is printed on the console
 */
void printMenu(void);



/*
 Prints out all the offers
 Input: ui - pointer to the UI
 Output: the offers are printed on the console
 */
void printAllOffers(UI* ui);



/*
 Prints out all the offers that contain a given string in the destination
 Input: ui - pointer to the UI
        str - a string
 Output: the offers are printed on the console
 */
void printWithGivenStr(UI* ui, char* str);



/*
 Prints out all the offers that contain a given destination
 Input: ui - pointer to the UI
        destination - a string
 Output: the offers are printed on the console
 */
void printWithGivenDest(UI* ui, char* destination);



/*
 Prints out all the offers that contain a given type
 Input: ui - pointer to the UI
        type - a string
 Output: the offers are printed on the console
 */
void printWithGivenType(UI* ui, char* type);


/*
 Prints out all the offers of a given type, starting from a given date
 Input: ui - pointer to the UI
        type - a string
        departureDate - a string
 Output: the offers are printed on the console
 */
void printStartingWithGivenDate(UI* ui, char* type, char* departureDate);


/*
 Prints out all the offers of a given type, with a price less than a given value
 Input: ui - pointer to the UI
        type - a string
        price - integer
 Output: the offers are printed on the console
 */
void printWithGivenTypeAndPrice(UI* ui, char* type, int price);


/*
 Function that starts the program
 Input: ui - pointer to the ui
 Output: None
 */
void start(UI* ui);

#endif /* ui_h */
