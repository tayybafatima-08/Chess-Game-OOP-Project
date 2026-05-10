#pragma once
#include <SFML/Graphics.hpp> 
#include <string>
using namespace std;

enum PieceColor { WHITE, BLACK };
class Piece {
protected:
    PieceColor pieceColor;
    int currentRow;
    int currentCol;
public:

    Piece(PieceColor color, int row, int col) {
        this->pieceColor  = color;
        this->currentRow  = row;
        this->currentCol  = col;}

    virtual ~Piece() {}

    PieceColor getColor()  const {
    return pieceColor;  }

    int getRow() const {
    return currentRow;  }

    int getCol() const {
    return currentCol;  }

    void setPosition(int newRow, int newCol) {
        currentRow = newRow;
        currentCol = newCol;}

    virtual bool isValidMove(int targetRow, int targetCol,Piece* board[8][8]) const = 0;
    virtual sf::String getSymbol() const = 0;             // [GRAPHIC]
    static bool isKing(Piece* piecePtr);};

inline bool inside(int row, int col) {
    return row >= 0 && row < 8 && col >= 0 && col < 8;}

inline bool pathClear(int fromRow, int fromCol, int toRow,   int toCol, Piece* board[8][8]){
    int rowStep = (toRow > fromRow) - (toRow < fromRow);
    int colStep = (toCol > fromCol) - (toCol < fromCol);
    int r = fromRow + rowStep;
    int c = fromCol + colStep;

    while (r != toRow || c != toCol) {
        if (board[r][c] != nullptr)
        return false;
        r += rowStep;
        c += colStep;}
    return true;}