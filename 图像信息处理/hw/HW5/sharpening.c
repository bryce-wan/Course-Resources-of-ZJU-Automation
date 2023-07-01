#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include "bmp.h"
#include <math.h>
BMP Img;

CACHE Cache;

void Convolve(BMP *pImg, CACHE *pCache, double *filter);

BYTE Calibrate(double a)
{

    if (a < 0)

        a = 0;

    if (a > 255)

        a = 255;

    return (BYTE)a;
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

    char *obj_filename = "img\\laplacian_sharpening_1.bmp";

    readBMP(filename, &Img, &Cache);

    Convolve(&Img, &Cache, lap_filter_1);

    writeBMP(obj_filename, &Img, &Cache);

    system(obj_filename);

    readBMP(filename, &Img, &Cache);

    Convolve(&Img, &Cache, lap_filter_2);

    obj_filename = "img\\laplacian_sharpening_2.bmp";

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

    memcpy((BYTE *)Temp, (BYTE *)pImg->pImgInfo, pCache->ImgSize * sizeof(BYTE));

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

                    k = filter[count];

                    mean_B += Temp[m * M + n * N] * k;

                    mean_G += Temp[m * M + n * N + 1] * k;

                    mean_R += Temp[m * M + n * N + 2] * k;

                    count++;
                }
            }

            pImg->pImgInfo[i * M + j * N] = Calibrate(pImg->pImgInfo[i * M + j * N] + mean_B);

            pImg->pImgInfo[i * M + j * N + 1] = Calibrate(pImg->pImgInfo[i * M + j * N + 1] + mean_G);

            pImg->pImgInfo[i * M + j * N + 2] = Calibrate(pImg->pImgInfo[i * M + j * N + 2] + mean_R);

            mean_R = mean_G = mean_B = 0;
        }
    }
}
