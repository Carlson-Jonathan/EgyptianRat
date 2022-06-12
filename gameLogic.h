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

    bool leftClick();
    bool mouseRelease();
    bool rightClick();
    bool joystick_0_Button_1();
    bool joystick_0_Button_2();
    bool joystick_1_Button_1();
    bool joystick_1_Button_2();
    bool keyboard_Play();
    bool keyboard_Slap();

    bool keyReleased();
    bool joystickRelease();

    void resetRound();
    void setPlayRequirement(const Card & card);
    void startPlayerRound(Player & player);
    void playCard(Player & player);
    void setTopCards(Player & player);

    bool isFaceCard(const Card & card);

    void test1();
    void test2();

};


// =================================================================================================


GameLogic::GameLogic(Initializer & globalData) {
    this->globalData = &globalData;
    cout << "Number of players = " << globalData.numberOfPlayers << endl;
}

// -------------------------------------------------------------------------------------------------

bool GameLogic::leftClick() {
    if(sf::Mouse::isButtonPressed(sf::Mouse::Left) && !buttonIsHeld) {
        cout << "GameLogic Left click" << endl; 
        buttonIsHeld = true;
        return true;
    }

    mouseRelease();

    return false;
}

// -------------------------------------------------------------------------------------------------

bool GameLogic::rightClick() {
    if(sf::Mouse::isButtonPressed(sf::Mouse::Right) && !buttonIsHeld) {
        cout << "GameLogic Right click" << endl; 
        buttonIsHeld = true;
        return true;
    }

    mouseRelease();

    return false;
}

// -------------------------------------------------------------------------------------------------

bool GameLogic::mouseRelease() {
    if(globalData->eventHandler.mouseRelease2) {
        buttonIsHeld = false;
        globalData->eventHandler.mouseRelease2 = false;
        return true;
    }
    return false;
}

// -------------------------------------------------------------------------------------------------

bool GameLogic::joystickRelease() {
    if(globalData->eventHandler.joystickRelease) {
        buttonIsHeld = false;
        globalData->eventHandler.joystickRelease = false;
        return true;
    }
    return false;
}

// -------------------------------------------------------------------------------------------------

bool GameLogic::joystick_0_Button_1() {
    if(sf::Joystick::isButtonPressed(0, 1) && !buttonIsHeld) {
        cout << "Joystick 0, button 1 pressed" << endl; 
        buttonIsHeld = true;
        return true;
    }
    joystickRelease();
    return false;
}

// -------------------------------------------------------------------------------------------------

bool GameLogic::joystick_1_Button_1() {

    if(sf::Joystick::isButtonPressed(1, 1) && !buttonIsHeld) {
        cout << "Joystick 1 - button 1 was pressed!" << endl;
        buttonIsHeld = true;
        return true;
    }

    joystickRelease();

    return false;
}

// -------------------------------------------------------------------------------------------------

bool GameLogic::keyReleased() {
    if(sf::Event::JoystickButtonReleased) {
        cout << "A key was released" << endl; 
        return true;
    }
    return false;
}

// -------------------------------------------------------------------------------------------------

void GameLogic::gameLogicLoop() {
    leftClick();
    rightClick();
    joystick_0_Button_1();
    joystick_1_Button_1();
    // keyReleased();
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