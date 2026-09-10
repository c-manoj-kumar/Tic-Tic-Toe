/*
    Mini Game Project - Tic Tac Toe
    ---------------------------------
    A console-based C++ Tic Tac Toe game demonstrating loops,
    arrays, and conditional logic.

    Features:
      - 2-player mode (Player X vs Player O) on the same console
      - 3x3 board stored in a 2D array
      - Board redraws dynamically after every move
      - Win / draw detection across rows, columns, and diagonals
      - Replay option after each game
      - Input validation (rejects out-of-range or already-taken cells)
*/

#include <iostream>
#include <limits>

using namespace std;

const int SIZE = 3;

// ---------------- Utility ----------------
void clearInputBuffer() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

// ---------------- Initialize board with numbers 1-9 ----------------
void initBoard(char board[SIZE][SIZE]) {
    int num = 1;
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            board[i][j] = '0' + num++;   // '1' through '9'
}

// ---------------- Display the board ----------------
void displayBoard(char board[SIZE][SIZE]) {
    cout << "\n";
    for (int i = 0; i < SIZE; i++) {
        cout << " ";
        for (int j = 0; j < SIZE; j++) {
            cout << board[i][j];
            if (j < SIZE - 1) cout << " | ";
        }
        cout << "\n";
        if (i < SIZE - 1) cout << "---+---+---\n";
    }
    cout << "\n";
}

// ---------------- Check for a win ----------------
bool checkWin(char board[SIZE][SIZE], char player) {
    // Rows and columns
    for (int i = 0; i < SIZE; i++) {
        if (board[i][0] == player && board[i][1] == player && board[i][2] == player)
            return true;
        if (board[0][i] == player && board[1][i] == player && board[2][i] == player)
            return true;
    }
    // Diagonals
    if (board[0][0] == player && board[1][1] == player && board[2][2] == player)
        return true;
    if (board[0][2] == player && board[1][1] == player && board[2][0] == player)
        return true;

    return false;
}

// ---------------- Check for a draw ----------------
bool checkDraw(char board[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            if (board[i][j] != 'X' && board[i][j] != 'O')
                return false;   // an empty (numbered) cell remains
    return true;
}

// ---------------- Get a valid move from the current player ----------------
void getMove(char board[SIZE][SIZE], char player) {
    int choice;
    int row, col;

    while (true) {
        cout << "Player " << player << ", enter a cell number (1-9): ";
        while (!(cin >> choice)) {
            cout << "Invalid input. Enter a number between 1 and 9: ";
            clearInputBuffer();
        }
        clearInputBuffer();

        if (choice < 1 || choice > 9) {
            cout << "Please choose a number between 1 and 9.\n";
            continue;
        }

        row = (choice - 1) / SIZE;
        col = (choice - 1) % SIZE;

        if (board[row][col] == 'X' || board[row][col] == 'O') {
            cout << "That cell is already taken. Try again.\n";
            continue;
        }

        board[row][col] = player;
        break;
    }
}

// ---------------- Play one full game ----------------
void playGame() {
    char board[SIZE][SIZE];
    initBoard(board);

    char currentPlayer = 'X';
    bool gameOver = false;

    cout << "\n===== TIC TAC TOE =====\n";
    cout << "Cells are numbered 1-9, left to right, top to bottom.\n";
    displayBoard(board);

    while (!gameOver) {
        getMove(board, currentPlayer);
        displayBoard(board);

        if (checkWin(board, currentPlayer)) {
            cout << "*** Player " << currentPlayer << " wins! Congratulations! ***\n";
            gameOver = true;
        } else if (checkDraw(board)) {
            cout << "*** It's a draw! ***\n";
            gameOver = true;
        } else {
            currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
        }
    }
}

// ---------------- Main ----------------
int main() {
    char playAgain;

    do {
        playGame();

        cout << "\nPlay again? (y/n): ";
        cin >> playAgain;
        clearInputBuffer();

    } while (playAgain == 'y' || playAgain == 'Y');

    cout << "\nThanks for playing! Goodbye.\n";
    return 0;
}
