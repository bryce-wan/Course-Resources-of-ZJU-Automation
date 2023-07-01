#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define RANDMAX 100
#define RANDMIN -100

clock_t start, stop;

double duration, ticks;

int maxSubRec_1(int **mat, int N); // Declaration of the funcion that calculate the MSS

int maxSubRec_2(int **mat, int N); // Declaration of the funcion that calculate the MSS

int maxSubRec_optim(int **mat, int N); // Declaration of the funcion that calculate the MSS

int main()
{

    int N;

    scanf("%d", &N);

    int i, j;

    int maxSum;

    int **matrix;

    for (i = 0; i < N; i++)
    {
        matrix[i] = (int *)malloc(N * sizeof(int));
    }

    for (i = 0; i < N; i++)
    {
        for (j = 0; j < N; j++)
        {
            scanf("%d", &matrix[i][j]);
        }
    }

    maxSum = maxSubRec_1(matrix, N);

    printf("When the function is version 1\n");

    printf("MaxSubmatrixSum:%d\n", maxSum);

    maxSum = maxSubRec_2(matrix, N);

    printf("When the function is version 2\n");

    printf("MaxSubmatrixSum:%d\n", maxSum);

    maxSum = maxSubRec_optim(matrix, N);

    printf("When the function is version bonus\n");

    printf("MaxSubmatrixSum:%d\n", maxSum);

    return 0;
}

int maxSubRec_optim(int **mat, int N)
{
    int Row, startCol, endCol, i, j;

    int thisSum = 0, maxSum = -9999;

    int *thisRowSum; // An array to record each row's sum of the submatrix

    thisRowSum = (int *)malloc(N * sizeof(int));

    for (startCol = 0; startCol < N; startCol++) // Traverse every col to make it the first col of the submatrix
    {
        for (i = 0; i < N; i++)
            thisRowSum[i] = 0; // Initialize the array

        for (endCol = startCol; endCol < N; endCol++) // Traverse every col after the startCol to make it the last col of the submatrix
        {
            thisSum = 0;

            for (Row = 0; Row < N; Row++) // Traverse all rows
            {
                thisSum += thisRowSum[Row] + mat[Row][endCol]; // Calculate the sum of all rows beetween starCol and endCol

                thisRowSum[Row] += mat[Row][endCol]; // Update the record of the sum of THIS row

                if (thisSum > maxSum) // Update the maxSum
                    maxSum = thisSum;

                if (thisSum < 0) // thisSum should be positive
                    thisSum = 0;
            }
        }
    }

    return maxSum;
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
