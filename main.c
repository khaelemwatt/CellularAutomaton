#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 20

typedef struct grid{
    char grid[MAXSIZE][MAXSIZE];
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
            printf("Please enter a gride size under 20x20");
        }
    }

    for(int i=0; i<pGrid->rows; i++){
        for (int j=0; j<pGrid->cols; j++){
            pGrid->grid[i][j] = 'O';
        }
    }

    return pGrid;
}

int main() {

  return 0;
 }
