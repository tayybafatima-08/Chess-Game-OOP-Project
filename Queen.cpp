//  QUEEN RULES:
//    The Queen combines the Rook and the Bishop:
//    1. Moves any number of squares in any direction: horizontally,vertically like Rook OR diagonally like Bishop
//    2. Cannot jump over pieces
//    3. Can capture an enemy piece at the destination
//    4. Most powerful piece,covers 27 squares from the center

#include "Queen.h"
#include <cmath>

Queen::Queen(PieceColor color, int row, int col)
    : Piece(color, row, col) {
}

bool Queen::isValidMove(int targetRow, int targetCol,Piece* board[8][8]) const
{
    if (!inside(targetRow, targetCol)) {
        return false;
    }

    if (currentRow == targetRow && currentCol == targetCol) {    // can't be in same square
        return false;
    }

    int rowDistance = abs(targetRow - currentRow);
    int colDistance = abs(targetCol - currentCol);

    bool isStraightMove = (currentRow == targetRow || currentCol == targetCol);
    bool isDiagonalMove = (rowDistance == colDistance);

    if (!isStraightMove && !isDiagonalMove) {        // must move straight or diagonal
        return false;
    }

    if (!pathClear(currentRow, currentCol, targetRow, targetCol, board)) {     // can't jump over pieces
        return false;
    }

    bool destinationEmpty = (board[targetRow][targetCol] == nullptr);
    bool destinationEnemy = (board[targetRow][targetCol] != nullptr && board[targetRow][targetCol]->getColor() != pieceColor);

    return destinationEmpty || destinationEnemy;      // destination must be empty or enemy 
}

sf::String Queen::getSymbol() const {         // GRAPHIC
    return sf::String(pieceColor == WHITE ? L'\u2655' : L'\u265B');
}