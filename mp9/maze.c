#include <stdio.h>
#include <stdlib.h>
#include "maze.h"

/* In the createMaze method, I allocated memory to first the maze, the cells array, and then each cell.
I then set the startRow, startCol, endRow, endCol to i and j respectively based on where i and j was
located. In the destroyMaze method, I freed memory to first each cell, then the cells array, and then
the maze itself. In the printMaze method, I printed every character of each cell using two for loops.
In the solveMaze method, I used recursion to check in DFS if the move was valid. If it was not valid,
I used recursion backtracking by setting the cell to visited. Depening on if the move was valid or not
I return true(1) or false(0)
*/

/*
 * createMaze -- Creates and fills a maze structure from the given file
 * INPUTS:       fileName - character array containing the name of the maze file
 * OUTPUTS:      None 
 * RETURN:       A filled maze structure that represents the contents of the input file
 * SIDE EFFECTS: None
 */
maze_t * createMaze(char * fileName)
{
    // Your code here. Make sure to replace following line with your own code.
    FILE * file = fopen(fileName, "r"); 
    maze_t * maze = (maze_t *)malloc(sizeof(maze_t)); //allocate memory for maze
    fscanf(file, "%d", &maze->width);
    fscanf(file, "%d \n", &maze->height);

    maze->cells = (char **)malloc(maze->height * sizeof(char *)); //allocate memory for cells array
 
    int ind;
    for (ind = 0; ind < maze->height; ind++) {
        maze->cells[ind] = (char *)malloc(maze->width * sizeof(char)); //allocate memory for each cell
    }

    int i, j;
    char temp;
    for (i = 0; i < maze->height; i++){ //row
        for (j = 0; j < maze->width; j++) { //col
            fscanf(file, "%c", &maze->cells[i][j]);
            if (maze->cells[i][j] == 'S') { //if cell is at the start
                maze->startRow = i; //set start row to i(row)
                maze->startColumn = j; //set start col to j(col)
            }
            if (maze->cells[i][j] == 'E') {
                maze->endRow = i;
                maze->endColumn = j;
            }
        }
        fscanf(file, "%c", &temp); //newline char has to be discarded
    }
    fclose(file); //after iterating, close the file
    return maze;  
}

/*
 * destroyMaze -- Frees all memory associated with the maze structure, including the structure itself
 * INPUTS:        maze -- pointer to maze structure that contains all necessary information 
 * OUTPUTS:       None
 * RETURN:        None
 * SIDE EFFECTS:  All memory that has been allocated for the maze is freed
 */
void destroyMaze(maze_t * maze)
{
    // Your code here.
    int i;
    for(i = 0; i < maze->height; i++){
        free(maze->cells[i]); //free each cell
    }
    free(maze->cells); //free the cells array
    free(maze); //free the maze 
}

/*
 * printMaze --  Prints out the maze in a human readable format (should look like examples)
 * INPUTS:       maze -- pointer to maze structure that contains all necessary information 
 *               width -- width of the maze
 *               height -- height of the maze
 * OUTPUTS:      None
 * RETURN:       None
 * SIDE EFFECTS: Prints the maze to the console
 */
void printMaze(maze_t * maze)
{
    // Your code here.
    int i, j;
    for(i = 0; i < maze->height; i++){
        for(j = 0; j < maze->width; j++){
            printf("%c",maze->cells[i][j]); //print every character of maze
        }
        printf("\n"); //print new line after row
    }
}

/*
 * solveMazeManhattanDFS -- recursively solves the maze using depth first search,
 * INPUTS:               maze -- pointer to maze structure with all necessary maze information
 *                       col -- the column of the cell currently beinging visited within the maze
 *                       row -- the row of the cell currently being visited within the maze
 * OUTPUTS:              None
 * RETURNS:              0 if the maze is unsolvable, 1 if it is solved
 * SIDE EFFECTS:         Marks maze cells as visited or part of the solution path
 */ 
int solveMazeDFS(maze_t * maze, int col, int row)
{
    // Your code here. Make sure to replace following line with your own code.
    if(col < 0 || col >= maze->width || row < 0 || row >= maze->height){ //If (col, row) outside bounds of the maze return false
        return 0;
    }
  
    if(maze->cells[row][col] == 'E'){ //if (col, row) is the end of the maze return true
        return 1;	
    }	

    if(maze->cells[row][col] != 'S'){ //check if cell is at the start
        if(maze->cells[row][col] != ' '){ //if (col, row) is not an empty cell return false
            return 0;
        }
        maze->cells[row][col] = '*'; //set (col, row) as part of the solution path in the maze
    }
    
    if(solveMazeDFS(maze, col, row-1) == 1){ //if (solveMaze(up of (col, row) ) == true) return true
        return 1;
    }

    if(solveMazeDFS(maze, col+1, row) == 1){ //if (solveMaze(right of (col, row) ) == true) return true
        return 1;
    }

    if(solveMazeDFS(maze, col, row+1) == 1){ //if (solveMaze(down of (col, row) ) == true) return true
        return 1;
    }

    if(solveMazeDFS(maze, col-1, row) == 1){ //if (solveMaze(left of (col, row) ) == true) return true
        return 1;
    }

    if(maze->cells[row][col] != 'S'){ 
        maze->cells[row][col] = '~'; //unmark (col, row) as part of solution and mark as visited
    }

    return 0; //return false
}
