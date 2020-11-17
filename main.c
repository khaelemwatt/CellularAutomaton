#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXSIZE 20


typedef struct grid{
    char curGrid[MAXSIZE][MAXSIZE];
    char prevGrid[MAXSIZE][MAXSIZE];
    int rows;
    int cols;
}Grid;

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

    for(int i=0; i<pGrid->rows; i++){
        for (int j=0; j<pGrid->cols; j++){
            pGrid->curGrid[i][j] = '0';
            pGrid->prevGrid[i][j] = '0';
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

    char topLeft, top, topRight;

    for (int i = 0; i < pGrid->rows; i++) {
        for (int j = 0; j < pGrid->cols; j++) {
            if(j<1){

                topLeft='0';
                top=pGrid->prevGrid[i][j];
                topRight=pGrid->prevGrid[i][j+1];

            }else if(j==pGrid->cols-1){

                topLeft=pGrid->prevGrid[i][j-1];
                top=pGrid->prevGrid[i][j];
                topRight='0';

            }else{

                topLeft=pGrid->prevGrid[i][j-1];
                top=pGrid->prevGrid[i][j];
                topRight=pGrid->prevGrid[i][j+1];

            }

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

    pGrid->curGrid[0][5]='1';

    displayGrid(pGrid);

    for(int i=0; i<5; i++){
        nextGen(pGrid);
        displayGrid(pGrid);
    }  

    free(pGrid);

    return 0;
}
