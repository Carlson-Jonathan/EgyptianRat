// Copyright Jonathan Carlson 2022

#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <vector>
#include <memory>
using namespace std;

#include "initializer.h"

class Player {
public:

    Player () {}

    Player* after       = NULL;
    Player* before      = NULL;
    string  name        = "Unset";
    short   number      = 0;
    bool    isOutOfGame = false;
    short   numCardsInHand = 0;

    vector<shared_ptr<Card>> hand;
    vector<shared_ptr<Card>> topCards;

};


// =================================================================================================


#endif // PLAYER_H