// Copyright Jonathan Carlson 2022

#ifndef EVENTHANDLER_H
#define EVENTHANDLER_H

#include <iostream>
#include <vector>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "joystick.h"

using namespace std;

class EventHandler {
public:

	EventHandler() {}
	EventHandler(sf::RenderWindow & window);

	void listen();
	sf::Event event;

	bool mouseRelease = false;
	bool mouseRelease2 = false;
	bool joystickButtonHeld = false;
	bool mouseButtonIsHeld = false;
	bool keyboardButtonHeld = false;

	bool windowResized = false;

	unsigned int screenWidth = 0;
	unsigned int screenHeight = 0;

	short getJoystickButtonPressed(short joystickNumber);
	short getMouseButtonPressed();
	short getKeyboardButtonPressed();

private:

	sf::RenderWindow* window;
	Joystick 		  joystick;

	string mouseButton();
	void closeWindow();
	void resizeWindow();

	vector<bool> joystickButtonPresses = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	vector<bool> mouseButtonPresses = {0, 0, 0, 0, 0}; // Left, Right, Middle, X1, X2
};


// =================================================================================================


EventHandler::EventHandler(sf::RenderWindow & window) {
	this->window = &window;
}

// -------------------------------------------------------------------------------------------------

void EventHandler::listen() {
	while (window->pollEvent(event)) {

		switch(event.type) {
			case sf::Event::Closed:
				closeWindow();
				break;
			case sf::Event::Resized:
				resizeWindow();
				break;
			case sf::Event::MouseButtonPressed:
				break;
			case sf::Event::MouseButtonReleased:
				// cout << "Released!" << endl;
				mouseRelease = true;
				mouseRelease2 = true;
				mouseButtonIsHeld = false;
				break;		
			case sf::Event::MouseWheelMoved:
				// cout << "Mouse wheel Scroll:" << event.mouseWheel.delta << endl;
				break;	
			case sf::Event::MouseMoved:
				// cout << "Mouse position: {" << event.mouseMove.x << ", " << event.mouseMove.y << "}" << endl;
				break;
			case sf::Event::JoystickButtonReleased:
				// cout << "Joystick button was released!!!" << endl;
				joystickButtonHeld = false;
				break;
			case sf::Event::KeyReleased:
				keyboardButtonHeld = false;
				break;
			default:
				break;
		}	
	}
}

// -------------------------------------------------------------------------------------------------

// When a mouse button is pressed (any button), this performs an action based on which button.
short EventHandler::getMouseButtonPressed() {

	if(mouseButtonIsHeld) return -1;

	mouseButtonPresses    = {0, 0, 0, 0, 0};
	mouseButtonPresses[0] = sf::Mouse::isButtonPressed(sf::Mouse::Left);
	mouseButtonPresses[1] = sf::Mouse::isButtonPressed(sf::Mouse::Right);
	mouseButtonPresses[2] = sf::Mouse::isButtonPressed(sf::Mouse::Middle);

	for(short i = 0; i < mouseButtonPresses.size(); i++) {
		if(mouseButtonPresses[i]) {
			mouseButtonIsHeld = true;
			return i;
		}
	}

	return -1;
}	

// -------------------------------------------------------------------------------------------------

short EventHandler::getJoystickButtonPressed(short joystickNumber) {
    for(short i = 0; i < joystickButtonPresses.size(); i++) {
        joystickButtonPresses[i] = sf::Joystick::isButtonPressed(joystickNumber, i);
        if(joystickButtonPresses[i] && !joystickButtonHeld) {
			joystickButtonHeld = true;
			return i;
        }
    };

	return -1;
}

// -------------------------------------------------------------------------------------------------

short EventHandler::getKeyboardButtonPressed() {
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && !keyboardButtonHeld) {
		keyboardButtonHeld = true;
		return 0;
	}

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) && !keyboardButtonHeld) {
		keyboardButtonHeld = true;
		return 1;
	}	

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad0) && !keyboardButtonHeld) {
		keyboardButtonHeld = true;
		return 2;
	}	

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::RShift) && !keyboardButtonHeld) {
		keyboardButtonHeld = true;
		return 3;
	}			

	return -1;
};

// -------------------------------------------------------------------------------------------------

void EventHandler::closeWindow() {
	cout << "Thanks for playing!" << endl;
	window->close();
}

// -------------------------------------------------------------------------------------------------

void EventHandler::resizeWindow() {
	this->screenWidth = event.size.width;
	this->screenHeight = event.size.height;
	sf::FloatRect visibleArea(0, 0, screenWidth, screenHeight);
	window->setView(sf::View(visibleArea));
	windowResized = true;
}

#endif // EVENTHANDLER_H