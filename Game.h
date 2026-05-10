#pragma once
// @@@@@@@@@@@@@@@@@@@@@@==========================================
// 
//  OOP Concept: Composition
//    Game HAS-A Board  (board is a member object, not inherited)
//    Game HAS-A sf::RenderWindow  [GRAPHIC]
//    Game HAS-A sf::Font          [GRAPHIC]
//
//  This class is responsible for:
//    - Opening the window                [GRAPHIC]
//    - Drawing the board and pieces      [GRAPHIC]
//    - Handling mouse clicks             [GRAPHIC]
//    - Applying move logic (calls Board) [LOGIC]
//    - Detecting win condition           [LOGIC]
// 
// ==========================================@@@@@@@@@@@@@@@@@@@@@@

#include "Board.h"
#include <SFML/Graphics.hpp>   // the entire SFML library for Graphics

class Game {
private:
    // Constants
    static const int TILE_SIZE  = 90;              // pixels per square
    static const int BOARD_PIXELS = TILE_SIZE * 8; // 720 px total
    Board board;        // the 8x8 board with all pieces
    PieceColor currentTurn;  // whose turn it is: WHITE or BLACK
    bool gameOver;     // true when a King has been captured
    PieceColor winner;       // who won (only meaningful if gameOver)

    int selectedRow;  // row of the piece the player clicked first
    int selectedCol;  // col of that piece  (-1 = nothing selected)

    sf::RenderWindow window;  // the OS window that appears on screen
    sf::Font font;    // font used to draw chess piece glyphs
    bool fontLoaded; // true if a usable font was found

    void drawSquare(int row, int col);   // draw one board tile
    void drawPiece (Piece* piece);       // draw one chess piece glyph
    void drawWinnerOverlay();            // dark veil + "WHITE WINS" text
    void render();                       // calls all draw functions

    void handleClick(int row, int col);  // process a player's mouse click

public:
    Game();
    void run();
};
