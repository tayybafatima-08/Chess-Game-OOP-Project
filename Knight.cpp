//    KNIGHT RULES:
//    1. Moves in an L-shape:
//    2. The ONLY piece that can JUMP OVER other pieces
//    3. Can capture an enemy piece at the destination

#include "Knight.h"
#include <cmath>

Knight::Knight(PieceColor color, int row, int col) : Piece(color, row, col) {}

bool Knight::isValidMove(int targetRow, int targetCol, Piece* board[8][8]) const {
    if (!inside(targetRow, targetCol))
    return false;

    int rowDistance = abs(targetRow - currentRow);
    int colDistance = abs(targetCol - currentCol);
    bool validLShape = (rowDistance == 2 && colDistance == 1) || (rowDistance == 1 && colDistance == 2);

    if (!validLShape)
    return false;

    bool destinationEmpty = (board[targetRow][targetCol] == nullptr);
    bool destinationEnemy = (board[targetRow][targetCol] != nullptr && board[targetRow][targetCol]->getColor() != pieceColor);
    return destinationEmpty || destinationEnemy;}

sf::String Knight::getSymbol() const {        // [GRAPHIC]
    return sf::String(pieceColor == WHITE ? L'\u2658' : L'\u265E');}