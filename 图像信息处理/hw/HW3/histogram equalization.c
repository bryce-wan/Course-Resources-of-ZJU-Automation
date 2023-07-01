#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <math.h>
#include <string.h>
#include "bmp.h"

void Equalize_Hist(BMP *pImg, CACHE *pCache);

BMP Img;

CACHE Cache;

int main()
{

    Img.bf = (BITMAPFILEHEADER *)malloc(sizeof(BITMAPFILEHEADER));

    Img.bi = (BITMAPINFOHEADER *)malloc(sizeof(BITMAPINFOHEADER));

    Img.pRGB = NULL;

    Img.pImgInfo = NULL;

    char *filename = "img\\gray.bmp";

    char *obj_filename = "img\\equalhist.bmp";

    readBMP(filename, &Img, &Cache);

    Equalize_Hist(&Img, &Cache);

    writeBMP(obj_filename, &Img, &Cache);

    system(obj_filename);

    system("pause");
}

void Equalize_Hist(BMP *pImg, CACHE *pCache)
{
    DWORD rows = pCache->ImgHeight; // the height of the image matrix

    DWORD cols = pCache->ImgWidth; // the width of the image matrix

    DWORD M = pCache->LineBytes, N = 3;

    DWORD hist[256], eq_hist[256], gray; // temp histogram hist[256], the result of the histogram equalization eq_hist[256]

    double density_hist[256], temp[256];

    DWORD size = cols * rows;

    for (int i = 0; i < 256; i++) // initialization
    {
        hist[i] = 0;

        density_hist[i] = 0;

        eq_hist[i] = 0;
    }

    for (int i = 0; i < rows; i++) // traverse to generate the histogram
    {
        for (int j = 0; j < cols; j++)
        {
            gray = pImg->pImgInfo[i * M + N * j];

            hist[gray]++;
        }
    }

    for (int i = 0; i < 256; i++) // 0~255 -> 0~1
    {
        density_hist[i] = (double)hist[i] / (double)size;
    }

    for (int i = 0; i < 256; i++) // generating the accumulated density
    {
        if (i == 0)
            temp[i] = density_hist[i];
        else
            temp[i] = temp[i - 1] + density_hist[i];
    }

    for (int i = 0; i < 256; i++)

        eq_hist[i] = (BYTE)(255.0 * temp[i] + 0.5); // transform the Cumulative Distribution to integers between 0~255

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            pImg->pImgInfo[i * M + N * j] = (WORD)eq_hist[pImg->pImgInfo[i * M + N * j]];

            pImg->pImgInfo[i * M + N * j + 1] = (WORD)eq_hist[pImg->pImgInfo[i * M + N * j + 1]];

            pImg->pImgInfo[i * M + N * j + 2] = (WORD)eq_hist[pImg->pImgInfo[i * M + N * j + 2]];
        }
    }
}