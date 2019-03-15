//
//  DynamicArray.c
//  c
//
//  Created by Crisan Alexandra on 15/03/2018.
//  Copyright © 2018 Crisan Alexandra. All rights reserved.
//

#include "DynamicArray.h"
#include <stdlib.h>
#include <assert.h>
#include <string.h>

DynamicArray* createDA(int capacity)
{
    DynamicArray* da = (DynamicArray*)malloc(sizeof(DynamicArray));
    da->capacity = capacity;
    da->len = 0;
    
    da->elems = (TElement*)malloc(capacity * sizeof(TElement));
    if (da->elems == NULL)
        return NULL;
    return da;
}

void destroyDA(DynamicArray* da)
{
    if (da == NULL)
        return;
    for(int i = 0; i < da->len; i++)
        destroyOffer(da->elems[i]);
    
    free(da->elems);
    da->elems = NULL;
    
    free(da);
    da = NULL;
}

int resize(DynamicArray* da)
{
    da->capacity = da->capacity * 2;
    
    TElement* aux = (TElement*)realloc(da->elems, da->capacity * sizeof(TElement));
    if (aux == NULL)
        return -1;
    da->elems = aux;
    
    return 0;
}

void addEl(DynamicArray* da, TElement e)
{
    if (da->len == da->capacity)
        resize(da);
    da->elems[da->len++] = e;
}

void deleteEl(DynamicArray* da, int poz)
{
    if(poz < 0 || poz >= da->len)
        return;
    for(int i = poz; i < da->len - 1; i++)
        da->elems[i] = da->elems[i + 1];
    da->len--;
}

void updateEl(DynamicArray* da, int poz, TElement e)
{
    if(poz < 0 || poz >= da->len)
        return;
    
    deleteEl(da, poz);
    addEl(da, e);
}

int getLenDA(DynamicArray* da)
{
    return da->len;
}

TElement getElem(DynamicArray* da, int poz)
{
    return da->elems[poz];
}


// Tests

void testsDynamicArray()
{
    DynamicArray* da = createDA(2);
    
    assert(da->capacity == 2);
    assert(da->len == 0);
    
    Offer* o1 = createOffer("mountain", "Milan", "22.07.2019", 270);
    addEl(da, o1);
    assert(da->len == 1);
    
    Offer* o2 = createOffer("seaside", "Pisa", "16.05.2018", 600);
    addEl(da, o2);
    assert(da->len == 2);
    
    Offer* o3 = createOffer("seaside", "London", "16.05.2017", 400);
    addEl(da, o3);
    assert(da->len == 3);
    assert(da->capacity == 4);
    
    Offer* o = getElem(da, 0);
    deleteEl(da, 0);
    destroyOffer(o);
    
    o = getElem(da, 0);
    assert(strcmp(getDestination(o), "Pisa") == 0);
    assert(da->len == 2);
    
    Offer* offer = createOffer("seaside", "Paris", "16.06.2018", 400);
    updateEl(da, 0, offer);
    
    destroyOffer(o2);
    
    Offer* of = getElem(da, 1);
    assert(strcmp(getDestination(of), "Paris") == 0);
    assert(da->len == 2);

    
    destroyDA(da);
}

