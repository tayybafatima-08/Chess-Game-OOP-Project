#include "Piece.h"
#include "King.h"
bool Piece::isKing(Piece* piecePtr) {
   return dynamic_cast<King*>(piecePtr) != nullptr;}
