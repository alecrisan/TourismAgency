//
//  Repo.h
//  c
//
//  Created by Crisan Alexandra on 08/03/2018.
//  Copyright © 2018 Crisan Alexandra. All rights reserved.
//

#ifndef Repo_h
#define Repo_h

#include <stdio.h>
#include "OfferEntity.h"
#include "DynamicArray.h"

typedef struct
{
    DynamicArray* OffersList;
}OfferRepo;



/*
 Creates a repo
 Input: None
 Output: an OfferRepo
 */
OfferRepo* createRepo(void);


/*
 Destroys the repo
 Input: repo - pointer to the repo
 Output: None
 */
void destroyRepo(OfferRepo* repo);


/*
 Checks if an Offer is already in the repo
 Input: repo - pointer to the repo
        offer - pointer to a given offer
 Output: 0 if it's in the repo already, 1 if it's not
 */
int checkOffer(OfferRepo* repo, Offer* offer);



/*
 Searches for an offer in the repo
 An offer is uniquely identified by its destination and departureDate
 Input: repo - pointer to the repo
        destination - a string
        departureDate - a string
 Output: if the offer is found, it returns its position, -1 otherwise
 */
int findOffer(OfferRepo* repo, char* destination, char* departureDate);



/*
 Adds an offer to the repo if it passes all the criteria
 Input: repo - pointer to repo
        offer - pointer to an offer
 Output: 0 if the given offer is already in the repo
        -1 if the given type is not one of: seaside/mountain/citybreak
        1 if the offer was added
 */
int add(OfferRepo* repo, Offer* offer);



/*
 Deletes an offer if it exists in the repo
 An offer is uniquely identified by its destination and departureDate
 Input: repo - pointer to repo
        destination - a string
        departureDate - a string
 Output: 0 if the given offer doesn't exist
        1 if it was deleted successfully
 */
int del(OfferRepo* repo, char* destination, char* departureDate);



/*
 Updates an offer if it exists in the repo
 An offer is uniquely identified by its destination and departureDate
 Input: repo - pointer to repo
        destination - a string
        departureDate - a string
        offer - a pointer to the new updated offer
 Output: 0 if the given offer doesn't exist/the type entered is not valid
        1 if it was updated successfully
 */
int update(OfferRepo* repo, char* destination, char* departureDate, Offer* offer);



/*
 Sorts the list of offers ascending by price
 Input: repo - pointer to the repo
 Output: None
 */
void sortByPrice(OfferRepo* repo);



/*
 Sorts the list of offers ascending by month
 Input: repo - pointer to the repo
 Output: None
 */
void sortByMonth(OfferRepo* repo);



/*
 Sorts the list of offers ascending by destination
 Input: repo - pointer to the repo
 Output: None
 */
void sortByDestination(OfferRepo* repo);


/*
 Gets the length of the repo
 Input: repo - pointer to the repo
 Output: an integer
 */
int getRepoLen(OfferRepo* repo);



/*
 Gets the offer on a given position in the repo
 Input: repo - pointer to the repo
        poz - an integer that gives the position
 Output: a pointer to the searched offer
 */
Offer* getOffer(OfferRepo* repo, int poz);


/*
 Contains some tests for the implemented functionalities
 Input: None
 Output: None
 */
void testsOfferRepo(void);

#endif /* Repo_h */
