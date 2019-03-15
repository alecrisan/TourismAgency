//
//  main.c
//  c
//
//  Created by Crisan Alexandra on 08/03/2018.
//  Copyright © 2018 Crisan Alexandra. All rights reserved.
//
#include <stdio.h>
#include "ui.h"
#include "OperationsStack.h"

int main()
{
    testsStack();
    testsDynamicArray();
    testsOfferEntity();
    testsOfferRepo();
    testsController();
    OfferRepo* repo = createRepo();
    Stack* undoS = createStack();
    Stack* redoS = createStack();
    Ctrller* c = createController(repo, undoS, redoS);
    initCtrller(c);
    UI* ui = createUI(c);
    start(ui);
    destroyUI(ui);
    return 0;
}
