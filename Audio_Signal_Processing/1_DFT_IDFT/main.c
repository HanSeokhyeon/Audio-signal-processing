#include <stdio.h>
#include <math.h>
#define PI 3.141592
#define N 320 // Samples, Number, Block size [samples]
#define A 16000 // Sampling rate [Hz]

int main()
{
	FILE* fi, * fo;
	int k, n, i;
	short x[N];
	double realX[N], imagX[N], normSquareX[N], realx[N];

	fopen_s(&fi, "find_dtmf.pcm", "rb"); // input
	fopen_s(&fo, "out.pcm", "wb"); // output

	for (i = 0;; i++)
	{
		if (fread(x, sizeof(short), N, fi) == NULL) break; // EOF

		for (k = 0; k < N; k++)
		{
			realX[k] = 0; // initialization
			imagX[k] = 0;
			for (n = 0; n < N; n++) // N summation
			{
				realX[k] += x[n] * cos(2 * PI / N * k * n); // DFT real value
				imagX[k] -= x[n] * sin(2 * PI / N * k * n); // DFT imaginary value
			}
		}

		for (k = 0; k < N; k++)
		{
			normSquareX[k] = realX[k] * realX[k] + imagX[k] * imagX[k]; // calculate energy
		}

		for (n = 0; n < N; n++)
		{
			realx[n] = 0; // initialization
		
			for (k = 0; k < N; k++)
			{
				realx[n] += (realX[k] * cos(2 * PI / N * k * n) - imagX[k] * sin(2 * PI / N * k * n)); // IDFT real value
			}
			realx[n] /= N; // 1/N
			x[n] = realx[n];
		}
		fwrite(x, sizeof(short), N, fo); // save
		printf("%d write \n", i + 1);
	}
	_fcloseall();
}
