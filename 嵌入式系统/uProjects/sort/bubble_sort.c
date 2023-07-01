#include <reg51.h>

void main(void)
{
    unsigned char data A[15] = {27, 5, 32, 47, 38, 235, 79, 17, 187, 58, 23, 35, 211, 104, 9};

    unsigned int data i = 0, j = 0;

    for (i = 0; i < 15; i++)
    {
        for (j = i + 1; j < 15; j++)
        {
            if (A[i] > A[j])
            {
                A[j] = A[j] + A[i];
                A[i] = A[j] - A[i];
                A[j] = A[j] - A[i];
            }
        }
    }
}
