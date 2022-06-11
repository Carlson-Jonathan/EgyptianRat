#ifndef GAMELOGIC_TEST_H
#define GAMELOGIC_TEST_H

#include <iostream>
using namespace std;

class GameLogic_Test {
public:

    static bool setTopCards_test() {
        GameLogic gameLogic;
        Player player;
        string error = "";

        player.hand = generateDeck();
        gameLogic.setTopCards(player);

        short  expectedResultsValue[] = {0, 1, 2, 3};
        string expectedResultsSuite[] = {"A", "B", "C", "D"};

        for(short i = 0; i < player.topCards.size(); i++) {
            if(player.topCards[i]->value != expectedResultsValue[i]) {
                cout << "Top card values not matching expected results!" << endl;
                return false;
            }

            if(player.topCards[i]->suite != expectedResultsSuite[i]) {
                cout << "Top card suites not matching expected results!" << endl;
                return false;
            }
        }

        return true;
    }

private:

    static vector<shared_ptr<Card>> generateDeck() {
        vector<shared_ptr<Card>> cardDeck = {};

        for(short i = 0; i < 12; i++) {
            shared_ptr<Card> card = make_shared<Card>();
            card->value = i;
            card->suite = char(i + 65);
            cardDeck.push_back(card);
        }

        return cardDeck;
    }

};



#endif // GAMELOGIC_TEST_H