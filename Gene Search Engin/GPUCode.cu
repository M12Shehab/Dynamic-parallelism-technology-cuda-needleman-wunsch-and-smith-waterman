#include <cuda.h>
#include <cuda_runtime.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include "device_launch_parameters.h"
#define MIN(x,y) ((x) < (y) ? (x) : (y))
#define MAX(x,y) ((x) > (y) ? (x) : (y))


__device__ void NW(char *Adata, char *Bdata, int slice, int z, int blen, int *NewH, int Increment, int Max)
{
	//int i = threadIdx.x;

	int y = blockIdx.y * blockDim.y + threadIdx.y;
	int x = blockIdx.x * blockDim.x + threadIdx.x;
	int i = ((gridDim.x * blockDim.x) * y) + x;

	if (i <= Max)
	{
		int match = 0;
		int mismatch = 1;

		int startIndex;
		if (z <= 0)
		{
			startIndex = slice;
		}
		else
		{
			startIndex = Increment * z + slice;
		}

		int j = startIndex + (i*Increment);

		int row = j / blen;
		int column = j % blen;

		if (row == 0 || column == 0)
		{
			return;
		}

		int score = (Adata[row - 1] == Bdata[column - 1]) ? match : mismatch;
		NewH[column + row* blen] = MIN(NewH[(column - 1) + (row - 1) * blen] + score, MIN(NewH[(column)+(row - 1) * blen] + 1, NewH[(column - 1) + (row)* blen] + 1));
	}
}

__global__ void init_rows_NW(int *NewH, int blen)
{
	int y = blockIdx.y * blockDim.y + threadIdx.y;
	int x = blockIdx.x * blockDim.x + threadIdx.x;
	int i = ((gridDim.x * blockDim.x) * y) + x;


	int row = i / blen;
	int column = i % blen;

	if (row == 0 && column>0)
	{
		NewH[column + row* blen] = i;
	}

	if (column == 0 && row>0)
	{
		NewH[column + row* blen] = row;
	}
}

__global__ void init_columns_NW(int *NewH, int blen)
{
	int y = blockIdx.y * blockDim.y + threadIdx.y;
	int x = blockIdx.x * blockDim.x + threadIdx.x;
	int i = ((gridDim.x * blockDim.x) * y) + x;


	int row = i / blen;
	int column = i % blen;

	if (column == 0 && row>0)
	{
		NewH[column + row* blen] = row;
	}
}

__global__ void StartNW(char *Adata, char *Bdata, int blen, int *NewH, int Increment, int Max)
{
	int loop1 = (blen << 1) - 1;
	for (int slice = 0; slice < loop1; ++slice)
	{
		int z = slice < blen ? 0 : slice - blen + 1;//CPU
		int size = (int)ceil((float)((slice - (z << 1)) + 1));
		NW(Adata, Bdata, slice, z, blen, NewH, Increment, Max);
	}
}

void NW_GPU(char *Adata, char *Bdata, int alen, int blen, int *NewH, clock_t &Begain, clock_t &End, clock_t &CreateBegain, clock_t &CreateEnd)
{
	int *dev_H = 0;
	char *dev_a;
	char *dev_b;
	cudaSetDevice(0);
	CreateBegain = clock();
	//Create memory allocation in GPU
	cudaMalloc((void**)&dev_H, alen * blen * sizeof(int));
	cudaMalloc((void**)&dev_a, (alen-1)  * sizeof(char));
	cudaMalloc((void**)&dev_b, (alen - 1)  * sizeof(char));
	CreateEnd = clock();

	Begain = clock();
	//Copy all arrays to GPU memory
//	cudaMemcpy(dev_H, NewH, alen * blen * sizeof(int), cudaMemcpyHostToDevice);
	cudaMemcpy(dev_a, Adata, (alen - 1)  * sizeof(char), cudaMemcpyHostToDevice);
	cudaMemcpy(dev_b, Bdata, (alen - 1)  * sizeof(char), cudaMemcpyHostToDevice);
	
	const int NumberOfThreads = 256;
	dim3 ThreadsWarp(32, 8);
	// Here run initionlize in GPU side
	
	
	init_rows_NW << <ThreadsWarp, alen >> >(dev_H, blen);
	
	//Set GPU for parallel working

	int size = (int)ceil((float)blen / (float)NumberOfThreads);
	int Increment = alen - 1;
	//begain time of GPU
	int MemSize = alen * blen;
	StartNW << <ThreadsWarp, MemSize >> >(dev_a, dev_b, alen, dev_H, Increment, size);
	cudaMemcpy(NewH, dev_H, alen * blen  * sizeof(int), cudaMemcpyDeviceToHost);
	End = clock();								//End time of GPU

	cudaFree(dev_a);
	cudaFree(dev_b);
	cudaFree(dev_H);
	cudaDeviceReset();
}

void NW_CPU(char *Adata, char *Bdata, int alen, int blen, int *NewH, clock_t &Begain, clock_t &End)
{
	int i, j;
	int inf = 9999;
	//------------------Initializing The Matricies-------------------
	int score;
	int match = 0;
	int mismatch = 1;
	
	NewH[0] = 0;
	Begain = clock();										//begain time of GPU
	
	for (i = 1; i < blen; ++i)
	{
		NewH[i] = i;
	}

	for (j = 1; j < alen; j++)
	{
		NewH[blen * j] = j;
	}

	Begain = clock();										//begain time of CPU
	for (int slice = 0; slice < 2 * alen - 1; ++slice)
	{
		int z = slice < alen ? 0 : slice - alen + 1;
		for (int j = z; j <= slice - z; ++j)
		{
			int row = j;
			int column = (slice - j);

			if (row == 0 || column == 0)
			{
				continue;
			}
			score = (Adata[row - 1] == Bdata[column - 1]) ? 0 : 1;
			NewH[(column)+row * blen] = MIN(NewH[(column - 1) + (row - 1) * blen] + score, MIN(NewH[(column)+(row - 1) * blen] + 1, NewH[(column - 1) + (row)* blen] + 1));

		}
	}

	End = clock();
}

__global__ void init_SM(int *NewH, int MAX)
{
	int y = blockIdx.y * blockDim.y + threadIdx.y;
	int x = blockIdx.x * blockDim.x + threadIdx.x;
	int i = ((gridDim.x * blockDim.x) * y) + x;

	if (i <= MAX)
	{
		if (i == 0)
		{
			NewH[0] = 0;
		}
		else
		{
			NewH[i] =0;
			NewH[MAX * i] = 0;
		}
	}
}

__device__ void SM(char *Adata, char *Bdata, int slice, int z, int blen, int *NewH, int Increment, int Max)
{
	int y = blockIdx.y * blockDim.y + threadIdx.y;
	int x = blockIdx.x * blockDim.x + threadIdx.x;
	int i = ((gridDim.x * blockDim.x) * y) + x;

	if (i <= Max)
	{
		int match = 1;
		int mismatch = -1;
		int Gap = -2;

		int startIndex;
		if (z <= 0)
		{
			startIndex = slice;
		}
		else
		{
			startIndex = Increment * z + slice;
		}

		int j = startIndex + (i*Increment);

		int row = j / blen;
		int column = j % blen;

		if (row == 0 || column == 0)
		{
			return;
		}

		int score = (Adata[row - 1] == Bdata[column - 1]) ? match : mismatch;
		NewH[column + row* blen] = MAX(NewH[(column - 1) + (row - 1) * blen] + score, MAX(NewH[(column - 1) + row * blen] + Gap, NewH[column + (row - 1) * blen] + Gap));
		if (NewH[column + row * blen] <= 0)
			{
				NewH[column + row * blen] = 0;
			}
	}
}

__global__ void StartSW(char *Adata, char *Bdata, int blen, int *NewH, int Increment, int Max)
{
	int loop1 = (blen << 1) - 1;
	for (int slice = 0; slice < loop1; ++slice)
	{
		int z = slice < blen ? 0 : slice - blen + 1;//CPU
		int size = (int)ceil((float)((slice - (z << 1)) + 1));
		SM(Adata, Bdata, slice, z, blen, NewH, Increment, Max);
	}
}
void SM_CPU(char *Adata, char *Bdata, int alen, int blen, int *NewH, clock_t &Begain, clock_t &End)
{
	int score;
	int match = 1;
	int mismatch = -1;
	int Gap = -2;
	int i, j;
	//--------Init----------
	for (i = 0; i < alen; ++i)
	{
		NewH[i] = 0;
	}

	for (j = 0; j < blen; ++j)
	{
		NewH[j*blen] = 0;
	}
	//---------------------

	Begain = clock();										//begain time of CPU
	for (int slice = 0; slice < 2 * alen - 1; ++slice)
	{
		//printf("Slice %d: \n", slice);
		int z = slice < alen ? 0 : slice - alen + 1;
		for (int j = z; j <= slice - z; ++j)
		{
			int row = j;
			int column = (slice - j);

			if (row == 0 || column == 0)
			{
				continue;
			}
			score = (Adata[row - 1] == Bdata[column - 1]) ? match : mismatch;

			NewH[column + row * blen] = MAX(NewH[(column - 1) + (row - 1) * blen] + score, MAX(NewH[(column - 1) + row * blen] + Gap, NewH[column + (row - 1) * blen] + Gap));
			if (NewH[column + row * blen] <= 0)
			{
				NewH[column + row * blen] = 0;
			}
		}
	}
	End = clock();

}

void SM_GPU(char *Adata, char *Bdata, int alen, int blen, int *NewH, clock_t &Begain, clock_t &End, clock_t &CreateBegain, clock_t &CreateEnd)
{

	int i, j;
	int inf = 9999;
	//------------------Initializing The Matricies-------------------

	int *dev_H = 0;

	char *dev_a;
	char *dev_b;
	
	cudaSetDevice(0);
	CreateBegain = clock();
	//Create memory allocation in GPU
	cudaMalloc((void**)&dev_H, alen * blen * sizeof(int));
	cudaMalloc((void**)&dev_a, alen  * sizeof(char));
	cudaMalloc((void**)&dev_b, alen  * sizeof(char));
	CreateEnd =  clock();

	//Copy all arrays to GPU memory
	Begain = clock();										//begain time of GPU
	cudaMemcpy(dev_a, Adata, alen * sizeof(char), cudaMemcpyHostToDevice);
	cudaMemcpy(dev_b, Bdata, blen * sizeof(char), cudaMemcpyHostToDevice);

	//cudaMemcpy(dev_H, NewH, alen * blen * sizeof(int), cudaMemcpyHostToDevice);
	const int NumberOfThreads = 256;

	//Set GPU for parallel working
	dim3 ThreadsWarp(32, 8);
	int size = (int)ceil((float)blen / (float)NumberOfThreads);
	int Increment = alen - 1;
	int MemSize = alen * blen;
	//int MEM1 = 
	init_SM << < NumberOfThreads, size >> >(dev_H, blen);
	StartSW << <ThreadsWarp, MemSize >> >(dev_a, dev_b, alen, dev_H, Increment, size);
	//for (int slice = 0; slice < 2 * alen - 1; ++slice)
	//{
	//	int z = slice < alen ? 0 : slice - alen + 1;//CPU
	//	size = (int)ceil((float)((slice - 2 * z) + 1));

	//	SM << <ThreadsWarp, MemSize >> >(dev_a, dev_b, slice, z, alen, dev_H, Increment, size);
	//}

	cudaMemcpy(NewH, dev_H, alen * blen  * sizeof(int), cudaMemcpyDeviceToHost);
	End = clock();								//End time of GPU
	cudaFree(dev_a);
	cudaFree(dev_b);
	
	cudaFree(dev_H);
	cudaDeviceReset();
}

// ---------------------Test Section---------------------------------
__global__ void Kernel(int *a, int *b, int *c)
{
	int i = threadIdx.x;
	c[i] = a[i] + b[i];
}


void Kernal_Test(int *a, int *b, int* c,int &count)
{
	int *d_a, *d_b,*d_c;
	cudaError_t cudaStatus;
	cudaStatus = cudaSetDevice(0);
	if (cudaStatus != cudaSuccess) {
		fprintf(stderr, "cudaSetDevice failed!  Do you have a CUDA-capable GPU installed?");
		return;
	}
	cudaStatus = cudaMalloc((void **)&d_a, count *sizeof(int));
	if (cudaStatus != cudaSuccess) {
		fprintf(stderr, "cudaSetDevice failed!  Do you have a CUDA-capable GPU installed?");
		return;
	}
	cudaStatus = cudaMalloc((void **)&d_b, count *sizeof(int));
	if (cudaStatus != cudaSuccess) {
		fprintf(stderr, "cudaSetDevice failed!  Do you have a CUDA-capable GPU installed?");
		return;
	}
	cudaStatus = cudaMalloc((void **)&d_c, count *sizeof(int));
	if (cudaStatus != cudaSuccess) {
		fprintf(stderr, "cudaSetDevice failed!  Do you have a CUDA-capable GPU installed?");
		return;
	}

	cudaMemcpy(d_a, a, count * sizeof(int), cudaMemcpyHostToDevice);
	cudaMemcpy(d_b, b, count * sizeof(int), cudaMemcpyHostToDevice);
	int blocks = 1;
	Kernel << < blocks, count >> >(d_a, d_b, d_c);
	cudaMemcpy(c,d_c , count * sizeof(int), cudaMemcpyDeviceToHost);
	cudaFree(d_a);
	cudaFree(d_b);
	cudaFree(d_c);
	cudaDeviceReset();
	count = 10;
}