#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>
#include <time.h>
#include <string.h>

#define ROWS 6
#define COLUMNS 7

// Define a 6x7 game board and a variable to track the current player.
char board[ROWS][COLUMNS];
int currentPlayer = 1; // Player 1 or Player 2

// Initialize the game board with empty spaces.
void initializeBoard()
{
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLUMNS; j++)
        {
            board[i][j] = ' ';
        }
    }
}

// Print the current state of the game board.
void printBoard()
{
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLUMNS; j++)
        {
            printf("| %c ", board[i][j]);
        }
        printf("|\n");
    }
    printf("-----------------------------\n");
    for (int i = 1; i <= COLUMNS; i++)
    {
        printf("  %d ", i);
    }
    printf("\n");
}
int getValidColumnInput()
{
    int column;
    while (1)
    {
        printf("Player %d, enter a column (1-%d): ", currentPlayer, COLUMNS);

        if (scanf("%d", &column) != 1)
        {
            // Non-numeric input, clear the input buffer.
            while (getchar() != '\n')
                continue;

            printf("Invalid input. Please enter a number.\n");
            continue;
        }

        if (column < 1 || column > COLUMNS)
        {
            printf("Invalid move. Column must be between 1 and %d. Try again.\n", COLUMNS);
            continue;
        }

        // Valid input, break out of the loop.
        break;
    }

    return column;
}

// // Check if a move to a given column is valid (within bounds and column not full)
// int isValidMove(int column)
// {
//     return column >= 1 && column <= COLUMNS && board[0][column - 1] == ' ';
// }

// Make a move for the current player in the given column
void makeMove(int column)
{
    for (int i = ROWS - 1; i >= 0; i--)
    {
        if (board[i][column - 1] == ' ')
        {
            if (currentPlayer == 1)
            {
                board[i][column - 1] = 'X';
            }
            else
            {
                board[i][column - 1] = 'O';
            }
            return;
        }
    }
}

// Check for a win by checking for four consecutive discs in all directions.
int checkWin(int row, int col)
{
    char player = currentPlayer == 1 ? 'X' : 'O';

    // Check horizontally
    int count = 0;
    for (int j = col - 3; j <= col + 3; j++)
    {
        if (j >= 0 && j < COLUMNS && board[row][j] == player)
        {
            count++;
            if (count == 4)
                return 1;
        }
        else
        {
            count = 0;
        }
    }

    // Check vertically
    count = 0;
    for (int i = row - 3; i <= row + 3; i++)
    {
        if (i >= 0 && i < ROWS && board[i][col] == player)
        {
            count++;
            if (count == 4)
                return 1;
        }
        else
        {
            count = 0;
        }
    }

    // Check diagonally (top-left to bottom-right)
    count = 0;
    for (int i = row - 3, j = col - 3; i <= row + 3; i++, j++)
    {
        if (i >= 0 && i < ROWS && j >= 0 && j < COLUMNS && board[i][j] == player)
        {
            count++;
            if (count == 4)
                return 1;
        }
        else
        {
            count = 0;
        }
    }

    // Check diagonally (bottom-left to top-right)
    count = 0;
    for (int i = row + 3, j = col - 3; i >= row - 3; i--, j++)
    {
        if (i >= 0 && i < ROWS && j >= 0 && j < COLUMNS && board[i][j] == player)
        {
            count++;
            if (count == 4)
                return 1;
        }
        else
        {
            count = 0;
        }
    }

    return 0;
}

// Check if the game board is full, indicating a draw.
int isBoardFull()
{
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLUMNS; j++)
        {
            if (board[i][j] == ' ')
            {
                return 0;
            }
        }
    }
    return 1;
}
void play_puissance4()
{
    // Initialize the game board.
    initializeBoard();
    int column, row;

    printf("Welcome to the Power 4 game!\n");
    printf("Player 1: X, Player 2: O\n");

    // Main game loop.
    while (1)
    {
        printBoard();
        column = getValidColumnInput();

        // Make the move and update the game state.
        makeMove(column);
        row = 0;
        while (row < ROWS && board[row][column - 1] == ' ')
            row++;

        // Check for a win.
        if (checkWin(row, column - 1))
        {
            printBoard();
            printf("Player %d ( %c ) wins!\n", currentPlayer, (currentPlayer == 1) ? 'X' : 'O');
            break;
        }

        // Check for a draw.
        if (isBoardFull())
        {
            printBoard();
            printf("It's a draw!\n");
            break;
        }

        // Switch to the other player's turn.
        currentPlayer = (currentPlayer == 1) ? 2 : 1;
    }
}