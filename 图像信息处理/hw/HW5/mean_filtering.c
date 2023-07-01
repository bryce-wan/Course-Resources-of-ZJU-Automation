#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include "bmp.h"
BMP Img;

CACHE Cache;

void Convolve(BMP *pImg, CACHE *pCache, double *filter);

int main()
{
    Img.bf = (BITMAPFILEHEADER *)malloc(sizeof(BITMAPFILEHEADER));

    Img.bi = (BITMAPINFOHEADER *)malloc(sizeof(BITMAPINFOHEADER));

    Img.pRGB = NULL;

    Img.pImgInfo = NULL;

    char *filename = "img\\lena.bmp";

    char *obj_filename = "img\\mean_filtering.bmp";

    readBMP(filename, &Img, &Cache);

    double mean_filter[9] = {1. / 9, 1. / 9, 1. / 9, 1. / 9, 1. / 9, 1. / 9, 1. / 9, 1. / 9, 1. / 9};

    Convolve(&Img, &Cache, mean_filter);

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

    memcpy((char *)Temp, (BYTE *)pImg->pImgInfo, pCache->ImgSize * sizeof(BYTE));

    double mean_R = 0, mean_G = 0, mean_B = 0;

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

                    mean_R += Temp[m * M + n * N + 2] * k;
                }
            }

            pImg->pImgInfo[i * M + j * N] = (BYTE)mean_B;

            pImg->pImgInfo[i * M + j * N + 1] = (BYTE)mean_G;

            pImg->pImgInfo[i * M + j * N + 2] = (BYTE)mean_R;

            mean_R = mean_G = mean_B = 0;
        }
    }
}
