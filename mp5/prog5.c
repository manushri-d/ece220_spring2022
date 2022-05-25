/*In this program, the user enters a seed value which generates a 4 integer solution
 to the game. The user then has 12 guesses to guess the correct combination and 
integer of the 4 numbers. The number of perfect matches and misplaced matches is 
printed after every guess. The program tereminates once all 4 matches have been found. 
In prog5.c I implemented 3 methods. set_seed returns 1 if the user entered only 
1 integer, and 0 for anything else. start_game computes random solution values from 
1-8, using rand()%8+1. start_game also calls srand, and sets the pointers to the 
solution values. make_guess returns 1 if the guess is 4 numbers from 1-8, and 0 for 
anything else. make_guess also computes the amount of perfect and misplaced 
matches using if and if else statements to check if each condition is valid. 
 */


/*			
 *
 * prog5.c - source file adapted from UIUC ECE198KL Spring 2013 Program 4
 *           student code -- GOLD VERSION by Steven S. Lumetta
 */


/*
 * The functions that you must write are defined in the header file.
 * Blank function prototypes with explanatory headers are provided
 * in this file to help you get started.
 */



#include <stdio.h>
#include <stdlib.h>

#include "prog5.h"


/*
 * You will need to keep track of the solution code using file scope
 * variables as well as the guess number.
 */

static int guess_number;
static int solution1;
static int solution2;
static int solution3;
static int solution4;


/*
 * set_seed -- This function sets the seed value for pseudorandom
 * number generation based on the number the user types.
 * The input entered by the user is already stored in the string seed_str by the code in main.c.
 * This function should use the function sscanf to find the integer seed value from the 
 * string seed_str, then initialize the random number generator by calling srand with the integer
 * seed value. To be valid, exactly one integer must be entered by the user, anything else is invalid. 
 * INPUTS: seed_str -- a string (array of characters) entered by the user, containing the random seed
 * OUTPUTS: none
 * RETURN VALUE: 0 if the given string is invalid (string contains anything
 *               other than a single integer), or 1 if string is valid (contains one integer)
 * SIDE EFFECTS: initializes pseudo-random number generation using the function srand. Prints "set_seed: invalid seed\n"
 *               if string is invalid. Prints nothing if it is valid.
 */
int
set_seed (const char seed_str[])
{
//    Example of how to use sscanf to read a single integer and check for anything other than the integer
//    "int seed" will contain the number typed by the user (if any) and the string "post" will contain anything after the integer
//    The user should enter only an integer, and nothing else, so we will check that only "seed" is read. 
//    We declare
//    int seed;
//    char post[2];
//    The sscanf statement below reads the integer into seed. 
//    sscanf (seed_str, "%d%1s", &seed, post)
//    If there is no integer, seed will not be set. If something else is read after the integer, it will go into "post".
//    The return value of sscanf indicates the number of items read succesfully.
//    When the user has typed in only an integer, only 1 item should be read sucessfully. 
//    Check that the return value is 1 to ensure the user enters only an integer. 
//    Feel free to uncomment these statements, modify them, or delete these comments as necessary. 
//    You may need to change the return statement below
  int seed=0;
  char post[2];
  int check = sscanf (seed_str, "%d%1s", &seed, post);
  int rv;
  if(check == 1){ 
    srand(seed); //call the srand method
    rv = 1; //set return value to 1
  }else{
    printf("set_seed: invalid seed\n");
    rv = 0; //set return value to 0
  }
  return rv;
}


/*
 * start_game -- This function is called by main.c after set_seed but before the user makes guesses.
 *               This function creates the four solution numbers using the approach
 *               described in the wiki specification (using rand())
 *               The four solution numbers should be stored in the static variables defined above. 
 *               The values at the pointers should also be set to the solution numbers.
 *               The guess_number should be initialized to 1 (to indicate the first guess)
 * INPUTS: none
 * OUTPUTS: *one -- the first solution value (between 1 and 8)
 *          *two -- the second solution value (between 1 and 8)
 *          *three -- the third solution value (between 1 and 8)
 *          *four -- the fourth solution value (between 1 and 8)
 * RETURN VALUE: none
 * SIDE EFFECTS: records the solution in the static solution variables for use by make_guess, set guess_number
 */
void
start_game (int* one, int* two, int* three, int* four)
{
  //your code here
  solution1 = (rand()%8)+1; //rand()%8 returns a value from 0-7, and adding 1 returns a value from 1-8
  solution2 = (rand()%8)+1;
  solution3 = (rand()%8)+1;
  solution4 = (rand()%8)+1;
  *one = solution1;
  *two = solution2;
  *three = solution3;
  *four = solution4;
  guess_number = 1;
}

/*
 * make_guess -- This function is called by main.c after the user types in a guess.
 *               The guess is stored in the string guess_str. 
 *               The function must calculate the number of perfect and misplaced matches
 *               for a guess, given the solution recorded earlier by start_game
 *               The guess must be valid (contain only 4 integers, within the range 1-8). If it is valid
 *               the number of correct and incorrect matches should be printed, using the following format
 *               "With guess %d, you got %d perfect matches and %d misplaced matches.\n"
 *               If valid, the guess_number should be incremented.
 *               If invalid, the error message "make_guess: invalid guess\n" should be printed and 0 returned.
 *               For an invalid guess, the guess_number is not incremented.
 * INPUTS: guess_str -- a string consisting of the guess typed by the user
 * OUTPUTS: the following are only valid if the function returns 1 (A valid guess)
 *          *one -- the first guess value (between 1 and 8)
 *          *two -- the second guess value (between 1 and 8)
 *          *three -- the third guess value (between 1 and 8)
 *          *four -- the fourth color value (between 1 and 8)
 * RETURN VALUE: 1 if the guess string is valid (the guess contains exactly four
 *               numbers between 1 and 8), or 0 if it is invalid
 * SIDE EFFECTS: prints (using printf) the number of matches found and increments guess_number(valid guess) 
 *               or an error message (invalid guess)
 *               (NOTE: the output format MUST MATCH EXACTLY, check the wiki writeup)
 */
int
make_guess (const char guess_str[], int* one, int* two, 
	    int* three, int* four)
{
//  One thing you will need to read four integers from the string guess_str, using a process
//  similar to set_seed
//  The statement, given char post[2]; and four integers w,x,y,z,
//  sscanf (guess_str, "%d%d%d%d%1s", &w, &x, &y, &z, post)
//  will read four integers from guess_str into the integers and read anything else present into post
//  The return value of sscanf indicates the number of items sucessfully read from the string.
//  You should check that exactly four integers were sucessfully read.
//  You should then check if the 4 integers are between 1-8. If so, it is a valid guess
//  Otherwise, it is invalid.  
//  Feel free to use this sscanf statement, delete these comments, and modify the return statement as needed
  int w,x,y,z;
  char post[2];
  int check = sscanf (guess_str, "%d%d%d%d%1s", &w, &x, &y, &z, post);
  int rv; //variable that holds the return value
  int c1,c2,c3,c4; //variables that checks if each number is between 1-8 and also checks if a perfect match is made
  int pm=0; //variable that holds perfect match and misplaced match counts
  int mm=0;
  int wd,xd,yd,zd; //variables that checks if the variable is found
  if(check==4){
    //check if the 4 integers are between 1-8
    for(int i=1; i<=8; i++){
      if(w==i)
	c1 = 1;
      if(x==i)
	c2 = 1;
      if(y==i)
	c3 = 1;
      if(z==i)
	c4 = 1;
    }
    if(c1+c2+c3+c4==4){
      rv = 1; //set the rv to 1
      *one = w; //set the pointers to the values
      *two = x;
      *three = y;
      *four = z;
      //test for perfect matches first
      if(w == solution1){
	pm++; //increment the perfect match counter
	c1 = 2; //set the checker to 2
      }
      if(x == solution2){
	pm++;
	c2 = 2;
      }
      if(y == solution3){
	pm++;
	c3 = 2;
      }
      if(z == solution4){
	pm++;
	c4 = 2;
      }
      //test solution1
      if(c1 != 2){ //if a perfect match was not found for solution1
	if(x == solution1 && c2 != 2){//if x==solution1 and a perfect match for x does not exist
	  mm++; //increment misplaced match counter
	  xd = 1; //set the x done to 1 since a misplaced match was found
	}else if(y == solution1 && c3 != 2){//repeat a similar process
	  mm++;
	  yd = 1;
	}else if(z == solution1 && c4 != 2){
	  mm++;
	  zd = 1;
	}
      }
      //test solution2
      if(c2 != 2){//if a perfect match was not found for solution2
	if(w == solution2 && c1 != 2){//if w==solution2 and a perfect match for w is not found yet, enter loop
	  mm++; //increment misplaced match counter
	  wd = 1; //set the w done to 1 since a misplaced match was found
	}else if(y == solution2 && yd != 1 && c3 != 2){//if y==solution2 and if y is not done yet and if a perfect match for y was not found
	   mm++;
	   yd = 1;
	}else if(z == solution2 && zd != 1 && c4 != 2){//repeat a similar process
	   mm++;
	   zd = 1;
	 }
      }
      //test solution3
      if(c3 != 2){//if a perfect match was not found for solution3
	if(w == solution3 && wd != 1 && c1 != 2){//something added was checking if w is found yet
	   mm++;
	   wd = 1;
	}else if(x == solution3 && xd != 1 && c2 != 2){//repeat a similar process 
	   mm++;
	   xd = 1;
	}else if(z == solution3 && zd != 1 && c4 != 2){//repeat a similar process
	   mm++;
	   zd = 1;
	 }
      }
      //test solution4
      if(c4 != 2){
	if(w == solution4 && wd != 1 && c1 != 2){//repeat a similar process
	   mm++;
	}else if(x == solution4 && xd != 1 && c2 != 2){//repeat a similar process
	   mm++;
	}else if(y == solution4 && yd != 1 && c3 != 2){//repeat a similar process
	   mm++;
	 }
      }
      
      printf("With guess %d, you got %d perfect matches and %d misplaced matches.\n",guess_number,pm,mm);
      guess_number++; //increment guess number
    }else{
      rv = 0; //set the return value to 0
      printf("make_guess: invalid guess\n");
    }
  }else{
    rv = 0; //set the return value to 0
    printf("make_guess: invalid guess\n");
  }
  
  return rv;
}


