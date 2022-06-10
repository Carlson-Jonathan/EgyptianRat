// Copyright Jonathan Carlson 2022

#ifndef GAMETABLE_H
#define GAMETABLE_H

#include <iostream>
#include <vector>
#include <memory>
#include <set>
#include <assert.h>
#include "cardDeck.h"
#include "initializer.h"
#include "player.h"

using namespace std;

class GameTable {
public:

    GameTable() {}
    GameTable(Initializer & globalData);
    void construct(Initializer & globalData);

    void gameTableLoop();

    short numberOfPlayers = 0;

    
private:

    short timeElapsed = 0;

    string cardBack = "redCardBack";
    Initializer* globalData;
    CardDeck cardDeck; 
    float xMid, yMid;
    float zoomMultiplier = 1.f;

    vector<shared_ptr<Player>> playerList;
    vector<pair<float, float>> cardPositions;
    vector<pair<float, float>> cardPositionOffsets;
    vector<shared_ptr<Card>>   prizePot;
    vector<sf::RectangleShape> greenRectangles;
    vector<sf::Text>           deckSizeNumbers;

    bool buttonIsHeld = false;

    pair<pair<float, float>, pair<float, float>> gearIconClickArea  = {{10, 40}, {10,  40}};    
    pair<pair<float, float>, pair<float, float>> plusIconClickArea  = {{15, 40}, {55,  80}}; 
    pair<pair<float, float>, pair<float, float>> minusIconClickArea = {{15, 40}, {95, 120}};         

	sf::Font  font; 
    sf::Clock clock;
    sf::Time  elapsed; 
    sf::Sprite gearMenuIcon;
    sf::Text plus;
    sf::Text minus;

    // ---------------------------------------------------------------------------------------------

    void set_GearMenuIcon();
    void set_PlusIcon();
    void set_MinusIcon();
    void set_CardPositions();
    void set_CardBackPositions();
    void set_DeckSizeText();
    void set_DeckSizeTextPositions();
    void set_GreenRectangles();
    void set_GreenRectanglePositions();

    void draw_CardsBacks();
    void draw_GreenRectangles();
    void draw_DeckSizeNumbers();
    void draw_AllTableSprites();

    void listen_ForMouseClicks();
    void listener_GearMenuIconClick(float x, float y);
    void listener_PlusClick(float x, float y);
    void listener_MinusClick(float x, float y);
    void listener_MenuEventMonitor();
    void listener_WindowResized();

    bool leftClick();
    bool leftRelease();

    // ------------------------------

    void verifyNumberOfPlayers();
    void generatePlayers();
    void dealCardsToPlayers();  

    void adjustDeckSizeNumber(shared_ptr<Player> player);
    void popPlayedCardsFromPlayerDecks();

    void printAllPlayerStats();
    void printAllBooleanPermissions();
    void printPrizePotContents();
    void printPlayerMove(shared_ptr<Player> player);
    void changeCardStyle();
};


// =================================================================================================


GameTable::GameTable(Initializer & globalData) {
    construct(globalData);
}

// -------------------------------------------------------------------------------------------------

void GameTable::construct(Initializer & globalData) {
    this->cardDeck = CardDeck(globalData);
    this->globalData = &globalData;
    this->numberOfPlayers = globalData.numberOfPlayers;
    this->font = globalData.defaultFont;        
    verifyNumberOfPlayers();
    generatePlayers();
    dealCardsToPlayers();
    set_GearMenuIcon();
    set_PlusIcon();
    set_MinusIcon();
    set_CardPositions();
    set_CardBackPositions();
    set_GreenRectangles();
    set_DeckSizeText();
}

// -------------------------------------------------------------------------------------------------

void GameTable::set_GearMenuIcon() {
	gearMenuIcon.setTextureRect(sf::IntRect(0, 0, 30, 30));
    gearMenuIcon.setTexture(globalData->textures.textures["gearMenuIcon"]);
    gearMenuIcon.setScale(zoomMultiplier, zoomMultiplier);
    sf::Vector2f staticPosition = globalData->window.mapPixelToCoords({10, 10});
    gearMenuIcon.setPosition(staticPosition);    
}

// -------------------------------------------------------------------------------------------------

void GameTable::set_CardPositions() {

    // pair<float, float> center = globalData->screenCenter;
    float centerX = globalData->screenCenter.first;
    float centerY =  globalData->screenCenter.second;

    cout << "Screen Center is " << centerX << ", " << centerY << endl;

    cardPositions = { 
        {centerX - 70.f, centerY - 72.f}, // Player 1
        {centerX - 50.f, centerY - 97.f}, // Player 2
        {centerX - 30.f, centerY - 72.f}, // Player 3
        {centerX - 50.f, centerY - 48.f}, // Player 4
    };

    cardPositionOffsets = {
        {-20.f,   0.f}, // Player 1
        {  0.f, -20.f}, // Player 2
        { 20.f,   0.f}, // Player 3
        {  0.f,  20.f}  // Player 4
    };

    // Apply screen positions to player card decks
    for(short i = 0; i < 4; i++) {
        for(short j = 0, x = 0, y = 0; j < 4; 
        j++, x += cardPositionOffsets[i].first, y += cardPositionOffsets[i].second) {
            playerList[i]->hand[j]->cardSprite.setPosition(cardPositions[i].first + x, cardPositions[i].second + y);
        }
    }
}

// -------------------------------------------------------------------------------------------------

void GameTable::set_CardBackPositions() {
    float xCenter = globalData->screenCenter.first;
    float yCenter = globalData->screenCenter.second;

    cardDeck.cardBacks[0].setPosition(xCenter - 260.f, yCenter - 72.f);  
    cardDeck.cardBacks[1].setPosition(xCenter -  50.f, yCenter - 325.f);   
    cardDeck.cardBacks[2].setPosition(xCenter + 157.f, yCenter -  73.f);   
    cardDeck.cardBacks[3].setPosition(xCenter -  50.f, yCenter + 180.f);
}

// -------------------------------------------------------------------------------------------------

void GameTable::set_PlusIcon() {
    plus.setFont(font);
    plus.setCharacterSize(75.f * zoomMultiplier);
    plus.setFillColor(sf::Color(0, 60, 0));
    plus.setString("+");
    globalData->view.zoom(zoomMultiplier);
    sf::Vector2f staticPosition = globalData->window.mapPixelToCoords({14, 15});
    plus.setPosition(staticPosition);
}

// -------------------------------------------------------------------------------------------------

void GameTable::set_MinusIcon() {
    minus.setFont(font);
    minus.setCharacterSize(75.f * zoomMultiplier);
    minus.setFillColor(sf::Color(0, 60, 0));
    minus.setString("-");
    globalData->view.zoom(zoomMultiplier);
    sf::Vector2f staticPosition = globalData->window.mapPixelToCoords({14, 50});
    minus.setPosition(staticPosition);
}

// -------------------------------------------------------------------------------------------------

void GameTable::set_GreenRectangles() {
    for(short i = 0; i < 4; i++) {
        sf::RectangleShape greenRectangle;
        greenRectangle.setSize(sf::Vector2f(60.f, 93.f));
        greenRectangle.setFillColor(sf::Color(0.f, 90.f, 0.f));
        greenRectangle.setOutlineColor(sf::Color(100.f, 150.f, 100.f));
        greenRectangle.setOutlineThickness(8.f);
        greenRectangles.push_back(greenRectangle);
    }

    set_GreenRectanglePositions();
}

// -------------------------------------------------------------------------------------------------

void GameTable::set_GreenRectanglePositions() {
    for(short i = 0; i < 4; i++) {
        greenRectangles[i].setPosition(cardDeck.cardBacks[i].getPosition().x + 21, 
                                       cardDeck.cardBacks[i].getPosition().y + 26);        
    }
}

// -------------------------------------------------------------------------------------------------

void GameTable::set_DeckSizeText() {
    for(short i = 0; i < 4; i++) {
        deckSizeNumbers.push_back(sf::Text());
        deckSizeNumbers[i].setFont(font); 
        deckSizeNumbers[i].setCharacterSize(50); 
        deckSizeNumbers[i].setFillColor(sf::Color(255, 255, 255));
        deckSizeNumbers[i].setString(to_string(playerList[i]->numCardsInHand));
    }

    set_DeckSizeTextPositions();
}

// -------------------------------------------------------------------------------------------------

void GameTable::set_DeckSizeTextPositions() {
    for(short i = 0; i < 4; i++) {
        float cardPosX = cardDeck.cardBacks[i].getPosition().x;
        float cardPosY = cardDeck.cardBacks[i].getPosition().y;
        deckSizeNumbers[i].setPosition(cardPosX + 50.f,  cardPosY + 72.f);
        Miscellaneous::centerTextAlignment(deckSizeNumbers[i]);
    }
}

// -------------------------------------------------------------------------------------------------

void GameTable::verifyNumberOfPlayers() {
    if(numberOfPlayers < 2 || numberOfPlayers > 4) {
        cout << "ERROR: GameTable::numberOfPlayers: Out of range. Value must be 2-4." << endl;
        exit(139);
    }
}

// -------------------------------------------------------------------------------------------------

void GameTable::generatePlayers() {
    for(short i = 0; i < 4; i++) {
        playerList.push_back(make_shared<Player>());
        playerList[i]->number = i + 1;
        playerList[i]->name = "Player " + to_string(i + 1);
    }
}

// -------------------------------------------------------------------------------------------------

void GameTable::dealCardsToPlayers() {
    vector<vector<shared_ptr<Card>>> hands;
    hands = cardDeck.divideDeck(numberOfPlayers);
    for(short i = 0; i < numberOfPlayers; i++) {
        playerList[i]->hand = hands[i];
        playerList[i]->numCardsInHand = hands[i].size();
        playerList[i]->topCard = playerList[i]->hand[0];
    }
}

// -------------------------------------------------------------------------------------------------

void GameTable::listen_ForMouseClicks() {

    float mouseX = sf::Mouse::getPosition(globalData->window).x;
    float mouseY = sf::Mouse::getPosition(globalData->window).y;

    if(leftClick()) {
        listener_GearMenuIconClick(mouseX, mouseY);
        listener_PlusClick(mouseX, mouseY);
        listener_MinusClick(mouseX, mouseY);

        sf::Vector2i mousePos = sf::Mouse::getPosition(globalData->window);
        sf::Vector2f worldPos = globalData->window.mapPixelToCoords(mousePos);

        cout << "Left mouse button clicked @ {" << sf::Mouse::getPosition(globalData->window).x  
             << ", " << sf::Mouse::getPosition(globalData->window).y << "} - View conversion: {" 
             << worldPos.x << ", " << worldPos.y << "}" << endl;
        cout << "View center is: {" << globalData->view.getCenter().x << ", " << globalData->view.getCenter().y << "}" << endl;
        cout << "View size: {" << globalData->view.getSize().x << ", " << globalData->view.getSize().y << "}" << endl;
    }

    if(leftRelease()) {
    }
}

// -------------------------------------------------------------------------------------------------

bool GameTable::leftClick() {
    if(sf::Mouse::isButtonPressed(sf::Mouse::Left) && !buttonIsHeld) {
        buttonIsHeld = true;
        return true;
    }

    return false;
}

// -------------------------------------------------------------------------------------------------

bool GameTable::leftRelease() {
    if(globalData->eventHandler.mouseRelease) {
        buttonIsHeld = false;
        globalData->eventHandler.mouseRelease = false;
        return true;
    }
    return false;
}

// -------------------------------------------------------------------------------------------------

void GameTable::listener_WindowResized() {
    if(globalData->eventHandler.windowResized) {
        globalData->screenWidth = globalData->eventHandler.screenWidth;
        globalData->screenHeight = globalData->eventHandler.screenHeight;
        globalData->setScreenCenter();
        globalData->view.setCenter(globalData->screenCenter.first, globalData->screenCenter.second);
        set_CardBackPositions(); 
        set_DeckSizeTextPositions();
        set_GreenRectanglePositions();
        set_CardPositions(); // This does not include additional cards played 
        set_GearMenuIcon();
        set_PlusIcon();
        set_MinusIcon();
        globalData->eventHandler.windowResized = false;

    }
}

// -------------------------------------------------------------------------------------------------

void GameTable::listener_GearMenuIconClick(float x, float y) {

    bool xBegin = x > gearIconClickArea.first.first;
    bool xEnd   = x < gearIconClickArea.first.second;
    bool yBegin = y > gearIconClickArea.second.first;
    bool yEnd   = y < gearIconClickArea.second.second;

    if(xBegin && xEnd && yBegin && yEnd) {
        globalData->gameSound.playSoundEffect("tClick.ogg");
        globalData->gameMenuIsOpen = true;
    }
}

// -------------------------------------------------------------------------------------------------

void GameTable::listener_PlusClick(float x, float y) {
    bool xBegin = x > plusIconClickArea.first.first;
    bool xEnd   = x < plusIconClickArea.first.second;
    bool yBegin = y > plusIconClickArea.second.first;
    bool yEnd   = y < plusIconClickArea.second.second;

    if(xBegin && xEnd && yBegin && yEnd) {
        globalData->gameSound.playSoundEffect("tClick.ogg");
        globalData->view.setSize(globalData->screenWidth, globalData->screenHeight);
        zoomMultiplier *= 0.8f;
        globalData->view.zoom(zoomMultiplier);
        globalData->view.setCenter(globalData->screenCenter.first, globalData->screenCenter.second);
        globalData->window.setView(globalData->view);
        set_GearMenuIcon();
        set_PlusIcon();
        set_MinusIcon();
    }  
}

// -------------------------------------------------------------------------------------------------

void GameTable::listener_MinusClick(float x, float y) {
    bool xBegin = x > minusIconClickArea.first.first;
    bool xEnd   = x < minusIconClickArea.first.second;
    bool yBegin = y > minusIconClickArea.second.first;
    bool yEnd   = y < minusIconClickArea.second.second;

    if(xBegin && xEnd && yBegin && yEnd) {
        globalData->gameSound.playSoundEffect("tClick.ogg");
        globalData->view.setSize(globalData->screenWidth, globalData->screenHeight);
        zoomMultiplier *= 1.25f;
        globalData->view.zoom(zoomMultiplier);
        globalData->view.setCenter(globalData->screenCenter.first, globalData->screenCenter.second);
        globalData->window.setView(globalData->view);
        set_GearMenuIcon();
        set_PlusIcon();
        set_MinusIcon();
    }  
}


// =================================================================================================
// ======================================== Game Mechanics =========================================
// =================================================================================================


void GameTable::adjustDeckSizeNumber(shared_ptr<Player> player) {
    player->numCardsInHand--;
    deckSizeNumbers[player->number - 1].setString(to_string(player->numCardsInHand));
    if(player->numCardsInHand < 1) 
        deckSizeNumbers[player->number - 1].setString("Out");
    Miscellaneous::centerTextAlignment(deckSizeNumbers[player->number - 1]);

    short randNum = Miscellaneous::generateRandomNumber(2);
    globalData->gameSound.playSoundEffect("cardDeal" + to_string(randNum) + ".ogg");
}

// -------------------------------------------------------------------------------------------------

void GameTable::draw_CardsBacks() {
    for(short i = 0; i < numberOfPlayers; i++) {
        
        if(playerList[i]->numCardsInHand > 0)
            globalData->window.draw(cardDeck.cardBacks[i]);

        elapsed = clock.getElapsedTime();
    }
}

// -------------------------------------------------------------------------------------------------

void GameTable::draw_GreenRectangles() {
    for(short i = 0; i < greenRectangles.size(); i++) {
        globalData->window.draw(greenRectangles[i]);
    }
}

// -------------------------------------------------------------------------------------------------

void GameTable::draw_DeckSizeNumbers() {
    for(short i = 0; i < deckSizeNumbers.size(); i++) {
        globalData->window.draw(deckSizeNumbers[i]);
    }
}

// -------------------------------------------------------------------------------------------------

void GameTable::gameTableLoop() {
        listen_ForMouseClicks();
        listener_MenuEventMonitor();
        listener_WindowResized();
        draw_AllTableSprites();
}

// -------------------------------------------------------------------------------------------------

void GameTable::draw_AllTableSprites() {
    draw_GreenRectangles();
    draw_CardsBacks();
    draw_DeckSizeNumbers();
    globalData->window.draw(gearMenuIcon);
    globalData->window.draw(plus);
    globalData->window.draw(minus);

    globalData->window.draw(playerList[0]->hand[0]->cardSprite);
    globalData->window.draw(playerList[0]->hand[1]->cardSprite);
    globalData->window.draw(playerList[0]->hand[2]->cardSprite);
    globalData->window.draw(playerList[0]->hand[3]->cardSprite);            

    globalData->window.draw(playerList[1]->hand[0]->cardSprite);
    globalData->window.draw(playerList[1]->hand[1]->cardSprite);
    globalData->window.draw(playerList[1]->hand[2]->cardSprite);
    globalData->window.draw(playerList[1]->hand[3]->cardSprite);

    globalData->window.draw(playerList[2]->hand[0]->cardSprite);
    globalData->window.draw(playerList[2]->hand[1]->cardSprite);
    globalData->window.draw(playerList[2]->hand[2]->cardSprite);
    globalData->window.draw(playerList[2]->hand[3]->cardSprite);            

    globalData->window.draw(playerList[3]->hand[0]->cardSprite);
    globalData->window.draw(playerList[3]->hand[1]->cardSprite);
    globalData->window.draw(playerList[3]->hand[2]->cardSprite);
    globalData->window.draw(playerList[3]->hand[3]->cardSprite);
}

// -------------------------------------------------------------------------------------------------

void GameTable::listener_MenuEventMonitor() {
    changeCardStyle();
}

// -------------------------------------------------------------------------------------------------

void GameTable::changeCardStyle() {
    if(cardBack != globalData->cardBack) {
        cardBack = globalData->cardBack;
        cardDeck.generateCardBacks(4);
        set_CardBackPositions();
    }
}

// -------------------------------------------------------------------------------------------------

void GameTable::printAllPlayerStats() {
    for(short i = 0; i < numberOfPlayers; i++) {
        cout << "\n==============================\n\tPlayer " << i + 1 << "\n\tHand size: " 
                << playerList[i]->hand.size() << "\n\tCards on deck: " << playerList[i]->numCardsInHand 
                << "\n\tTop card: " << playerList[i]->topCard->cardName 
                << "\n==============================\n";
        for(short j = 0; j < playerList[i]->hand.size(); j++) {
            cout << playerList[i]->hand[j]->cardName << "\t{" 
                 << playerList[i]->hand[j]->cardSprite.getPosition().x << ", "
                 << playerList[i]->hand[j]->cardSprite.getPosition().y << "}\n";
        }
    }
    cout << "========================================================\n";
}

// -------------------------------------------------------------------------------------------------

void GameTable::printAllBooleanPermissions() {
    cout << "============= Booleans =============" << endl;
    // cout << "mayConcludeRound: "          << mayConcludeRound          << endl;
}

// -------------------------------------------------------------------------------------------------

void GameTable::printPrizePotContents() {
    cout << "=============== Prize Pot: ===============" << endl;
    for(auto i : prizePot) {
        cout << i->cardName << "\t" << i->cardSprite.getPosition().x << ", " << i->cardSprite.getPosition().y << endl;
    }
    cout << "Prize Pot size: " << prizePot.size() << endl;
}

// -------------------------------------------------------------------------------------------------

void GameTable::printPlayerMove(shared_ptr<Player> player) {
    cout << player->name << " is out: " << player->isOutOfGame 
         << " Cards on deck: " << player->numCardsInHand << "\t" << player->topCard->cardName << endl; 
}

#endif // GAMETABLE_H