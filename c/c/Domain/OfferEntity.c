//
//  OfferEntity.c
//  c
//
//  Created by Crisan Alexandra on 08/03/2018.
//  Copyright © 2018 Crisan Alexandra. All rights reserved.
//

#include "OfferEntity.h"
#include <string.h>
#include <stdlib.h>
#include <assert.h>

Offer* createOffer(char *type, char* destination, char* departureDate, int price)
{
    Offer * o = (Offer*)malloc(sizeof(Offer));
    o->type = (char*)malloc(sizeof(char) * (strlen(type) + 1));
    o->destination = (char*)malloc(sizeof(char) * (strlen(destination) + 1));
    o->departureDate = (char*)malloc(sizeof(char) * (strlen(departureDate) + 1));
    
    strcpy(o->type, type);
    strcpy(o->destination, destination);
    strcpy(o->departureDate, departureDate);
    
    o->price = price;
    
    return o;
}

void destroyOffer(Offer* o)
{
    if (o == NULL)
        return;
    free(o->type);
    free(o->destination);
    free(o->departureDate);

    free(o);
}

int checkType(char* type)
{
    if (strcmp(type, "seaside") == 0 || strcmp(type, "mountain") == 0 || strcmp(type, "citybreak") == 0)
        return 1;
    
    return 0;
        
}

Offer* copyOffer(Offer* o)
{
    Offer* new = createOffer(getType(o), getDestination(o), getDepartureDate(o), getPrice(o));
    return new;
}

int getDay(char* departureDate)
{
    char *token;
    char s[20];
    Offer* o = createOffer("seaside", "Cluj", departureDate, 0);
    token = strtok(o->departureDate, ".");
    int i = 0;
    while(token != NULL)
    {
        if(i == 0)
            strcpy(s, token);
        token = strtok(NULL, ".");
        i++;
    }
    destroyOffer(o);
    int n = atoi(s);
    return n;
}


int getMonth(char* departureDate)
{
    char *token;
    char s[20];
    Offer* o = createOffer("seaside", "Cluj", departureDate, 0);
    token = strtok(o->departureDate, ".");
    int i = 0;
    while(token != NULL)
    {
        if(i == 1)
            strcpy(s, token);
        token = strtok(NULL, ".");
        i++;
    }
    destroyOffer(o);
    int n = atoi(s);
    return n;
}

int getYear(char* departureDate)
{
    char *token;
    char s[20];
    Offer* o = createOffer("seaside", "Cluj", departureDate, 0);
    token = strtok(o->departureDate, ".");
    int i = 0;
    while(token != NULL)
    {
        if(i == 2)
            strcpy(s, token);
        token = strtok(NULL, ".");
        i++;
    }
    destroyOffer(o);
    int n = atoi(s);
    return n;
}

int checkDate(Offer* o, char* departureDate)
{
    int o_day = getDay(o->departureDate);
    int o_month = getMonth(o->departureDate);
    int o_year = getYear(o->departureDate);

    int d_day = getDay(departureDate);
    int d_month = getMonth(departureDate);
    int d_year = getYear(departureDate);
    
    if (o_year > d_year)
        return 1;
    
    if (o_year == d_year)
        if(o_month > d_month)
            return 1;
    
    if (o_month == d_month)
        if(o_day >= d_day)
            return 1;
    return 0;
}

char* getType(Offer* o)
{
    return o->type;
}

char* getDestination(Offer* o)
{
    return o->destination;
}

char* getDepartureDate(Offer* o)
{
    return o->departureDate;
}

int getPrice(Offer* o)
{
    return o->price;
}

void toString(Offer* o)
{
    printf("Offer: type %s, destination %s, departure date %s, and price %d\n", o->type, o->destination, o->departureDate, o->price);
}


//Tests

void testCreate()
{
    Offer* o = createOffer("seaside", "Paris", "23.04.2019", 200);
    assert(strcmp(o->type, "seaside") == 0);
    assert(strcmp(o->destination, "Paris") == 0);
    assert(strcmp(o->departureDate, "23.04.2019") == 0);
    assert(o->price == 200);
    destroyOffer(o);
}

void testCheckType()
{
    int t1 = checkType("seaside");
    int t2 = checkType("dasj");
    int t3 = checkType("mountainfdf");

    assert(t1 == 1);
    assert(t2 == 0);
    assert(t3 == 0);
}

void testCopy()
{
    Offer* o1 = createOffer("seaside", "Paris", "23.04.2019", 200);
    Offer* o2 = copyOffer(o1);
    assert(strcmp(o1->type, o2->type) == 0);
    assert(strcmp(o1->destination, o2->destination) == 0);
    assert(strcmp(o1->departureDate, o2->departureDate) == 0);
    assert(o1->price == o2->price);
    destroyOffer(o1);
    destroyOffer(o2);
}

void testGetDay()
{
    char* departureDate = "22.07.2018";
    
    assert(getDay(departureDate) == 22);
}

void testGetMonth()
{
    char* departureDate = "22.07.2018";

    assert(getMonth(departureDate) == 7);
}

void testGetYear()
{
    char* departureDate = "22.07.2018";
    
    assert(getYear(departureDate) == 2018);
}

void testCheckDate()
{
    Offer* o = createOffer("mountain", "Milan", "22.07.2019", 270);
    assert(checkDate(o, "10.06.2019") == 1);
    assert(checkDate(o, "15.08.2019") == 0);
    destroyOffer(o);
}

void testGetType()
{
    Offer* o = createOffer("mountain", "Milan", "22.07.2019", 270);
    assert(strcmp(getType(o), "mountain") == 0);
    destroyOffer(o);
}

void testGetDestination()
{
    Offer* o = createOffer("mountain", "Milan", "22.07.2019", 270);
    assert(strcmp(getDestination(o), "Milan") == 0);
    destroyOffer(o);
}

void testGetDepartureDate()
{
    Offer* o = createOffer("mountain", "Milan", "22.07.2019", 270);
    assert(strcmp(getDepartureDate(o), "22.07.2019") == 0);
    destroyOffer(o);
}

void testGetPrice()
{
    Offer* o = createOffer("mountain", "Milan", "22.07.2019", 270);
    assert(getPrice(o) == 270);
    destroyOffer(o);
}

void testsOfferEntity()
{
    testCreate();
    testCheckType();
    testCopy();
    testGetDay();
    testGetMonth();
    testGetYear();
    testCheckDate();
    testGetType();
    testGetDestination();
    testGetDepartureDate();
    testGetPrice();
}

