#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include "bmp.h"

BMP Img;

CACHE Cache;

BYTE regulation;

int main()
{

    Img.bf = (BITMAPFILEHEADER *)malloc(sizeof(BITMAPFILEHEADER));

    Img.bi = (BITMAPINFOHEADER *)malloc(sizeof(BITMAPINFOHEADER));

    Img.pRGB = NULL;

    Img.pImgInfo = NULL;

    char *color_filename = "img\\rgb24.bmp";

    char *new_filename = "img\\written_rgb24.bmp";

    readBMP(color_filename, &Img, &Cache);

    writeBMP(new_filename, &Img, &Cache);

    system(new_filename);

    system("pause");
}
