#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include "bmp.h"

void showBmpInfoHeader(BITMAPINFOHEADER *pbi);

void showBmpFileHeader(BITMAPFILEHEADER *pbf);

BMP Img;

CACHE Cache;

int main()
{

    Img.bf = (BITMAPFILEHEADER *)malloc(sizeof(BITMAPFILEHEADER));

    Img.bi = (BITMAPINFOHEADER *)malloc(sizeof(BITMAPINFOHEADER));

    Img.pRGB = NULL;

    Img.pImgInfo = NULL;

    char *filename = "img\\rgb24.bmp";

    readBMP(filename, &Img, &Cache);

    showBmpFileHeader(Img.bf); //展示位图文件头

    showBmpInfoHeader(Img.bi); //展示位图信息头

    // system(filename);

    system("pause");
}

void showBmpFileHeader(BITMAPFILEHEADER *pbf)
{
    printf("\nBmpFileHeader:\n");
    printf("bfSize: %d\n", pbf->bfSize);
    printf("bfReserved11: %d\n", pbf->bfReserved1);
    printf("bfReserved2: %d\n", pbf->bfReserved2);
    printf("bfOffBits: %d\n", pbf->bfOffBits);
}

void showBmpInfoHeader(BITMAPINFOHEADER *pbi)
{
    printf("\nBmpInfoHeader:\n");
    printf("biSize: %d\n", pbi->biSize);
    printf("biWidth: %d\n", pbi->biWidth);
    printf("biHeight: %d\n", pbi->biHeight);
    printf("biPlanes: %d\n", pbi->biPlanes);
    printf("biBitCount: %d\n", pbi->biBitCount);
    printf("biCompression: %d\n", pbi->biCompression);
    printf("biSizeImage: %d\n", pbi->biSizeImage);
    printf("biXPelsPerMeter: %d\n", pbi->biXPelsPerMeter);
    printf("biYPelsPerMeter: %d\n", pbi->biYPelsPerMeter);
    printf("biClrUsed: %d\n", pbi->biClrUsed);
    printf("biClrImportant: %d\n", pbi->biClrImportant);
}
