#include "Examples.h"
#include <windows.h>
#include <stdlib.h>
#include <math.h>

#define MAX_THREADS 16
#define MAX_BUFFER 2000

DWORD WINAPI ThreadFunction2(LPVOID lpParam);
double result;
double data1[MAX_BUFFER];
HANDLE mutex;

void Example2()
{
	HANDLE  hThreadArray[MAX_THREADS];
	DWORD   dwThreadIdArray[MAX_THREADS];
	mutex = CreateMutex(NULL, FALSE, NULL);
	for (int i = 0; i < MAX_BUFFER; i++)
	{
		data1[i] = i;
	}


	for (int i = 0; i < MAX_THREADS; i++)
	{
		hThreadArray[i] = CreateThread(NULL,
			0,
			ThreadFunction2,
			i,
			CREATE_SUSPENDED,
			&dwThreadIdArray[i]);
	}
	for (int i = 0; i < MAX_THREADS; i++) ResumeThread(hThreadArray[i]);

	WaitForMultipleObjects(MAX_THREADS, hThreadArray, TRUE, INFINITE);
	for (int i = 0; i < MAX_THREADS; i++) CloseHandle(hThreadArray[i]);

	printf("%f\n", result);
}

DWORD WINAPI ThreadFunction2(LPVOID lpParam)
{
	int length = (MAX_BUFFER) / (MAX_THREADS);
	int myNumber = (int)lpParam;
	for (int i = myNumber * length; i < (myNumber + 1) * length; i++)
	{
		double temp = cos(sin(data1[i]));
		WaitForSingleObject(mutex, INFINITE);
		result += temp;
		ReleaseMutex(mutex);
	}

	return myNumber;
}