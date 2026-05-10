
#include "Game.h"
#include <optional>    // Graphic needed for SFML 3 event polling
using namespace std;

Game::Game()
    : currentTurn(WHITE),
      gameOver(false),
      winner(WHITE),
      selectedRow(-1),              // -1 = nothing selected yet
      selectedCol(-1),

      window(sf::VideoMode(sf::Vector2u(BOARD_PIXELS, BOARD_PIXELS)),
             "Chess - CS1004 OOP Project"),

      fontLoaded(false)             // assume no font until we load one
{
 
    window.setFramerateLimit(60);

    if (font.openFromFile("C:/Windows/Fonts/seguisym.ttf")) fontLoaded = true;
    else if (font.openFromFile("C:/Windows/Fonts/arial.ttf"))    fontLoaded = true;
    else if (font.openFromFile("arial.ttf"))                     fontLoaded = true;
    
}


void Game::drawSquare(int row, int col) {
    bool isLightSquare = ((row + col) % 2 == 0);
    sf::Color tileColor = isLightSquare
        ? sf::Color(232, 220, 202)   // warm beige  (light squares)
        : sf::Color(120,  90,  70);  // dark brown  (dark squares)

    sf::RectangleShape tileShape(sf::Vector2f((float)TILE_SIZE, (float)TILE_SIZE));
    tileShape.setPosition(sf::Vector2f((float)(col * TILE_SIZE),
                                       (float)(row * TILE_SIZE)));
    tileShape.setFillColor(tileColor);
    window.draw(tileShape); 

    sf::ConvexShape shineTriangle;
    shineTriangle.setPointCount(3);

    shineTriangle.setPoint(0, sf::Vector2f((float)(col * TILE_SIZE),
                                            (float)(row * TILE_SIZE)));
    shineTriangle.setPoint(1, sf::Vector2f((float)(col * TILE_SIZE + TILE_SIZE),
                                            (float)(row * TILE_SIZE)));
    shineTriangle.setPoint(2, sf::Vector2f((float)(col * TILE_SIZE),
                                            (float)(row * TILE_SIZE + TILE_SIZE)));
    shineTriangle.setFillColor(sf::Color(255, 255, 255, isLightSquare ? 35 : 22));
    window.draw(shineTriangle);

    if (row == selectedRow && col == selectedCol) {
        sf::RectangleShape selectionBorder(
            sf::Vector2f((float)TILE_SIZE - 6, (float)TILE_SIZE - 6));
        selectionBorder.setPosition(sf::Vector2f((float)(col * TILE_SIZE + 3),
                                                  (float)(row * TILE_SIZE + 3)));
        selectionBorder.setFillColor(sf::Color::Transparent); 
        selectionBorder.setOutlineColor(sf::Color(255, 215, 0)); 
        selectionBorder.setOutlineThickness(4.0f);
        window.draw(selectionBorder);
    }
}


void Game::drawPiece(Piece* piece) {
    if (piece == nullptr) return;   
    if (!fontLoaded)      return;   

    // Pixel center of this tile
    float centerX = piece->getCol() * TILE_SIZE + TILE_SIZE / 2.0f;
    float centerY = piece->getRow() * TILE_SIZE + TILE_SIZE / 2.0f;

    sf::String glyphSymbol = piece->getSymbol();

    sf::Text shadowText(font, glyphSymbol, (unsigned int)(TILE_SIZE * 0.75f));
    shadowText.setFillColor(sf::Color(0, 0, 0, 100)); 
    sf::FloatRect shadowBounds = shadowText.getLocalBounds();
    shadowText.setOrigin(sf::Vector2f(
        shadowBounds.position.x + shadowBounds.size.x / 2.0f,
        shadowBounds.position.y + shadowBounds.size.y / 2.0f));
    shadowText.setPosition(sf::Vector2f(centerX + 2, centerY + 3)); 
    window.draw(shadowText);  

    // Main piece pass
    sf::Text pieceText(font, glyphSymbol, (unsigned int)(TILE_SIZE * 0.75f));

    if (piece->getColor() == WHITE) {
        pieceText.setFillColor(sf::Color(250, 248, 240));    
        pieceText.setOutlineColor(sf::Color( 40,  30,  20)); // dark outline
    } else {
        pieceText.setFillColor(sf::Color( 35,  25,  20));    // near-black fill
        pieceText.setOutlineColor(sf::Color(220, 215, 200)); // light outline
    }
    pieceText.setOutlineThickness(1.5f);  

    sf::FloatRect pieceBounds = pieceText.getLocalBounds();
    pieceText.setOrigin(sf::Vector2f(
        pieceBounds.position.x + pieceBounds.size.x / 2.0f,
        pieceBounds.position.y + pieceBounds.size.y / 2.0f));
    pieceText.setPosition(sf::Vector2f(centerX, centerY));
    window.draw(pieceText);  
}

void Game::drawWinnerOverlay() {
    sf::RectangleShape veil(sf::Vector2f((float)BOARD_PIXELS,
                                          (float)BOARD_PIXELS));
    veil.setFillColor(sf::Color(0, 0, 0, 160)); 
    window.draw(veil);  

    if (!fontLoaded) return;

    sf::String winMessage = (winner == WHITE)
        ? sf::String(L"WHITE WINS")
        : sf::String(L"BLACK WINS");

    sf::Text winText(font, winMessage, 70);
    winText.setFillColor(sf::Color(255, 215, 0));    // gold
    winText.setOutlineColor(sf::Color::Black);
    winText.setOutlineThickness(3.0f);

    sf::FloatRect textBounds = winText.getLocalBounds();
    winText.setOrigin(sf::Vector2f(
        textBounds.position.x + textBounds.size.x / 2.0f,
        textBounds.position.y + textBounds.size.y / 2.0f));
    winText.setPosition(sf::Vector2f(BOARD_PIXELS / 2.0f,
                                      BOARD_PIXELS / 2.0f));
    window.draw(winText); 
}

void Game::render() {
    // Fill background with near-black (visible between tiles)
    window.clear(sf::Color(20, 18, 16));

    // Draw all 64 squares (background tiles)
    for (int row = 0; row < 8; row++)
        for (int col = 0; col < 8; col++)
            drawSquare(row, col);

    // Draw all pieces on top of the tiles
    for (int row = 0; row < 8; row++)
        for (int col = 0; col < 8; col++)
            drawPiece(board.getPiece(row, col));  

    if (gameOver)
        drawWinnerOverlay();

    window.display();
}

void Game::handleClick(int clickedRow, int clickedCol) {
    if (gameOver) return; 

    if (selectedRow == -1) {
        Piece* clickedPiece = board.getPiece(clickedRow, clickedCol);

        if (clickedPiece != nullptr &&
            clickedPiece->getColor() == currentTurn) {
            selectedRow = clickedRow;
            selectedCol = clickedCol;
        }
    }
    else {
        if (clickedRow == selectedRow && clickedCol == selectedCol) {
            selectedRow = selectedCol = -1;
        }
        else {
            Piece* movingPiece = board.getPiece(selectedRow, selectedCol);

            if (movingPiece->isValidMove(clickedRow, clickedCol,
                                          board.getGrid()))
            {
                Piece* capturedPiece = board.movePiece(selectedRow, selectedCol,
                                                        clickedRow,  clickedCol);

                if (capturedPiece != nullptr) {
                    if (Piece::isKing(capturedPiece)) {
                        gameOver = true;
                        winner   = currentTurn; 
                    }
                    delete capturedPiece;  
                }

                if (!gameOver)
                    currentTurn = (currentTurn == WHITE) ? BLACK : WHITE;
            }

            selectedRow = selectedCol = -1;
        }
    }
}


void Game::run() {
    while (window.isOpen()) {

        while (const std::optional event = window.pollEvent()) {

            if (event->is<sf::Event::Closed>()) {
                window.close();
            }

            else if (const auto* mouseEvent =
                     event->getIf<sf::Event::MouseButtonPressed>()) {

                if (mouseEvent->button == sf::Mouse::Button::Left) {

                    int boardCol = mouseEvent->position.x / TILE_SIZE;
                    int boardRow = mouseEvent->position.y / TILE_SIZE;

                    if (inside(boardRow, boardCol))
                        handleClick(boardRow, boardCol);
                }
            }
        }

        render();
    }
}
