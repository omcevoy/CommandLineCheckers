//
// Created by Ryan Gurnick on 2019-05-08.
//
#include "heads/Board.h"
#include <vector>

using namespace std;

Board::Board() {
    int tileIterator = 0;
    for (int y = 0; y < BoardSize; ++y) { // y
        for (int x = 0; x < BoardSize; ++x) { // x
            if (((x + y) % 2) == 0) // create checkerboard pattern
            {
                board[y][x] = 0; // white
            }
            else
            {
                board[y][x] = 1; // black

                if ( y < TeamRows ) {
                    // player 0
                    Tile *t0 = new Tile(x, y, 0);
                    tiles[tileIterator] = t0;
                    tileIterator++;
                }

                if ( y > ((BoardSize-1)-TeamRows) && y <= (BoardSize-1) ) {
                    //player 1
                    Tile *t1 = new Tile(x, y, 1);
                    tiles[tileIterator] = t1;
                    tileIterator++;
                }
            }
        }
    }
}

string Board::printBoard() {
    string returnBoard;
    // starting y at -1 so that i can add the column numbers at the top
    for (int y = -1; y < BoardSize; ++y) { // loop through rows
        for (int x = 0; x < BoardSize; ++x) { // loop through columns

            if( y == -1 ) // add the column numbers at the top
            {
                returnBoard += to_string(x); // print the column numbers
                if ( x == BoardSize-1 ) returnBoard += "\n"; // at the end add a newline
            }
            else // for the checker board itself just print that normally.
            {
                returnBoard += to_string(board[y][x]);
            }
        }
        // ternary operator to print the row information only if the row is not -1
        (y != -1) ? returnBoard += "\t" + to_string(y) + "\n" : returnBoard += "\n";
    }
    return returnBoard;
}


string Board::printCombinedBoard() {
    // string for returning
    string megaString = "";
    int rowIterator = 0; // row number for printing

    for (int i = 0; i < BoardSize; ++i){
        megaString += to_string(i) + " ";    //prints the column number
    }
    megaString += "\n\n"; // give me some space

    for (int y = 0; y < BoardSize; ++y) { // rows
        for (int x = 0; x < BoardSize; ++x) { // cols
            if( (( ( x + y ) % 2 ) != 0)) { // confidential trade secrets
                bool playerZeroExists = tileWithNameExists(0, x, y); // is there a player 0 tile there?
                bool playerOneExists = tileWithNameExists(1, x, y); // is there a player 1 tile there?
                if (playerZeroExists || playerOneExists) { // or...

                    // check which player specifically
                    int player = 0;
                    if( playerZeroExists && !playerOneExists ) {
                        player = 0; // 0
                    }else if ( playerOneExists && !playerZeroExists ) {
                        player = 1; // 1
                    }

                    Tile *foundTile = getTileWithName(player, x, y); // get the specific tile
                    if ( foundTile != nullptr && foundTile->valid ) {   // was that tile really found and valid
                        // which symbol
                        megaString += [](int player) { if (player) return "\e[32m-\e[0m "; else return "\e[33m*\e[0m "; }(player);
                    }
                } else {
                    // free black spots
                    megaString += "1 ";
                }
            } else {
                // use the board pattern now.
                megaString += to_string(board[y][x]) + " ";

            }
        }
        megaString += "  " + to_string(rowIterator); rowIterator++; //prints the row number
        megaString += "\n"; // give me some space
    }
    return megaString; // return it.
}


string Board::printTiles() {
    string returnTiles; // accumulator
    for (int i = 0; i < 2*TeamTileCount; ++i) {
        returnTiles += tiles[i]->printTile(); // print tile str
        returnTiles += "\n"; // new line
    }
    return returnTiles; // returned
}

bool Board::tileWithNameExists(int playerID, int coorX, int coorY) {
    bool tileExists = false;
    // retrieves the start index to iterate through the array
    int startI = [](int player){ if (!player) return 0; else return 20;}(playerID);
    // retrieves the end count to stop iterating through the array
    int endI = [](int player){ if (!player) return 20; else return 40;}(playerID);
    // check if the name exists on any of the elements of the tiles array.
    for (int i = startI; i < endI; ++i) {
        if(coorX == tiles[i]->x && coorY == tiles[i]->y && tiles[i]->valid) {
            tileExists = true;
        }
    }
    return tileExists;
}

Tile *Board::getTileWithName(int playerID, int coorX, int coorY) {
    Tile *returnTile = nullptr;
    // retrieves the start index to iterate through the array
    int startI = [](int player){ if (!player) return 0; else return 20;}(playerID);
    // retrieves the end count to stop iterating through the array
    int endI = [](int player){ if (!player) return 20; else return 40;}(playerID);
    // check if the name exists on any of the elements of the tiles array.
    for (int i = startI; i < endI; ++i) {
        // loop through the tiles and get the given tile that we are looking for.
        if(coorX == tiles[i]->x && coorY == tiles[i]->y && tiles[i]->valid) {
            returnTile = tiles[i];
        }
    }
    return returnTile;
}

bool Board::selectTile(string tileName) {
    int playerID, selectX, selectY = 0;
    smatch payload;

    regex expression("([01])-([0-9]+)-([0-9]+)");
    bool found = regex_search(tileName, payload, expression);

    if(!found){
        cout << "Invalid Tile Selection" << endl;
        return false;
    }

    // set all of the tile related info
    // playerid will automatically be checked with regex to be 0 or 1
    playerID = atoi(payload[1].str().c_str());
    selectX = atoi(payload[2].str().c_str());
    selectY = atoi(payload[3].str().c_str());

    // check the x and y value and ensure that they are on the board
    if(selectX > BoardSize-1 || selectY > BoardSize-1){
        cout << "Invalid Tile Selection"<< endl;
        return false;
    }
    // check to see if the tile exists or not
    bool tileExists = tileWithNameExists(playerID, selectX, selectY);
    if(tileExists) {
        // if the tile does exist then make the selection of the tile
        cout << "Tile now selected " << tileName << endl;
        Tile *returnedTile = getTileWithName(playerID, selectX, selectY);

        tileSelectedObject = returnedTile;
        tileSelected = tileName;
        return true;
    }
    else
    {
        cout << "Tile does not exists on the board as you specified: " << tileName << endl;
        return false;
    }
}

bool Board::moveSelectedTile(int dirX, int dirY) {
    // if the selected tile is the nullptr then we cannot select this tile
    if(tileSelectedObject == nullptr){
        cout << "Tile Selected is the nullptr" << endl;
        return false;
    }
    // if the direction the tile wants to be moved is invalid then we cant move
    if((dirX != 1 && dirX != -1) || (dirY != 1 && dirY != -1)) {
        return false;
    }

    // This creates the bias for the players direction since both sets of tiles are on the same x-y plane.
    int dirBias = [](int player){ if (player == 0) { return 1; }else{ return -1;}}(tileSelectedObject->player);
    // check to see if our tile is the tile that is taking up that current position on the checkers board
    bool spotTakenBySelf = tileWithNameExists(tileSelectedObject->player, tileSelectedObject->x+ (dirX * dirBias), tileSelectedObject->y+ (dirY * dirBias));
    if(spotTakenBySelf){
        // if the spot is taken, we cannot move
        return false;
    }

    int other_player;
    // find the other player's id
    if(tileSelectedObject->player == 1) {
        other_player = 0;
    } else {
        other_player = 1;
    }
    // if the spot is taken by another tile that exists on the board. Similiar to spotTakenBySelf.
    bool spotTakenByOther = tileWithNameExists(other_player, tileSelectedObject->x + (dirX * dirBias), tileSelectedObject->y + (dirY * dirBias));
    if(spotTakenByOther){
        // this is going to check if there is a tile that we are able to jump over,
        bool spotTakenByOtherEx = tileWithNameExists(other_player, tileSelectedObject->x + ((dirX*2) * dirBias), tileSelectedObject->y + ((dirY*2) * dirBias));
        if(spotTakenByOtherEx) {
            // if the spot is taken and the jump cannot be performed.
            return false;
        } else {
            // if the jump can be performed then jump over the tile and take it off the board. (make it invalid)
            Tile *overTakenTile = getTileWithName(other_player,  tileSelectedObject->x + (dirX * dirBias), tileSelectedObject->y + (dirY * dirBias));
            overTakenTile->valid = false;
            capturedTile = true;
            if(other_player == 0) {
                this->player1Score++;
                cout << "You have overtaken an enemy tile " << overTakenTile->name << endl;
            } else if (other_player == 1) {
                this->player0Score++;
                cout << "You have overtaken an enemy tile " << overTakenTile->name << endl;
            }
            tileSelectedObject->moveTile(dirX, dirY, dirBias);
        }
    }

    return tileSelectedObject->moveTile(dirX, dirY, dirBias);
}

Tile *Board::getSelectedTile() {
    return tileSelectedObject;
}

bool Board::completed() {
    bool playerO, player1 = false;
    for(int i = 0; i < 2*TeamTileCount; ++i) {
        if (tiles[i]->valid && tiles[i]->player == 0) {
            playerO = true;
        }

        if (tiles[i]->valid && tiles[i]->player == 1) {
            player1 = true;
        }
    }

    if((!playerO && player1) || (playerO && !player1)){
        return true;
    }
    return false;
}
void Board::bestTile(int playerID) {
    tuple<string, int> maxMove;
    Tile *wantedTile;
    maxMove = make_tuple("cats are nice", -100);
    for (Tile* t: tiles){
        if (t->player == playerID) {
            vector< tuple <string, int> > moves = possibleMoves(t);
            if (moves.size()) {
                for (int i = 0; i < moves.size(); i++){
                    if (get<1>(maxMove) < get<1>(moves[i])){
                        maxMove = moves[i];
                        wantedTile = t;
                    }
                }

            }
        }
    }
    cout << "Optimal Tile is: " << wantedTile->name << endl;
    cout << "It's best move is to: " <<  get<0>(maxMove) << endl;

}

vector<tuple <string, int> > Board::possibleMoves(Tile *currTile) {
    vector<tuple <string, int> > moves;
    int playerID = currTile->player;
    int selectX = currTile->x;
    int selectY = currTile->y;

    int dirBias = [](int pID){ if (pID == 0) { return 1; }else{ return -1;}}(playerID); //accounts for players opposite movements
    int other_player;
    if(playerID == 1) {
        other_player = 0;
    } else {
        other_player = 1;
    }
    // All Tiles to check: "U-L", "U-R", "B-L", "B-R" = Upper Left, Upper Right, Back Left, Back Right
    // Three Cases for Movements: Taken by a friend, a capture is possible, or its empty.

    //if Tile is landlocked by friends, there are no possible moves
    if (tileWithNameExists(playerID, selectX - (1 * dirBias) , selectY + (1 * dirBias))){ //checks if friend is at U-L
        if (tileWithNameExists(playerID, selectX + (1 * dirBias) , selectY + (1 * dirBias))){//checks friend at U-R
            if (currTile->isKing()) { //if king check backwards
                if (tileWithNameExists(playerID, selectX - (1 * dirBias),
                                       selectY - (1 * dirBias))) { //checks if friend is at B-L
                    if (tileWithNameExists(playerID, selectX + (1 * dirBias),
                                           selectY - (1 * dirBias))) {//checks friend at B-R
                        return moves;
                    }
                } //if a tile is landlocked by friends, there are no possible moves
            }else{
                return moves;
            }
        }
    }
    //Checks if U-L is an enemy/empty
    if (!tileWithNameExists(playerID, selectX - (1 * dirBias) , selectY + (1 * dirBias))) {//Checks if U-L !=friendly
        //checks if U-L is taken by an enemy
        if(tileWithNameExists(other_player, selectX - (1 * dirBias), selectY + (1 * dirBias))) {
            //*** checks if 2 * U-L is empty for potential capture
            if (tileWithNameExists(other_player, selectX - (2 * dirBias), selectY + (2 * dirBias))) {
                //pass, there's an enemy there already
            }else{ //Checks that 2 * U-L is an empty tile is not occupied by a friend
                if (!tileWithNameExists(playerID, selectX - (2 * dirBias), selectY + (2 * dirBias))) {
                    //if empty, add capture
                    if (tileWithNameExists(other_player, selectX - (3 * dirBias), selectY + (3 * dirBias))) {
                        appendMove(&moves, playerID, selectX - (2 * dirBias), selectY + (2 * dirBias), 5);
                    } else {
                        appendMove(&moves, playerID, selectX - (2 * dirBias), selectY + (2 * dirBias), 10);
                    }
                }
            }
        } else {  //U-L is not taken by enemy or a friend, so it must be empty
            if (tileWithNameExists(other_player, selectX - (2 * dirBias), selectY + (2 * dirBias))) {
                    appendMove(&moves, playerID, selectX - (1 * dirBias), selectY + (1 * dirBias), -10);
            } else if (tileWithNameExists(other_player, selectX, selectY + (2*dirBias))){
                appendMove(&moves, playerID, selectX - (1 * dirBias), selectY + (1 * dirBias), -10);
            } else {
                appendMove(&moves, playerID, selectX - (1 * dirBias), selectY + (1 * dirBias), 0); //add move
            }
        }
    }
    //Checks if U-R is an enemy/empty
    if (!tileWithNameExists(playerID, selectX + (1 * dirBias) , selectY + (1 * dirBias))) {//Checks if U-R !=friendly
        //Checks if U-R is taken by an enemy
        if (tileWithNameExists(other_player, selectX + (1 * dirBias), selectY + (1 * dirBias))){//is U-R an enemy
            //*** checks if 2 * U-R is empty for potential capture
            if (tileWithNameExists(other_player, selectX + (2 * dirBias), selectY + (2 * dirBias))) {
                //pass, there's an enemy
            } else {//check if it's a friend
                if (!tileWithNameExists(playerID, selectX + (2 * dirBias), selectY + (2 * dirBias))) {
                    //tile is empty, add capture
                    if (tileWithNameExists(other_player, selectX + (3 * dirBias), selectY + (3 * dirBias))) {
                        appendMove(&moves, playerID, selectX + (2 * dirBias), selectY + (2 * dirBias), 5);
                    } else {
                        appendMove(&moves, playerID, selectX + (2 * dirBias), selectY + (2 * dirBias), 10);
                    }
                }
            }
        }
        else {  //U-R is not taken by enemy or friend, so it must be empty
            if (tileWithNameExists(other_player, selectX - (2 * dirBias), selectY + (2 * dirBias))) {
                if (tileWithNameExists(other_player, selectX, selectY + (2*dirBias))) {
                    appendMove(&moves, playerID, selectX + (1 * dirBias), selectY + (1 * dirBias), -10);
                } else if (tileWithNameExists(other_player, selectX, selectY + (2*dirBias))) {
                    appendMove(&moves, playerID, selectX + (1 * dirBias), selectY + (1 * dirBias), -10);
                }
            } else {
                appendMove(&moves, playerID, selectX + (1 * dirBias), selectY + (1 * dirBias), 0); //add move
            }
        }
    }

    if(currTile->isKing()){
        //Checks if B-L is an enemy/friendly
        if (!tileWithNameExists(playerID, selectX - (1 * dirBias) , selectY - (1 * dirBias))) {//Checks if B-L !=friendly
            //checks if B-L is taken by an enemy
            if(tileWithNameExists(other_player, selectX - (1 * dirBias), selectY - (1 * dirBias))) {
                //*** checks if 2 * B-L is empty for potential capture
                if (tileWithNameExists(other_player, selectX - (2 * dirBias), selectY - (2 * dirBias))) {
                    //pass, there's an enemy
                }else{ //Checks that 2 * B-L is not taken by a friend
                    if (!tileWithNameExists(playerID, selectX - (2 * dirBias), selectY - (2 * dirBias))) {
                        //tile is empty, add capture
                        if (tileWithNameExists(other_player, selectX - (3 * dirBias), selectY - (3 * dirBias))) {
                            appendMove(&moves, playerID, selectX - (2 * dirBias), selectY - (2 * dirBias), 5);
                        } else {
                            appendMove(&moves, playerID, selectX - (2 * dirBias), selectY - (2 * dirBias), 10);
                        }
                    }
                }
            } else {  //B-L is not taken by enemy or friend, so it must be empty
                if (tileWithNameExists(other_player, selectX - (2 * dirBias), selectY - (2 * dirBias))) {
                    appendMove(&moves, playerID, selectX - (1 * dirBias), selectY - (1 * dirBias), -10);
                } else {
                    appendMove(&moves, playerID, selectX - (1 * dirBias), selectY - (1 * dirBias), 0); //add move
                }
            }
        }
        //Checks if B-R is an enemy/friendly
        if (!tileWithNameExists(playerID, selectX + (1 * dirBias) , selectY - (1 * dirBias))) {//Checks if B-R !=friendly
            //checks if B-R is taken by an enemy
            if(tileWithNameExists(other_player, selectX + (1 * dirBias), selectY - (1 * dirBias))) {
                //*** checks if 2 * B-R is empty for potential capture
                if (tileWithNameExists(other_player, selectX + (2 * dirBias), selectY - (2 * dirBias))) {
                    //pass, there's an enemy
                } else { //Checks that 2 * B-R is not taken by a friend
                    if (!tileWithNameExists(playerID, selectX + (2 * dirBias), selectY - (2 * dirBias))) {
                        //tile is empty, add capture
                        if (tileWithNameExists(other_player, selectX + (3 * dirBias), selectY - (3 * dirBias))) {
                            appendMove(&moves, playerID, selectX + (2 * dirBias), selectY - (2 * dirBias), 5);
                        } else {
                            appendMove(&moves, playerID, selectX + (2 * dirBias), selectY - (2 * dirBias), 10);
                        }
                    }
                }
            }else{  //B-R is not taken by enemy or friend, so it must be empty
                if (tileWithNameExists(other_player, selectX + (2 * dirBias), selectY - (2 * dirBias))) {
                    appendMove(&moves, playerID, selectX + (1 * dirBias), selectY - (1 * dirBias), -10);
                } else {
                    appendMove(&moves, playerID, selectX + (1 * dirBias), selectY - (1 * dirBias), 0); //add move
                } //add move
            }
        }
    }
    return moves;
}

bool Board::appendMove(vector<tuple <string, int> > *mov, int playerId, int x, int y, int weight) {
    tuple <string, int> applesauce;
    if(x >= 0 && x < BoardSize){
        if( y >= 0 && y < BoardSize ) {
            //mov->push_back(to_string(playerId) + '-' + to_string(x) + '-' + to_string(y));
            applesauce = make_tuple(to_string(playerId) + '-' + to_string(x) + '-' + to_string(y), weight);
            mov->push_back(applesauce);
            return true;
        }
    }
    return false;
}



Board::~Board() {
    // destruct all the things
    // loop through tiles and destroy pointers
    for ( Tile *t: tiles ){
        delete t;
    }
}
