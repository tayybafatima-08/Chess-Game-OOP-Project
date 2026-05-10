#include "Board.h"
#include "Pawn.h"
#include "Rook.h"
#include "Knight.h"
#include "Bishop.h"
#include "Queen.h"
#include "King.h"

Board::Board() {
    for (int row = 0; row < 8; row++)
        for (int col = 0; col < 8; col++)
            grid[row][col] = nullptr;

    //BLACK pieces on rows 0 and 1 (top of screen)
    grid[0][0] = new Rook(BLACK, 0, 0);
    grid[0][1] = new Knight(BLACK, 0, 1);
    grid[0][2] = new Bishop(BLACK, 0, 2);
    grid[0][3] = new Queen(BLACK, 0, 3);
    grid[0][4] = new King(BLACK, 0, 4);
    grid[0][5] = new Bishop(BLACK, 0, 5);
    grid[0][6] = new Knight(BLACK, 0, 6);
    grid[0][7] = new Rook(BLACK, 0, 7);
    for (int col = 0; col < 8; col++)
        grid[1][col] = new Pawn(BLACK, 1, col);

    //WHITE pieces on rows 6 and 7 (bottom of screen)
    for (int col = 0; col < 8; col++)
        grid[6][col] = new Pawn(WHITE, 6, col);
    grid[7][0] = new Rook(WHITE, 7, 0);
    grid[7][1] = new Knight(WHITE, 7, 1);
    grid[7][2] = new Bishop(WHITE, 7, 2);
    grid[7][3] = new Queen(WHITE, 7, 3);
    grid[7][4] = new King(WHITE, 7, 4);
    grid[7][5] = new Bishop(WHITE, 7, 5);
    grid[7][6] = new Knight(WHITE, 7, 6);
    grid[7][7] = new Rook(WHITE, 7, 7);
}

Board::~Board() {
    for (int row = 0; row < 8; row++)
        for (int col = 0; col < 8; col++)
            if (grid[row][col] != nullptr)
                delete grid[row][col];
}

Piece* Board::getPiece(int row, int col) const {
    return grid[row][col];
}

Piece* Board::movePiece(int fromRow, int fromCol,
    int toRow, int toCol)
{
    Piece* movingPiece = grid[fromRow][fromCol];    // piece being moved
    Piece* capturedPiece = grid[toRow][toCol];      // piece being taken (may be nullptr)


    grid[toRow][toCol] = movingPiece;  // Place moving piece at destination
    grid[fromRow][fromCol] = nullptr;  // Clear the source square

    movingPiece->setPosition(toRow, toCol); // Update the piece's own internal position record

    return capturedPiece;    // Return whatever was at the destination
}

Piece* (*Board::getGrid())[8] {
    return grid;
}