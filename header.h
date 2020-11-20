/**
 * FILE: HEADER.H
 */

#ifndef __CELL_AUTOMATA_HEADER__ // this is a 'guard' on the header file, to prevent it's contents from
#define __CELL_AUTOMATA_HEADER__ // being redefined more than once during the build process

// ### DATA STRUCTURES ### 
#define MAXSIZE 20

/* typedef for a a grid */
typedef struct grid{
    char curGrid[MAXSIZE][MAXSIZE]; // Current grid
    char prevGrid[MAXSIZE][MAXSIZE]; // Previous grid
    int rows; // Rows in the grid
    int cols; // Columns in the grid
}Grid;

/* Create a new, empty grid, returning a pointer to the newly 
   allocated grid OR a value of NULL in the event of error */
Grid* createGrid();

// Displays the current state of the grid to the user int displayGrid(Grid* pGrid);
int displayGrid(Grid* pGrid);

// Handles cell population for the game of life
int populate(Grid* pGrid, char neighbours[8], int row, int col);

// Creates the next grid for the cellular automaton
int nextGen(Grid* pGrid);

//Creates the next grid for the game of life
int nextGenGameOfLife(Grid* pGrid);

// Used to validate the users input choice for the menu system
int getValidInteger(char textToDisplay[]);

#endif
