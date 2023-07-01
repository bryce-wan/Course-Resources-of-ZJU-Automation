#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include "bmp.h"

BMP Img;

CACHE Cache;

BYTE otsu(BMP *pImg, CACHE *pCache);

void Binarize(BMP *pImg, CACHE *pCache, BYTE threshold);

int main()
{

    BYTE best_threshold = 0;

    Img.bf = (BITMAPFILEHEADER *)malloc(sizeof(BITMAPFILEHEADER));

    Img.bi = (BITMAPINFOHEADER *)malloc(sizeof(BITMAPINFOHEADER));

    Img.pRGB = NULL;

    Img.pImgInfo = NULL;

    char *filename = "img\\gray.bmp";

    char *binary_filename = "img\\binary.bmp";

    readBMP(filename, &Img, &Cache);

    best_threshold = otsu(&Img, &Cache);

    Binarize(&Img, &Cache, best_threshold);

    writeBMP(binary_filename, &Img, &Cache);

    system(binary_filename);

    system("pause");
}

BYTE otsu(BMP *pImg, CACHE *pCache)
{
    int i, j;

    int threshold = 0, hist[256];

    int pixel_cnt = pCache->ImgHeight * pCache->ImgWidth;

    double var = .0, max_var = .0;

    double u0 = .0, u1 = .0, w0 = .0, w1 = .0;

    int N0 = 0, N1 = 0;

    for (i = 0; i < 256; i++)

        hist[i] = 0;

    for (int i = 0; i < pCache->ImgSize; i += pCache->LineBytes)
    {

        for (int j = 0; j < pCache->ImgWidth * 3; j += 3)
        {

            hist[pImg->pImgInfo[i + j]]++;
        }
    }

    for (i = 0; i < 256; i++)
    {
        N0 = 0;

        for (j = 0; j < i; j++)
        {

            N0 += hist[j];
        }

        w0 = N0 * 1.0 / pixel_cnt;

        for (j = 0; j < i; j++)
        {

            if (N0 == 0)
            {
                u0 = 0;
            }

            else
            {

                u0 += hist[j] * j * 1.0 / N0;
            }
        }

        N1 = pixel_cnt - N0;

        w1 = 1 - w0;

        for (j = i; j < 256; j++)
        {

            if (N1 == 0)
            {
                u1 = 0;
            }

            else
            {
                u1 += hist[j] * j * 1.0 / N1;
            }
        }

        var = w0 * w1 * (u0 - u1) * (u0 - u1);

        if (var >= max_var)

        {

            max_var = var;

            threshold = i;
        }
    }

    return threshold;
}

void Binarize(BMP *pImg, CACHE *pCache, BYTE threshold)
{
    BYTE gray;

    if (0 == pCache->IsPalette)

    {
        for (int i = 0; i < pCache->ImgSize; i += pCache->LineBytes)
        {
            for (int j = 0; j < pCache->ImgWidth * 3; j += 3)
            {
                gray = pImg->pImgInfo[i + j];

                if (gray < threshold)
                    gray = 0;
                else
                    gray = 255;

                pImg->pImgInfo[i + j] = gray;
                pImg->pImgInfo[i + j + 1] = gray;
                pImg->pImgInfo[i + j + 2] = gray;
            }
        }
    }

    else if (1 == pCache->IsPalette)

    {
        for (int i = 0; i < pCache->NumColors; i += 1)
        {

            gray = pImg->pRGB[i].rgbBlue;

            if (gray < threshold)
                gray = 0;
            else
                gray = 255;

            pImg->pRGB[i].rgbBlue = gray;
            pImg->pRGB[i].rgbGreen = gray;
            pImg->pRGB[i].rgbRed = gray;
        }
    }
}
