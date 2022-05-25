/*The first error in semiprime.c was in is_prime. According to the 
directions, if the number is prime, 1 should be returned, however
when the value was prime 0 was returned. I changed the values to 
return properly and fixed is_prime.

The second error in semiprime.c was in the print_semiprimes method. 
k was set to the modulus of i and j, which was 0 since there was an 
if statement that let the code go into that if statement only if i%j 
equaled 0. Therefore, is_prime(k) did not give the correct output. 
So, I changed the line to be k = i/j, since we dont want the remainder 
for k, which printed the correct values for output. 

The third error was in print_semiprimes. Each correct value printed 
twice since j kept iterating in the for loop. Therefore, I entered a 
line "j = i" if is_prime(k) was true, which quit the for loop if 
the correct value was printed.
 
The fourth error was in the print_semiprimes method. The return value 
was always 0, and did not change even if there were semiprimes in the 
range. Therefore, if is_prime(k) returned true, I set the return value 
to 1, since it meant that there were semiprimes in the given range. */

#include <stdlib.h>
#include <stdio.h>


/*
 * is_prime: determines whether the provided number is prime or not
 * Input    : a number
 * Return   : 0 if the number is not prime, else 1
 */
int is_prime(int number)
{
    int i;
    if (number == 1) {return 0;}
    for (i = 2; i < number; i++) { //for each number smaller than it
        if (number % i == 0) { //check if the remainder is 0
            return 0;
        }
    }
    return 1;
}


/*
 * print_semiprimes: prints all semiprimes in [a,b] (including a, b).
 * Input   : a, b (a should be smaller than or equal to b)
 * Return  : 0 if there is no semiprime in [a,b], else 1
 */
int print_semiprimes(int a, int b)
{
    int i, j, k;
    int ret = 0;
    for (i = a; i <=b; i++) { //for each item in interval
        //check if semiprime
        for (j = 2; j <= i; j++) {
            if (i%j == 0) {
                if (is_prime(j)) {
		  k = i/j; /*changed i%j to i/j*/
                    if (is_prime(k)) {
                        printf("%d ", i);
			j = i; /*set j to i if k is prime*/
			ret = 1; /*set ret to 1 if k is prime*/ 
                    }
                }
            }
        }

    }
    printf("\n");
    return ret;

}
