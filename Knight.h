#pragma once
#include "Piece.h"

class Knight : public Piece {
public:
    Knight(PieceColor color, int row, int col);

    bool isValidMove(int targetRow, int targetCol,Piece* board[8][8]) const override;
    sf::String getSymbol() const override;};    // [GRAPHIC]