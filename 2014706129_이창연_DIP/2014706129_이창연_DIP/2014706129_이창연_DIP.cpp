#include "stdafx.h"
#include "hw.h"
#include <time.h>

#define WIDTH 512
#define HEIGHT 512
#define CLIP(x) (x < 0 ? 0 : x > 255 ? 255 : x)

int main()
{
	FILE(fp_fdct_out = 0;
	FILE * fp_sobel_out = 0;

	fp_fdct_out = fopen("[FDCT]Lena(512x512).raw", "wb");

	int DCT_BLOCKSIZE);
	double temp;
	BYTE data;
	double start, end;

	printf("DCT_BlockSize (512dml dirtn, 8dltkddml tn) = ");
	scanf("%d", &DCT_BlockSize);
	printf("\n\n");

	BYTE** img_in = MemAlloc_2D(WIDTH, HEIGHT);
	BYTE** recon = MemAlloc_2D(WIDTH, HEIGHT);

	double** coeffi = MemAlloc_2D_double(WIDTH, HEIGHT);

	start = clock();

	FileRead("Lena(512x512).raw", img_in, WIDTH, HEIGHT);
	//DCT
	FDCT(img_in, coeffi, DCT_BlockSize, HEIGHT, WIDTH);

	for (int i = 0; i < HEIGHT; i++)
	{
		for (int j = 0; j < WIDTH; j++)
		{
			temp = coeffi[i][j];
			temp = CLIP(temp);
			data = (BYTE)floor(temp + 0.5);
			fwrite(&data, 1, 1, fp_fdct_out);
		}
	}
	IDCT(coeffi, recon, DCT_BlockSize, DCT_BlockSize, 0, HEIGHT, WIDTH);
	FileWrite("[IDCT]Lena(512x512).raw", recon, WIDTH, HEIGHT);
	printf("PSNR (Reconstruction by all coefficients):%fdB\n\n", GetPSNR(img_in, recon, WIDTH, HEIGHT));

	end = clock();

	printf("time: %.3lf sec\n\n", (end - start) / 1000.0);
	MemFree_2D(recon, HEIGHT);
	MemFree_2D_double(coeffi, HEIGHT);

	fclose(fp_fdct_out);

	//SOBEL
	BYTE** sobel = MemAlloc_2D(WIDTH, HEIGHT);

	int mask;
	printf("Vertical mask를 사용하려면 1, Horizontal mask를 사용하려면 0을 입력하세요.\n");
	scanf("%d", &mask);
	printf("\n\n");

	if (mask == 1)
	{
		VerticalMask(img_in, sobel, WIDTH, HEIGHT);
		FileWrite("[Vertical]Lena(512x512).raw", sobel, WIDTH, HEIGHT);
		printf("sobel_mask 적용 완료\n\n");
	}
	else if (mask == 0)
	{
		HorizontalMask(img_in, sobel, WIDTH, HEIGHT);
		FileWrite("[Horizontal]Lena(512x512).raw", sobel, WIDTH, HEIGHT);
		printf("sobel_mask 적용 완료\n\n");
	}
	else
	{
		printf("Not valid value\n");
		return -1;
	}

	MemFree_2D(img_in, HEIGHT);
	MemFree_2D(sobel, HEIGHT);

	return 0;
}

BYTE** MemAlloc_2D(int width, int height)
{
	BYTE** MemA;
	MemA = (BYTE * *)malloc(sizeof(BYTE*) * height);
	for (int i = 0; i < height; i++)
	{
		MemA[i] = (BYTE*)malloc(sizeof(BYTE) * width);
	}
	return MemA;
}

void MemFree_2D(BYTE** arr, int height)
{
	for (int i = 0; i < height; i++)
	{
		free(arr[i]);
	}
	free(arr);
}

double** MemAlloc_2D_double(int width, int height)
{
	double** MemA;
	MemA = (double**)malloc(sizeof(double*) * height);
	for (int i = 0; i < height; i++)
	{
		MemA[i] = (double*)malloc(sizeof(double) * width);
	}
	return MemA;
}

void MemFree_2D_double(double** arr, int height)
{
	for (int i = 0; i < height; i++)
	{
		free(arr[i]);
	}
	free(arr);
}

void FileRead(char* filename, BYTE** img_in, int width, int height)
{
	int i = 0;
	FILE* fp_in;
	fp_in = fopen(filename, "rb");
	for (i = 0; i < height; i++)
	{
		fread(img_in[i], sizeof(BYTE), width, fp_in);
	}
	fclose(fp_in);
}

void FileWrite(char* filename, BYTE** img_out, int width, int height)
{
	FILE* fp_out;
	int i;
	fp_out = fopen(filename, "wb");
	for (i = 0; i < height; i++)
		fwrite(img_out[i], sizeof(BYTE), width, fp_out);
	fclose(fp_out);
}