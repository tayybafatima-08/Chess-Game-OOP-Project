//  ROOK RULES:
//    1. Moves any number of squares HORIZONTALLY or VERTICALLY
//    2. Cannot move diagonally
//    3. Cannot jump over pieces,path must be completely clear
//    4. Can capture an enemy piece at the destination


#include "Rook.h"

Rook::Rook(PieceColor color, int row, int col): Piece(color, row, col) { 
}

bool Rook::isValidMove(int targetRow, int targetCol,Piece* board[8][8]) const 
{
    if (!inside(targetRow, targetCol)){
        return false;
    }

    if (currentRow == targetRow && currentCol == targetCol) {   // Rook can't be in same square
        return false;
    }

    bool isHorizontalMove = (currentRow == targetRow);
    bool isVerticalMove = (currentCol == targetCol);
    if (!isHorizontalMove && !isVerticalMove) {           // must move straight
        return false;
    }

    if (!pathClear(currentRow, currentCol, targetRow, targetCol, board)) {      // can't jump over pieces
        return false;
    }

    bool destinationEmpty = (board[targetRow][targetCol] == nullptr);
    bool destinationEnemy = (board[targetRow][targetCol] != nullptr && board[targetRow][targetCol]->getColor() != pieceColor);

    return destinationEmpty || destinationEnemy;      //destination must be empty or enemy 
}

sf::String Rook::getSymbol() const {          // GRAPHIC
    return sf::String(pieceColor == WHITE ? L'\u2656' : L'\u265C');
}