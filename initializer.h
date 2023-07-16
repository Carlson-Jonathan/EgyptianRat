// Copyright Jonathan Carlson 2022

#ifndef INITIALIZER_H
#define INITIALIZER_H

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include "gameSound.h"
#include "eventHandler.h"
#include "textureManager.h"

using namespace std;

class Initializer {
public:
	Initializer(const Initializer& obj) = delete; // This is now a singleton

    //----------------------------------------------------------------------------------------------

	string test = "";
	
	unsigned int screenWidth  = 600;
	unsigned int screenHeight = 700;
	pair<float, float> screenCenter = {};
	
	short frameRate = 20;
	short gameSpeed	= 4;
	short numberOfPlayers = 4;

	string defaultMusic      = "Sounds/Music/TownTheme.ogg";
	string defaultFontFamily = "Fonts/Robusta-Regular.ttf";
	string cardBack          = "redCardBack";

	bool gameMenuIsOpen = false;
	bool atTitleScreen  = true;
	bool autoClick      = false;	
	bool mayInitializeGameTable = false;

	sf::RenderWindow window;
	sf::View view;
	sf::Font defaultFont;
	// sf::Sprite background;

	GameSound      gameSound;
	EventHandler   eventHandler;
	TextureManager textures;

    static Initializer* getInstance() {
    	if(!instancePtr)                       
            instancePtr = new Initializer();
        return instancePtr;
    }

	void setScreenCenter() {
		this->screenCenter = {screenWidth / 2.f, screenHeight / 2.f};
	}

private:
	Initializer() : window(sf::VideoMode(screenWidth, screenHeight), "Egyptian Rat | by Jonathan Carlson"), 
					eventHandler(window), 
					view(sf::Vector2f(screenWidth / 2.f, screenHeight / 2.f), sf::Vector2f(screenWidth, screenHeight)) {		
						
		window.setFramerateLimit(frameRate);

		// Set background texture
		// background.setTexture(textures.textures["sample2"]);  
		// background.setOrigin(0, 0);	

		// Play song
		// gameSound.loadAndPlayMusic(defaultMusic);
		setFontFamily();
		setScreenCenter();
	}

	static Initializer* instancePtr;

	void setFontFamily() {
		if (!this->defaultFont.loadFromFile(this->defaultFontFamily)) {
			cout << "ERROR: GameTable::setText(): Font " << defaultFontFamily << " not found." << endl; 
			exit(139);
		}   
	}
};

Initializer* Initializer::instancePtr = NULL;
Initializer* globalData = Initializer::getInstance();

// =================================================================================================


#endif // INITIALIZER_H