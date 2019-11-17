//
// Created by Ryan Gurnick on 2019-05-21.
//
#include <iostream>
#include <stdio.h>
#include <strings.h>
#include "Board.h"


#ifndef GAME_CLI_H
#define GAME_CLI_H

using namespace std;

class CLI {
private:
    // implement random function... let the player know before hand
    int currentPlayer;
    int currentMoveVecX;
    int currentMoveVecY;

    Board board = *(new Board);
    bool gameStarted = false;
    string player0Name = "Jee";
    string player1Name = "Chris";

    void buildHeader();
    bool setPlayers();
    int getSelection();
    void tellCurrentPlayer(bool stupid = false);
    void requestMove();
    void requestMoveVector();


public:
    CLI();
    ~CLI();

    void createMenu();
};


#endif //GAME_CLI_H
