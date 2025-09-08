#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void printBoard(int *board, int n)
{
	for (int i = 0; i < n - 1; i++) 
		printf("%i ", board[i]);
	printf("%i\n", board[n - 1]);
}

bool isSafe(int* board, int targetRow, int targetCol, int boardSize) {

    for ( int rowIndex = targetRow - 1, offset = 1 ; rowIndex >= 0 ; rowIndex --, offset ++) {

        if (board[rowIndex] == targetCol)
            return false;

        if (targetCol + offset <= boardSize && board[rowIndex] == targetCol + offset)
            return false;

        if (targetCol - offset >= 0 && board[rowIndex] == targetCol - offset)
            return false;
    }
    return true;
}

void solve(int* board, int boardSize, int row) {

    if (row == boardSize) {
        printBoard(board, boardSize);
        // printf("valid\n");
        return ;
    }

    for (int col = 0; col < boardSize; col ++) {

        board[row] = col;
        if (isSafe(board, row, col, boardSize))
            solve(board, boardSize, row + 1);
        else
            continue;
    }
}

int main(int ac, char **av) {

    if ( ac == 2 )
    {
        int a = atoi(av[1]);
        int *board = malloc(sizeof(int) * a);


        solve(board, a, 0);
        free(board);
    }

}