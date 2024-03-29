// Copyright Jonathan Carlson 2022

#ifndef TESTHARNESS_CPP
#define TESTHARNESS_CPP

#include <iostream>
#include <map>

using namespace std;

#include "gameTable.h"

#include "miscellaneous_test.h"
#include "cardDeck_test.h"
#include "card_test.h"
#include "gameTable_test.h"
#include "gameLogic_test.h"

//--------------------------------------------------------------------------------------------------

void printResults(const map<string, bool> & allResults) {
    cout << "############################# Unit Test Summary: #############################" << endl;
    for(auto i : allResults) {
        if(i.second) 
            cout << "Passed: " << i.first << endl;
        else
            cout << "FAILED: " << i.first << " <--Errors!" << endl;
    }
}

//--------------------------------------------------------------------------------------------------

int main() {

    map<string, bool> allResults;

    // =================== Miscellaneous.h ====================

    allResults.insert(pair<string, bool>(
        "Miscellaneous_Test::generateRandomNumber_test()",
        Miscellaneous_Test::generateRandomNumber_test()
    ));    

    allResults.insert(pair<string, bool>(
        "Miscellaneous_Test::convertStringToFloat_test()",
        Miscellaneous_Test::convertStringToFloat_test()
    ));   

    // ====================== CardDeck.h ======================

    // allResults.insert(pair<string, bool>(
    //     "CardDeck_Test::divideDeck_test()",
    //     CardDeck_Test::divideDeck_test()
    // ));   

    // allResults.insert(pair<string, bool>(
    //     "CardDeck_Test::shuffleDeck_test()",
    //     CardDeck_Test::shuffleDeck_test()
    // ));   

    // ======================== Card.h ========================

    allResults.insert(pair<string, bool>(
        "Card_Test::setCardValue_test()",
        Card_Test::setCardValue_test()
    )); 

    allResults.insert(pair<string, bool>(
        "Card_Test::setCardSuite_test()",
        Card_Test::setCardSuite_test()
    ));    

    // ===================== GameLogic.h ======================

    allResults.insert(pair<string, bool>(
        "GameLogic_Test::setTopCards_test()",
        GameLogic_Test::setTopCards_test()
    ));  

    //----------------------------------------------------------------------------------------------

    printResults(allResults);

    return 0;
}

#endif // TESTHARNESS_CPP