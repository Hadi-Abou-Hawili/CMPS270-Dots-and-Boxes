#include <stdio.h>
#include <stdbool.h>

#define ROWS 4               // Number of boxes vertically
#define COLS 5               // Number of boxes horizontally
#define DOTS_ROWS (ROWS + 1) // 1 more row for dots than boxes
#define DOTS_COLS (COLS + 1) // 1 more column for dots than boxes

char grid[DOTS_ROWS * 2 - 1][DOTS_COLS * 2 - 1];
int scores[ROWS][COLS] = {0};

void InitializeGrid()
{
    for (int i = 0; i < DOTS_ROWS * 2 - 1; i++)
    {
        for (int j = 0; j < DOTS_COLS * 2 - 1; j++)
        {
            if (i % 2 == 0 && j % 2 == 0)
                grid[i][j] = '.';
            else
                grid[i][j] = ' ';
        }
    }
}

void DrawGrid()
{

    printf("\n  "); // Extra spaces for alignment

    for (int j = 0; j < DOTS_COLS; j++)
        printf("%d   ", j);

    printf("\n");

    for (int i = 0; i < DOTS_ROWS * 2 - 1; i++)
    {
        if (i % 2 == 0)
            printf("%d ", i / 2);
        else
            printf("  ");

        for (int j = 0; j < DOTS_COLS * 2 - 1; j++)
        {
            printf("%c ", grid[i][j]);
        }
        printf("\n");
    }
}

void Turn(int counter, int *x1, int *y1, int *x2, int *y2)
{

    char player;
if (counter % 2 == 0) {
    player = 'A';
} else {
    player = 'B';
}


    
        printf("Player %c's turn. Enter the row and column of the first dot (e.g., A0 -> 0 0) and second dot:\n", player);
        while(1){
                scanf("%d %d %d %d", x1, y1, x2, y2);

                if(*x1<0 || *x1 >= DOTS_ROWS || *y1 <0 || *y1 >= DOTS_COLS || *x2 < 0 || *x2 >=DOTS_ROWS || *y2 <0 || *y2 >= DOTS_COLS)

        }



}

bool CheckForBox(int x, int y, char player)
{
    int row = x * 2, col = y * 2;
    if (row > 0 && row < DOTS_ROWS * 2 - 2 && col > 0 && col < DOTS_COLS * 2 - 2)
    {
        if (grid[row - 1][col] != ' ' && grid[row + 1][col] != ' ' &&
            grid[row][col - 1] != ' ' && grid[row][col + 1] != ' ')
        {
            scores[x][y] = (player == 'A') ? 1 : 2;
            grid[row][col] = player;
            return true;
        }
    }
    return false;
}

bool IsGameOver()
{
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; j++)
        {
            if (scores[i][j] == 0)
                return false; // If any box is unclaimed, game is not over
        }
    }
    return true;
}

int PlaceLine(int x1, int y1, int x2, int y2, char grid[DOTS_ROWS * 2 - 1][DOTS_COLS * 2 - 1])
{
    int row1 = x1 * 2;
    int col1 = y1 * 2;
    int row2 = x2 * 2;
    int col2 = y2 * 2;

    if (row1 > row2)
    {
        int temp = row1;
        row1 = row2;
        row2 = temp;
    }
    if (col1 > col2)
    {
        int temp = col1;
        col1 = col2;
        col2 = temp;
    }

    if (row1 == row2 && col1 + 2 == col2)
    {
        if (grid[row1][(col1 + col2) / 2] == ' ')
        {
            grid[row1][(col1 + col2) / 2] = '_';
            return 1; // horizontal line since having different columns
        }
    }
    if (col1 == col2 && row1 + 2 == row2)
    {
        if (grid[(row1 + row2) / 2][col1] == ' ')
        {
            grid[(row1 + row2) / 2][col1] = '|';
            return 1; // wertical line same columns
        }
    }
    return 0;
}

void DeclareWinner()
{
    int scoreA = 0;
    int scoreB = 0;
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; j++)
        {
            if (scores[i][j] == 1)
                scoreA++;
            if (scores[i][j] == 2)
                scoreB++;
        }
    }
    printf("\nGame Over!\n");
    printf("Player A: %d boxes\n", scoreA);
    printf("Player B: %d boxes\n", scoreB);

    if (scoreA > scoreB)
    {
        printf("Player A Wins!\n");
    }
    else if (scoreB > scoreA)
    {
        printf("Player B Wins!\n");
    }
    else
    {
        printf("It's a Draw!\n");
    }
}

int main()
{
    InitializeGrid();
    int turn = 0, x1, y1, x2, y2;
    char currentplayer;

    while (!IsGameOver())
    {
        DrawGrid();
        currentplayer = (turn % 2 == 0) ? 'A' : 'B';
        Turn(turn, &x1, &y1, &x2, &y2);
        if (PlaceLine(x1, y1, x2, y2)) {
            bool boxCompleted = false;

            if (x1 == x2) { 
                int y = (y1 < y2) ? y1 : y2;

                if (x1 > 0) 
                    boxCompleted |= CheckForBox(x1 - 1, y, currentPlayer);
             
                if (x1 < ROWS) 
                    boxCompleted |= CheckForBox(x1, y, currentPlayer);
            } else { 
                int x = (x1 < x2) ? x1 : x2;
             
                if (y1 > 0) 
                    boxCompleted |= CheckForBox(x, y1 - 1, currentPlayer);
              
                if (y1 < COLS) 
                    boxCompleted |= CheckForBox(x, y1, currentPlayer);
            }

            if (!boxCompleted)
                turn++;
        } else {
            printf("Invalid move. Try again.\n");
        }
    }

    DrawGrid();
    DeclareWinner();
    return 0;
}