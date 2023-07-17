#!/bin/bash
clear
g++ -c -I../Game/include -I../Initialize/include testHarness.cpp miscellaneous_test.cpp ../Initialize/src/miscellaneous.cpp
g++ testHarness.o miscellaneous.o miscellaneous_test.o -o executable.out -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lsfml-network
./executable.out
exit