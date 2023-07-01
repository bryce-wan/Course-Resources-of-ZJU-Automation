#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include "bmp.h"

void YUV_to_RGB(BMP *pImg, CACHE *pCache);

BMP Img;

CACHE Cache;

int main()
{

    Img.bf = (BITMAPFILEHEADER *)malloc(sizeof(BITMAPFILEHEADER));

    Img.bi = (BITMAPINFOHEADER *)malloc(sizeof(BITMAPINFOHEADER));

    Img.pRGB = NULL;

    Img.pImgInfo = NULL;

    char *YUV_filename = "img\\yuv24.bmp";

    char *RGB_filename = "img\\rgb24_new.bmp";

    readBMP(YUV_filename, &Img, &Cache);

    YUV_to_RGB(&Img, &Cache);

    writeBMP(RGB_filename, &Img, &Cache);

    // system(YUV_filename);

    system(RGB_filename);

    system("pause");
}

void YUV_to_RGB(BMP *pImg, CACHE *pCache)
{
    BYTE R, B, G, Y, U, V;

    if (0 == pCache->IsPalette)

    {
        for (int i = 0; i < pCache->ImgSize; i += pCache->LineBytes)
        {
            for (int j = 0; j < pCache->ImgWidth * 3; j += 3)
            {
                Y = pImg->pImgInfo[i + j];
                U = pImg->pImgInfo[i + j + 1];
                V = pImg->pImgInfo[i + j + 2];

                // R = 1 * Y - 0 * (U - 128) + 1.4020 * (V - 128);
                // G = 1 * Y - 0.3441 * (U - 128) - 0.7139 * (V - 128);
                // B = 1 * Y - 1.7718 * (U - 128) - 0.0013 * (V - 128);

                R = Y + ((360 * (V - 128)) >> 8);
                G = Y - (((88 * (U - 128) + 184 * (V - 128))) >> 8);
                B = Y + ((455 * (U - 128)) >> 8);

                pImg->pImgInfo[i + j] = B;
                pImg->pImgInfo[i + j + 1] = G;
                pImg->pImgInfo[i + j + 2] = R;
            }
        }
    }

    else if (1 == pCache->IsPalette)

    {
        for (int i = 0; i < pCache->NumColors; i += 1)
        {

            Y = pImg->pRGB[i].rgbBlue;
            U = pImg->pRGB[i].rgbGreen;
            V = pImg->pRGB[i].rgbRed;

            // R = 1.0000 * Y - 0.0000 * (U - 128) + 1.4020 * (V - 128);
            // G = 1.0000 * Y - 0.3441 * (U - 128) - 0.7139 * (V - 128);
            // B = 1.0000 * Y - 1.7718 * (U - 128) - 0.0013 * (V - 128);

            R = Y + ((360 * (V - 128)) >> 8);
            G = Y - (((88 * (U - 128) + 184 * (V - 128))) >> 8);
            B = Y + ((455 * (U - 128)) >> 8);

            pImg->pRGB[i].rgbBlue = B;
            pImg->pRGB[i].rgbGreen = G;
            pImg->pRGB[i].rgbRed = R;
        }
    }
}
