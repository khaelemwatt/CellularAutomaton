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
            printf("Please enter a gride size under 20x20\n");
        }
    }

    // USER-GENERATED GRID
    
   char userRow[pGrid->cols];   
   
       for(int i=0; i<pGrid->rows; i++){

                printf("Enter Row %d : " , i+1 );
                scanf("%s", userRow);  

                for ( int j=0; j<pGrid->cols; j++){
                    if (userRow[j] == '1' || userRow[j] == '0'){
                        continue;
                    }else{
                        printf("Row must be a string of 1s and 0s\n");
                        printf("Enter Row %d : " , i+1 );
                        scanf("%s", userRow); 
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

int main()
{
    

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

    return 0;
}
