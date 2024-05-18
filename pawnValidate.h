#ifndef PAWN_VALIDATE_H
#define PAWN_VALIDATE_H

#include <vector>


// Function declaration

bool isValidPawnMove(int startX, 
                    int startY, 
                    int endX, 
                    int endY, 
                    int piece, 
                    bool hasMoved,
                    const int board[8][8]
);


#endif