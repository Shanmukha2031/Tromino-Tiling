// Program: Tromino Tiling Problem Solver
// Author: Shanmukha Subrahmanyam Rallapalli
// Date: September 2024
// 
// Description: 
// This program solves the Tromino Tiling problem for a given power-of-two sized board,
// where one square is missing. It uses recursion to place L-shaped trominoes on the board.
// The program prompts the user to input the board size and the coordinates of the missing square.
//
// Compilation: gcc tromino.c -o tromino
// To run: ./tromino
//

#include <stdio.h>
#include <string.h>

#define MAX_BOARD_SIZE 200
#define MAX_STR_SIZE 3

char board[MAX_BOARD_SIZE][MAX_BOARD_SIZE][MAX_STR_SIZE];

// Functions for power check, tiling, and printing the board continue here...

int isPowerOfTwo(int x) {
    return (x & (x - 1)) == 0;
}

void tromino(int x_board, int y_board, int x_missing, int y_missing, int board_size) {
    if (board_size == 2) {
        // Fill the 2x2 board with the appropriate L-shaped tromino based on the missing square
        if (x_missing == x_board && y_missing == y_board) {
            // Missing square is in the lower-left corner
            strcpy(board[x_board][y_board + 1], "UR");
            strcpy(board[x_board + 1][y_board], "UR");
            strcpy(board[x_board + 1][y_board + 1], "UR");
        } else if (x_missing == x_board && y_missing == y_board + 1) {
            // Missing square is in the upper-left corner
            strcpy(board[x_board][y_board], "LR");
            strcpy(board[x_board + 1][y_board], "LR");
            strcpy(board[x_board + 1][y_board + 1], "LR");
        } else if (x_missing == x_board + 1 && y_missing == y_board) {
            // Missing square is in the lower-right corner
            strcpy(board[x_board][y_board], "UL");
            strcpy(board[x_board][y_board + 1], "UL");
            strcpy(board[x_board + 1][y_board + 1], "UL");
        } else if (x_missing == x_board + 1 && y_missing == y_board + 1) {
            // Missing square is in the upper-right corner
            strcpy(board[x_board][y_board], "LL");
            strcpy(board[x_board + 1][y_board], "LL");
            strcpy(board[x_board][y_board + 1], "LL");
        }
        return;
    }
    
    int halfSize = board_size / 2;
    int centerX = x_board + halfSize;
    int centerY = y_board + halfSize;

    if (x_missing < centerX && y_missing < centerY) {
        strcpy(board[centerX - 1][centerY], "UR");
        strcpy(board[centerX][centerY - 1], "UR");
        strcpy(board[centerX][centerY], "UR");
        tromino(x_board, y_board, x_missing, y_missing, halfSize);
        tromino(x_board, y_board + halfSize, centerX - 1, centerY, halfSize);
        tromino(x_board + halfSize, y_board, centerX, centerY - 1, halfSize);
        tromino(x_board + halfSize, y_board + halfSize, centerX, centerY, halfSize);
    } else if (x_missing < centerX && y_missing >= centerY) {
        strcpy(board[centerX - 1][centerY - 1], "LR");
        strcpy(board[centerX][centerY - 1], "LR");
        strcpy(board[centerX][centerY], "LR");
        tromino(x_board, y_board + halfSize, x_missing, y_missing, halfSize);
        tromino(x_board, y_board, centerX - 1, centerY - 1, halfSize);
        tromino(x_board + halfSize, y_board, centerX, centerY - 1, halfSize);
        tromino(x_board + halfSize, y_board + halfSize, centerX, centerY, halfSize);
    } else if (x_missing >= centerX && y_missing < centerY) {
        strcpy(board[centerX - 1][centerY - 1], "UL");
        strcpy(board[centerX - 1][centerY], "UL");
        strcpy(board[centerX][centerY], "UL");
        tromino(x_board + halfSize, y_board, x_missing, y_missing, halfSize);
        tromino(x_board, y_board, centerX - 1, centerY - 1, halfSize);
        tromino(x_board, y_board + halfSize, centerX - 1, centerY, halfSize);
        tromino(x_board + halfSize, y_board + halfSize, centerX, centerY, halfSize);
    } else if (x_missing >= centerX && y_missing >= centerY) {
        strcpy(board[centerX - 1][centerY - 1], "LL");
        strcpy(board[centerX][centerY - 1], "LL");
        strcpy(board[centerX - 1][centerY], "LL");
        tromino(x_board + halfSize, y_board + halfSize, x_missing, y_missing, halfSize);
        tromino(x_board, y_board, centerX - 1, centerY - 1, halfSize);
        tromino(x_board, y_board + halfSize, centerX - 1, centerY, halfSize);
        tromino(x_board + halfSize, y_board, centerX, centerY - 1, halfSize);
    }
}

void printBoard(int boardSize) {
    for (int i = boardSize - 1; i >= 0; i--) {
        for (int j = 0; j < boardSize; j++) {
            if (board[j][i][0] == '\0') {
                printf("   ");
            } else {
                printf("%s ", board[j][i]);
            }
        }
        printf("\n");
    }
}

int main() {
    int boardSize, x_missing, y_missing;
    do {
        printf("Please enter size of board (need to be 2^n and 0 to quit): ");
        scanf("%d", &boardSize);
        if (boardSize == 0) break;

        if (!isPowerOfTwo(boardSize) || boardSize == 1) {
            printf("The board size should be a power of 2\n");
            continue; // Prompt again for valid input
        }
        memset(board, 0, sizeof(board)); // Initialize the board
        printf("Please enter coordinates of missing square (separate by a space): ");
        scanf("%d %d", &x_missing, &y_missing);
        strcpy(board[x_missing][y_missing], "MS"); // Mark the missing square
        tromino(0, 0, x_missing, y_missing, boardSize);
        printBoard(boardSize);
    } while (boardSize != 0);

    return 0;
}
