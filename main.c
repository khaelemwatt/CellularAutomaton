#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"

Grid* createGrid(){
    Grid* pGrid = NULL;    
    pGrid = (Grid*)malloc(sizeof(Grid));
    if (pGrid==NULL)
        return NULL;


    int valid = 0;
    while(valid == 0){
        printf("Grid Size (ROW COL): ");
        scanf("%d %d", &(pGrid->rows), &(pGrid->cols));

        if(pGrid->rows<=MAXSIZE && pGrid->cols<=MAXSIZE){
            valid = 1;
        }else{
            printf("ERROR: Maximum gird size is 20x20\n");
        }
    }

    // USER-GENERATED GRID
    
   char userRow[pGrid->cols];   
   
       for(int i=0; i<pGrid->rows; i++){                

            int valid = 0;

            while(valid==0){

                valid = 1;

                printf("Enter Row %d : " , i+1);
                scanf("%s", userRow);  

                if((int)strlen(userRow)!=pGrid->cols){
                    printf("Row must contain %d elements\n", pGrid->cols);
                    valid = 0;
                }

                for ( int j=0; j<pGrid->cols; j++){
                    if (userRow[j] == '1' || userRow[j] == '0'){
                        continue;
                    }else{
                        printf("Row must be a string of 1s and 0s\n");
                        valid = 0;
                        break;
                    }
                }

            }

            for (int j=0; j<pGrid->cols; j++){
                
                    pGrid->curGrid[i][j] = userRow[j];
                    pGrid->prevGrid[i][j] = userRow[j];
            }

        }

    return pGrid;
}

int displayGrid(Grid* pGrid){

    if(pGrid == NULL)
        return 1;

    for (int i = 0; i < pGrid->rows; i++) {
        for (int j = 0; j < pGrid->cols; j++) {
            printf("%c ", pGrid->curGrid[i][j]);
        }
        printf("\n");
    }
    return 0;
}

int nextGen(Grid* pGrid){
    for (int i = 0; i < pGrid->rows; i++) {
        for (int j = 0; j < pGrid->cols; j++) {
            pGrid->prevGrid[i][j] = pGrid->curGrid[i][j];
        }
    }

    //top is the elt in the SAME position in prevGrid
    //topLeft the elt to the LEFT the same position in prevGrid
    //topRight the elt to the RIGHT the same position in prevGrid
    char topLeft, top, topRight;

    for (int i = 0; i < pGrid->rows; i++) {
        for (int j = 0; j < pGrid->cols; j++) {
            if(j<1){    // if in the first column (no elts to the LEFT)

                topLeft=pGrid->prevGrid[i][pGrid->cols-1];
                top=pGrid->prevGrid[i][j];
                topRight=pGrid->prevGrid[i][j+1];

            }else if(j==pGrid->cols-1){ // if in the last column (no elts to the RIGHT)

                topLeft=pGrid->prevGrid[i][j-1];
                top=pGrid->prevGrid[i][j];
                topRight=pGrid->prevGrid[i][0];

            }else{ // middle columns

                topLeft=pGrid->prevGrid[i][j-1];
                top=pGrid->prevGrid[i][j];
                topRight=pGrid->prevGrid[i][j+1];

            }

            // RULE 30 

            if(topLeft=='1' && top=='1' && topRight=='1'){
                pGrid->curGrid[i][j]='0';
            }else if(topLeft=='1' && top=='1' && topRight=='0'){
                pGrid->curGrid[i][j]='0';
            }else if(topLeft=='1' && top=='0' && topRight=='1'){
                pGrid->curGrid[i][j]='0';
            }else if(topLeft=='1' && top=='0' && topRight=='0'){
                pGrid->curGrid[i][j]='1';
            }else if(topLeft=='0' && top=='1' && topRight=='1'){
                pGrid->curGrid[i][j]='1';
            }else if(topLeft=='0' && top=='1' && topRight=='0'){
                pGrid->curGrid[i][j]='1';
            }else if(topLeft=='0' && top=='0' && topRight=='1'){
                pGrid->curGrid[i][j]='1';
            }else if(topLeft=='0' && top=='0' && topRight=='0'){
                pGrid->curGrid[i][j]='0';
            }

        }
    }

    return 0;
}

int populate(Grid* pGrid, char neighbours[8], int row, int col){
    int count=0;
    for(int i=0; i<8; i++){
        if(neighbours[i]=='1') 
            count++;
    }
        
    if(pGrid->prevGrid[row][col]=='1'){
        if(count<2){
            pGrid->curGrid[row][col]='0';
        }else if(count<4){
            pGrid->curGrid[row][col]='1';
        }else{
            pGrid->curGrid[row][col]='0';
        }
    }else{
        if(count==3){
            pGrid->curGrid[row][col]='1';
        }
    }
    return 0;
}

int nextGenGameOfLife(Grid* pGrid){
    for (int i = 0; i < pGrid->rows; i++) {
        for (int j = 0; j < pGrid->cols; j++) {
            pGrid->prevGrid[i][j] = pGrid->curGrid[i][j];
        }
    }

    int endRow = pGrid->rows-1;
    int endCol = pGrid->cols-1;

    for (int i = 0; i < pGrid->rows; i++) {
        for (int j = 0; j < pGrid->cols; j++) {

            if(i<1){    // if in the first row 

                if(j<1){    // if in the first column (no elts to the LEFT)

                    char neighbours[8] = {pGrid->prevGrid[endRow][endCol], pGrid->prevGrid[endRow][j], pGrid->prevGrid[endRow][j+1], pGrid->prevGrid[i][endCol], pGrid->prevGrid[i][j+1], pGrid->prevGrid[i+1][endCol], pGrid->prevGrid[i+1][j], pGrid->prevGrid[i+1][j+1]};                    
                    populate(pGrid, neighbours, i, j);
                    
                }else if(j==pGrid->cols-1){ // if in the last column (no elts to the RIGHT)

                    char neighbours[8] = {pGrid->prevGrid[endRow][j-1], pGrid->prevGrid[endRow][j], pGrid->prevGrid[endRow][0], pGrid->prevGrid[i][j-1], pGrid->prevGrid[i][0], pGrid->prevGrid[i+1][j-1], pGrid->prevGrid[i+1][j], pGrid->prevGrid[i+1][0]};
                    populate(pGrid, neighbours, i, j);

                }else{ // middle columns

                    char neighbours[8] = {pGrid->prevGrid[endRow][j-1], pGrid->prevGrid[endRow][j], pGrid->prevGrid[endRow][j+1], pGrid->prevGrid[i][j-1], pGrid->prevGrid[i][j+1], pGrid->prevGrid[i+1][j-1], pGrid->prevGrid[i+1][j], pGrid->prevGrid[i+1][j+1]};
                    populate(pGrid, neighbours, i, j);

                }
                
            }else if(i==pGrid->rows-1){ // if in the last row 

                if(j<1){    // if in the first column (no elts to the LEFT)

                    char neighbours[8] = {pGrid->prevGrid[i-1][endCol], pGrid->prevGrid[i-1][j], pGrid->prevGrid[i-1][j+1], pGrid->prevGrid[i][endCol], pGrid->prevGrid[i][j+1], pGrid->prevGrid[0][endCol], pGrid->prevGrid[0][j], pGrid->prevGrid[0][j+1]};
                    populate(pGrid, neighbours, i, j);

                }else if(j==pGrid->cols-1){ // if in the last column (no elts to the RIGHT)

                    char neighbours[8] = {pGrid->prevGrid[i-1][j-1], pGrid->prevGrid[i-1][j], pGrid->prevGrid[i-1][0], pGrid->prevGrid[i][j-1], pGrid->prevGrid[i][0], pGrid->prevGrid[0][j-1], pGrid->prevGrid[0][j], pGrid->prevGrid[0][0]};
                    populate(pGrid, neighbours, i, j);

                }else{ // middle columns

                    char neighbours[8] = {pGrid->prevGrid[i-1][j-1], pGrid->prevGrid[i-1][j], pGrid->prevGrid[i-1][j+1], pGrid->prevGrid[i][j-1], pGrid->prevGrid[i][j+1], pGrid->prevGrid[0][j-1], pGrid->prevGrid[0][j], pGrid->prevGrid[0][j+1]};
                    populate(pGrid, neighbours, i, j);
                }

            }else{ // middle rows

                if(j<1){    // if in the first column (no elts to the LEFT)

                    char neighbours[8] = {pGrid->prevGrid[i-1][endCol], pGrid->prevGrid[i-1][j], pGrid->prevGrid[i-1][j+1], pGrid->prevGrid[i][endCol], pGrid->prevGrid[i][j+1], pGrid->prevGrid[i+1][endCol], pGrid->prevGrid[i+1][j], pGrid->prevGrid[i+1][j+1]};
                    populate(pGrid, neighbours, i, j);
                    
                }else if(j==pGrid->cols-1){ // if in the last column (no elts to the RIGHT)

                    char neighbours[8] = {pGrid->prevGrid[i-1][j-1], pGrid->prevGrid[i-1][j], pGrid->prevGrid[i-1][0], pGrid->prevGrid[i][j-1], pGrid->prevGrid[i][0], pGrid->prevGrid[i+1][j-1], pGrid->prevGrid[i+1][j], pGrid->prevGrid[i+1][0]};
                    populate(pGrid, neighbours, i, j);

                }else{ // middle columns

                    char neighbours[8] = {pGrid->prevGrid[i-1][j-1], pGrid->prevGrid[i-1][j], pGrid->prevGrid[i-1][j+1], pGrid->prevGrid[i][j-1], pGrid->prevGrid[i][j+1], pGrid->prevGrid[i+1][j-1], pGrid->prevGrid[i+1][j], pGrid->prevGrid[i+1][j+1]};
                    populate(pGrid, neighbours, i, j);

                }

            }

        }
    }

    return 0;
}

int getValidInteger(char textToDisplay[])
{
    int input;
    int valid = 0;
    
    printf("%s", textToDisplay);
    valid = (scanf("%d", &input)==1 && input>0 && input<4) ? 1 : 0;

    while(valid != 1)
    {
        while((getchar()) != '\n');
        printf("Invalid Input\n%s", textToDisplay);
        valid = (scanf("%d", &input)==1 && input>0&& input<4) ? 1 : 0;
    }

    return input;

}

int main()
{
    int choice=0, end=0;

    while(end==0){
        printf("1. Rule 30\n");
        printf("2. Conway's Game of Life\n");
        printf("3. Exit\n");

        choice = getValidInteger("Choice: ");

        switch(choice){
            case 1: {
                Grid* pGrid = NULL;
                pGrid = createGrid();

                int iterations;
                printf("Generations: ");
                scanf("%d", &iterations);

                displayGrid(pGrid);

                for(int i=0; i<iterations; i++){
                    nextGen(pGrid);
                    displayGrid(pGrid);
                }  

                free(pGrid);
                end = 1;
                break;
            }
            case 2: {
                Grid* pGrid = NULL;
                pGrid = createGrid();

                int iterations;
                printf("Generations: ");
                scanf("%d", &iterations);

                printf("----------GENERATION 0----------\n");
                displayGrid(pGrid);

                for(int i=0; i<iterations; i++){
                    nextGenGameOfLife(pGrid);
                    printf("----------GENERATION %d----------\n", i+1);
                    displayGrid(pGrid);
                }  

                free(pGrid);
                end = 1;
                break;
            }
            case 3: {
                end = 1;
                break;
            }
        }
    }

    return 0;
}
