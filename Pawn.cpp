//  PAWN RULES:
//    1. Moves ONE square forward (toward the opponent's side)
//    2. On its very first move it MAY move TWO squares forward
//    3. Captures DIAGONALLY one square forward-left or forward-right
//    4. Cannot capture straight ahead
//    5. White moves UP   the board (row index decreases)
//       Black moves DOWN the board (row index increases)


#include "Pawn.h"
#include <cmath>

Pawn::Pawn(PieceColor color, int row, int col) : Piece(color, row, col) {}

bool Pawn::isValidMove(int targetRow, int targetCol,Piece* board[8][8]) const{
    if (!inside(targetRow, targetCol)) return false;    // White pawn moves toward row 0, so it's direction is  = -1, Black pawn moves toward row 7  so it's direction is  = +1
    int moveDirection = (pieceColor == WHITE) ? -1 : 1; // White pawns start on row 6, Black pawns start on row 1
    int startingRow = (pieceColor == WHITE) ? 6 : 1;
    int rowDiff = targetRow - currentRow;  // how far we move vertically
    int colDiff = targetCol - currentCol;  // how far we move horizontally

    //   Column must NOT change (colDiff == 0)
    //   Row must change by exactly 1 step in the correct direction
    //   Destination square must be EMPTY (pawns cannot capture forward)
    if (colDiff == 0 && rowDiff == moveDirection && board[targetRow][targetCol] == nullptr)
        return true;

    //   Pawn must be on its starting row
    //   Column must NOT change
    //   Both the square we skip AND the destination must be empty
    if (colDiff == 0 && currentRow == startingRow && rowDiff == 2 * moveDirection && board[currentRow + moveDirection][currentCol] == nullptr && board[targetRow][targetCol] == nullptr)
        return true;

    //   Move exactly 1 column left or right (abs makes -1 and +1 both work)
    //   Move 1 row in the correct direction
    //   Destination must hold an ENEMY piece
    if (abs(colDiff) == 1 && rowDiff == moveDirection && board[targetRow][targetCol] != nullptr && board[targetRow][targetCol]->getColor() != pieceColor)
        return true;

    return false;}

sf::String Pawn::getSymbol() const {
   return sf::String(pieceColor == WHITE ? L'\u2659' : L'\u265F');}
