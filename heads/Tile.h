//
// Created by Ryan Gurnick on 2019-05-08.
//

#include <iostream>
#include <stdio.h>

using namespace std;

#ifndef GAME_TILE_H
#define GAME_TILE_H


class Tile {
private:

public:
    int     x;
    int     y;
    int     startX;
    int     startY;
    bool    valid = true;
    bool    king = false;
    int     player;
    string  name;

    Tile(int x, int y, int player);

    // TODO: add docstring
    string printTile();

    /**
     * Updates the Tile Name (updateTileName)
     * This will take the current x and current y
     * and use the normal form to set the new name.
     *
     * @param void
     * @return void
     */
    void updateTileName();

    // TODO: add docstring
    void makeKing();

    //TODO: add docstring
    bool isKing();

    // TODO: add docstring
    bool moveTile(int dirX, int dirY, int dirBias);

};


#endif //GAME_TILE_H
