#define _CRT_SECURE_NO_DEPRECATE
#include <windows.h>
#include "stdio.h"
#include <tchar.h>
#include "io.h"
#include "conio.h"
#include <iostream>

    void newProc() {
        PROCESS_INFORMATION ProcessInfo; //This is what we get as an [out] parameter
	    ZeroMemory(&ProcessInfo, sizeof(PROCESS_INFORMATION));

        TCHAR lpszClientPath[] = "hi.exe";

	    SECURITY_ATTRIBUTES SecAtr;
        SecAtr.nLength = sizeof(SECURITY_ATTRIBUTES);
        SecAtr.lpSecurityDescriptor = NULL;//PROCESS_QUERY_INFORMATION;
        SecAtr.bInheritHandle = TRUE;

        HANDLE readSrv, writeCl, readCl, writeSrv;
        CreatePipe(&readCl, &writeSrv, &SecAtr, 0);
        CreatePipe(&readSrv, &writeCl, &SecAtr, 0);

	    STARTUPINFO StartupInfo; //This is an [in] parameter
	    ZeroMemory(&StartupInfo, sizeof(StartupInfo));
	    StartupInfo.cb = sizeof (STARTUPINFO); //Only compulsory field
        StartupInfo.dwFlags = STARTF_USESTDHANDLES;
    //StartupInfo.hStdOutput = writePipe;
        StartupInfo.hStdInput = readSrv;
        StartupInfo.hStdOutput = writeSrv;

	    bool process = CreateProcess(NULL, //NULL
                                 lpszClientPath,
								 NULL, NULL, true, CREATE_NO_WINDOW,// CREATE_NEW_CONSOLE|CREATE_SUSPENDED
								 NULL, NULL, &StartupInfo, &ProcessInfo);

        CloseHandle(readSrv);
        CloseHandle(writeSrv);

        DWORD ID;
        ID = ProcessInfo.dwProcessId;
        printf("ID: %d\n", ID);
        CloseHandle(readCl);
        CloseHandle(writeCl);
	    CloseHandle(ProcessInfo.hThread);
	    CloseHandle(ProcessInfo.hProcess);
    }

int main() {
    newProc();
    newProc();
    newProc();

	//ExitProcess(ProcessInfo.dwProcessId);
/*
	PROCESS_INFORMATION ProcessInfo2; //This is what we get as an [out] parameter
	ZeroMemory(&ProcessInfo2, sizeof(PROCESS_INFORMATION));

    SECURITY_ATTRIBUTES SecAtr2;
    SecAtr2.nLength = sizeof(SECURITY_ATTRIBUTES);
    SecAtr2.lpSecurityDescriptor = NULL;//PROCESS_QUERY_INFORMATION;
    SecAtr2.bInheritHandle = TRUE;

    HANDLE readSrv2, writeCl2, readCl2, writeSrv2;
	CreatePipe(&readCl2, &writeSrv2, &SecAtr2, 0);
    CreatePipe(&readSrv2, &writeCl2, &SecAtr2, 0);

    STARTUPINFO StartupInfo2; //This is an [in] parameter
	ZeroMemory(&StartupInfo2, sizeof(StartupInfo2));
	StartupInfo2.cb = sizeof (STARTUPINFO); //Only compulsory field
    StartupInfo2.dwFlags = STARTF_USESTDHANDLES;
    StartupInfo2.hStdInput = readSrv2;
    StartupInfo2.hStdOutput = writeSrv2;

	bool process2 = CreateProcess(NULL, //NULL
                                 lpszClientPath,
								 NULL, NULL, true, CREATE_NO_WINDOW,// CREATE_NEW_CONSOLE|CREATE_SUSPENDED
								 NULL, NULL, &StartupInfo2, &ProcessInfo2);
    if (!process2) {
        printf("blabla2\n");
        exit(0);
    }

    CloseHandle(readSrv2);
    CloseHandle(writeSrv2);

    DWORD ID2;
    ID2 = ProcessInfo2.dwProcessId;
    printf("ID: %d\n", ID2);

    CloseHandle(readCl2);
    printf("blabla21\n");
    CloseHandle(writeCl2);
    printf("blabla22\n");
   // ExitProcess(ProcessInfo.dwProcessId);
	printf("blabla25\n");
	//ExitProcess(ProcessInfo2.dwProcessId);
	//LPDWORD lpExitCode;
    //if (!GetExitCodeProcess(ProcessInfo2.hProcess, lpExitCode)) printf("error 1\n");
    //UINT cd = *lpExitCode;
    //ExitProcess(cd);
    //WaitForSingleObject(ProcessInfo2.hProcess, INFINITE);
	CloseHandle(ProcessInfo2.hThread);
	printf("blabla23\n");
	CloseHandle(ProcessInfo2.hProcess);
	printf("blabla24\n");
*/
	//printf("blabla26\n");
    return 0;
}
