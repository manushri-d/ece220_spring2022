#include "sudoku.h"

//-------------------------------------------------------------------------------------------------
// Start here to work on your MP7
//-------------------------------------------------------------------------------------------------
/* The purpose of this program was to solve a sudoku puzzle using recursive backtracking.
  In order to do this, I implemented 3 helper methods to code another helper method used
  in the sudoku recursive method. One helper method checked if a val was in a given row
  (using a for loop and a if statement) and if it was, it returned 1. Another helper 
  method checked if a val was in a given row (using a for loop and a if statement) and 
  if it was, it returned 1. Another helper method checked if a val was in a 3 x 3 cell
  zone(using multiple for loops and if statements) and if it was, it returned 1. These
  3 helper methods were used for another helper method, called is_val_valid, where the
  3 methods were called to see if the val is present. This last helper method was used 
  in the recursive solve_sudoku method. In that method, I first checked for an unassigned
  value in the cell, and if there was one, I set variables i and j to the row and col at
  those values respectively and also set the "filled" variable to 0 since the cell is not
  filled. If filled was equal to 1 at the end of iterating through the cells, the program 
  ended. If not, I went into another for loop with all the possible solutions for the 
  puzzle(aka 1-9). Using the helper method is_val_valid, I checked if the cell at that
  particular place can be filled with the number. I then set the value at that cell to
  the number and then recalled solve sudoku to go into recursion. */
  
// You are free to declare any private functions if needed.

// Function: is_val_in_row
// Return true if "val" already existed in ith row of array sudoku.
int is_val_in_row(const int val, const int i, const int sudoku[9][9]) {

  assert(i>=0 && i<9);

  // BEG TODO
  for(int rCheck = 0; rCheck < 9; rCheck++){ //iterate through all col
    if(sudoku[i][rCheck] == val){ //if val exists in ith row
      return 1;
    }
  }
  return 0;
  // END TODO
}

// Function: is_val_in_col
// Return true if "val" already existed in jth column of array sudoku.
int is_val_in_col(const int val, const int j, const int sudoku[9][9]) {

  assert(j>=0 && j<9);

  // BEG TODO
  for(int cCheck = 0; cCheck < 9; cCheck++){ //iterate through all row
    if(sudoku[cCheck][j] == val){ //if val exists in jth col
      return 1;
    }
  }
  return 0;
  // END TODO
}

// Function: is_val_in_3x3_zone
// Return true if val already existed in the 3x3 zone corresponding to (i, j)
int is_val_in_3x3_zone(const int val, const int i, const int j, const int sudoku[9][9]) {
   
  assert(i>=0 && i<9);
  
  // BEG TODO
  if(i<3){ // it would be in the first couple of cells, but have to find which col
    if(j<3){ //first cell
      for(int r = 0; r < 3; r++){ //this row and col combination depends on cell number
        for(int c = 0; c < 3; c++){
          if(sudoku[r][c] == val){ //if val is in the 3x3 zone, return 1
            return 1;
          }
        }
      }
    } else if(j>=3 && j<6){ //second cell
        for(int r = 0; r < 3; r++){ //this row and col combination depends on cell number
          for(int c = 3; c < 6; c++){
            if(sudoku[r][c] == val){ //if val is in the 3x3 zone, return 1
              return 1;
            }
          }
        }
    } else if(j>=6 && j<9){ //third cell
        for(int r = 0; r < 3; r++){ //this row and col combination depends on cell number
          for(int c = 6; c < 9; c++){
            if(sudoku[r][c] == val){ //if val is in the 3x3 zone, return 1
              return 1;
            }
          }
        }
    }
  } else if (i>=3 && i<6){
    if(j<3){ //fourth cell
      for(int r = 3; r < 6; r++){ //this row and col combination depends on cell number
        for(int c = 0; c < 3; c++){
          if(sudoku[r][c] == val){ //if val is in the 3x3 zone, return 1
            return 1;
          }
        }
      }
    } else if(j>=3 && j<6){ //fifth cell
        for(int r = 3; r < 6; r++){ //this row and col combination depends on cell number
          for(int c = 3; c < 6; c++){
            if(sudoku[r][c] == val){ //if val is in the 3x3 zone, return 1
              return 1;
            }
          }
        }
    } else if(j>=6 && j<9){ //sixth cell
        for(int r = 3; r < 6; r++){ //this row and col combination depends on cell number
          for(int c = 6; c < 9; c++){
            if(sudoku[r][c] == val){ //if val is in the 3x3 zone, return 1
              return 1;
            }
          }
        }
    }
  } else {
    if(j<3){ //seventh cell
      for(int r = 6; r < 9; r++){ //this row and col combination depends on cell number
        for(int c = 0; c < 3; c++){
          if(sudoku[r][c] == val){ //if val is in the 3x3 zone, return 1
            return 1;
          }
        }
      }
    } else if(j>=3 && j<6){ //eighth cell
        for(int r = 6; r < 9; r++){ //this row and col combination depends on cell number
          for(int c = 3; c < 6; c++){
            if(sudoku[r][c] == val){ //if val is in the 3x3 zone, return 1
              return 1;
            }
          }
        }
    } else if(j>=6 && j<9){ //ninth cell
        for(int r = 6; r < 9; r++){ //this row and col combination depends on cell number
          for(int c = 6; c < 9; c++){
            if(sudoku[r][c] == val){ //if val is in the 3x3 zone, return 1
              return 1;
            }
          }
        }
    }
  }
  return 0;
  // END TODO
}

// Function: is_val_valid
// Return true if the val is can be filled in the given entry.
int is_val_valid(const int val, const int i, const int j, const int sudoku[9][9]) {

  assert(i>=0 && i<9 && j>=0 && j<9);

  // BEG TODO
  if(is_val_in_row(val,i,sudoku) == 1 || is_val_in_col(val,j,sudoku) == 1 || is_val_in_3x3_zone(val,i,j,sudoku) == 1){
    return 0; //checks if val is found at a given i and j based on all 3 methods 
  }
  return 1;
  // END TODO
}

// Procedure: solve_sudoku
// Solve the given sudoku instance.
int solve_sudoku(int sudoku[9][9]) {

  // BEG TODO.
  int i, j; //var to store row and col
  int filled = 1; //temp var that will check if a value is assigneed
  
  for(int x = 0; x < 9; x++){
    for(int y = 0; y < 9; y++){
      if(sudoku[x][y]==0){ //if a cell is unassigned by numbers
        i = x; //set the unassigned row
        j = y; //set the unassigned col
        filled = 0; //this means that the sudoku is not full
        break;
      }
    }
  }
  
  if(filled == 1){ //if the sudoku is filled, return 1
    return 1;
  }
  
  for (int num = 1; num <= 9; num++) { 
    if (is_val_valid(num,i,j,sudoku)==1) { //cell (i, j) can be filled with num
      sudoku[i][j] = num; 
      if (solve_sudoku(sudoku)) { //base case
        return 1;
      }
      sudoku[i][j] = 0; //recursive backtracking
    }
  }
  
  return 0;
  // END TODO.
}

// Procedure: print_sudoku
void print_sudoku(int sudoku[9][9])
{
  int i, j;
  for(i=0; i<9; i++) {
    for(j=0; j<9; j++) {
      printf("%2d", sudoku[i][j]);
    }
    printf("\n");
  }
}

// Procedure: parse_sudoku
void parse_sudoku(const char fpath[], int sudoku[9][9]) {
  FILE *reader = fopen(fpath, "r");
  assert(reader != NULL);
  int i, j;
  for(i=0; i<9; i++) {
    for(j=0; j<9; j++) {
      fscanf(reader, "%d", &sudoku[i][j]);
    }
  }
  fclose(reader);
}




