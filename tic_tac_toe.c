#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>

// Global variables
char board[3][3];
const char PLAYER = 'X';
const char COMPUTER = 'O';

// Prototype declaration
void resetBoard();
void printBoard();
int checkFreeSpaces();
void playerMove();
void computerMove();
char checkWinner();
void printWinner(char);

// main() function
int main(void) {
    char winner;
    char response;

    do {
        winner = ' ';
        response = ' ';
        resetBoard();
    
        while (winner == ' ' && checkFreeSpaces() != 0) {
            printBoard();

            playerMove();
            winner = checkWinner();
            if (winner != ' ' || checkFreeSpaces() == 0) {
                break;
            }

            computerMove();
            winner = checkWinner();
            if (winner != ' ' || checkFreeSpaces() == 0) {
                break;
            }
        }
    
        printBoard();
        printWinner(winner);
        printf("Would you like to play again? (y/n): ");
        getchar();
        scanf("%c", &response);
        getchar();
    } while (response == 'y');

    printf("Thanks for playing!\n");

    return 0;
}

// Writes functions
void resetBoard() {
    int i, j;
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            board[i][j] = ' ';
        }
    }
}

void printBoard() {
    printf(" %c | %c | %c \n", board[0][0], board[0][1], board[0][2]);
    printf("---|---|---\n");
    printf(" %c | %c | %c \n", board[1][0], board[1][1], board[1][2]);
    printf("---|---|---\n");
    printf(" %c | %c | %c \n", board[2][0], board[2][1], board[2][2]);
}

int checkFreeSpaces() {
    int freeSpaces = 9;
    int i, j;
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            if (board[i][j] != ' ') {
                freeSpaces--;
            }
        }
    }
    return freeSpaces;
}

void playerMove() {
    int x, y;
    do {
        printf("Enter row and column #(1-3): ");
        scanf("%d %d", &x, &y);
        --x; --y;

        if (board[x][y] != ' ') {
            printf("Invalid move!\n");
        } else {
            board[x][y] = PLAYER;
            break;
        }
    } while (board[x][y] != ' ');
}

void computerMove() {
    // creates a seed based on current time
    srand(time(0));
    int x, y;
    if (checkFreeSpaces() > 0) {
        do {
            x = rand() % 3;
            y = rand() % 3;
        } while (board[x][y] != ' ');

        board[x][y] = COMPUTER;
    } else {
        printWinner(' ');
    }
}

char checkWinner() {
    int i, j;
    // check rows
    for (i = 0; i < 3; i++) {
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2]) {
            return board[i][0];
        }
    }
    // check column
    for (j = 0; j < 3; j++) {
        if (board[0][j] == board[1][j] && board[1][j] == board[2][j]) {
            return board[0][j];
        }
    }
    // check diagonals
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2]) {
        return board[0][0];
    }
    if (board[0][2] == board[1][1] && board[1][1] == board[2][0]) {
        return board[0][2];
    }
    // Have no winner
    return ' ';
}

void printWinner(char winner) {
    if (winner == PLAYER) printf("You win!\n");
    else if (winner == COMPUTER) printf("You lose!\n");
    else printf("It's a tie!\n");
}