//  BISHOP RULES:
//    1. Moves any number of squares DIAGONALLY
//    2. Stays on the same color squares for the entire game
//    3. Cannot jump over pieces,diagonal path must be clear
//    4. Can capture an enemy piece at the destination

#include "Bishop.h"
#include <cmath>

Bishop::Bishop(PieceColor color, int row, int col)
    : Piece(color, row, col) {
}

bool Bishop::isValidMove(int targetRow, int targetCol,Piece* board[8][8]) const
{
    if (!inside(targetRow, targetCol)) {
        return false;
    }

    int rowDistance = abs(targetRow - currentRow);
    int colDistance = abs(targetCol - currentCol);

    if (rowDistance != colDistance || rowDistance == 0) {  //must move in diagonal (rowDistance == colDistance)
        return false;
    }

    if (!pathClear(currentRow, currentCol, targetRow, targetCol, board)) {  // can't jump over pieces
        return false;
    }

    bool destinationEmpty = (board[targetRow][targetCol] == nullptr);
    bool destinationEnemy = (board[targetRow][targetCol] != nullptr && board[targetRow][targetCol]->getColor() != pieceColor);

    return destinationEmpty || destinationEnemy;       //destination must be empty or enemy 
}

sf::String Bishop::getSymbol() const {        // GRAPHIC
    return sf::String(pieceColor == WHITE ? L'\u2657' : L'\u265D');
}