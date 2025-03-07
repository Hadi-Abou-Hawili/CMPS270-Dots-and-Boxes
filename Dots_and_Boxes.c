#include <stdio.h>
#include <stdbool.h>
 
#define ROWS 4  // Number of boxes vertically
#define COLS 5  // Number of boxes horizontally
#define DOTS_ROWS (ROWS + 1)  // 1 more row for dots than boxes
#define DOTS_COLS (COLS + 1)  // 1 more column for dots than boxes

void DrawGrid(char grid [6][6]){
    printf("*******************************************************\n  0 1 2 3 4 5\n");
    // for(int i = 0; i <= 5; i++){
    //     for(int j = 0; j <= 5; j++){
    //         grid[i][j] = ''
    //     }
    // }
    
    // for(int i = 0; i <= 5; i++){
    //     printf("%d . . . . . .\n", i);
    // }
}

void Turn(int counter){

    char letter;

    if(counter % 2 == 0){
        letter = 'A';
    }
    else{
        letter = 'B';
    }
    printf("Player %c's turn. Enter the row and column of the first dot (e.g., A0 -> 0 0) and second dot:\n", letter);
}

bool IsGameOver(int scores[ROWS][COLS]) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            if (scores[i][j] == 0) return false;  // If any box is unclaimed, game is not over
        }
    }
    return true;
}

int PlaceLine(char grid [ROWS][COLS] , int x1 , int x2 , int y1 , int y2 , char currentPlayer  ){
int row1 = x1 * 2;
int col1 = y1 * 2;
int row2 = x2 * 2;
int col2 = y2 * 2;
if (row 1 == row2 && clo1 + 2 == col2 ) {
    if (board[row1][(col1 + col2) / 2] == ' ') {
    grid[row1][(col1 + col2) / 2 ] = '-'  ;     // horizontal line since having different columns 
}
}
if ( col1 == col2 && row1 + 2 == row2 ){
    if (board[(row1 + row2) / 2][col1] == ' ') {
    grid[(row1 + row2 ) / 2 ][col1] = '|';      // wertical line same columns 
}
}
}
}

void DeclareWinner(int scores[ROWS][COLS]) {
    int scoreA = 0;
    int scoreB = 0;
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            if (scores[i][j] == 1) scoreA++;
            if (scores[i][j] == 2) scoreB++;
        }
    }
    printf("\nGame Over!\n");
    printf("Player A: %d boxes\n", scoreA);
    printf("Player B: %d boxes\n", scoreB);
    
    if (scoreA > scoreB) {
        printf("Player A Wins!\n");
    } else if (scoreB > scoreA) {
        printf("Player B Wins!\n");
    } else {
        printf("It's a Draw!\n");
    }
}


int main(){
     char grid[6][6];
    /*
    Test 2
    */
   int counter = 0;
   Turn(counter);

    // while for multiple turns until grids are all done
    // still need to increment counter 

     DrawGrid(grid);

    //Turn();
}