// Copyright Jonathan Carlson 2022

#ifndef MAIN_CPP
#define MAIN_CPP

#include <iostream>
#include <time.h>
#include "initializer.h"
#include "gameLogic.h"

using namespace std;

int main() {

	srand(time(NULL)); 		// For seeding the random number generator
	Initializer globalData;
	GameLogic gameLogic(globalData);

	while(globalData.window.isOpen()) {
		globalData.eventHandler.listen();
		globalData.window.clear(sf::Color(0, 90, 0));

		gameLogic.gameLogicLoop();

		globalData.window.display();
	} 

	return 0;
}

#endif // MAIN_CPP