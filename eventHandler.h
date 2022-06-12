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

	string listen();
	sf::Event 	 	  event;

	bool mouseRelease = false;
	bool mouseRelease2 = false;
	bool joystickButtonHeld = false;

	bool windowResized = false;

	unsigned int screenWidth = 0;
	unsigned int screenHeight = 0;

	short getJoystickButtonPressed(short joystickNumber);

private:

	sf::RenderWindow* window;
	Joystick 		  joystick;

	string mouseButton();
	void closeWindow();
	void resizeWindow();

	vector<bool> joystickButtonPresses = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
};


// =================================================================================================


EventHandler::EventHandler(sf::RenderWindow & window) {
	this->window = &window;
}

// -------------------------------------------------------------------------------------------------

string EventHandler::listen() {
	while (window->pollEvent(event)) {

		switch(event.type) {
			case sf::Event::Closed:
				closeWindow();
				break;
			case sf::Event::Resized:
				resizeWindow();
				break;
			case sf::Event::MouseButtonPressed:
				return mouseButton();
				break;
			case sf::Event::MouseButtonReleased:
				// cout << "Released!" << endl;
				mouseRelease = true;
				mouseRelease2 = true;
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
			default:
				return "";
				break;
		}	
	}

	return "";
}

// -------------------------------------------------------------------------------------------------

// When a mouse button is pressed (any button), this performs an action based on which button.
string EventHandler::mouseButton() {
	switch(event.key.code) {
		case sf::Mouse::Left:
			// cout << "Mouse LEFT" << endl;
			return "leftClick";
			break;
		case sf::Mouse::Right:
			cout << "Mouse RIGHT" << endl;
			break;
		case sf::Mouse::Middle:
			cout << "Mouse MIDDLE" << endl;
			break;
		case sf::Mouse::XButton1:
			cout << "Mouse XButton1" << endl;
			break;
		case sf::Mouse::XButton2:
			cout << "Mouse XButton2" << endl;
			break;
	}
	return "";
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