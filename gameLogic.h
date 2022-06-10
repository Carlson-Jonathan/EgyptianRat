#ifndef GAMELOGIC_H
#define GAMELOGIC_H

#include <iostream>
#include "initializer.h"
#include "gameTable.h"
#include "gameMenu.h"
#include "titleScreen.h"
using namespace std;

class GameLogic {
public:

    GameLogic() {}
    GameLogic(Initializer & globalData) : titleScreen(globalData), gameMenu(globalData) {
        this->globalData = &globalData;
    }

    void gameLogicLoop();

private: 

    Initializer* globalData;
	TitleScreen  titleScreen;
	GameMenu     gameMenu;   
    GameTable    gameTable; 
};


// =================================================================================================


void GameLogic::gameLogicLoop() {
    if(globalData->mayInitializeGameTable) {
        globalData->mayInitializeGameTable = false;
        gameMenu.updateNumberOfPlayersText(globalData->numberOfPlayers);
        gameTable.construct(*globalData);
    }

    if(globalData->atTitleScreen)
        titleScreen.titleScreenLoop();
    else if(globalData->gameMenuIsOpen)
        gameMenu.gameMenuLoop();
    else
        gameTable.gameTableLoop();
}

// -------------------------------------------------------------------------------------------------


#endif // GAMELOGIC_H