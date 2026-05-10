#pragma once
#include "Piece.h"

class Board {
private:
    Piece* grid[8][8];        //Board has-a 2D array of Piece pointers(Composition)
                              //8×8 board
public:
    Board();    
    ~Board();   

    Piece* getPiece(int row, int col) const;    

    Piece* movePiece(int fromRow, int fromCol, int toRow, int toCol);   //returns the captured piece (or nullptr if none)

    Piece* (*getGrid())[8];      // GRAPHIC 

};