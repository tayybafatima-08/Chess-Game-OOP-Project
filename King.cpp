
//  KING RULES:
//    1. Moves exactly one square in any direction
//       (horizontal, vertical, or diagonal - all 8 neighbours)
//    2. Cannot move to a square that is under attack
//       (this is handled in Game — not inside isValidMove itself)
//    3. If the King is captured the game ends immediately

#include "King.h"
#include <cmath>

King::King(PieceColor color, int row, int col) : Piece(color, row, col) {}

bool King::isValidMove(int targetRow, int targetCol, Piece* board[8][8]) const
{
    if (!inside(targetRow, targetCol)) {
        return false;
    }

    if (currentRow == targetRow && currentCol == targetCol) { // King cannot stay in the same square
        return false;
    }

    int rowDistance = abs(targetRow - currentRow);
    int colDistance = abs(targetCol - currentCol);

    if (rowDistance > 1 || colDistance > 1) { //May move at most 1 square in either axis
        return false;
    }

    bool destinationEmpty = (board[targetRow][targetCol] == nullptr); // Destination must be empty or enemy
    bool destinationEnemy = (board[targetRow][targetCol] != nullptr && board[targetRow][targetCol]->getColor() != pieceColor);

    return destinationEmpty || destinationEnemy;
}

sf::String King::getSymbol() const {
    return sf::String(pieceColor == WHITE ? L'\u2654' : L'\u265A');
}
