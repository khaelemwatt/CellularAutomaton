#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"

Grid* createGrid(int op){
    Grid* pGrid = NULL;    
    pGrid = (Grid*)malloc(sizeof(Grid));
    if (pGrid==NULL){
        printf("Memory allocation error");
        return NULL;
    }

    int valid = 0;

    //Checks to see if the integer provided is 1. If it is, this means it is a rule 30 grid
    //which means we only need one row
    if(op==1){
        while(valid == 0){
            printf("Number of Columns: ");
            scanf("%d", &(pGrid->cols));
            pGrid->rows=1;

            if(pGrid->rows<=MAXSIZE && pGrid->cols<=MAXSIZE){
                valid = 1;
            }else{
                printf("ERROR: Maximum column size is 20\n");
            }
        }
    }else{
        while(valid == 0){
            printf("Grid Size (ROW COL): ");
            scanf("%d %d", &(pGrid->rows), &(pGrid->cols));

            if(pGrid->rows<=MAXSIZE && pGrid->cols<=MAXSIZE){
                valid = 1;
            }else{
                printf("ERROR: Maximum grid size is 20x20\n");
            }
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

//saves the cellular automaton output to a text file
int saveGrid(Grid* pGrid, int counter){

    if(pGrid == NULL)
        return 1;

    char c1 = '\n';
    FILE *fp;

    if( counter ==0){
        fp = fopen("CA.txt", "w");
    }else{
        fp = fopen("CA.txt", "a");
    }
    

    if( fp != NULL){
        for (int i = 0; i < pGrid->rows; i++) {
            for (int j = 0; j < pGrid->cols; j++) {
                char c2 = pGrid->curGrid[i][j];
                fputc(c2, fp);
            }
        fputc(c1, fp);
        }
        fclose(fp);
    }else{
        printf("Error opening file\n");
        return 1;
    }
    return 0;
}

//counts the nu,ber of lines in a file
int countRows(char filename[]){
  
    int rows =0;
    char ch;
    char last;

    FILE *fp;
    fp = fopen(filename, "r");

    if (fp != NULL){

        //Add initial line
        rows++;
        
        while ((ch = fgetc(fp)) != EOF)
        {
            /* Check new line */
            if (ch == '\n' || ch == '\0')
                rows++;
            last = ch;
        }

        if(last=='\n')
            rows--;

        fclose(fp);
    }
    return rows;

}

//count the number of chars in a file
int countChars(char filename[]){
    int chars =0;
    char ch;

    FILE *fp;
    fp = fopen(filename, "r");

    if (fp != NULL){
        while ((ch = fgetc(fp)) != EOF)
        {
           if (ch != '\n' ){
                chars++;
           }
        }
        fclose(fp);  
    }
    return chars;

}

//Creates a grid from lines in a text file
Grid *loadGrid(int op){

    //get filename
    char filename[50];
    printf("Filename: ");
    scanf("%50s", filename);

    FILE *fp;
    fp = fopen(filename, "r");

    if(!fp)
        return NULL;
    
    fclose(fp);
    //create & allocate memory for grid
    Grid* pGrid = NULL;    
    pGrid = (Grid*)malloc(sizeof(Grid));
    if (pGrid==NULL){
        printf("Memory allocation error");
        return NULL;
    }

    //count the rows and columns from the text file given
    int rows = countRows(filename);
    int numChars = countChars(filename);
    int columns;

    if(rows%numChars!=0){
        columns = numChars/rows;
    }else{
        printf("Invalid file format. Please have equal column size for each row\n");
        return NULL;
    }

    if(columns >20){
        printf("Invalid file format. Max column size is 20\n");
    }

    if(op==1 && rows>1){
        printf("Invalid file format. Must be 1 row only\n");
        return NULL;
    }
    
    if(op!=1 && rows<3){
        printf("Invalid file format. Must be 3 or more rows\n");
        return NULL;
    }

    printf("Rows: %d\nCols: %d\n", rows, columns);

    fp = fopen(filename, "r");

    if (fp != NULL){
        
        
        char line[MAXSIZE];
        pGrid->rows = rows;
        pGrid->cols = columns;
        int i =0;

            while (fgets(line, 60, fp) != NULL){

                for (int j=0; j<pGrid->cols; j++){
                
                    pGrid->curGrid[i][j] = line[j];
                    pGrid->prevGrid[i][j] = line[j];
                }
            i++;
            }
        
        fclose(fp);
        
    }else{
        printf("File %s not found!\n", filename );
    }
    
    return pGrid;
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

int populate(Grid* pGrid, char neighbours[8], int row, int col, char ruleset[2][9]){
    int count=0;
    for(int i=0; i<8; i++){
        if(neighbours[i]=='1') 
            count++;
    }
        
    if(pGrid->prevGrid[row][col]=='1'){
        if(count==0){
            pGrid->curGrid[row][col]=ruleset[1][0];
        }else if(count==1){
            pGrid->curGrid[row][col]=ruleset[1][1];
        }else if(count==2){
            pGrid->curGrid[row][col]=ruleset[1][2];
        }else if(count==3){
            pGrid->curGrid[row][col]=ruleset[1][3];
        }else if(count==4){
            pGrid->curGrid[row][col]=ruleset[1][4];
        }else if(count==5){
            pGrid->curGrid[row][col]=ruleset[1][5];
        }else if(count==6){
            pGrid->curGrid[row][col]=ruleset[1][6];
        }else if(count==7){
            pGrid->curGrid[row][col]=ruleset[1][7];
        }else if(count==8){
            pGrid->curGrid[row][col]=ruleset[1][8];
        }
    }else{
        if(count==0){
            pGrid->curGrid[row][col]=ruleset[0][0];
        }else if(count==1){
            pGrid->curGrid[row][col]=ruleset[0][1];
        }else if(count==2){
            pGrid->curGrid[row][col]=ruleset[0][2];
        }else if(count==3){
            pGrid->curGrid[row][col]=ruleset[0][3];
        }else if(count==4){
            pGrid->curGrid[row][col]=ruleset[0][4];
        }else if(count==5){
            pGrid->curGrid[row][col]=ruleset[0][5];
        }else if(count==6){
            pGrid->curGrid[row][col]=ruleset[0][6];
        }else if(count==7){
            pGrid->curGrid[row][col]=ruleset[0][7];
        }else if(count==8){
            pGrid->curGrid[row][col]=ruleset[0][8];
        }
    }
    return 0;
}

int nextGen2d(Grid* pGrid, char ruleset[2][9]){
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
                    populate(pGrid, neighbours, i, j, ruleset);
                    
                }else if(j==pGrid->cols-1){ // if in the last column (no elts to the RIGHT)

                    char neighbours[8] = {pGrid->prevGrid[endRow][j-1], pGrid->prevGrid[endRow][j], pGrid->prevGrid[endRow][0], pGrid->prevGrid[i][j-1], pGrid->prevGrid[i][0], pGrid->prevGrid[i+1][j-1], pGrid->prevGrid[i+1][j], pGrid->prevGrid[i+1][0]};
                    populate(pGrid, neighbours, i, j, ruleset);

                }else{ // middle columns

                    char neighbours[8] = {pGrid->prevGrid[endRow][j-1], pGrid->prevGrid[endRow][j], pGrid->prevGrid[endRow][j+1], pGrid->prevGrid[i][j-1], pGrid->prevGrid[i][j+1], pGrid->prevGrid[i+1][j-1], pGrid->prevGrid[i+1][j], pGrid->prevGrid[i+1][j+1]};
                    populate(pGrid, neighbours, i, j, ruleset);

                }
                
            }else if(i==pGrid->rows-1){ // if in the last row 

                if(j<1){    // if in the first column (no elts to the LEFT)

                    char neighbours[8] = {pGrid->prevGrid[i-1][endCol], pGrid->prevGrid[i-1][j], pGrid->prevGrid[i-1][j+1], pGrid->prevGrid[i][endCol], pGrid->prevGrid[i][j+1], pGrid->prevGrid[0][endCol], pGrid->prevGrid[0][j], pGrid->prevGrid[0][j+1]};
                    populate(pGrid, neighbours, i, j, ruleset);

                }else if(j==pGrid->cols-1){ // if in the last column (no elts to the RIGHT)

                    char neighbours[8] = {pGrid->prevGrid[i-1][j-1], pGrid->prevGrid[i-1][j], pGrid->prevGrid[i-1][0], pGrid->prevGrid[i][j-1], pGrid->prevGrid[i][0], pGrid->prevGrid[0][j-1], pGrid->prevGrid[0][j], pGrid->prevGrid[0][0]};
                    populate(pGrid, neighbours, i, j, ruleset);

                }else{ // middle columns

                    char neighbours[8] = {pGrid->prevGrid[i-1][j-1], pGrid->prevGrid[i-1][j], pGrid->prevGrid[i-1][j+1], pGrid->prevGrid[i][j-1], pGrid->prevGrid[i][j+1], pGrid->prevGrid[0][j-1], pGrid->prevGrid[0][j], pGrid->prevGrid[0][j+1]};
                    populate(pGrid, neighbours, i, j, ruleset);
                }

            }else{ // middle rows

                if(j<1){    // if in the first column (no elts to the LEFT)

                    char neighbours[8] = {pGrid->prevGrid[i-1][endCol], pGrid->prevGrid[i-1][j], pGrid->prevGrid[i-1][j+1], pGrid->prevGrid[i][endCol], pGrid->prevGrid[i][j+1], pGrid->prevGrid[i+1][endCol], pGrid->prevGrid[i+1][j], pGrid->prevGrid[i+1][j+1]};
                    populate(pGrid, neighbours, i, j, ruleset);
                    
                }else if(j==pGrid->cols-1){ // if in the last column (no elts to the RIGHT)

                    char neighbours[8] = {pGrid->prevGrid[i-1][j-1], pGrid->prevGrid[i-1][j], pGrid->prevGrid[i-1][0], pGrid->prevGrid[i][j-1], pGrid->prevGrid[i][0], pGrid->prevGrid[i+1][j-1], pGrid->prevGrid[i+1][j], pGrid->prevGrid[i+1][0]};
                    populate(pGrid, neighbours, i, j, ruleset);

                }else{ // middle columns

                    char neighbours[8] = {pGrid->prevGrid[i-1][j-1], pGrid->prevGrid[i-1][j], pGrid->prevGrid[i-1][j+1], pGrid->prevGrid[i][j-1], pGrid->prevGrid[i][j+1], pGrid->prevGrid[i+1][j-1], pGrid->prevGrid[i+1][j], pGrid->prevGrid[i+1][j+1]};
                    populate(pGrid, neighbours, i, j, ruleset);

                }

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
    return 0;
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
    return 0;
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

int getValidInteger(char textToDisplay[], int max)
{
    int input;
    int valid = 0;
    
    printf("%s", textToDisplay);
    valid = (scanf("%d", &input)==1 && input>0 && input<max+1) ? 1 : 0;

    while(valid != 1)
    {
        while((getchar()) != '\n');
        printf("Invalid Input\n%s", textToDisplay);
        valid = (scanf("%d", &input)==1 && input>0&& input<max+1) ? 1 : 0;
    }

    return input;

}

void makeRules(char ruleset[2][9]){
    char input;
    int valid;

    for(int j=0; j<2; j++){
        for(int i=0; i<9; i++){

            valid=0;
            while((getchar()) != '\n');
            printf("If there is %d alive neighbours around a %d cell: ", i, j);
            input = getchar();
            if(input=='1' || input == '0')
                valid = 1;

            while(valid !=1){
                while((getchar()) != '\n');
                printf("\nIf there is %d alive neighbours around a %d cell: ", i, j);
                input = getchar();
                if(input=='1' || input == '0')
                    valid = 1;
            }

            ruleset[j][i] = input;
        }
    }
}

int main()
{
    
    int loadChoice=0;
    printf("\n---CHOOSE INPUT METHOD---\n");
    printf("1. Load grid from file\n");
    printf("2. Enter grid manually\n\n");
    loadChoice = getValidInteger("Choice: ", 2);


    int choice=0, end=0;
    while(end==0){
        printf("\n------- MAIN MENU -------\n");
        printf("1. Rule 30\n");
        printf("2. Conway's Game of Life\n");
        printf("3. Custom Rules\n");
        printf("4. Exit\n");

        choice = getValidInteger("Choice: ", 3);

        switch(choice){
            case 1: {
                Grid* pGrid = NULL;

                if (loadChoice==1){
                    while(pGrid==NULL)
                        pGrid = loadGrid(1);
                    displayGrid(pGrid);
                }else if (loadChoice==2){
                    while(pGrid==NULL)
                        pGrid = createGrid(1);
                }
               
                int counter=0;
                int iterations;
                printf("Generations: ");
                scanf("%d", &iterations);

                displayGrid(pGrid);
                saveGrid(pGrid, counter);
                for(int i=0; i<iterations; i++){
                    counter++;
                    nextGen(pGrid);
                    displayGrid(pGrid);
                    saveGrid(pGrid, counter);
                }  

                free(pGrid);
                end = 1;
                break;
            }
            case 2: {
                Grid* pGrid = NULL;
                
                if (loadChoice==1){
                    while(pGrid==NULL)
                        pGrid = loadGrid(0);
                    displayGrid(pGrid);
                }else if (loadChoice==2){
                    while(pGrid==NULL)
                        pGrid = createGrid(0);
                }

                int counter =0;
                int iterations;
                printf("Generations: ");
                scanf("%d", &iterations);

                printf("----------GENERATION 0----------\n");
                displayGrid(pGrid);
                saveGrid(pGrid, counter);

                char ruleset[2][9] = {{'0','0','0','1','0','0','0','0','0'}, {'0','0','1','1','0','0','0','0','0'}};

                for(int i=0; i<iterations; i++){
                    counter ++;
                    nextGen2d(pGrid, ruleset);
                    printf("----------GENERATION %d----------\n", i+1);
                    displayGrid(pGrid);
                    saveGrid(pGrid, counter);
                }  

                free(pGrid);
                end = 1;
                break;
            }
            case 3: {
                Grid* pGrid = NULL;
                
                if (loadChoice==1){
                    while(pGrid==NULL)
                        pGrid = loadGrid(0);
                    displayGrid(pGrid);
                }else if (loadChoice==2){
                    while(pGrid==NULL)
                        pGrid = createGrid(0);
                }                

                char ruleset[2][9];
                makeRules(ruleset);

                int counter =0;
                int iterations;
                printf("Generations: ");
                scanf("%d", &iterations);

                printf("----------GENERATION 0----------\n");
                displayGrid(pGrid);
                saveGrid(pGrid, counter);

                for(int i=0; i<iterations; i++){
                    counter ++;
                    nextGen2d(pGrid, ruleset);
                    printf("----------GENERATION %d----------\n", i+1);
                    displayGrid(pGrid);
                    saveGrid(pGrid, counter);
                }  

                free(pGrid);
                end = 1;
                break;
            }
            case 4:{
                end=1;
                break;
            }
        }
    }

    return 0;
}

