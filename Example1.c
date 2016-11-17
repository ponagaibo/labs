#include "Examples.h"
#include <windows.h>
#include <stdlib.h>
#include <math.h>

#define MAX_THREADS 16
#define MAX_BUFFER 2000

DWORD WINAPI ThreadFunction(LPVOID lpParam);
double result;
double data1[MAX_BUFFER];

void Example1()
{
	printf("%d\n", MAXIMUM_WAIT_OBJECTS);
	HANDLE  hThreadArray[MAX_THREADS];
	DWORD   dwThreadIdArray[MAX_THREADS];
	for (int i = 0; i < MAX_BUFFER; i++)
	{
		data1[i] = i;
	}


	for (int i = 0; i < MAX_THREADS; i++)
	{
		hThreadArray[i] = CreateThread(NULL,
			0,
			ThreadFunction,
			i,
			CREATE_SUSPENDED,
			&dwThreadIdArray[i]);
	}
	for (int i = 0; i < MAX_THREADS; i++) ResumeThread(hThreadArray[i]);


	WaitForMultipleObjects(MAX_THREADS, hThreadArray, TRUE, INFINITE);
	for (int i = 0; i < MAX_THREADS; i++) CloseHandle(hThreadArray[i]);
	/*for (int i = 0; i < MAX_THREADS; i++)
	{
		DWORD code;
		GetExitCodeThread(hThreadArray[i], &code);
		printf("%d\n", code);
	}*/

	printf("%f\n", result);
}

DWORD WINAPI ThreadFunction(LPVOID lpParam)
{
	int length = (MAX_BUFFER) / (MAX_THREADS);
	int myNumber = (int)lpParam;
	for (int i = myNumber * length; i < (myNumber + 1) * length; i++)
	{
		result += cos(sin(data1[i]));
	}

	return myNumber;
}