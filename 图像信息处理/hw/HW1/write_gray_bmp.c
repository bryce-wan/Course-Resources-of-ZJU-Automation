#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include "bmp.h"

void Color_to_Gray(BMP *pImg, CACHE *pCache);

BMP Img;

CACHE Cache;

int main()
{

    Img.bf = (BITMAPFILEHEADER *)malloc(sizeof(BITMAPFILEHEADER));

    Img.bi = (BITMAPINFOHEADER *)malloc(sizeof(BITMAPINFOHEADER));

    Img.pRGB = NULL;

    Img.pImgInfo = NULL;

    char *color_filename = "img\\rgb24.bmp";

    char *gray_filename = "img\\gray24.bmp";

    readBMP(color_filename, &Img, &Cache);

    Color_to_Gray(&Img, &Cache);

    writeBMP(gray_filename, &Img, &Cache);

    // system(color_filename);

    system(gray_filename);

    system("pause");
}

void Color_to_Gray(BMP *pImg, CACHE *pCache)
{
    BYTE R, B, G, Y, U, V;
    BYTE gray;

    if (0 == pCache->IsPalette)

    {
        for (int i = 0; i < pCache->ImgSize; i += pCache->LineBytes)
        {
            for (int j = 0; j < pCache->ImgWidth * 3; j += 3)
            {
                B = pImg->pImgInfo[i + j];
                G = pImg->pImgInfo[i + j + 1];
                R = pImg->pImgInfo[i + j + 2];

                gray = Y = 0.299 * R + 0.587 * G + 0.114 * B;
                // U = -0.1684 * R - 0.3316 * G + 0.5 * B + 128;
                // V = 0.5 * R - 0.4187 * G - 0.0813 * B + 128;

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

            B = pImg->pRGB[i].rgbBlue;
            G = pImg->pRGB[i].rgbGreen;
            R = pImg->pRGB[i].rgbRed;

            gray = Y = 0.299 * B + 0.587 * G + 0.114 * B;
            // U = -0.1684 * R - 0.3316 * G + 0.5 * B + 128;
            // V = 0.5 * R - 0.4187 * G - 0.0813 * B + 128;

            pImg->pRGB[i].rgbBlue = gray;
            pImg->pRGB[i].rgbGreen = gray;
            pImg->pRGB[i].rgbRed = gray;
        }
    }
}
