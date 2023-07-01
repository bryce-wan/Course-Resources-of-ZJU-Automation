#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include "bmp.h"

void RGB_to_YUV(BMP *pImg, CACHE *pCache);

BMP Img;

CACHE Cache;

int main()
{

    Img.bf = (BITMAPFILEHEADER *)malloc(sizeof(BITMAPFILEHEADER));

    Img.bi = (BITMAPINFOHEADER *)malloc(sizeof(BITMAPINFOHEADER));

    Img.pRGB = NULL;

    Img.pImgInfo = NULL;

    char *RGB_filename = "img\\rgb24.bmp";

    char *YUV_filename = "img\\yuv24.bmp";

    readBMP(RGB_filename, &Img, &Cache);

    RGB_to_YUV(&Img, &Cache);

    writeBMP(YUV_filename, &Img, &Cache);

    // system(RGB_filename);

    system(YUV_filename);

    system("pause");
}

// void RGB_to_YUV(BMP *pImg, CACHE *pCache)
//   pImg：指向储存bmp图像本身信息的结构体的指针
//   pCache：指向暂存图像部分计算后所得信息的结构体的指针
void RGB_to_YUV(BMP *pImg, CACHE *pCache)
{
    BYTE R, B, G, Y, U, V;

    if (0 == pCache->IsPalette) //针对无调色板的图像

    {
        for (int i = 0; i < pCache->ImgSize; i += pCache->LineBytes)
        {
            for (int j = 0; j < pCache->ImgWidth * 3; j += 3)
            {
                B = pImg->pImgInfo[i + j];
                G = pImg->pImgInfo[i + j + 1];
                R = pImg->pImgInfo[i + j + 2];

                // Y = 0.299 * R + 0.587 * G + 0.114 * B;
                // U = -0.1684 * R - 0.3316 * G + 0.5 * B + 128;
                // V = 0.5 * R - 0.4187 * G - 0.0813 * B + 128;

                Y = (77 * R + 150 * G + 29 * B) >> 8;
                U = ((-44 * R - 87 * G + 131 * B) >> 8) + 128;
                V = ((131 * R - 110 * G - 21 * B) >> 8) + 128;

                pImg->pImgInfo[i + j] = Y;
                pImg->pImgInfo[i + j + 1] = U;
                pImg->pImgInfo[i + j + 2] = V;
            }
        }
    }

    else if (1 == pCache->IsPalette) //针对有调色板的图像

    {
        for (int i = 0; i < pCache->NumColors; i += 1)
        {
            //读取RGB三个通道
            B = pImg->pRGB[i].rgbBlue;
            G = pImg->pRGB[i].rgbGreen;
            R = pImg->pRGB[i].rgbRed;

            // Y = 0.299 * R + 0.587 * G + 0.114 * B;
            // U = -0.1684 * R - 0.3316 * G + 0.5 * B + 128;
            // V = 0.5 * R - 0.4187 * G - 0.0813 * B + 128;

            //这里没有使用小数计算

            Y = (77 * R + 150 * G + 29 * B) >> 8;
            U = ((-44 * R - 87 * G + 131 * B) >> 8) + 128;
            V = ((131 * R - 110 * G - 21 * B) >> 8) + 128;

            //将YUV信息写入
            pImg->pRGB[i].rgbBlue = Y;
            pImg->pRGB[i].rgbGreen = U;
            pImg->pRGB[i].rgbRed = V;
        }
    }
}
