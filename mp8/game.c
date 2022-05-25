#include "game.h"

/* In this game, I implemented the make game function, which initialized variables
in the game data structure. I initialized using the -> which is essentially '*.' 
Remake game used the same method, I just had an extra pointer before the ->, 
meaning '**.' The move w,a,s,d methods were all pretty similar. I had two for loops
for the row and column, and then I had another for loop to loop until the row/col
is empty. Once it is, then I moved the value in the cell to a certain location,
depending on W,A,S,D. I then checked if the next row/col is empty, and if it was not
then I checked if the current cell and next cell are the same. If it is, then I changed
the score. I also merged the cells together, and then set the current cell to empty.
The way I implemented the move W,A,S,D did not revert the game if the game was invalid.
To balance this out, in legal_move_check, I created a copy game and then tested to see
if the moving methods would be valid on the copy game, and if not I returned 0.
*/

game * make_game(int rows, int cols)
/*! Create an instance of a game structure with the given number of rows
    and columns, initializing elements to -1 and return a pointer
    to it. (See game.h for the specification for the game data structure) 
    The needed memory should be dynamically allocated with the malloc family
    of functions.
*/
{
    //Dynamically allocate memory for game and cells (DO NOT modify this)
    game * mygame = malloc(sizeof(game));
    mygame->cells = malloc(rows*cols*sizeof(cell));

    //YOUR CODE STARTS HERE:  Initialize all other variables in game struct
    mygame->rows = rows; //init
    mygame->cols = cols;
    mygame->score = 0;
    for(int i=0; i<(rows*cols); i++){ //rows*cols = end 
        mygame->cells[i] = -1; //empty cell
    }

    return mygame;
}

void remake_game(game ** _cur_game_ptr,int new_rows,int new_cols)
/*! Given a game structure that is passed by reference, change the
	game structure to have the given number of rows and columns. Initialize
	the score and all elements in the cells to -1. Make sure that any 
	memory previously allocated is not lost in this function.	
*/
{
	/*Frees dynamically allocated memory used by cells in previous game,
	 then dynamically allocates memory for cells in new game.  DO NOT MODIFY.*/
	free((*_cur_game_ptr)->cells);
	(*_cur_game_ptr)->cells = malloc(new_rows*new_cols*sizeof(cell));

	 //YOUR CODE STARTS HERE:  Re-initialize all other variables in game struct
    (*_cur_game_ptr)->rows = new_rows; //init
    (*_cur_game_ptr)->cols = new_cols;
    (*_cur_game_ptr)->score = 0;
    for(int i=0; i<(new_rows*new_cols); i++){ //rows * cols is the size
        (*_cur_game_ptr)->cells[i] = -1; //empty cell
    }

	return;	
}

void destroy_game(game * cur_game)
/*! Deallocate any memory acquired with malloc associated with the given game instance.
    This includes any substructures the game data structure contains. Do not modify this function.*/
{
    free(cur_game->cells);
    free(cur_game);
    cur_game = NULL;
    return;
}

cell * get_cell(game * cur_game, int row, int col)
/*! Given a game, a row, and a column, return a pointer to the corresponding
    cell on the game. (See game.h for game data structure specification)
    This function should be handy for accessing game cells. Return NULL
	if the row and col coordinates do not exist.
*/
{
    //YOUR CODE STARTS HERE
    if(row < 0 || row >= cur_game->rows || col < 0 || col >= cur_game->cols){
        return NULL;
    }else{
        return &cur_game->cells[row*(cur_game->cols)+col]; //& because if not, the pointer would return
    }
}

int move_w(game * cur_game)
/*!Slides all of the tiles in cur_game upwards. If a tile matches with the 
   one above it, the tiles are merged by adding their values together. When
   tiles merge, increase the score by the value of the new tile. A tile can 
   not merge twice in one turn. If sliding the tiles up does not cause any 
   cell to change value, w is an invalid move and return 0. Otherwise, return 1. 
*/
{
    //YOUR CODE STARTS HERE
    /*check the cell right above, if empty move, if a value, check if value is ==,
      if yes then add by value and then set the first cell to -1*/
    int valid = 0;
    int findRow;
    for(int j = 0; j < cur_game->cols; j++){ //column                             
        for(int i = 0; i < cur_game->rows; i++){ //row
            if(cur_game->cells[i * cur_game->cols + j] != -1){   
                for(findRow = 0; findRow < i; findRow++){
                    if(cur_game->cells[findRow * cur_game->cols + j] == -1){ //if findRow and j col value is empty
                        cur_game->cells[(findRow) * cur_game->cols + j] = cur_game->cells[i * cur_game->cols + j];  //move val into findRow and j cell
                        cur_game->cells[i * cur_game->cols + j] = -1; //set the original row and col value to be empty
                        valid = 1; //valid move
                        break; //end once the empty row and col value is found
                    }
                }
                if((findRow-1) != -1 && cur_game->cells[(findRow-1) * cur_game->cols + j] == cur_game->cells[(findRow) * cur_game->cols + j]){ //if row above == current row, and not empty
                    cur_game->cells[(findRow-1) * cur_game->cols + j] = 2 * cur_game->cells[(findRow-1) * cur_game->cols + j]; //set the row above to twice the 
                    cur_game->cells[(findRow) * cur_game->cols + j] = -1; //empty the current row
                    cur_game->score = cur_game->score + cur_game->cells[(findRow-1) * cur_game->cols + j]; //add score based on the value that findRow is(row above in this case)
                    valid = 1;
                }
            }
        }
    }
    
    if(valid == 0){
        return 0; //if valid did not go in the if statements, it returns 0 since it was an invalid move
    }else{
        return 1; //move is valid
    }
};

int move_s(game * cur_game) //slide down
{
    //YOUR CODE STARTS HERE
    int valid = 0;
    int findRow;
    for(int j = 0; j < cur_game->cols; j++){ //column                             
        for(int i = cur_game->rows - 1; i >= 0; i--){ //row
            if(cur_game->cells[i * cur_game->cols + j] != -1){   
                for(findRow = cur_game->rows - 1; findRow > i; findRow--){       
                    if(cur_game->cells[findRow * cur_game->cols + j] == -1){ //if findRow and j col value is empty
                        cur_game->cells[(findRow) * cur_game->cols + j] = cur_game->cells[i * cur_game->cols + j];  //move val into findRow and j cell
                        cur_game->cells[i * cur_game->cols + j] = -1; //set the original row and col value to be empty
                        valid = 1;
                        break; //end once the empty row and col value is found
                    }
                }
                if((findRow+1) != -1 && cur_game->cells[(findRow+1) * cur_game->cols + j] == cur_game->cells[(findRow) * cur_game->cols + j]){ //if row above == current row, and not empty
                    cur_game->cells[(findRow+1) * cur_game->cols + j] = 2 * cur_game->cells[(findRow+1) * cur_game->cols + j]; //set the row above to twice the 
                    cur_game->cells[(findRow) * cur_game->cols + j] = -1; //empty the current row
                    cur_game->score = cur_game->score + cur_game->cells[(findRow+1) * cur_game->cols + j]; //add score based on the value that findRow is(row above in this case)
                    valid = 1;
                }
            }
        }
    }
    
    if(valid == 0){
        return 0; //if valid did not go in the if statements, it returns 0 since it was an invalid move
    }else{
        return 1; //move is valid
    }
};

int move_a(game * cur_game) //slide left
{
    //YOUR CODE STARTS HERE
    int valid = 0;
    int findCol;
    for(int i = 0; i <= cur_game->rows -1; i++){ //column                             
        for(int j = 0; j <= cur_game->cols -1; j++){ //row
            if(cur_game->cells[i * cur_game->cols + j] != -1){   
                for(findCol = 0; findCol < j; findCol++){     
                    if(cur_game->cells[i * cur_game->cols + findCol] == -1){ //if findRow and j col value is empty
                        cur_game->cells[i * cur_game->cols + findCol] = cur_game->cells[i * cur_game->cols + j];  //move val into findRow and j cell
                        cur_game->cells[i * cur_game->cols + j] = -1; //set the original row and col value to be empty
                        valid = 1;
                        break; //end once the empty row and col value is found
                    }
                }
                if((findCol-1) != -1 && cur_game->cells[i * cur_game->cols + (findCol-1)] == cur_game->cells[i * cur_game->cols + (findCol)]){ //if row above == current row, and not empty
                    cur_game->cells[i * cur_game->cols + (findCol-1)] = 2 * cur_game->cells[i * cur_game->cols + (findCol-1)];
                    cur_game->cells[i * cur_game->cols + findCol] = -1;
                    cur_game->score = cur_game->score + cur_game->cells[i * cur_game->cols + (findCol-1)];
                    valid = 1;
                }   
            }
        }
    }
    
    if(valid == 0){
        return 0; //if valid did not go in the if statements, it returns 0 since it was an invalid move
    }else{
        return 1; //move is valid
    }
};

int move_d(game * cur_game){ //slide to the right
    //YOUR CODE STARTS HERE
    int valid = 0;
    int findCol;
    for(int i = 0; i < cur_game->rows; i++){ //column                             
        for(int j = cur_game->cols-1; j >= 0; j--){ //row
            if(cur_game->cells[i * cur_game->cols + j] != -1){   
                for(findCol = cur_game->cols-1; findCol > j; findCol--){   
                    if(cur_game->cells[i * cur_game->cols + findCol] == -1){ //if findRow and j col value is empty
                        cur_game->cells[i * cur_game->cols + findCol] = cur_game->cells[i * cur_game->cols + j];  //move val into findRow and j cell
                        cur_game->cells[i * cur_game->cols + j] = -1; //set the original row and col value to be empty
                        valid = 1;
                        break; //end once the empty row and col value is found
                    }
                }
                if((findCol+1) != -1 && cur_game->cells[i * cur_game->cols + (findCol+1)] == cur_game->cells[i * cur_game->cols + (findCol)]){ //if row above == current row, and not empty
                    cur_game->cells[i * cur_game->cols + (findCol+1)] = 2 * cur_game->cells[i * cur_game->cols + (findCol+1)];
                    cur_game->cells[i * cur_game->cols + findCol] = -1;
                    cur_game->score = cur_game->score + cur_game->cells[i * cur_game->cols + (findCol+1)];
                    valid = 1;
                } 
            }
        }
    }
    
    if(valid == 0){
        return 0; //if valid did not go in the if statements, it returns 0 since it was an invalid move
    }else{
        return 1; //move is valid
    }
};

int legal_move_check(game * cur_game)
/*! Given the current game check if there are any legal moves on the board. There are
    no legal moves if sliding in any direction will not cause the game to change.
	Return 1 if there are possible legal moves, 0 if there are none.
 */
{
    //YOUR CODE STARTS HERE
    game * checkGame = make_game(cur_game->rows, cur_game->cols); //cannot modify current game, so make a test game
    for (int i = 0; i < cur_game->rows * cur_game->cols; i++){
      checkGame->cells[i] = cur_game->cells[i]; //copy all the values in check game to the current game
    }
    if(move_w(checkGame)==1 || move_a(checkGame) == 1 || move_s(checkGame) == 1 || move_d(checkGame) == 1){ //test w,a,s,d on checking game
        return 1;
    } else {
        return 0;
    }
}


/*! code below is provided and should not be changed */

void rand_new_tile(game * cur_game)
/*! insert a new tile into a random empty cell. First call rand()%(rows*cols) to get a random value between 0 and (rows*cols)-1.
*/
{
	
	cell * cell_ptr;
    cell_ptr = 	cur_game->cells;
	
    if (cell_ptr == NULL){ 	
        printf("Bad Cell Pointer.\n");
        exit(0);
    }
	
	
	//check for an empty cell
	int emptycheck = 0;
	int i;
	
	for(i = 0; i < ((cur_game->rows)*(cur_game->cols)); i++){
		if ((*cell_ptr) == -1){
				emptycheck = 1;
				break;
		}		
        cell_ptr += 1;
	}
	if (emptycheck == 0){
		printf("Error: Trying to insert into no a board with no empty cell. The function rand_new_tile() should only be called after tiles have succesfully moved, meaning there should be at least 1 open spot.\n");
		exit(0);
	}
	
    int ind,row,col;
	int num;
    do{
		ind = rand()%((cur_game->rows)*(cur_game->cols));
		col = ind%(cur_game->cols);
		row = ind/cur_game->cols;
    } while ( *get_cell(cur_game, row, col) != -1);
        //*get_cell(cur_game, row, col) = 2;
	num = rand()%20;
	if(num <= 1){
		*get_cell(cur_game, row, col) = 4; // 1/10th chance
	}
	else{
		*get_cell(cur_game, row, col) = 2;// 9/10th chance
	}
}

int print_game(game * cur_game) 
{
    cell * cell_ptr;
    cell_ptr = 	cur_game->cells;

    int rows = cur_game->rows;
    int cols = cur_game->cols;
    int i,j;
	
	printf("\n\n\nscore:%d\n",cur_game->score); 
	
	
	printf("\u2554"); // topleft box char
	for(i = 0; i < cols*5;i++)
		printf("\u2550"); // top box char
	printf("\u2557\n"); //top right char 
	
	
    for(i = 0; i < rows; i++){
		printf("\u2551"); // side box char
        for(j = 0; j < cols; j++){
            if ((*cell_ptr) == -1 ) { //print asterisks
                printf(" **  "); 
            }
            else {
                switch( *cell_ptr ){ //print colored text
                    case 2:
                        printf("\x1b[1;31m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 4:
                        printf("\x1b[1;32m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 8:
                        printf("\x1b[1;33m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 16:
                        printf("\x1b[1;34m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 32:
                        printf("\x1b[1;35m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 64:
                        printf("\x1b[1;36m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 128:
                        printf("\x1b[31m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 256:
                        printf("\x1b[32m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 512:
                        printf("\x1b[33m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 1024:
                        printf("\x1b[34m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 2048:
                        printf("\x1b[35m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 4096:
                        printf("\x1b[36m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 8192:
                        printf("\x1b[31m%04d\x1b[0m ",(*cell_ptr));
                        break;
					default:
						printf("  X  ");

                }

            }
            cell_ptr++;
        }
	printf("\u2551\n"); //print right wall and newline
    }
	
	printf("\u255A"); // print bottom left char
	for(i = 0; i < cols*5;i++)
		printf("\u2550"); // bottom char
	printf("\u255D\n"); //bottom right char
	
    return 0;
}

int process_turn(const char input_char, game* cur_game) //returns 1 if legal move is possible after input is processed
{ 
	int rows,cols;
	char buf[200];
	char garbage[2];
    int move_success = 0;
	
    switch ( input_char ) {
    case 'w':
        move_success = move_w(cur_game);
        break;
    case 'a':
        move_success = move_a(cur_game);
        break;
    case 's':
        move_success = move_s(cur_game);
        break;
    case 'd':
        move_success = move_d(cur_game);
        break;
    case 'q':
        destroy_game(cur_game);
        printf("\nQuitting..\n");
        return 0;
        break;
	case 'n':
		//get row and col input for new game
		dim_prompt: printf("NEW GAME: Enter dimensions (rows columns):");
		while (NULL == fgets(buf,200,stdin)) {
			printf("\nProgram Terminated.\n");
			return 0;
		}
		
		if (2 != sscanf(buf,"%d%d%1s",&rows,&cols,garbage) ||
		rows < 0 || cols < 0){
			printf("Invalid dimensions.\n");
			goto dim_prompt;
		} 
		
		remake_game(&cur_game,rows,cols);
		
		move_success = 1;
		
    default: //any other input
        printf("Invalid Input. Valid inputs are: w, a, s, d, q, n.\n");
    }

	
	
	
    if(move_success == 1){ //if movement happened, insert new tile and print the game.
         rand_new_tile(cur_game); 
		 print_game(cur_game);
    } 

    if( legal_move_check(cur_game) == 0){  //check if the newly spawned tile results in game over.
        printf("Game Over!\n");
        return 0;
    }
    return 1;
}
