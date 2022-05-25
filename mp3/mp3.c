/*In this program, given a row number in Pascal's triangle(user input),
the program computed all of the binomial coefficients, and printed
each cofficient and then a space. To compute the binomial coefficients
I used two for loops. The first for loop counted the number of 
coefficients per the row input given, while the second for loop calculated
the coefficent value based on the coefficient the program was currently at.*/

#include <stdio.h>
#include <stdlib.h>

int main()
{
  int row;

  printf("Enter a row index: ");
  scanf("%d",&row);

  // Write your code here
  unsigned long sum = 1; /*set sum to 1 so we can multiply*/
  unsigned long n = row + 1; /*number of coefficients = n = row+1*/
  for(unsigned long j=0; j<n; j++){ /*j increments until it hits n*/
    for(unsigned long i=1; i<n-j; i++){ /*i increments until i<n-current coeff*/
      sum = sum*(n-i)/i; /*multiplies sum with formula*/
    }
    printf("%lu ",sum); /*prints the coefficient with a space*/
    sum = 1; /*reset sum to 1 to multiply*/
  }
  return 0;
}
