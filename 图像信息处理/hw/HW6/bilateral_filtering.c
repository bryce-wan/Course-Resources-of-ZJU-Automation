#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include <math.h>
#include "bmp.h"

#define size 3

BMP Img;

CACHE Cache;

void BilateralFiltering(BMP *pImg, CACHE *pCache, double sigma_s, double sigma_r);

double dist(double x1, double y1, double x2, double y2);

int main()
{
    Img.bf = (BITMAPFILEHEADER *)malloc(sizeof(BITMAPFILEHEADER));

    Img.bi = (BITMAPINFOHEADER *)malloc(sizeof(BITMAPINFOHEADER));

    Img.pRGB = NULL;

    Img.pImgInfo = NULL;

    char *filename = "img\\test.bmp";

    char *obj_filename = "img\\bilateral_filtering.bmp";

    double sigma_s, sigma_r;

    printf("Please input the parameters:\n");

    printf("sigma_s: ");

    scanf("%lf", &sigma_s);

    printf("sigma_r: ");

    scanf("%lf", &sigma_r);

    readBMP(filename, &Img, &Cache);

    BilateralFiltering(&Img, &Cache, sigma_s, sigma_r);

    writeBMP(obj_filename, &Img, &Cache);

    system(obj_filename);

    system("pause");
}

double dist(double x1, double y1, double x2, double y2)
{
    return ((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}

void BilateralFiltering(BMP *pImg, CACHE *pCache, double sigma_s, double sigma_r)
{

    DWORD rows = pCache->ImgHeight;

    DWORD cols = pCache->ImgWidth;

    DWORD M = pCache->LineBytes, N = 3;

    BYTE *Temp = (BYTE *)malloc(pCache->ImgSize * sizeof(BYTE));

    memcpy((char *)Temp, (BYTE *)pImg->pImgInfo, pCache->ImgSize * sizeof(BYTE));

    double new_R = 0, new_G = 0, new_B = 0;

    double k;

    for (int i = size; i < rows - size; i++)
    {
        for (int j = size; j < cols - size; j++)
        {
            double W_p_B, W_p_G, W_p_R, W_P_B, W_P_G, W_P_R;

            W_p_B = W_p_G = W_p_R = W_P_B = W_P_G = W_P_R = 0;

            for (int m = i - size; m <= i + size; m++)
            {
                for (int n = j - size; n <= j + size; n++)
                {

                    double G_s = exp(dist(i, j, m, n) / (-2 * (sigma_s) * (sigma_s)));

                    double G_r_B = exp((Temp[i * M + j * N] - Temp[m * M + n * N]) * (Temp[i * M + j * N] - Temp[m * M + n * N]) / (-2 * (sigma_r) * (sigma_r)));

                    double G_r_G = exp((Temp[i * M + j * N + 1] - Temp[m * M + n * N + 1]) * (Temp[i * M + j * N + 1] - Temp[m * M + n * N + 1]) / (-2 * (sigma_r) * (sigma_r)));

                    double G_r_R = exp((Temp[i * M + j * N + 2] - Temp[m * M + n * N + 2]) * (Temp[i * M + j * N + 2] - Temp[m * M + n * N + 2]) / (-2 * (sigma_r) * (sigma_r)));

                    W_p_B += G_s * G_r_B;

                    W_p_G += G_s * G_r_G;

                    W_p_R += G_s * G_r_R;

                    W_P_B += G_s * G_r_B * Temp[m * M + n * N];

                    W_P_G += G_s * G_r_G * Temp[m * M + n * N + 1];

                    W_P_R += G_s * G_r_R * Temp[m * M + n * N + 2];
                }
            }

            new_B = W_P_B / W_p_B;

            new_G = W_P_G / W_p_G;

            new_R = W_P_R / W_p_R;

            pImg->pImgInfo[i * M + j * N] = (BYTE)new_B;

            pImg->pImgInfo[i * M + j * N + 1] = (BYTE)new_G;

            pImg->pImgInfo[i * M + j * N + 2] = (BYTE)new_R;

            new_R = new_G = new_B = 0;
        }
    }
}
