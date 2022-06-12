#ifndef GAMELOGIC_H
#define GAMELOGIC_H

#include <iostream>
#include <vector>
#include <memory>
using namespace std;

class GameLogic_Test;

class GameLogic {
public:

    GameLogic() {}
    GameLogic(Initializer & globalData); 
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

    Initializer* globalData;

    short playRequirement = 0;
    bool  buttonIsHeld = false;

    vector<shared_ptr<Card>> prizePot = {};

    void resetRound();
    void setPlayRequirement(const Card & card);
    void startPlayerRound(Player & player);
    void playCard(Player & player);
    void setTopCards(Player & player);

    bool isFaceCard(const Card & card);
};


// =================================================================================================


GameLogic::GameLogic(Initializer & globalData) {
    this->globalData = &globalData;
}

// -------------------------------------------------------------------------------------------------

void GameLogic::gameLogicLoop() {
    // leftClick();
    // rightClick();

    short mouseButton = globalData->eventHandler.getMouseButtonPressed();     
    if(mouseButton != -1)
        cout << "Mouse button " << mouseButton << " pressed." << endl;

    short button0 = globalData->eventHandler.getJoystickButtonPressed(0);
    if(button0 != -1)
        cout << "Joystick 0 button " << button0 << " pressed." << endl;        

    short button1 = globalData->eventHandler.getJoystickButtonPressed(1);
    if(button1 != -1)
        cout << "Joystick 1 button " << button1 << " pressed." << endl;   

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