//
//  DynamicArray.h
//  c
//
//  Created by Crisan Alexandra on 15/03/2018.
//  Copyright © 2018 Crisan Alexandra. All rights reserved.
//

#ifndef DynamicArray_h
#define DynamicArray_h

#include <stdio.h>
#include "OfferEntity.h"

typedef Offer* TElement;

typedef struct
{
    TElement* elems;
    int len;
    int capacity;
}DynamicArray;

/*
 Creates a dynamic array of generic elements
 Input: capacity - an integer representing the maximum capacity of the array
 Output: a pointer to the dynamic array created
 */
DynamicArray* createDA(int capacity);

/*
 Destroys a dynamic array
 Input: da - a pointer to the array that needs to be destroyed
 Output: None
 */
void destroyDA(DynamicArray* da);

/*
 Resizes the array
 Input: da - a pointer to the dynamic array
 Output: 0 if it was resized successfully, -1 otherwise
 */
int resize(DynamicArray* da);

/*
 Adds an element to the dynamic array
 Input: da - pointer to the array
        e - the element(offer) to be added
 */
void addEl(DynamicArray* da, TElement e);

/*
 Deletes an element from the dynamic array with a given position
 Input: da - pointer to the array
        poz - integer representing the position
 Output: None
 */
void deleteEl(DynamicArray* da, int poz);

/*
 Updates an element from the dynamic array
 Input: da - pointer to the array
        poz - integer representing the position
        e - the new element that replaces the old one
 Output: None
 */
void updateEl(DynamicArray* da, int poz, TElement e);

/*
 Gets the length of the dynamic array
 Input: da - pointer to the array
 Output: an integer
 */
int getLenDA(DynamicArray* da);

/*
 Gets an element from the dynamic array
 Input: da - pointer to the array
        poz - an integer representing the position
 Output: an element(offer)
 */
TElement getElem(DynamicArray* da, int poz);

/*
 Contains some tests for the implemented functionalities
 Input: None
 Output: None
 */
void testsDynamicArray(void);

#endif /* DynamicArray_h */
