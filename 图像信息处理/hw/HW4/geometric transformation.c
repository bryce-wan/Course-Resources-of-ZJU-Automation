#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include "bmp.h"
#include <math.h>

#define PI 3.1415926

BMP Img;

CACHE Cache;

void Trans(BMP *pImg, CACHE *pCache, int xOffset, int yOffset);

void Rotate(BMP *pImg, CACHE *pCache, double angle);

void Mirror(BMP *pImg, CACHE *pCache, int direction);

void Scale(BMP *pImg, CACHE *pCache, double x_ratio, double y_ratio);

void Shear(BMP *pImg, CACHE *pCache, int direction, double ratio);

int Max(double a, double b)
{
    return a > b ? a : b;
}

int main()
{

    Img.bf = (BITMAPFILEHEADER *)malloc(sizeof(BITMAPFILEHEADER));

    Img.bi = (BITMAPINFOHEADER *)malloc(sizeof(BITMAPINFOHEADER));

    Img.pRGB = NULL;

    Img.pImgInfo = NULL;

    char *src_filename = "img\\lena.bmp";

    readBMP(src_filename, &Img, &Cache);

    int command;

    printf("��ѡ��Ҫ���еļ��α任(�������):\n");
    printf("1->Translation\n");
    printf("2->Rotation\n");
    printf("3->Scale\n");
    printf("4->Shear\n");
    printf("5->Mirror\n");

    scanf("%d", &command);

    char *obj_filename;

    switch (command)
    {

    case 1:
    {
        int xOffset, yOffset;

        printf("��������x�᷽���λ����(������Ϊ��λ):\n");

        scanf("%d", &xOffset);

        printf("��������y�᷽���λ����(������Ϊ��λ):\n");

        scanf("%d", &yOffset);

        Trans(&Img, &Cache, xOffset, yOffset);

        obj_filename = "img\\translation.bmp";

        break;
    }

    case 2:
    {
        double angle;

        printf("������˳ʱ����ת�ĽǶ�(�Ƕ�ֵ���ǻ�����):\n");

        scanf("%lf", &angle);

        angle = angle * (PI) / 180;

        Rotate(&Img, &Cache, angle);

        obj_filename = "img\\rotation.bmp";

        break;
    }

    case 3:
    {
        double x_ratio, y_ratio;

        printf("������x�᷽��(ˮƽ����)�����ű���:\n");

        scanf("%lf", &x_ratio);

        printf("������y�᷽��(��ֱ����)�����ű���:\n");

        scanf("%lf", &y_ratio);

        Scale(&Img, &Cache, x_ratio, y_ratio);

        obj_filename = "img\\scale.bmp";

        break;
    }

    case 4:
    {
        int direction;

        printf("��ѡ����еķ���(�������):\n");
        printf("0->��x�᷽�����\n");
        printf("1->��y�᷽�����\n");

        scanf("%d", &direction);

        if ((direction != 0) && (direction != 1))
        {
            printf("Error Commands\n");

            return;
        }

        double ratio;

        printf("��������еı���:\n");

        scanf("%lf", &ratio);

        Shear(&Img, &Cache, direction, ratio);

        obj_filename = "img\\shear.bmp";

        break;
    }

    case 5:
    {
        int direction;

        printf("��ѡ����ת�ķ���(�������):\n");
        printf("0->��x��Ϊ�Գ��᾵��ת\n");
        printf("1->��y��Ϊ�Գ��᾵��ת\n");

        scanf("%d", &direction);

        if ((direction != 0) && (direction != 1))
        {
            printf("Error Commands\n");

            return;
        }

        Mirror(&Img, &Cache, direction);

        obj_filename = "img\\mirror.bmp";

        break;
    }

    default:
    {
        printf("Error Commands\n");

        break;
    }
    }

    writeBMP(obj_filename, &Img, &Cache);

    system(obj_filename);

    // system("pause");
}

void Trans(BMP *pImg, CACHE *pCache, int xOffset, int yOffset)
{
    DWORD height = pCache->ImgHeight; // the height of the iamge matrix

    DWORD width = pCache->ImgWidth; // the width of the image matrix

    DWORD M = pCache->LineBytes, N = 3;

    BYTE *Temp = (BYTE *)malloc(pCache->ImgSize * sizeof(BYTE));

    memcpy((char *)Temp, (BYTE *)pImg->pImgInfo, pCache->ImgSize * sizeof(BYTE));

    memset(pImg->pImgInfo, 255, pCache->ImgSize);

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width * N; j++)
        {
            if (((i + yOffset) < pCache->ImgHeight) && ((j + xOffset * N) < pCache->ImgWidth * N))
            {
                pImg->pImgInfo[(i + yOffset) * M + j + xOffset * N] = Temp[i * M + j];

                pImg->pImgInfo[(i + yOffset) * M + j + xOffset * N + 1] = Temp[i * M + j];

                pImg->pImgInfo[(i + yOffset) * M + j + xOffset * N + 2] = Temp[i * M + j];
            }
        }
    }
}

void Rotate(BMP *pImg, CACHE *pCache, double angle)
{
    DWORD height = pCache->ImgHeight; // the height of the iamge matrix

    DWORD width = pCache->ImgWidth; // the width of the image matrix

    DWORD M = pCache->LineBytes, N = 3;

    BYTE *Temp = (BYTE *)malloc(pCache->ImgSize * sizeof(BYTE));

    memcpy((BYTE *)Temp, (BYTE *)pImg->pImgInfo, pCache->ImgSize * sizeof(BYTE));

    double cosa = cos(angle), sina = sin(angle);

    double x_1 = -width * cosa + height * sina, y_1 = width * sina + height * cosa;
    double x_2 = width * cosa + height * sina, y_2 = -width * sina + height * cosa;
    double x_3 = -width * cosa - height * sina, y_3 = width * sina - height * cosa;
    double x_4 = width * cosa - height * sina, y_4 = -width * sina - height * cosa;

    int width_new = (int)(sqrt(height * height + width * width));

    int height_new = (int)(sqrt(height * height + width * width));

    DWORD LineBytes_new = (DWORD)WIDTH(width_new);

    pImg->bi->biWidth = width_new;

    pImg->bi->biHeight = height_new;

    pImg->bi->biSizeImage = height_new * LineBytes_new * sizeof(BYTE);

    pImg->bf->bfSize = 54 + height_new * LineBytes_new * sizeof(BYTE);

    pImg->pImgInfo = (BYTE *)realloc(pImg->pImgInfo, height_new * LineBytes_new * sizeof(BYTE));

    memset(pImg->pImgInfo, 255, height_new * LineBytes_new * sizeof(BYTE));

    double const1 = -width_new * cosa / 2.0 + height_new * sina / 2.0 + width / 2.0;

    double const2 = -width_new * sina / 2.0 - height_new * cosa / 2.0 + height / 2.0;

    int x0, y0;

    for (int i = 0; i < height_new; i++)
    {
        for (int j = 0; j < width_new; j++)
        {

            x0 = (int)(j * cosa - i * sina + const1 + 0.5);

            y0 = (int)(j * sina + i * cosa + const2 + 0.5);

            if (x0 >= 0 && x0 < width && y0 >= 0 && y0 < height)
            {
                pImg->pImgInfo[LineBytes_new * i + j * N] = Temp[y0 * M + x0 * N];

                pImg->pImgInfo[LineBytes_new * i + j * N + 1] = Temp[y0 * M + x0 * N + 1];

                pImg->pImgInfo[LineBytes_new * i + j * N + 2] = Temp[y0 * M + x0 * N + 2];
            }
        }
    }
}

void Mirror(BMP *pImg, CACHE *pCache, int direction)
{
    DWORD height = pCache->ImgHeight; // the height of the iamge matrix

    DWORD width = pCache->ImgWidth; // the width of the image matrix

    DWORD M = pCache->LineBytes, N = 3;

    BYTE *Temp = (BYTE *)malloc(pCache->ImgSize * sizeof(BYTE));

    memcpy((char *)Temp, (BYTE *)pImg->pImgInfo, pCache->ImgSize * sizeof(BYTE));

    memset(pImg->pImgInfo, 255, pCache->ImgSize);

    if (direction == 0)
    {
        for (int i = 0; i < height; i++)
        {
            for (int j = 0; j < width * N; j++)
            {
                pImg->pImgInfo[M * i + j] = Temp[M * (height - 1 - i) + j];
            }
        }
    }

    else if (direction == 1)
    {
        for (int i = 0; i < height; i++)
        {
            for (int j = 0; j < width; j++)
            {
                pImg->pImgInfo[M * i + j * N] = Temp[M * i + (width - j) * N];

                pImg->pImgInfo[M * i + j * N + 1] = Temp[M * i + (width - j) * N + 1];

                pImg->pImgInfo[M * i + j * N + 2] = Temp[M * i + (width - j) * N + 2];
            }
        }
    }
}

void Scale(BMP *pImg, CACHE *pCache, double x_ratio, double y_ratio)
{
    DWORD height = pCache->ImgHeight; // the height of the iamge matrix

    DWORD width = pCache->ImgWidth; // the width of the image matrix

    DWORD M = pCache->LineBytes, N = 3;

    BYTE *Temp = (BYTE *)malloc(pCache->ImgSize * sizeof(BYTE));

    memcpy((BYTE *)Temp, (BYTE *)pImg->pImgInfo, pCache->ImgSize * sizeof(BYTE));

    DWORD width_new = (DWORD)(width * x_ratio + 0.5), height_new = (DWORD)(height * y_ratio + 0.5);

    DWORD LineBytes_new = (DWORD)WIDTH(width_new);

    pImg->bi->biWidth = width_new;

    pImg->bi->biHeight = height_new;

    pImg->bi->biSizeImage = height_new * LineBytes_new * sizeof(BYTE);

    pImg->bf->bfSize = 54 + height_new * LineBytes_new * sizeof(BYTE);

    pImg->pImgInfo = (BYTE *)realloc(pImg->pImgInfo, height_new * LineBytes_new * sizeof(BYTE));

    memset(pImg->pImgInfo, 255, height_new * LineBytes_new * sizeof(BYTE));

    int x0, y0;

    for (int i = 0; i < height_new; i++)
    {
        for (int j = 0; j < width_new; j++)
        {
            x0 = (int)(j / x_ratio);

            y0 = (int)(i / y_ratio);

            if (x0 >= 0 && x0 < width && y0 >= 0 && y0 < height)

            {
                pImg->pImgInfo[LineBytes_new * i + j * N] = Temp[y0 * M + x0 * N];

                pImg->pImgInfo[LineBytes_new * i + j * N + 1] = Temp[y0 * M + x0 * N + 1];

                pImg->pImgInfo[LineBytes_new * i + j * N + 2] = Temp[y0 * M + x0 * N + 2];
            }
        }
    }
}

void Shear(BMP *pImg, CACHE *pCache, int direction, double ratio)
{
    DWORD height = pCache->ImgHeight; // the height of the iamge matrix

    DWORD width = pCache->ImgWidth; // the width of the image matrix

    DWORD M = pCache->LineBytes, N = 3;

    BYTE *Temp = (BYTE *)malloc(pCache->ImgSize * sizeof(BYTE));

    memcpy((BYTE *)Temp, (BYTE *)pImg->pImgInfo, pCache->ImgSize * sizeof(BYTE));

    switch (direction)
    {

    case 0:

    {
        DWORD width_new = (DWORD)(width + abs(height * ratio));

        DWORD height_new = (DWORD)(height);

        DWORD LineBytes_new = (DWORD)WIDTH(width_new);

        pImg->bi->biWidth = width_new;

        pImg->bi->biHeight = height_new;

        pImg->bi->biSizeImage = height_new * LineBytes_new * sizeof(BYTE);

        pImg->bf->bfSize = 54 + height_new * LineBytes_new * sizeof(BYTE);

        pImg->pImgInfo = (BYTE *)realloc(pImg->pImgInfo, height_new * LineBytes_new * sizeof(BYTE));

        memset(pImg->pImgInfo, 255, height_new * LineBytes_new * sizeof(BYTE));

        int x0, y0;

        for (int i = 0; i < height_new; i++)
        {
            for (int j = 0; j < width_new; j++)
            {
                x0 = ratio > 0 ? (int)(j - i * ratio) : (int)(j - i * ratio + height * ratio);

                y0 = (int)(i);

                if (x0 >= 0 && x0 < width && y0 >= 0 && y0 < height)

                {
                    pImg->pImgInfo[LineBytes_new * i + j * N] = Temp[y0 * M + x0 * N];

                    pImg->pImgInfo[LineBytes_new * i + j * N + 1] = Temp[y0 * M + x0 * N + 1];

                    pImg->pImgInfo[LineBytes_new * i + j * N + 2] = Temp[y0 * M + x0 * N + 2];
                }
            }
        }

        break;
    }

    case 1:
    {
        DWORD width_new = (DWORD)(width);

        DWORD height_new = (DWORD)(height + abs(width * ratio));

        DWORD LineBytes_new = (DWORD)WIDTH(width_new);

        pImg->bi->biWidth = width_new;

        pImg->bi->biHeight = height_new;

        pImg->bi->biSizeImage = height_new * LineBytes_new * sizeof(BYTE);

        pImg->bf->bfSize = 54 + height_new * LineBytes_new * sizeof(BYTE);

        pImg->pImgInfo = (BYTE *)realloc(pImg->pImgInfo, height_new * LineBytes_new * sizeof(BYTE));

        memset(pImg->pImgInfo, 255, height_new * LineBytes_new * sizeof(BYTE));

        int x0, y0;

        for (int i = 0; i < height_new; i++)
        {
            for (int j = 0; j < width_new; j++)
            {
                x0 = (int)(j);

                y0 = ratio > 0 ? (int)(i - j * ratio) : (int)(i - j * ratio + width * ratio);

                if (x0 >= 0 && x0 < width && y0 >= 0 && y0 < height)

                {
                    pImg->pImgInfo[LineBytes_new * i + j * N] = Temp[y0 * M + x0 * N];

                    pImg->pImgInfo[LineBytes_new * i + j * N + 1] = Temp[y0 * M + x0 * N + 1];

                    pImg->pImgInfo[LineBytes_new * i + j * N + 2] = Temp[y0 * M + x0 * N + 2];
                }
            }
        }

        break;
    }
    }
}