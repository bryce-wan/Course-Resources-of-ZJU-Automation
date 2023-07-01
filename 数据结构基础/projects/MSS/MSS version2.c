#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define RANDMAX 100
#define RANDMIN -100

clock_t start, stop;

double duration, ticks;

int maxSubRec_2(int **mat, int N); // Declaration of the funcion that calculate the MSS

int main()
{
    int N, n, i, j, iter;

    int maxSum;

    int **matrix;

    int size[6] = {5, 10, 30, 50, 80, 100}; // An array to store the size of the test input

    int iteration[6] = {10000, 10000, 1000, 100, 10, 10};

    for (n = 0; n < 6; n++)
    {
        N = size[n]; // the size of the matrix is N by N

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
            maxSum = maxSubRec_2(matrix, N);

        stop = clock(); // Stop to timing

        ticks = (double)(stop - start); // Calculatee the ticks

        duration = ticks / CLK_TCK; // Calculate the duration

        printf("When the size of the matrix is %d by %d\n", N, N);

        printf("The iteration K:%d\n", iter);

        printf("MaxSubmatrixSum:%d\n", maxSum);

        printf("time ticks:%f\n", ticks);

        printf("time cost:%f seconds\n\n", duration);
    }

    return 0;
}

int maxSubRec_2(int **mat, int N)
{
    int startRow, endRow, startCol, endCol, i, j;

    int thisSum = 0, maxSum = -9999;

    int *thisRowSum; // An array to record each row's sum of the submatrix

    thisRowSum = (int *)malloc(N * sizeof(int));

    for (startCol = 0; startCol < N; startCol++) // Traverse every col to make it the first col of the submatrix
    {
        for (startRow = 0; startRow < N; startRow++) // Traverse every row to make it the first row of the submatrix
        {
            for (i = startRow; i < N; i++)
                thisRowSum[i] = 0; // Initialize the record array

            for (endCol = startCol; endCol < N; endCol++) // Traverse every col after the startCol to make it the last col of the submatrix
            {
                thisSum = 0;

                for (endRow = startRow; endRow < N; endRow++) // Traverse all rows
                {
                    thisSum += thisRowSum[endRow] + mat[endRow][endCol]; // Calculate the sum of all rows beetween starCol and endCol

                    thisRowSum[endRow] += mat[endRow][endCol]; // Update the record of the sum of THIS row

                    if (thisSum > maxSum)
                        maxSum = thisSum; // Update the maxSum
                }
            }
        }
    }

    return maxSum;
}
