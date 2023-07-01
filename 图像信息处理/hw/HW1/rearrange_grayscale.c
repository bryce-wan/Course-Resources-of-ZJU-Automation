#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include "bmp.h"

void Rearrange_Grayscale(BMP *pImg, CACHE *pCache); //将灰度信息进行调整，充分利用色彩空间

BMP Img;

CACHE Cache;

int main()
{

    Img.bf = (BITMAPFILEHEADER *)malloc(sizeof(BITMAPFILEHEADER));

    Img.bi = (BITMAPINFOHEADER *)malloc(sizeof(BITMAPINFOHEADER));

    Img.pRGB = NULL;

    Img.pImgInfo = NULL;

    char *gray_filename = "img\\gray24.bmp";

    char *new_gray_filename = "img\\gray24_rescaled.bmp";

    readBMP(gray_filename, &Img, &Cache);

    Rearrange_Grayscale(&Img, &Cache);

    writeBMP(new_gray_filename, &Img, &Cache);

    system(gray_filename);

    system(new_gray_filename);

    system("pause");
}

void Rearrange_Grayscale(BMP *pImg, CACHE *pCache)
{
    BYTE R, B, G, Y, U, V;
    double gray, maxGray = 0, minGray = 255;
    BYTE rescaled_gray;

    if (0 == pCache->IsPalette) //不存在调色板时

    {
        for (int i = 0; i < pCache->ImgSize; i += pCache->LineBytes)
        {
            for (int j = 0; j < pCache->ImgWidth * 3; j += 3)
            {
                gray = pImg->pImgInfo[i + j];

                if (gray > maxGray)
                    maxGray = gray; //遍历取最大灰度值，记录

                if (gray < minGray)
                    minGray = gray; //遍历取最小灰度值，记录
            }
        }

        for (int i = 0; i < pCache->ImgSize; i += pCache->LineBytes)
        {
            for (int j = 0; j < pCache->ImgWidth * 3; j += 3)
            {
                gray = pImg->pImgInfo[i + j];

                gray = 255 * ((gray - minGray) / (maxGray - minGray)); //标准化操作，使得灰度分布到0-255之间

                rescaled_gray = (BYTE)gray;

                pImg->pImgInfo[i + j] = rescaled_gray;
                pImg->pImgInfo[i + j + 1] = rescaled_gray;
                pImg->pImgInfo[i + j + 2] = rescaled_gray;
            }
        }
    }

    else if (1 == pCache->IsPalette) //如果存在调色盘，仅针对调色盘信息进行更改

    {
        for (int i = 0; i < pCache->NumColors; i += 1)
        {
            gray = pImg->pRGB[i].rgbBlue;

            if (gray > maxGray)
                maxGray = gray;

            if (gray < minGray)
                minGray = gray;
        }

        for (int i = 0; i < pCache->NumColors; i += 1)
        {
            gray = pImg->pRGB[i].rgbBlue;

            gray = 255 * ((gray - minGray) / (maxGray - minGray));

            rescaled_gray = (BYTE)gray;

            pImg->pRGB[i].rgbBlue = 0;
            pImg->pRGB[i].rgbGreen = 0;
            pImg->pRGB[i].rgbRed = 0;
        }
    }
}
