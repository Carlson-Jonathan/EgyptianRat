#ifndef GAMELOGIC_H
#define GAMELOGIC_H

#include <iostream>
#include <vector>
#include <memory>
#include "initializer.h"
#include "card.h"
#include "player.h"
using namespace std;

class GameLogic_Test;

class GameLogic {
public:

    GameLogic() {}
    friend GameLogic_Test;

    void gameLogicLoop();

private: 

    // Set default number of cards to play for next player (1) or...
    // 
    // play a card
    //     if playRequirement > 0, keep current player
    //     
    // is it a face card?
    //    if so, set number of plays for next player
    //

    short playRequirement = 0;
    bool  buttonIsHeld = false;

    vector<shared_ptr<Card>> prizePot = {};

    void resetRound();
    void setPlayRequirement(const Card & card);
    void startPlayerRound(Player & player);
    void playCard(Player & player);
    void setTopCards(Player & player);

    bool isFaceCard(const Card & card);

    string getPlayerInput();
};


// =================================================================================================

void GameLogic::gameLogicLoop() {

    string input = getPlayerInput();
    if(input != "Null")
        cout << input << endl;
}

// -------------------------------------------------------------------------------------------------

string GameLogic::getPlayerInput() {
    short mouseButton    = globalData->eventHandler.getMouseButtonPressed();
    short joystick0      = globalData->eventHandler.getJoystickButtonPressed(0);
    short joystick1      = globalData->eventHandler.getJoystickButtonPressed(1);
    short keyBoardButton = globalData->eventHandler.getKeyboardButtonPressed();

    if(mouseButton != -1)
        return "M-" + to_string(mouseButton);

    if(joystick0 != -1)
        return "J0-" + to_string(joystick0);

    if(joystick1 != -1)
        return "J1-" + to_string(joystick1);

    if(keyBoardButton != -1)
        return "K-" + to_string(keyBoardButton);

    return "Null";
}

// -------------------------------------------------------------------------------------------------

void GameLogic::resetRound() {
    playRequirement = 0;
}

// -------------------------------------------------------------------------------------------------

bool GameLogic::isFaceCard(const Card & card) {
    return card.value > 10;
}

// -------------------------------------------------------------------------------------------------

void GameLogic::setPlayRequirement(const Card & card) {
    playRequirement = card.value - 10;
}

// -------------------------------------------------------------------------------------------------

void GameLogic::setTopCards(Player & player) {
    player.topCards = {};
    for(short i = 0; i < player.hand.size(); i++) {
        if(i >= 4) break;
        player.topCards.push_back(player.hand[i]);
    }
}

// -------------------------------------------------------------------------------------------------


void GameLogic::playCard(Player & player) {

    prizePot.push_back(player.hand[0]);
    player.hand.erase(player.hand.begin());


    // draw card
    // compare against requirement
    // set requirement
    // end turn
}

// -------------------------------------------------------------------------------------------------

void GameLogic::startPlayerRound(Player & player) {
    setTopCards(player);

    // play a card
    // if isFaceCard
    //     set playRequirement   
    // if not playRequirement
    //    


    // end player round
}

#endif // GAMELOGIC_H