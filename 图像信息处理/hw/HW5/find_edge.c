#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include "bmp.h"
#include <math.h>
BMP Img;

CACHE Cache;

void Convolve(BMP *pImg, CACHE *pCache, double *filter);

BYTE Calibrate(int min, int max, double a)
{
    return (BYTE)(255 * (a - min) / (max - min));
}

int main()
{
    Img.bf = (BITMAPFILEHEADER *)malloc(sizeof(BITMAPFILEHEADER));

    Img.bi = (BITMAPINFOHEADER *)malloc(sizeof(BITMAPINFOHEADER));

    Img.pRGB = NULL;

    Img.pImgInfo = NULL;

    double lap_filter_1[9] = {0, -1, 0, -1, 4, -1, 0, -1, 0};

    double lap_filter_2[9] = {-1, -1, -1, -1, 8, -1, -1, -1, -1};

    char *filename = "img\\lena.bmp";

    char *obj_filename = "img\\edge.bmp";

    readBMP(filename, &Img, &Cache);

    Convolve(&Img, &Cache, lap_filter_2);

    writeBMP(obj_filename, &Img, &Cache);

    system(obj_filename);

    system("pause");
}

void Convolve(BMP *pImg, CACHE *pCache, double *filter)
{

    DWORD rows = pCache->ImgHeight;

    DWORD cols = pCache->ImgWidth;

    DWORD M = pCache->LineBytes, N = 3;

    BYTE *Temp = (BYTE *)malloc(pCache->ImgSize * sizeof(BYTE));

    int *Edge = (int *)malloc(pCache->ImgSize * sizeof(int));

    BYTE *StdEdge = (BYTE *)malloc(pCache->ImgSize * sizeof(BYTE));

    memcpy((BYTE *)Temp, (BYTE *)pImg->pImgInfo, pCache->ImgSize * sizeof(BYTE));

    memset(Edge, 0, pCache->ImgSize);

    memset(StdEdge, 0, pCache->ImgSize);

    double mean_R = 0, mean_G = 0, mean_B = 0;

    double max_B = 0, max_G = 0, max_R = 0;

    double min_B = 255, min_G = 255, min_R = 255;

    double k;

    for (int i = 1; i < rows - 1; i++)
    {
        for (int j = 1; j < cols - 1; j++)
        {
            int count = 0;

            for (int m = i - 1; m < i + 2; m++)
            {
                for (int n = j - 1; n < j + 2; n++)
                {

                    k = filter[count++];

                    mean_B += Temp[m * M + n * N] * k;

                    mean_G += Temp[m * M + n * N + 1] * k;

                    mean_R += Temp[m * M + n * N + 1] * k;
                }
            }

            Edge[i * M + j * N] = mean_B;

            if (mean_B > max_B)
                max_B = mean_B;
            if (mean_B < min_B)
                min_B = mean_B;

            Edge[i * M + j * N + 1] = mean_G;

            if (mean_G > max_G)
                max_G = mean_G;
            if (mean_G < min_G)
                min_G = mean_G;

            Edge[i * M + j * N + 2] = mean_R;

            if (mean_R > max_R)
                max_R = mean_R;
            if (mean_R < min_R)
                min_R = mean_R;

            mean_R = mean_G = mean_B = 0;
        }
    }

    for (int i = 1; i < rows - 1; i++)
    {
        for (int j = 1; j < cols - 1; j++)
        {
            StdEdge[i * M + j * N] = Calibrate(min_B, max_B, Edge[i * M + j * N]);

            StdEdge[i * M + j * N + 1] = Calibrate(min_G, max_G, Edge[i * M + j * N + 1]);

            StdEdge[i * M + j * N + 2] = Calibrate(min_R, max_R, Edge[i * M + j * N + 2]);
        }
    }

    pImg->pImgInfo = StdEdge;
}
