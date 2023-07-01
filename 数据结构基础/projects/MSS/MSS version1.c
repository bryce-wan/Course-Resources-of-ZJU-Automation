#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define RANDMAX 100
#define RANDMIN -100

clock_t start, stop;

double duration, ticks;

int maxSubRec_1(int **mat, int N); // Declaration of the funcion that calculate the MSS

int main()
{
    int N, n, i, j, iter;

    int maxSum;

    int **matrix;

    int size[6] = {5, 10, 30, 50, 80, 100}; // An array to store the sizes of the test input

    int iteration[6] = {10000, 10000, 10, 1, 1, 1}; // An array to store the appropriate iteration numbers K

    for (n = 0; n < 6; n++)
    {
        N = size[n]; // The size of the matrix is N by N

        iter = iteration[n];

        srand((unsigned int)time(NULL)); // Initialize the random seed

        matrix = (int **)malloc(N * sizeof(int *)); // An 2D array to store the matrix

        for (i = 0; i < N; i++)
        {
            matrix[i] = (int *)malloc(N * sizeof(int));
        }

        for (i = 0; i < N; i++)
        {
            for (j = 0; j < N; j++)
            {
                matrix[i][j] = ((rand() % (RANDMAX - RANDMIN)) + 1) + RANDMIN; // Initialize the matrix with random value
            }
        }

        start = clock(); // Start to timing

        for (i = 0; i < iter; i++) // A circle of K iterations to avoid the function ends in a tick
            maxSum = maxSubRec_1(matrix, N);

        stop = clock(); // Stop to timing

        ticks = (double)(stop - start); // Calculatee the ticks

        duration = ticks / CLK_TCK; // Calculate the duration

        printf("When the size of the matrix is %d by %d\n", N, N); // Show the size of the randomly initialized matrix

        printf("The iteration K:%d\n", iter); // Show the iteration K

        printf("MaxSubmatrixSum:%d\n", maxSum); // Show the result

        printf("time ticks:%f\n", ticks); // Show the time ticks

        printf("time cost:%f seconds\n\n", duration); // show the cost of time(seconds)
    }

    return 0;
}

int maxSubRec_1(int **mat, int N)
{
    int startRow, endRow, startCol, endCol, i, j;

    int tempSum, maxSum = -9999;

    for (startRow = 0; startRow < N; startRow++) // Traverse all rows to make it the first row of the submatrix
    {
        for (startCol = 0; startCol < N; startCol++) // Traverse all cols to make it the first col of the submatrix
        {
            for (endRow = startRow; endRow < N; endRow++) // Traverse all rows to make it the last row of the submatrix
            {
                for (endCol = startCol; endCol < N; endCol++) // Traverse all cols to make it the last col of the submatrix
                {
                    tempSum = 0;

                    for (i = startRow; i <= endRow; i++)
                    {
                        for (j = startCol; j <= endCol; j++)
                        {
                            tempSum += mat[i][j]; // Calculate the sum of the submatrix by 2 circle
                        }
                    }
                    if (tempSum > maxSum)
                        maxSum = tempSum; // Update the maxSum
                }
            }
        }
    }
    return maxSum;
}
