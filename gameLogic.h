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

    vector<shared_ptr<Card>> prizePot = {};


    void resetRound();
    void setPlayRequirement(const Card & card);
    void startPlayerRound();
    void playCard(Player & player);
    void setTopCards(Player & player);

    bool isFaceCard(const Card & card);

};


// =================================================================================================


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


    // place card in pot
    // Remove card[0] from player deck
    // draw card
    // compare against requirement
    // set requirement
    // end turn
}

// -------------------------------------------------------------------------------------------------

void GameLogic::startPlayerRound() {
    // play a card
    // if isFaceCard
    //     set playRequirement   
    // if not playRequirement
    //    


    // end player round
}

#endif // GAMELOGIC_H