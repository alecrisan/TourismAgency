//
//  OfferEntity.h
//  c
//
//  Created by Crisan Alexandra on 08/03/2018.
//  Copyright © 2018 Crisan Alexandra. All rights reserved.
//

#ifndef OfferEntity_h
#define OfferEntity_h

#include <stdio.h>

typedef struct
{
    char *type;
    char *destination;
    char *departureDate;
    int price;
}Offer;

/*
 Creates an entity of type 'Offer'
 Input: type - a string, the type of the offer (seaside/mountain/citybreak)
        destination - a string
        departureDate - a string (format: dd.mm.yyyy)
        price - integer
 Output: o -  pointer to an offer
 */
Offer* createOffer(char *type, char* destination, char* departureDate, int price);


/*
 Destroys an offer
 Input: o - pointer to an offer
 Output: None
 */
void destroyOffer(Offer* o);


/*
 Checks if the given type is valid(seaside/mountain/citybreak)
 Input: type - a string
 Output: 1 if it's valid, 0 otherwise
 */
int checkType(char* type);

/*
 Makes a copy of an offer
 Input: o - pointer to an offer
 Output: a pointer to the copy
 */
Offer* copyOffer(Offer* o);

/*
 Gets the day from a date and converts it to an integer
 Input: departureDate - a string
 Output: an integer containing the day
 */
int getDay(char* departureDate);


/*
 Gets the month from a date and converts it to an integer
 Input: departureDate - a string
 Output: an integer containing the month
 */
int getMonth(char* departureDate);


/*
 Gets the year from a date and converts it to an integer
 Input: departureDate - a string
 Output: an integer containing the year
 */
int getYear(char* departureDate);


/*
 Checks if an offer's date is after a given date
 Input: o - pointer to an offer
        departureDate - a string
 Output: 1 if it is, 0 otherwise
 */
int checkDate(Offer* o, char* departureDate);


/*
 Gets the type of an Offer
 Input: o - pointer to an offer
 Output: a pointer to a string
 */
char* getType(Offer* o);

/*
 Gets the destination of an Offer
 Input: o - pointer to an offer
 Output: a pointer to a string
 */
char* getDestination(Offer* o);

/*
 Gets the departure date of an Offer
 Input: o - pointer to an offer
 Output: a pointer to a string
 */
char* getDepartureDate(Offer* o);

/*
 Gets the price of an Offer
 Input: o - pointer to an offer
 Output: an integer
 */
int getPrice(Offer* o);

/*
 Pretty prints an Offer
 Input: o - pointer to an offer
 Output: the information is printed on the console
 */
void toString(Offer* o);

/*
 Contains some tests for the implemented functionalities
 Input: None
 Output: None
 */
void testsOfferEntity(void);

#endif /* OfferEntity_h */
