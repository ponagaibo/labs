#define _CRT_SECURE_NO_DEPRECATE
#include <windows.h>
#include "stdio.h"
#include <tchar.h>
#include "io.h"
#include "conio.h"
#include <iostream>

int main() {
    PROCESS_INFORMATION ProcessInfo; //This is what we get as an [out] parameter
	ZeroMemory(&ProcessInfo, sizeof(PROCESS_INFORMATION));

    TCHAR lpszClientPath[] = "hi.exe";
	//HANDLE writePipe, readPipe;

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
/*
    if (!CreatePipe(&readPipe, &writePipe, &SecAtr, 0)) {
        printf("blabla");
        exit(0);
    }
*/
	bool process = CreateProcess(NULL, //NULL
                                 lpszClientPath,
								 NULL, NULL, true, CREATE_NO_WINDOW,// CREATE_NEW_CONSOLE|CREATE_SUSPENDED
								 NULL, NULL, &StartupInfo, &ProcessInfo);
    if (!process) {
        printf("blabla2");
        exit(0);
    }

    CloseHandle(readSrv);
    CloseHandle(writeSrv);

    DWORD ID;
    ID = ProcessInfo.dwProcessId;
    printf("ID: %d", ID);

    DWORD writeBytes, readBytes;
    /*
    int buf;
    int result;
    while (std::cin >> buf) {
        WriteFile(writeCl, &buf, sizeof(buf), &writeBytes, NULL);
        ReadFile(readCl, &result, sizeof(result), &readBytes, NULL);
        if (readBytes == 1) continue;
        std::cout << result << std::endl;
    }
    */
    CloseHandle(readCl);
    CloseHandle(writeCl);

    //CloseHandle(writePipe);
	CloseHandle(ProcessInfo.hThread);
	CloseHandle(ProcessInfo.hProcess);
	ExitProcess(ProcessInfo.dwProcessId);

	PROCESS_INFORMATION ProcessInfo2; //This is what we get as an [out] parameter
	ZeroMemory(&ProcessInfo2, sizeof(PROCESS_INFORMATION));

    STARTUPINFO StartupInfo2; //This is an [in] parameter
	ZeroMemory(&StartupInfo2, sizeof(StartupInfo));
	StartupInfo2.cb = sizeof (STARTUPINFO); //Only compulsory field
    StartupInfo2.dwFlags = STARTF_USESTDHANDLES;
    //StartupInfo.hStdOutput = writePipe;
    StartupInfo2.hStdInput = readSrv;
    StartupInfo2.hStdOutput = writeSrv;
	CreatePipe(&readCl, &writeSrv, &SecAtr, 0);
    CreatePipe(&readSrv, &writeCl, &SecAtr, 0);
	bool process2 = CreateProcess(NULL, //NULL
                                 lpszClientPath,
								 NULL, NULL, true, CREATE_NO_WINDOW,// CREATE_NEW_CONSOLE|CREATE_SUSPENDED
								 NULL, NULL, &StartupInfo2, &ProcessInfo2);
    if (!process) {
        printf("blabla2");
        exit(0);
    }

    CloseHandle(readSrv);
    CloseHandle(writeSrv);

    DWORD ID2;
    ID2 = ProcessInfo2.dwProcessId;
    printf("ID: %d", ID2);

    CloseHandle(readCl);
    CloseHandle(writeCl);

    //CloseHandle(writePipe);
	CloseHandle(ProcessInfo2.hThread);
	CloseHandle(ProcessInfo2.hProcess);
	ExitProcess(ProcessInfo2.dwProcessId);
/*


    //STARTUPINFO          si;// Specifies the window station, desktop, standard handles, and appearance of the main window for a process at creation time.
    //PROCESS_INFORMATION  pi;//
    LPTSTR szCmdline = _tcsdup(TEXT("sort Text.txt"));// A pointer to a null-terminated string, malloc
    HANDLE writePipe, readPipe;
    SECURITY_ATTRIBUTES sa;// This structure provides security settings for objects created by various functions, such as CreateFile
    //ZeroMemory(&si, sizeof(STARTUPINFO));// Fills a block of memory with zeros.
    //si.cb = sizeof(STARTUPINFO);
    sa.nLength = sizeof(SECURITY_ATTRIBUTES);
    sa.lpSecurityDescriptor = PROCESS_QUERY_INFORMATION;
    sa.bInheritHandle = TRUE;
    if (!CreatePipe(&readPipe, &writePipe, &sa, 0)) {
        printf("blabla");
        exit(0);
    }
    si.dwFlags = STARTF_USESTDHANDLES;
    si.hStdOutput = writePipe;// If dwFlags specifies STARTF_USESTDHANDLES, this member is the standard output handle for the process.
    //Otherwise, this member is ignored and the default for standard output is the console window's buffer.
    //_stprintf(np_name, _T("%s\\notepad.exe"), windir); - format strings
    //WaitForSingleObject(processInfo.hProcess, INFINITE);
    if (!CreateProcess(0, szCmdline, 0, 0, TRUE, CREATE_NO_WINDOW, 0, 0, &si, &pi)) {
        printf("blabla2");
        exit(0);
    }
    CloseHandle(writePipe);
    char readData;

    DWORD dwByteRead = 1;
    while(ReadFile(readPipe, &readData, 1, &dwByteRead, NULL)) {
	    if(readData == '9') readData ='+';
	    if(readData >='0' && readData <'9') readData ++;
	    printf("%c",readData);
    }
    system("pause");


*/
    return 0;
}
