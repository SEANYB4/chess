#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "pawnValidate.h"


const int WINDOW_WIDTH = 400;
const int WINDOW_HEIGHT = 400;
const int BOARD_SIZE = 8; // Chessboard is 8x8
const int SQUARE_SIZE = WINDOW_WIDTH / BOARD_SIZE;


bool isWhiteTurn = true;


std::vector<sf::Texture> textures(13);
sf::Sprite pieces[BOARD_SIZE][BOARD_SIZE];

// Selected square

sf::Vector2i selectedSquare(-1, -1); // Initialize to an invalid position

int main() {

    try {
    // Load textures for white pieces
    textures[12].loadFromFile("WP.png"); // White Pawn
    textures[1].loadFromFile("WKn.png"); // WHite Knight
    textures[2].loadFromFile("WB.png"); // White Bishop
    textures[3].loadFromFile("WR.png"); // White Rook
    textures[4].loadFromFile("WQ.png"); // White Queen
    textures[5].loadFromFile("WK.png"); // White King

    // Load textures for Black pieces
    textures[6].loadFromFile("BP.png"); // Black Pawn
    textures[7].loadFromFile("BKn.png"); // Black Knight
    textures[8].loadFromFile("BB.png"); // Black Bishop
    textures[9].loadFromFile("BR.png"); // Black Rook
    textures[10].loadFromFile("BQ.png"); // Black Queen
    textures[11].loadFromFile("BK.png"); // Black King

    
    } catch (const std::exception& e) {
        std::cerr << "Error loading textures: " << e.what() << std::endl;
        return -1;
    }


    int board[BOARD_SIZE][BOARD_SIZE] = {
        {9, 7, 8, 10, 11, 8, 7, 9},
        {6, 6, 6, 6, 6, 6, 6, 6},
        {13, 13, 13, 13, 13, 13, 13, 13},
        {13, 13, 13, 13, 13, 13, 13, 13},
        {13, 13, 13, 13, 13, 13, 13, 13},
        {13, 13, 13, 13, 13, 13, 13, 13},
        {12, 12, 12, 12, 12, 12, 12, 12},
        {3, 1, 2, 4, 5, 2, 1, 3}
    };



    // Assign textures to sprites based on board setup

    for (int x = 0; x < BOARD_SIZE; x++) {
        for (int y = 0; y < BOARD_SIZE; y++) {

            if (board[y][x] != 13) {
                pieces[y][x].setTexture(textures[board[y][x]]);
                pieces[y][x].setPosition((x * SQUARE_SIZE) + SQUARE_SIZE/2, (y * SQUARE_SIZE) + SQUARE_SIZE/2);
            }

        }
    }



    // Create the main window
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Chess Game");



    // Main loop that continues until we close the window
    while (window.isOpen()) {




        // Event Handling

        sf::Event event;
        while (window.pollEvent(event)) {

            // Close window: exit
            if (event.type == sf::Event::Closed) {
                window.close();
            }


            // select square
            else if (event.type == sf::Event::MouseButtonPressed) {

                if (event.mouseButton.button == sf::Mouse::Left) {

                    int x = event.mouseButton.x;
                    int y = event.mouseButton.y;
                    

                    if (selectedSquare.x != -1 && selectedSquare.y != -1) {


                        bool isValidMove;
                        // Check if piece belongs to current turn's side
                        if (
                            (isWhiteTurn && (board[selectedSquare.y][selectedSquare.x] <= 5 || 
                            board[selectedSquare.y][selectedSquare.x] == 12)) ||
                            (!isWhiteTurn && board[selectedSquare.y][selectedSquare.x] >= 6 &&
                            board[selectedSquare.y][selectedSquare.x] <= 11)
                            ) {


                                // CHECK FOR VALID MOVE
                                switch(board[selectedSquare.y][selectedSquare.x]) {
                                    
                                    case 12: // White Pawn
                                        isValidMove = isValidPawnMove(selectedSquare.x,
                                                                      selectedSquare.y,
                                                                      (x/SQUARE_SIZE),
                                                                      (y/SQUARE_SIZE),
                                                                      board[selectedSquare.y][selectedSquare.x],
                                                                      false,
                                                                      board
                                                                      );
                                        std::cout << "Valid: " << isValidMove << std::endl;
                                        break;


                                    case 6: // Black Pawn
                                        isValidMove = true;
                                        break;



                                    default:
                                        isValidMove = true;
                                        break;


                                }


                                if (isValidMove) {

                                    int position = board[y/SQUARE_SIZE][x/SQUARE_SIZE];
                                    int temp = board[selectedSquare.y][selectedSquare.x];

                                    board[selectedSquare.y][selectedSquare.x] = 13;
                                    board[y/SQUARE_SIZE][x/SQUARE_SIZE] = temp;

                                    x = x/SQUARE_SIZE;
                                    y = y/SQUARE_SIZE;

                                    pieces[selectedSquare.y][selectedSquare.x].setPosition(x*SQUARE_SIZE + SQUARE_SIZE/2, y*SQUARE_SIZE + SQUARE_SIZE/2);

                                    selectedSquare = sf::Vector2i(-1, -1);


                                    // Toggle the turn
                                    isWhiteTurn = !isWhiteTurn;

                                } else {
                                     selectedSquare = sf::Vector2i(-1, -1);
                                }                             


                            } else {

                                    selectedSquare = sf::Vector2i(-1, -1);
                                    // Deselect if the same square is clicked again
                                }   

                    } else {


                        int x = event.mouseButton.x / SQUARE_SIZE;
                        int y = event.mouseButton.y / SQUARE_SIZE;
                        // Toggle selection

                        if (selectedSquare.x == x && selectedSquare.y == y) {

                            selectedSquare = sf::Vector2i(-1, -1);
                            // Deselect if the same square is clicked again
                        } else {

                            selectedSquare = sf::Vector2i(x, y); // Select new square
                        }

                    }                   
                }
            }
        }
    
    

        // Clear the screen with a dark gray background
        window.clear(sf::Color(50, 50, 50));


        // Draw the chessboard

        for (int x = 0; x < BOARD_SIZE; x++) {


            for (int y = 0; y < BOARD_SIZE; y++) {

                sf::RectangleShape square(sf::Vector2f(SQUARE_SIZE, SQUARE_SIZE));
                square.setPosition(x * SQUARE_SIZE, y * SQUARE_SIZE);


                // Set the color based on board size
                if ((x + y) % 2 == 0) {
                    square.setFillColor(sf::Color(238, 238, 210)); // light color
                } else {
                    square.setFillColor(sf::Color(118, 150, 86)); // dark color
                }
                window.draw(square);


                // Draw selection highlight if this square is selected
                if (selectedSquare.x == x && selectedSquare.y == y) {

                    square.setFillColor(sf::Color::Transparent); // No Fill
                    square.setOutlineThickness(5); // Thick outline
                    square.setOutlineColor(sf::Color::White); // White outline

                    window.draw(square);

                }

            }
         }



         



         // Draw the pieces

         for (int x = 0; x < BOARD_SIZE; x++) {
            for (int y = 0; y < BOARD_SIZE; y++) {

                if (board[y][x] != 0) {
                    window.draw(pieces[y][x]);
                }
            }
         }
        

        // Update the window
        window.display();

    }

    return 0;
}