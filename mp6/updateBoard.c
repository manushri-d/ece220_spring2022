/*In this program, given a 2D array converted into a 1D array that have the states alive
  and dead, the program computes different states based on th methods. In countLiveNeighbor
  I counted how many alive neigbors there were using 2 for loops and if statements, and if
  the row and col index passed the if statements, that meant that there is an alive neighbor
  at that index. In updateBoard, I set another array equal to the changed values in board
  depending on the amount of alive neighbors(so I called the countLiveNeighbor method), and 
  then deep copied the elements of that array into the board array. In the aliveStable method
  it was a similar process. I had a temp array that I deep copied the elements from the board
  array into. I then called the updateBoard method to test if the next step is different 
  from the board array. I tested this using a for loop that checked every element of the arrays,
  and if they were not the same, the method returned 0 immediately.
 */
/*
 * countLiveNeighbor
 * Inputs:
 * board: 1-D array of the current game board. 1 represents a live cell.
 * 0 represents a dead cell
 * boardRowSize: the number of rows on the game board.
 * boardColSize: the number of cols on the game board.
 * row: the row of the cell that needs to count alive neighbors.
 * col: the col of the cell that needs to count alive neighbors.
 * Output:
 * return the number of alive neighbors. There are at most eight neighbors.
 * Pay attention for the edge and corner cells, they have less neighbors.
 */

int countLiveNeighbor(int* board, int boardRowSize, int boardColSize, int row, int col){
  int aliveNumCount = 0;
  for(int i = row-1; i <= row+1; i++){
    if((i < boardRowSize) && (i >= 0)){ //row is within bounds
      for(int j = col-1; j <= col+1; j++){
	if((j < boardColSize) && (j >= 0)){ //col is within bounds
	  if((i != row) || (j != col)){ //cell is not at (row,col)
	    if(board[(i*boardColSize)+j] == 1){ //cell is alive
	      aliveNumCount++; //increment aliveNumCount
	    }
	  }
	}
      }
    }
  }
  return aliveNumCount;
}
  
/*
 * Update the game board to the next step.
 * Input: 
 * board: 1-D array of the current game board. 1 represents a live cell.
 * 0 represents a dead cell
 * boardRowSize: the number of rows on the game board.
 * boardColSize: the number of cols on the game board.
 * Output: board is updated with new values for next step.
 */


void updateBoard(int* board, int boardRowSize, int boardColSize){
  int neighborCount;
  int initBoard[boardRowSize*boardColSize]; //temp board
  for(int i = 0; i < boardRowSize; i++){ //setting two nested for loops equal to row and col
    for(int j = 0; j < boardColSize; j++){
      neighborCount = countLiveNeighbor(board, boardRowSize, boardColSize, i, j); //call countLiveNeighbor method
      if(neighborCount == 2 && board[(i*boardColSize)+j] == 1){ //if the amount of alive neighbors is 2, and the board is also alive at that point
	initBoard[(i*boardColSize)+j] = 1; //set the temp board at that index to 1
      } else if (neighborCount == 3){ //if there are 3 alive neighbors
	initBoard[(i*boardColSize)+j] = 1; //set the temp board at that index to 1
      } else {
	initBoard[(i*boardColSize)+j] = 0; //else, set the the temp board to 0, so it dies
      }
    }
  }
  for(int i=0; i<boardRowSize*boardColSize; i++){ //array that iterates to deep copy
    board[i] = initBoard[i]; //copies all elements of the temp array into the board array
  }
}

/*
 * aliveStable
 * Checks if the alive cells stay the same for next step
 * board: 1-D array of the current game board. 1 represents a live cell.
 * 0 represents a dead cell
 * boardRowSize: the number of rows on the game board.
 * boardColSize: the number of cols on the game board.
 * Output: return 1 if the alive cells for next step is exactly the same with 
 * current step or there is no alive cells at all.
 * return 0 if the alive cells change for the next step.
 */ 
int aliveStable(int* board, int boardRowSize, int boardColSize){
  int rv = 1;
  int temp[boardRowSize*boardColSize]; //set a temp array to the same size as the board array
  for(int i = 0; i < boardRowSize*boardColSize; i++){ //iterate to deep copy
    temp[i] = board[i]; //set all the elements of board to the temp array
  }
  updateBoard(temp, boardRowSize, boardColSize); //call the updateBoard method to test if the next step is different
  for(int i = 0; i < boardRowSize*boardColSize; i++){ //iterate
    if(temp[i] != board[i]){ //if the temp array(next step) is not the same as the prior step, return 0
      rv = 0;
      break;
    }
  }
  return rv; //at this point in the code, the elements in temp array and board array are the same, so return 1
}

				
				
			

