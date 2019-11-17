#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <regex>
#include "Tile.h"
#include "Score.h"

//
// Created by Ryan Gurnick on 2019-05-08.
//

#ifndef GAME_BOARD_H
#define GAME_BOARD_H

// this is the size of the n by n board.
#define BoardSize 10
// this is the amount of rows that each team member gets
#define TeamRows ((BoardSize/2)-1)
// the number of tiles for each player
#define TeamTileCount ((BoardSize/2)*TeamRows)
class Board{
private:
    /**
     * 2D Board Matrix (board)
     * This is the 2D integer array that will store the
     * boards pattern. That is the pattern of black and
     * white tiles on the board itself... NOT THE TILES.
     *
     * @showinitializer Board()
     *
     */
    int board[BoardSize][BoardSize];

    /**
     * Tile Array (tiles)
     * This is a 1D Tile array that will contain all
     * of the tiles for both of the tiles for both
     * of the players.
     *
     * @showinitializer Board()
     */
     Tile *tiles[2*TeamTileCount];

     /**
      * Current Tile Selected (tileSelected)
      * This is the string name of the current tile
      * selected.
      */
     string tileSelected;

     /**
      * Current Tile Selected Obj (tileSelectedObject)
      * This is the object for the current tile selected.
      */
     Tile *tileSelectedObject;

     /**
      * Check if a tile exists on the board (tileWithNameExists)
      * This will check all of the valid tiles to see if the
      * inputted name matches any.
      *
      * @param playerID
      * @param coorX
      * @param coorY
      * @return
      */
     bool tileWithNameExists(int playerID, int coorX, int coorY);

     /**
      * Get a tile that exists (getTileWithName)
      * This will check all of the valid tiles and
      * return the tile with the inputted name
      *
      * @param playerID
      * @param coorX
      * @param coorY
      * @return
      */
     Tile *getTileWithName(int playerID, int coorX, int coorY);


public:
    Score player0Score;
    Score player1Score;

    /**
     * Captured tile (capturedTile)
     * This deals with tile captured
     * this will be initialized to
     * this will allow for the user
     * who overtakes an enemy tile to
     * get an extra move
     */
    bool capturedTile = false;


    /**
     * Constructor (Board)
     * This function will construct the board object.
     * Generally it does not need to take any input
     * since all information for the board is within
     * the logic of the board or its subclasses.
     *
     * @param void
     * @returns void
     */
    Board();

    string printBoard();
    string printCombinedBoard();

    /**
     * Print All Tiles (printTiles)
     * This function will loop through the tiles array.
     * It will then go and run the print tiles for each
     * of the tiles.
     *
     * @param void
     * @return string
     */
    string printTiles();

    /**
     * Select a singular tile (selectTile)
     * This is the function that will select a tile
     * that will allow for the movement of the tile
     * and a variety of other checks.
     *
     * @param tileName
     * @return void
     */
    bool selectTile(string tileName);

    /**
     * Get the currently selected tile (getSelectedTile)
     * This will quickly allow you to access the current
     * tile object for comparison.
     *
     * @return
     */
    Tile *getSelectedTile();
    /**
     * Moves the selected Tile (moveSelectedTile)
     * This function determines if the given move is valid or not,
     * depending on the player and if it is a kind or not, then moves the tile on
     * the board. This also accounts for when the tile can jump/overtake the opposing players tile.
     * @param dirX
     * @param dirY
     * @return bool
     */
    bool moveSelectedTile(int dirX, int dirY);

    bool completed();

    /**
     * returns a list of possible moves for given Tile
     * This function checks the Upper-Left, Upper-Right, Back-Left, and Back-Right movements for the tile,
     * if the tile is empty or a capture is possible, the move is added to the vector.
     * @param currTile
     * @return vector<string>
     */
    vector<tuple <string, int> > possibleMoves(Tile *currTile);

    /**
     * Called in possibleMoves
     * Ensures that the move is within the bounds of the board. If it is, the move is added to the vector
     * of moves.
     * @param mov
     * @param playerId
     * @param x
     * @param y
     * @return
     */
    bool appendMove(vector<tuple <string, int> > *mov, int playerId, int x, int y, int weight);

    void bestTile(int playerID);

    ~Board();
};


#endif //GAME_BOARD_H
