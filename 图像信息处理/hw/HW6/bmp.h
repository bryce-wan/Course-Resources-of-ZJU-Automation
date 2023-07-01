#define WIDTH(i) ((i * 3 + 3) / 4 * 4)
#define FALSE -1

typedef unsigned char BYTE;
typedef int BOOL;
typedef unsigned short WORD;
typedef unsigned long DWORD;
typedef long LONG;

typedef struct tagBITMAPFILEHEADER
{
    // WORD bfType; //由于此处加入bfType项后会导致后续sizeof计算发生错误，因而略去，在读写bmp时候单独进行操作。
    DWORD bfSize;
    WORD bfReserved1;
    WORD bfReserved2;
    DWORD bfOffBits;
} BITMAPFILEHEADER; //定义bmp fileheader

typedef struct tagBITMAPINFOHEADER
{
    DWORD biSize;
    LONG biWidth;
    LONG biHeight;
    WORD biPlanes;
    WORD biBitCount;
    DWORD biCompression;
    DWORD biSizeImage;
    LONG biXPelsPerMeter;
    LONG biYPelsPerMeter;
    DWORD biClrUsed;
    DWORD biClrImportant;
} BITMAPINFOHEADER; //定义 bmp infoheader

typedef struct tagRGBQUAD
{
    BYTE rgbBlue;
    BYTE rgbGreen;
    BYTE rgbRed;
    BYTE rgbReserved;
} RGBQUAD; //定义调色板

typedef struct BMPFILE
{
    BITMAPFILEHEADER *bf;
    BITMAPINFOHEADER *bi;
    RGBQUAD *pRGB;
    BYTE *pImgInfo;
} BMP; //将bmp四部分集成，定义bmp文件结构体，储存

typedef struct INFOCACHE
{
    BOOL IsPalette;            //是否存在调色板
    DWORD ImgWidth, ImgHeight; //图像的宽度和高度
    DWORD NumColors;           //图像使用的颜色数目，对于没有调色板的图像该值为0
    DWORD LineBytes;           //每行存储所占用字节数
    DWORD ImgSize;             //实际位图信息存储占用字节数
} CACHE;                       // CACHE暂存图像的某些有关信息，供后续处理时读取调用

// BOOL readBMP(char *filename, BMP *pImg, CACHE *pCache)
// filename:目标文件名
// pImg：指向储存bmp图像本身信息的结构体的指针
// pCache：指向暂存图像部分计算后所得信息的结构体的指针

BOOL readBMP(char *filename, BMP *pImg, CACHE *pCache)
{
    FILE *fp;
    BOOL IsPalette;
    DWORD ImgWidth, ImgHeight;
    DWORD NumColors;
    DWORD LineBytes;
    DWORD ImgSize;

    fp = fopen(filename, "rb"); // 打开文件

    if (NULL == fp)
    {
        printf("\nFailed to open the bmp file.\n");

        return -1;
    }

    else
    {
        printf("\nThe file is opened successfully.\n");
    }

    WORD bfType;

    fread(&bfType, 1, sizeof(WORD), fp); //就像上面所说的，为防止sizeof错误，对bfType单独进行读取

    fread(pImg->bf, 1, sizeof(BITMAPFILEHEADER), fp); // 读取位图文件头

    fread(pImg->bi, 1, sizeof(BITMAPINFOHEADER), fp); //读取位图信息头

    if (bfType == 0x4d42) //根据bfType检查是否为bmp文件

    {
        printf("\nSuccessful to read the bmp file.\n");
    }

    else

    {
        printf("\nThe file is not a .bmp file.\n");
    }

    if (pImg->bi->biClrUsed != 0) //如果是真彩色图

        NumColors = (DWORD)pImg->bi->biClrUsed;

    else //不是真彩色图的话，根据biBitCount的值进行计算，得到使用色彩数

        switch (pImg->bi->biBitCount)

        {

        case 1:

            NumColors = 2;

            IsPalette = 1;

            break;

        case 4:

            NumColors = 16;

            IsPalette = 1;

            break;

        case 8:

            NumColors = 256;

            IsPalette = 1;

            break;

        case 24:

            NumColors = 0;

            IsPalette = 0;

            break;

        default:

            return -1;
        }

    if (IsPalette) //如果存在调色板，则申请空间进行储存

    {

        pImg->pRGB = (RGBQUAD *)malloc(NumColors * sizeof(RGBQUAD));

        int NumPalette = fread(pImg->pRGB, 4, NumColors, fp);
    }

    ImgHeight = pImg->bi->biHeight;

    ImgWidth = pImg->bi->biWidth;

    LineBytes = (DWORD)WIDTH(pImg->bi->biWidth); //计算每行所占字节数

    ImgSize = (DWORD)LineBytes * (pImg->bi->biHeight); //计算位图信息实际所占字节数

    pImg->pImgInfo = (BYTE *)malloc(ImgHeight * LineBytes); //储存位图数据信息

    fread(pImg->pImgInfo, 1, ImgSize, fp);

    fclose(fp);

    //将计算所得信息进行储存，方便后续使用
    pCache->ImgHeight = ImgHeight;
    pCache->ImgWidth = ImgWidth;
    pCache->ImgSize = ImgSize;
    pCache->IsPalette = IsPalette;
    pCache->NumColors = NumColors;
    pCache->LineBytes = LineBytes;
}

// BOOL writeBMP(char *filename, BMP *pImg, CACHE *pCache)
// filename：指定写入的文件名
//  pImg：指向储存bmp图像本身信息的结构体的指针
//  pCache：指向暂存图像部分计算后所得信息的结构体的指针

BOOL writeBMP(char *filename, BMP *pImg, CACHE *pCache)
{
    FILE *fp = fopen(filename, "wb");

    fprintf(fp, "BM"); //将bfType单独写入

    fwrite(pImg->bf, sizeof(BITMAPFILEHEADER), 1, fp); // 写入位图文件头

    fwrite(pImg->bi, sizeof(BITMAPINFOHEADER), 1, fp); //写入文件信息头

    fwrite(pImg->pRGB, 4, pCache->NumColors, fp); //写入调色板

    fwrite(pImg->pImgInfo, 1, pCache->ImgSize, fp); //写入位图数据

    fclose(fp);
}