#ifdef DLL_EXPORTS
#define DLL_decispec(dllexport)
#else
#define DLL_decispec(dllimport)
#endif

#include<stdio.h>
#include<stdlib.h>
#include<math.h>

#define PI 3.141592
typedef unsigned char BYTE;

BYTE** MemAlloc_2D(int width, int height);
void MemFree_2D(BYTE** arr, int height);
double** MemAlloc_2D_double(int width, int height);
void MemFree_2D_double(double** arr, int height);

void FileRead(char* filename, BYTE** img_in, int width, int height);
void FileWrite(char* filename, BYTE** img_out, int width, int height);

DLL float GetPSNR(BYTE** img_ori, BYTE** img_distm, int width, int height);

DLL void FDCT(BYTE** img_in, double** img_coeffi, int blocksize, int height, int width);
DLL void IDCT(double** img_coeffi, BYTE** img_recon, int blocksize, int lowFreqBlock, int highFreqBlock, int height, int width);

DLL void VerticalMask(unsigned char** img_in, unsigned char** img_out, int width, int height);
DLL void HorizontalMask(unsigned char** img_in, unsigned char** img_out, int width, int height);