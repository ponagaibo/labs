#include "Examples.h"
#include <windows.h>
#include <stdlib.h>
#include <math.h>

#define MAX_THREADS 16
#define MAX_BUFFER 2000

DWORD WINAPI ThreadFunction3(LPVOID lpParam);
double data1[MAX_BUFFER];

void Example3()
{
	//Init
	HANDLE  hThreadArray[MAX_THREADS];
	DWORD   dwThreadIdArray[MAX_THREADS];
	for (int i = 0; i < MAX_BUFFER; i++)
	{
		data1[i] = i;
	}
	//Part1 - Reduce
	for (int i = 0; i < MAX_THREADS; i++)
	{
		hThreadArray[i] = CreateThread(NULL,
			0,
			ThreadFunction3,
			i,
			NULL,
			&dwThreadIdArray[i]);
	}
	WaitForMultipleObjects(MAX_THREADS, hThreadArray, TRUE, INFINITE);
	for (int i = 0; i < MAX_THREADS; i++) CloseHandle(hThreadArray[i]);

	//Part2 - Aggregation
	for (int i = (MAX_BUFFER) / (MAX_THREADS); i < MAX_BUFFER; i += (MAX_BUFFER) / (MAX_THREADS))
	{
		data1[0] += data1[i];
	}
	
	printf("%f\n", data1[0]);
}

DWORD WINAPI ThreadFunction3(LPVOID lpParam)
{
	int length = (MAX_BUFFER) / (MAX_THREADS);
	int myNumber = (int)lpParam;
	int firstIndex = myNumber * length;
	data1[firstIndex] = cos(sin(data1[firstIndex]));

	for (int i = firstIndex + 1; i < firstIndex + length; i += 1)
	{
		data1[firstIndex] += cos(sin(data1[i]));
	}

	return myNumber;
}