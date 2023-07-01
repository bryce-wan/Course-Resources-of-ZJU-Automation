#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include "bmp.h"

void Luminance(BMP *pImg, CACHE *pCache, int regulation);

BMP Img;

CACHE Cache;

int regulation;

int main()
{

    Img.bf = (BITMAPFILEHEADER *)malloc(sizeof(BITMAPFILEHEADER));

    Img.bi = (BITMAPINFOHEADER *)malloc(sizeof(BITMAPINFOHEADER));

    Img.pRGB = NULL;

    Img.pImgInfo = NULL;

    char *filename = "img\\gray24.bmp";

    char *high_filename = "img\\high_luminance.bmp";

    char *low_filename = "img\\low_luminance.bmp";

    readBMP(filename, &Img, &Cache);

    regulation = 100;

    Luminance(&Img, &Cache, regulation);

    writeBMP(high_filename, &Img, &Cache);

    readBMP(filename, &Img, &Cache);

    regulation = -100;

    Luminance(&Img, &Cache, regulation);

    writeBMP(low_filename, &Img, &Cache);

    system(high_filename);

    system(low_filename);

    system("pause");
}

void Luminance(BMP *pImg, CACHE *pCache, int regualtion)
{
    int R, B, G, Y, U, V;

    if (0 == pCache->IsPalette)

    {
        for (int i = 0; i < pCache->ImgSize; i += pCache->LineBytes)
        {
            for (int j = 0; j < pCache->ImgWidth * 3; j += 3)
            {

                Y = pImg->pImgInfo[i + j]; //读取Y，因接受的图片是灰度图所以随便读取一个通道

                if (((Y + regualtion) <= 255) && ((Y + regualtion) >= 0)) //保证位于0到255之间
                    Y = (Y + regualtion);
                else if ((Y + regualtion) > 255)
                    Y = 255;
                else if (((Y + regualtion) < 0))
                    Y = 0;

                pImg->pImgInfo[i + j] = (BYTE)Y;
                pImg->pImgInfo[i + j + 1] = (BYTE)Y;
                pImg->pImgInfo[i + j + 2] = (BYTE)Y;
            }
        }
    }

    else if (1 == pCache->IsPalette)

    {
        for (int i = 0; i < pCache->NumColors; i += 1)
        {

            Y = pImg->pRGB[i].rgbBlue;

            if (((Y + regualtion) <= 255) && ((Y + regualtion) >= 0)) //保证位于0到255之间
                Y = (Y + regualtion);
            else if ((Y + regualtion) > 255)
                Y = 255;
            else if (((Y + regualtion) < 0))
                Y = 0;

            pImg->pRGB[i].rgbBlue = (BYTE)Y;
            pImg->pRGB[i].rgbGreen = (BYTE)Y;
            pImg->pRGB[i].rgbRed = (BYTE)Y;
        }
    }
}