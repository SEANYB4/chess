#include "pawnValidate.h"
#include <cmath>
#include <iostream>



bool isValidPawnMove(int startX,
                    int startY,
                    int endX,
                    int endY,
                    int piece,
                    bool hasMoved,
                    const int board[8][8]) {


                        std::cout << "Start X:" << startX << std::endl;
                        std::cout << "Start Y:" << startY << std::endl;
                        std::cout << "end X:" << endX << std::endl;
                        std::cout << "end Y:" << endY << std::endl;

                        int direction = (piece < 6 || piece == 12) ? 1 : -1;
                        if (startX == endX) {
                            // Move straight
                            if (abs(endY - startY) == direction) {
                                return board[endY][endX] == 13; // Ensure target square empty
                            } else if (endY - startY == 2 * direction && !hasMoved ) { // maybe extra condition
                                // Check both squares are empty for initial two-square move
                                return board[startY + direction][startX] == 13 && board[endY][endX] == 13;
                            }
                        } else if (abs(startX - endX) == 1 && endY - startY == direction) {
                            // Capture diagonally
                            return board[endY][endX] != 13 && board[endY][endX] / 6 != piece / 6; // Ensure capturing opponent piece
                        }
                        return false;
                    }