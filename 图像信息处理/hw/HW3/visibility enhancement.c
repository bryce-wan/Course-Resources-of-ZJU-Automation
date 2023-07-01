#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <math.h>
#include "bmp.h"

void Log_Enhance(BMP *pImg, CACHE *pCache);

BMP Img;

CACHE Cache;

int main()
{

    Img.bf = (BITMAPFILEHEADER *)malloc(sizeof(BITMAPFILEHEADER));

    Img.bi = (BITMAPINFOHEADER *)malloc(sizeof(BITMAPINFOHEADER));

    Img.pRGB = NULL;

    Img.pImgInfo = NULL;

    char *filename = "img\\gray.bmp";

    char *obj_filename = "img\\enhanced.bmp";

    readBMP(filename, &Img, &Cache);

    Log_Enhance(&Img, &Cache);

    writeBMP(obj_filename, &Img, &Cache);

    system(obj_filename);

    system("pause");
}

void Log_Enhance(BMP *pImg, CACHE *pCache)
{
    DWORD rows = pCache->ImgHeight; // the height of the iamge matrix

    DWORD cols = pCache->ImgWidth; // the width of the image matrix

    DWORD M = pCache->LineBytes, N = 3;

    double Lmax = .0; // Lmax to record the max L in the source image

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            if (pImg->pImgInfo[i * M + N * j] > Lmax)

                Lmax = (double)pImg->pImgInfo[i * M + N * j]; // traverse to get the max L
        }
    }

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            double Lw = pImg->pImgInfo[i * M + j * N];

            double Ld = 255.0 * (log(Lw / 255 + 1) / log(Lmax / 255 + 1)); // apply the formula to transform Lw to Ld

            pImg->pImgInfo[i * M + j * N] = (WORD)Ld;

            pImg->pImgInfo[i * M + j * N + 1] = (WORD)Ld;

            pImg->pImgInfo[i * M + j * N + 2] = (WORD)Ld;
        }
    }
}