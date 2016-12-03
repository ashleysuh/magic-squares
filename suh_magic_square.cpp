/*******************************************************************************
 *  Author:   Ashley Suh                                                       *
 *  Date:     6/1/16                                                           *
 *  Course:   COP 3514                                                         *
 *                                                                             *
 *  "A magic square is an arrangement of the numbers from 1 to n^2 in          *
 *  an n x n matrix, with each number occurring exactly once, and such         *
 *  that the sum of the entries of any row, any column, or any main            *
 *  diagonal is the same."                                                     *
 *                                                                             *
 *******************************************************************************/
#include <stdio.h>

// Prototypes for functions makeMagic, printMagic, sumMagic
void makeMagic (int SIZE, int matrix[][SIZE]);
void printMagic (int n, int m, int matrix2[n][m]);
int sumMagic (int inputSize);

int main (void) {

  // 'input' is the size of the n x n magic square, as entered by the user
  int input;

  printf ("Enter size of magic square: ");
  scanf ("%d", &input);

  /* The following conditional checks if the user inputs a value that is
     either less than 1, greater than 11, or an even number -- by evaluating
     whether the remainder is 0 when divided by 2. Program will exit if
     one of the above conditions is passed through */

  if (input < 1 || input > 11 || input % 2 == 0) {
    printf ("Invalid input: %d", input);
    return 0; // Terminates program if input is an illegal value
  }
  else {
    // Declares a 2d array using approved user input
    int array[input][input];
    // Calls function makeMagic to create the 2d array
    makeMagic(input, array);
    // Calls function printMagic to print the 2d array
    printMagic(input, input, array);

    // Prints the sum of all integers inside of the 2d array
    printf ("Sum of Magic Numbers: %d", sumMagic(input));
  }
}

/*******************************************************************************
 *  makeMagic:    Creates the magic square using a two dimensional array with  *
 *                the row and column size assigned by user's input. The        *
 *                variable SIZE is the value passed through by the user in     *
 *                main. SIZE will be referred to as 'n' in the comments to     *
 *                represent an n x n matrix.                                   *
 *                                                                             *
 * HOW IT WORKS:  Imagine an n x n matrix, stored as a 2d array and holding    *
 *                a magic square. The user has chosen the value of 'n' and we  *
 *                now have rows and columns inside the array, starting at 0    *
 *                and ending at n-1. The index in row 0 and center column is   *
 *                holding the value 1 for each magic square. We will now move  *
 *                one slot up and to the right and place the next value into   *
 *                that index. However, if our slot goes out of bounds from our *
 *                array, we wrap around and begin at either column 0 or        *
 *                row n-1, the final row. If that particular index has already *
 *                been filled, we will undo the previous steps and instead     *
 *                store the value into the index directly below our original   *
 *                location. We do this repeatedly until the entire array       *
 *                has been filled. No value is repeated.                       *
 *******************************************************************************/
void makeMagic (int SIZE, int matrix[][SIZE]) {

  int k,   // k is the value to be placed into each index of [i][j]
      row, // row is the "rows" of the magic square
      col; // col is the "columns" of the magic square

  // Begins by initializing the entire two-dimensional array to all 0's
  for (row = 0; row < SIZE; row++) {
    for (col = 0; col < SIZE; col++) {
      matrix[row][col] = 0; // Each index at [i][j] == 0
    }
  }

  // Sets the index of the first row and center column to hold value 1
  matrix[0][(SIZE-1)/2] = 1;

  // Row index is now in the final row of the array
  row = SIZE - 1;
  // Column index is now in the middle column and one slot to the right
  col = ((SIZE - 1) / 2) + 1;

  // k begins at 2 since k = 1 was initialized in line 63, k ends at n^2
  for (k = 2; k <= (SIZE * SIZE); k++) {
    // If the index [i][j] is still initialized to 0 from line 56
    if (matrix[row][col] == 0) {
      // Initializes the index to whatever k is inside the loop
      matrix[row][col] = k;
      row--; // Moves up one slot to the row above by decrementing 'row'

      // If row decrements smaller than 'n' (as in row == -1)
      if (row < 0) {
        row = SIZE - 1; // Resets row index to 'n-1': the last row in the array
      }
      col++; // Moves the column index one slot to the right

      // If column index exceeds n-1, that is if col moves outside the range
      if (col > (SIZE - 1)) {
        col = 0; // Resets column index to 0 -- the first column in the array
      }
    }

    // If the index [i][j] has already been assigned and contains a nonzero value
    if (matrix[row][col] != 0) {
      row++; // Move row index down one slot by increasing the row size

      // If the row index exceeds n-1, then reset to row index 0
      if (row > (SIZE - 1)) {
        row = 0;
      }
      col--; // Undoes the last movement in our index [i][j]

      // If column attempts to move left of index [i][0], wrap around the array
      if (col < 0) {
        col = (SIZE - 1); // Column index is now the last column in the array
      } // Index [i][j] is now initialized to the first row, last column

      ++row; // Moves the row index below the original location by one row

      // After finalizing index placement, set the value to k
      matrix[row][col] == k;
    }
  } // Continues until the last k has been printed to an index inside the array
}

/*******************************************************************************
 *  printMagic:   Prints the magic square using the parameter of user's input  *
 *                size as both 'n' and 'm'. 'n' is the row size and 'm' is the *
 *                column size of the magic square. Since our 2d array is a     *
 *                square, n == m within the array matrix2.                     *
 *******************************************************************************/
void printMagic (int n, int m, int matrix2[n][m]) {

  int y, z; /* Throwaway variables y and z that are used to assist in
               printing each index of the row & column of our 2d array */

  /* For loop goes through each iteration of the column while starting
     at row 0. Continues to row 1 and prints each column again. This happens
     repeatedly until each row has been printed. After the columns have
     been printed for the final row, the for loop will end */

  for (y = 0; y < n; y++) {
    for (z = 0; z < m; z++)
      printf ("%5d", matrix2[y][z]); // Field width 5 for formatting purposes
    printf ("\n");
  }
}

/*******************************************************************************
 *  sumMagic:     Sums every individual value contained in each [i][j] index   *
                  of the magic square. The variable int inputSize is the       *
                  user's input size from main.                                 *
 *******************************************************************************/
int sumMagic (int inputSize) {

  int a = 0; // Variable incrementor for our while loop
  int sum = 0; // Variable sum will track the total sum inside the magic square

  /* Loop begins at a = 0 and ends after a = n^2, where n is the input
     value entered from the user. Sum will add itself to 'a' through each
     iteration of the loop. Since no value of the magic square is repeated,
     we can safely increment 'a' each time and add that value to sum. */

  while (a <= (inputSize * inputSize)) {
    sum += a;
    a++;
  }
  return sum; // Returns sum of the values in our magic square
}
