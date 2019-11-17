//
// Created by Ryan Gurnick on 2019-05-08.
//

#include "heads/Tile.h"
#include "heads/Board.h"

using namespace std;

Tile::Tile(int initX, int initY, int initPlayer) {
    startX = initX;
    startY = initY;
    x = initX;
    y = initY;
    player = initPlayer;
    name = to_string(initPlayer) + "-" + to_string(initX) + "-" + to_string(initY);
    king = false;

}

string Tile::printTile() {
    return "Tile[" + (name) + "](sX: " + to_string(startX) + " sY: " + to_string(startY) + " cX: " + to_string(x) + " cY: " + to_string(y) + " valid: " + to_string(valid) + " king: " + to_string(king) + " player: " + to_string(player) + ")";
}

void Tile::updateTileName() {
    name = to_string(player) + "-" + to_string(x) + "-" + to_string(y);
}

void Tile::makeKing() {
    king = true;
}

bool Tile::isKing() {
    return king;
}

bool Tile::moveTile(int dirX, int dirY, int dirBias) {
    // !(((x + y) % 2) == 0) == BLACK
    if (((x+dirX + y+dirY) % 2) == 0){
        cout << "returned false in first base case" << endl;
        return false;
    }

    if (!king && dirY < 0){
        cout << "returned false in second base case" << endl;
        return false;
    }

    x = x + (dirX * dirBias);
    y = y + (dirY * dirBias);
    updateTileName();

    if(player == 0 && y == (BoardSize-1)){
        makeKing();
    }else if(player == 1 && y == 0){
        makeKing();
    }
    return true;
}