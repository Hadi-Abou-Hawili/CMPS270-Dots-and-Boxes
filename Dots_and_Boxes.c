#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>

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
    if (counter % 2 == 0)
    {
        player = 'A';
    }
    else
    {
        player = 'B';
    }

    printf("Player %c's turn. Enter the row and column of the first dot (e.g., A0 -> 0 0) and second dot:\n", player);
    while (1)
    {
        scanf("%d %d %d %d", x1, y1, x2, y2);

        if (*x1 < 0 || *x1 >= DOTS_ROWS || *y1 < 0 || *y1 >= DOTS_COLS || *x2 < 0 || *x2 >= DOTS_ROWS || *y2 < 0 || *y2 >= DOTS_COLS)
        {
            printf("Invalid coordinates. Try again.\n");
            continue;
        }

        if ((*x1 == *x2 && abs(*y1 - *y2) == 1) || (*y1 == *y2 && abs(*x1 - *x2) == 1))
            break;

        printf("Dots must be adjacent. Try again\n");
    }
}

bool CheckForBox(int x, int y, char player)
{
    int row = x * 2 + 1, col = y * 2 + 1;
    if (row > 0 && row < DOTS_ROWS * 2 - 2 && col > 0 && col < DOTS_COLS * 2 - 2)
    {
        if (grid[row - 1][col] != ' ' && grid[row + 1][col] != ' ' &&
            grid[row][col - 1] != ' ' && grid[row][col+1] != ' ')
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

bool PlaceLine(int x1, int y1, int x2, int y2)
{
    // Ensure the line is either horizontal or vertical and adjacent
    if (x1 == x2)
    { // Horizontal line
        int y_coordinate = (y1 < y2) ? y1 : y2;
        int c = y_coordinate * 2 + 1;
        int r = x1 * 2;
        if (grid[r][c] == ' ')
        {
            grid[r][c] = '_';
            return true;
        }
    }
    else if (y1 == y2)
    { // Vertical line
        int x_coordinate = (x1 < x2) ? x1 : x2;
        int r = x_coordinate * 2 + 1;
        int c = y1 * 2;
        if (grid[r][c] == ' ')
        {
            grid[r][c] = '|';
            return true;
        }
    }
    return false;
}

void Displayscores(){
    int scoreA = 0 ;
    int scoreB = 0 ;
    for(int i = 0 ; i < ROWS ; i++){
        for(int j = 0 ; j < COLS ; j++){
            if (scores[i][j]== 1 )
            scoreA++; 
            else if (scores[i][j] == 2 )
            scoreB++;
        }
    }
    printf("\nCurrent Score:\n");
    printf("Player A: %d boxes\n", scoreA);
    printf("Player B: %d boxes\n", scoreB);


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

char ChooseGameMode(char *botPlayer) {
    char choice;
    printf("Choose game mode:\n");
    printf("Enter 'B' to play against Bot or 'H' for Human vs Human:\n");
    scanf(" %c", &choice);
    choice = toupper(choice);
    
    if ( choice == 'B') {
        printf("Choose bot difficulty: \n");
        printf("E for Easy Mode \n");
        printf("M for Medium Mode \n");
        scanf(" %c", &choice);
        choice = toupper(choice);

        *botPlayer = (rand() % 2 == 0) ? 'A' : 'B';
        printf("Bot will be Player %c\n", *botPlayer);
    }
    
    return choice;
}

void RandBot(int *x1, int *y1, int *x2, int *y2)
{
    int PossibleMoves[DOTS_ROWS * DOTS_COLS * 2][4]; //Maximum possible moves
    int moveCount = 0;

    //We will scan the grid for possible moves horizontally and vertically
    for (int i = 0; i < DOTS_ROWS; i++)
    {
        for (int j = 0; j < DOTS_COLS; j++)
        {
            //Horizontal
            if (j < DOTS_COLS - 1 && grid[i * 2][j * 2 + 1] == ' ')
            {
                PossibleMoves[moveCount][0] = i;
                PossibleMoves[moveCount][1] = j;
                PossibleMoves[moveCount][2] = i;
                PossibleMoves[moveCount][3] = j + 1;
                moveCount++;
            }
            //Vertical
            if (i < DOTS_ROWS - 1 && grid[i * 2 + 1][j * 2] == ' ')
            {
                PossibleMoves[moveCount][0] = i;
                PossibleMoves[moveCount][1] = j;
                PossibleMoves[moveCount][2] = i + 1;
                PossibleMoves[moveCount][3] = j;
                moveCount++;
            }
        }
    }

    if (moveCount > 0)
    {
        int randomIndex = rand() % moveCount;
        *x1 = PossibleMoves[randomIndex][0];
        *y1 = PossibleMoves[randomIndex][1];
        *x2 = PossibleMoves[randomIndex][2];
        *y2 = PossibleMoves[randomIndex][3];
    }
}

void MediumBot(int *x1, int *y1, int *x2, int *y2, char botPlayer)
{
    
    for (int i = 0; i < DOTS_ROWS; i++) {
        for (int j = 0; j < DOTS_COLS; j++) {
           
            if (j < DOTS_COLS - 1 && grid[i * 2][j * 2 + 1] == ' ') {
                int boxesCompleted = 0;
                
                if (i > 0) {
                    int top = (i - 1) * 2 + 1;
                    int left = j * 2 + 1;
                    if (grid[top][left - 1] != ' ' && grid[top][left + 1] != ' ' && grid[top - 1][left] != ' ') {
                        boxesCompleted++;
                    }
                }

                if (i < ROWS) {
                    int bottom = (i) * 2 + 1;
                    int left = j * 2 + 1;
                    if (grid[bottom][left - 1] != ' ' && grid[bottom][left + 1] != ' ' && grid[bottom + 1][left] != ' ') {
                        boxesCompleted++;
                    }
                }
                
                if (boxesCompleted > 0) {
                    *x1 = i;
                    *y1 = j;
                    *x2 = i;
                    *y2 = j + 1;
                    return;
                }
            }

            if (i < DOTS_ROWS - 1 && grid[i * 2 + 1][j * 2] == ' ') {
                int boxesCompleted = 0;     
               
                if (j > 0) {
                    int center = (i) * 2 + 1;
                    int left = (j - 1) * 2 + 1;
                    if (grid[center - 1][left] != ' ' && grid[center + 1][left] != ' ' && grid[center][left - 1] != ' ') {
                        boxesCompleted++;
                    }
                }
                if (j < COLS) {
                    int center = (i) * 2 + 1;
                    int right = (j) * 2 + 1;
                    if (grid[center - 1][right] != ' ' && grid[center + 1][right] != ' ' && grid[center][right + 1] != ' ') {
                        boxesCompleted++;
                    }
                }
                
                if (boxesCompleted > 0) {
                    *x1 = i;
                    *y1 = j;
                    *x2 = i + 1;
                    *y2 = j;
                    return;
                }
            }
        }
    }

    RandBot(x1, y1, x2, y2);
}

int main()
{
    InitializeGrid();
    int turn = 0, x1, y1, x2, y2;
    char currentplayer;
    char botPlayer = ' ';
    char gameMode = ' ';

    gameMode = ChooseGameMode(&botPlayer);
    bool playAgainstBot = (gameMode == 'E' || gameMode == 'M');
    bool boxCompleted = false;

    while (!IsGameOver())
    {
        DrawGrid();
        Displayscores();
        currentplayer = (turn % 2 == 0) ? 'A' : 'B';


        if (playAgainstBot && currentplayer == botPlayer) {
            if (gameMode == 'E') {
                RandBot(&x1, &y1, &x2, &y2); // Easy bot
            } else {
                MediumBot(&x1, &y1, &x2, &y2, botPlayer); // Medium bot
            }
            printf("Bot (%c) played: (%d, %d) -> (%d, %d)\n", currentplayer, x1, y1, x2, y2);
        } 
        else {
            Turn(turn, &x1, &y1, &x2, &y2); // Human's move
        }




        if (PlaceLine(x1, y1, x2, y2))
        {
            boxCompleted = false;

            if (x1 == x2)
            {
                int y = (y1 < y2) ? y1 : y2;

                if (x1 > 0)
                    boxCompleted |= CheckForBox(x1 - 1, y, currentplayer);

                if (x1 < ROWS)
                    boxCompleted |= CheckForBox(x1, y, currentplayer);
            }
            else
            {
                int x = (x1 < x2) ? x1 : x2;

                if (y1 > 0)
                    boxCompleted |= CheckForBox(x, y1 - 1, currentplayer);

                if (y1 < COLS)
                    boxCompleted |= CheckForBox(x, y1, currentplayer);
            }

            if (!boxCompleted)
                turn++;
        }
        else
        {
            printf("Invalid move. Try again.\n");
        }
    }

    DrawGrid();
    DeclareWinner();
    return 0;
}


//Github page: https://github.com/Hadi-Abou-Hawili/CMPS270-Dots-and-Boxes