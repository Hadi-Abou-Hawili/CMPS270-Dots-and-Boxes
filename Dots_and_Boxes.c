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
void Turn(){
    int counter = 0;
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