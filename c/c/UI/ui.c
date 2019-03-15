//
//  ui.c
//  c
//
//  Created by Crisan Alexandra on 10/03/2018.
//  Copyright © 2018 Crisan Alexandra. All rights reserved.
//

#include "ui.h"
#include <string.h>
#include <stdlib.h>

UI* createUI(Ctrller* c)
{
    UI* ui = (UI*)malloc(sizeof(UI));
    ui->c = c;
    return ui;
}


void destroyUI(UI* ui)
{
    destroyController(ui->c);
    free(ui);
}

void printMenu()
{
    printf("1. List all offers\n");
    printf("2. Add an offer\n");
    printf("3. Delete an offer\n");
    printf("4. Update an offer\n");
    printf("5. List all offers that contain a certain destination(sorted ascending by price)\n");
    printf("6. List all offers with a given destination(sorted ascending by departure month)\n");
    printf("7. List all offers with a given type(sorted ascending by destination)\n");
    printf("8. List all offers of a given type, starting with a given date\n");
    printf("9. List all offers having a given type and a price less than a given value, sorted ascending by price\n");
    printf("u - Undo\n");
    printf("r - Redo\n");
    printf("0. Exit the program\n");
}

void printAllOffers(UI* ui)
{
    OfferRepo* repo = getRepo(ui->c);
    if (getRepoLen(repo) != 0)
        for (int i = 0; i < getRepoLen(repo) ; i++)
        {
            printf("%d. ", i + 1);
            toString(getOffer(repo, i));
        }
    else printf("None\n");
}


void printWithGivenStr(UI* ui, char* str)
{
    int ok = 0;
    OfferRepo* repo = getRepo(ui->c);
    sortByPrice(repo);
    if (strcmp(str, "null") == 0)
        printAllOffers(ui);
    else
        for (int i = 0; i < getRepoLen(repo); i++)
        {
            Offer* o = getOffer(repo, i);
            if (strstr(getDestination(o), str) != 0)
            {
                ok = 1;
                toString(getOffer(repo, i));
            }
        }
    if (ok == 0)
        printf("No matches\n");
}

void printWithGivenDest(UI* ui, char* destination)
{
    int ok = 0;
    OfferRepo* repo = getRepo(ui->c);
    sortByMonth(repo);
    if (strcmp(destination, "null") == 0)
        printAllOffers(ui);
    else
        for (int i = 0; i < getRepoLen(repo) ; i++)
        {
            Offer* o = getOffer(repo, i);
            if (strcmp(destination, o->destination) == 0)
            {
                ok =1;
                toString(getOffer(repo, i));
            }
        }
    if (ok == 0)
        printf("No matches.\n");
}

void printWithGivenType(UI* ui, char* type)
{
    int ok = 0;
    OfferRepo* repo = getRepo(ui->c);
    sortByDestination(repo);
    for (int i = 0; i < getRepoLen(repo) ; i++)
    {
        Offer* o = getOffer(repo, i);
        if (strcmp(type, o->type) == 0)
        {
            ok = 1;
            toString(getOffer(repo, i));
        }
    }
    if (ok == 0)
        printf("No matches.\n");
}

void printStartingWithGivenDate(UI* ui, char* type, char* departureDate)
{
    int ok = 0;
    OfferRepo* repo = getRepo(ui->c);
    for (int i = 0; i < getRepoLen(repo) ; i++)
    {
        Offer* o = getOffer(repo, i);
        if (strcmp(type, o->type) == 0 && checkDate(o, departureDate) == 1)
        {
            ok = 1;
            toString(getOffer(repo, i));
        }
    }
    if (ok == 0)
        printf("No matches.\n");
}

void printWithGivenTypeAndPrice(UI* ui, char* type, int price)
{
    int ok = 0;
    OfferRepo* repo = getRepo(ui->c);
    sortByPrice(repo);
    for (int i = 0; i < getRepoLen(repo) ; i++)
    {
        Offer* o = getOffer(repo, i);
        if (strcmp(type, o->type) == 0 && o->price < price)
        {
            ok = 1;
            toString(getOffer(repo, i));
        }
    }
    if (ok == 0)
        printf("No matches.\n");
}

void start(UI* ui)
{
    char option;
    printMenu();
    printf("Enter an option: ");
    scanf(" %c", &option);
    while (1)
    {
        if (option == '1')
        {
            printf("Tourism offers available:\n");
            printAllOffers(ui);
        }
        else if (option == '2')
        {
            char type[40];
            printf("Enter the type of the offer(seaside/mountain/citybreak): ");
            scanf("%s", type);
            
            char destination[40];
            printf("Enter a destination: ");
            scanf("%s", destination);
            
            char departureDate[20];
            printf("Enter a departure date: ");
            scanf("%s", departureDate);
            
            int price;
            printf("Enter a price: ");
            scanf("%d", &price);
            
            if (addOffer(ui->c, type, destination, departureDate, price, 1) == 1)
                printf("Offer added.\n");
            else if (addOffer(ui->c, type, destination, departureDate, price, 1) == 0)
                printf("An offer with the same destination and departure date already exists\n");
            else if (addOffer(ui->c, type, destination, departureDate, price, 1) == -1)
                printf("Incorrect type. Please choose between seaside, mountain and citybreak\n");
        }
        else if (option == '3')
        {
            char destination[40];
            printf("What offer do you want to delete?\nDestination: ");
            scanf("%s", destination);
            
            char departureDate[40];
            printf("Departure date: ");
            scanf("%s", departureDate);
            
            
            if(delOffer(ui->c, destination, departureDate, 1) == 1)
                printf("Offer deleted.\n");
            else printf("Error. Offer not deleted!\n");
        }
        else if (option == '4')
        {
            char destination[40];
            printf("What offer do you want to update?\nDestination: ");
            scanf("%s", destination);
            
            char departureDate[40];
            printf("Departure date: ");
            scanf("%s", departureDate);

            char newType[40];
            printf("Enter the new type: ");
            scanf("%s", newType);

            char newDestination[40];
            printf("Enter the new destination: ");
            scanf("%s", newDestination);

            char newDepartureDate[20];
            printf("Enter the new departure date: ");
            scanf("%s", newDepartureDate);

            int newPrice;
            printf("Enter the new price: ");
            scanf("%d", &newPrice);

            if (updateOffer(ui->c, destination, departureDate, newType, newDestination, newDepartureDate, newPrice, 1) == 1)
                printf("Offer updated.\n");
            else printf("Error. Offer not updated.\n");
        }
        else if (option == '5')
        {
            char str[40];
            printf("Enter a string: ");
            scanf(" %s", str);
            printWithGivenStr(ui, str);
        }
        else if (option == '6')
        {
            char destination[40];
            printf("Enter a destination: ");
            scanf(" %s", destination);
            printWithGivenDest(ui, destination);
        }
        else if (option == '7')
        {
            char type[40];
            printf("Enter a type: ");
            scanf(" %s", type);
            printWithGivenType(ui, type);
        }
        else if (option == '8')
        {
            char type[40];
            printf("Enter a type: ");
            scanf(" %s", type);
            
            char departureDate[40];
            printf("Departure date: ");
            scanf("%s", departureDate);
            
            printStartingWithGivenDate(ui, type, departureDate);
        }
        else if (option == '9')
        {
            char type[40];
            printf("Enter a type: ");
            scanf(" %s", type);
            
            int price;
            printf("Price: ");
            scanf("%d", &price);
            
            printWithGivenTypeAndPrice(ui, type, price);
        }
        else if (option == 'u')
        {
            if(undo(ui->c) == 1)
                printf("Successful undo.\n");
            else printf("Can't undo again.\n");
        }
        else if (option == 'r')
        {
            if(redo(ui->c) == 1)
                printf("Successful redo.\n");
            else printf("Can't redo again.\n");
        }
        else if (option == '0')
        {
            printf("Exited the program\n");
            break;
        }
        else
        {
            printf("Not a valid command\n");
        }
        printf("Enter an option: ");
        scanf(" %c", &option);
    }
}
