#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"

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

int binToDec(int binary){
    int decimal = 0; 
    int remainder; 
    int base = 1;
    
    while (binary > 0){
        remainder = binary % 10;
        decimal = decimal + remainder * base;

        binary = binary / 10;

        base = base * 2;
    }
    printf("Binary Number in Decimal form is: %d \n", decimal);

}

int decToBin(int dec_number){
    int bin_num = 0;
    int remainder;
    int base = 1;

    while (dec_number > 0){
        remainder = dec_number % 2;
        dec_number = dec_number / 2;

        bin_num = bin_num + remainder*base;
        base = base * 10;
    }

    printf("Decimal Number in Binary form is: %d \n", bin_num);
}

void binToVar(char *binString){
    char str[50];
    char string[50];
    strcpy(str, binString);
    int i;
    int strLength = strlen(str);

    for (i = 0; i < strLength; i++){
        printf("[%c]", str[i]);
    }
    
    memcpy(string, str, i);
    string[i] = '\0';
    printf("\n");
    printf("%s\n", string);
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
