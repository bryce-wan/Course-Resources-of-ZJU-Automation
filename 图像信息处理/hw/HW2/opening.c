#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include "bmp.h"

BMP Img;

CACHE Cache;

void Erode(BMP *pImg, CACHE *pCache);

void Dilate(BMP *pImg, CACHE *pCache);

int main()
{
    Img.bf = (BITMAPFILEHEADER *)malloc(sizeof(BITMAPFILEHEADER));

    Img.bi = (BITMAPINFOHEADER *)malloc(sizeof(BITMAPINFOHEADER));

    Img.pRGB = NULL;

    Img.pImgInfo = NULL;

    char *filename = "img\\binary.bmp";

    char *obj_filename = "img\\opening.bmp";

    readBMP(filename, &Img, &Cache);

    Erode(&Img, &Cache);

    Dilate(&Img, &Cache);

    writeBMP(obj_filename, &Img, &Cache);

    system(obj_filename);

    filename = "test\\binary.bmp";

    obj_filename = "test\\opening.bmp";

    readBMP(filename, &Img, &Cache);

    Erode(&Img, &Cache);

    Dilate(&Img, &Cache);

    writeBMP(obj_filename, &Img, &Cache);

    system("pause");
}

void Erode(BMP *pImg, CACHE *pCache)
{

    DWORD rows = pCache->ImgHeight;

    DWORD cols = pCache->ImgWidth;

    DWORD M = pCache->LineBytes, N = 3;

    BYTE *Temp = (BYTE *)malloc(pCache->ImgSize * sizeof(BYTE));

    memcpy((char *)Temp, (BYTE *)pImg->pImgInfo, pCache->ImgSize * sizeof(BYTE));

    for (int i = 1; i < rows - 1; i++)
    {
        for (int j = 1; j < cols - 1; j++)
        {
            int flag = 1;

            for (int m = i - 1; m < i + 2; m++)
            {
                for (int n = j - 1; n < j + 2; n++)
                {
                    if (Temp[m * M + n * N] == 0)
                    {
                        flag = 0;

                        break;
                    }
                }
            }

            if (flag == 1)
            {
                pImg->pImgInfo[i * M + j * N] = 255;

                pImg->pImgInfo[i * M + j * N + 1] = 255;

                pImg->pImgInfo[i * M + j * N + 2] = 255;
            }

            else if (flag == 0)
            {
                pImg->pImgInfo[i * M + j * N] = 0;

                pImg->pImgInfo[i * M + j * N + 1] = 0;

                pImg->pImgInfo[i * M + j * N + 2] = 0;
            }
        }
    }
}

void Dilate(BMP *pImg, CACHE *pCache)
{

    DWORD rows = pCache->ImgHeight;

    DWORD cols = pCache->ImgWidth;

    DWORD M = pCache->LineBytes, N = 3;

    BYTE *Temp = (BYTE *)malloc(pCache->ImgSize * sizeof(BYTE));

    memcpy((char *)Temp, (BYTE *)pImg->pImgInfo, pCache->ImgSize * sizeof(BYTE));

    for (int i = 1; i < rows - 1; i++)
    {
        for (int j = 1; j < cols - 1; j++)
        {
            int flag = 1;

            for (int m = i - 1; m < i + 2; m++)
            {
                for (int n = j - 1; n < j + 2; n++)
                {
                    if (Temp[m * M + n * N] == 255)
                    {
                        flag = 0;

                        break;
                    }
                }
            }

            if (flag == 0)
            {
                pImg->pImgInfo[i * M + j * N] = 255;

                pImg->pImgInfo[i * M + j * N + 1] = 255;

                pImg->pImgInfo[i * M + j * N + 2] = 255;
            }

            else if (flag == 1)
            {
                pImg->pImgInfo[i * M + j * N] = 0;

                pImg->pImgInfo[i * M + j * N + 1] = 0;

                pImg->pImgInfo[i * M + j * N + 2] = 0;
            }
        }
    }
}