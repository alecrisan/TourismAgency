//
//  Repo.c
//  c
//
//  Created by Crisan Alexandra on 08/03/2018.
//  Copyright © 2018 Crisan Alexandra. All rights reserved.
//

#include "Repo.h"
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#define capacity 100

OfferRepo* createRepo()
{
    OfferRepo* repo = (OfferRepo*)(malloc(sizeof(OfferRepo)));
    repo->OffersList = createDA(capacity);
    return repo;
}

void destroyRepo(OfferRepo* repo)
{
    if (repo == NULL)
        return;  
    destroyDA(repo->OffersList);
    free(repo);
}

int checkOffer(OfferRepo* repo, Offer* offer)
{
    int j = 0;
    for (j = 0; j < getLenDA(repo->OffersList); j++)
    {
        Offer* o = getElem(repo->OffersList, j);
        if (strcmp(o->destination, offer->destination) == 0 && strcmp(o->departureDate, offer->departureDate) == 0)
            return 0;
    }
    return 1;
}

int findOffer(OfferRepo* repo, char* destination, char* departureDate)
{
    int i, poz = 0, ok = 0;
    for (i = 0; i < getLenDA(repo->OffersList); i++)
    {
        Offer* o = getElem(repo->OffersList, i);
        if ((strcmp(o->destination, destination) == 0) && (strcmp(o->departureDate, departureDate) == 0))
        {
            poz = i;
            ok = 1;
        }
    }
    if (ok == 0)
        return -1;
    return poz;
}

int add(OfferRepo* repo, Offer* offer)
{
    if (checkOffer(repo, offer) == 0)
        return 0;
    if (checkType(offer->type) == 0)
        return -1;
    Offer* copy = copyOffer(offer);
    addEl(repo->OffersList, copy);
    return 1;
}

int del(OfferRepo* repo, char* destination, char* departureDate)
{
    int poz = findOffer(repo, destination, departureDate);

    if (poz == -1)
        return 0;
    
    Offer* o = getElem(repo->OffersList, poz);

    deleteEl(repo->OffersList, poz);
    
    destroyOffer(o);
    return 1;
}

int update(OfferRepo* repo, char* destination, char* departureDate, Offer* offer)
{
    int poz = findOffer(repo, destination, departureDate);
    if (poz == -1)
        return 0;
    if (checkType(offer->type) == 0)
        return 0;
    updateEl(repo->OffersList, poz, offer);
    return 1;
}

void sortByPrice(OfferRepo* repo)
{
    int i,j;
    Offer* aux;
    for(i = 0; i < getLenDA(repo->OffersList); i++)
    {
        Offer* o1 = getElem(repo->OffersList, i);
        for(j = 0; j < getLenDA(repo->OffersList) - 1; j++)
        {
            Offer* o2 = getElem(repo->OffersList, j);
            if(o1->price < o2->price)
            {
                aux = repo->OffersList->elems[i];
                repo->OffersList->elems[i] = repo->OffersList->elems[j];
                repo->OffersList->elems[j] = aux;
            }
        }
    }
}


void sortByMonth(OfferRepo* repo)
{
    int i,j;
    Offer* aux;
    for(i = 0; i < getLenDA(repo->OffersList); i++)
    {
        Offer* o1 = getElem(repo->OffersList, i);
        for(j = 0; j < getLenDA(repo->OffersList) - 1; j++)
        {
            Offer* o2 = getElem(repo->OffersList, j);
            if(getMonth(o1->departureDate) < getMonth(o2->departureDate))
            {
                aux = repo->OffersList->elems[i];
                repo->OffersList->elems[i] = repo->OffersList->elems[j];
                repo->OffersList->elems[j] = aux;
            }
        }
    }
}

void sortByDestination(OfferRepo* repo)
{
    int i,j;
    Offer* aux;
    for(i = 0; i < getLenDA(repo->OffersList); i++)
    {
        Offer* o1 = getElem(repo->OffersList, i);
        for(j = 0; j < getLenDA(repo->OffersList) - 1; j++)
        {
            Offer* o2 = getElem(repo->OffersList, j);
            if(strcmp(o1->destination, o2->destination) < 0)
            {
                aux = repo->OffersList->elems[i];
                repo->OffersList->elems[i] = repo->OffersList->elems[j];
                repo->OffersList->elems[j] = aux;
            }
        }
    }
}

int getRepoLen(OfferRepo* repo)
{
    return getLenDA(repo->OffersList);
}

Offer* getOffer(OfferRepo* repo, int poz)
{
    return getElem(repo->OffersList, poz);
}

// Tests


void testCheckOffer()
{
    Offer* o1 = createOffer("mountain", "Milan", "22.07.2019", 270);
    OfferRepo* repo = createRepo();
    Offer* o = createOffer("seaside", "Pisa", "16.03.2019", 600);
    add(repo,o);

    assert(checkOffer(repo, o1) == 1);
    assert(checkOffer(repo, o) == 0);
    
    destroyRepo(repo);
    destroyOffer(o1);
    destroyOffer(o);
}

void testFindOffer()
{

    OfferRepo* repo = createRepo();
    Offer* o = createOffer("seaside", "Pisa", "16.03.2019", 600);
    add(repo,o);

    assert(findOffer(repo, "Pisa", "16.03.2019") == 0); // it's on position 0
    assert(findOffer(repo, "Milan", "16.05.2019") == -1); // not found
    
    destroyRepo(repo);
    destroyOffer(o);
    
}

void testAdd()
{
    Offer* o = createOffer("mountain", "Milan", "22.07.2019", 270);

    OfferRepo* repo = createRepo();
    Offer* o1 = createOffer("seaside", "Pisa", "16.03.2019", 600);
    add(repo,o1);
    
    assert(getRepoLen(repo) == 1);

    assert(add(repo, o) == 1);
    assert(getRepoLen(repo) == 2);

    assert(add(repo, o) == 0);
    
    destroyOffer(o);
    destroyOffer(o1);
    destroyRepo(repo);
}

void testDelete()
{

    OfferRepo* repo = createRepo();
    Offer* o = createOffer("seaside", "Pisa", "16.03.2019", 600);
    add(repo,o);
    assert(getRepoLen(repo) == 1);

    assert(del(repo, "Pisa", "16.03.2019") == 1);
    assert(getRepoLen(repo) == 0);
    
    destroyOffer(o);
    destroyRepo(repo);
    
}

void testUpdate()
{
    OfferRepo* repo = createRepo();
    Offer* o = createOffer("mountain", "Milan", "22.07.2019", 270);

    int rez = update(repo, "Ro", "12.04.2019", o);
    assert(rez == 0);

    destroyOffer(o);
    destroyRepo(repo);
}

void testGetLen()
{
    OfferRepo* repo = createRepo();
    Offer* o1 = createOffer("seaside", "Pisa", "16.03.2019", 600);
    add(repo,o1);
    assert(getRepoLen(repo) == 1);
    
    Offer* o = createOffer("mountain", "Milan", "22.07.2019", 270);
    add(repo, o);

    assert(getRepoLen(repo) == 2);
    
    destroyOffer(o);
    destroyOffer(o1);
    destroyRepo(repo);
}

void testGetOffer()
{
    Offer* o1 = createOffer("seaside", "Pisa", "16.03.2019", 600);
    OfferRepo* repo = createRepo();
    Offer* o2 = createOffer("seaside", "Pisa", "16.03.2019", 600);
    add(repo,o2);
    
    
    assert(strcmp(o1->type, o2->type) == 0);
    assert(strcmp(o1->destination, o2->destination) == 0);
    assert(strcmp(o1->departureDate, o2->departureDate) == 0);
    assert(o1->price == o2->price);
    
    destroyOffer(o1);
    destroyOffer(o2);
    destroyRepo(repo);
}

void testsOfferRepo()
{
    testCheckOffer();
    testFindOffer();
    testAdd();
    testDelete();
    testUpdate();
    testGetLen();
    testGetOffer();
}


