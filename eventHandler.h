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

	bool mouseRelease = false;
	bool windowResized = false;

	unsigned int screenWidth = 0;
	unsigned int screenHeight = 0;

private:

	sf::RenderWindow* window;
	sf::Event 	 	  event;
	Joystick 		  joystick;

	void mouseButton();
	void closeWindow();
	void resizeWindow();
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
				mouseButton();
				break;
			case sf::Event::MouseButtonReleased:
				// cout << "Released!" << endl;
				mouseRelease = true;
				break;		
			case sf::Event::MouseWheelMoved:
				cout << "Mouse wheel Scroll:" << event.mouseWheel.delta << endl;
				break;	
			case sf::Event::MouseMoved:
				// cout << "Mouse position: {" << event.mouseMove.x << ", " << event.mouseMove.y << "}" << endl;
				break;
			default:
				break;
		}	

		joystick.joystickActions(0);
		joystick.joystickActions(1);
	}
}

// -------------------------------------------------------------------------------------------------

// When a mouse button is pressed (any button), this performs an action based on which button.
void EventHandler::mouseButton() {
	switch(event.key.code) {
		case sf::Mouse::Left:
			// cout << "Mouse LEFT" << endl;
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