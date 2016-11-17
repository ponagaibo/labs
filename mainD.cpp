#include <Windows.h>
#include <tchar.h>
#include <iostream>

using namespace std;

int _tmain(int argc, _TCHAR* argv[]) {
    SECURITY_ATTRIBUTES sa;
    sa.nLength = sizeof(SECURITY_ATTRIBUTES);
    sa.lpSecurityDescriptor = NULL;
    sa.bInheritHandle = TRUE;


    HANDLE readSrv, writeCl, readCl, writeSrv;
    CreatePipe(&readCl, &writeSrv, &sa, 0);
    CreatePipe(&readSrv, &writeCl, &sa, 0);

    PROCESS_INFORMATION ProcessInfo;
    ZeroMemory(&ProcessInfo, sizeof(PROCESS_INFORMATION));

    TCHAR clientPath[] = L"Debug\\Server.exe";
    STARTUPINFO StartupInfo;
    ZeroMemory(&StartupInfo, sizeof(StartupInfo));
    StartupInfo.cb = sizeof(STARTUPINFO);
    StartupInfo.dwFlags = STARTF_USESTDHANDLES;
    StartupInfo.hStdInput = readSrv;
    StartupInfo.hStdOutput = writeSrv;

    int process = CreateProcess(NULL, clientPath, NULL, NULL, true, CREATE_NO_WINDOW, NULL, NULL, &StartupInfo, &ProcessInfo);
    CloseHandle(readSrv);
    CloseHandle(writeSrv);
    if (!process) {
        CloseHandle(readCl);
        CloseHandle(writeCl);
        throw::logic_error("Can't create process");
    }

    DWORD writeBytes, readBytes;
    char buf[64];
    double result;
    while (std::cin >> buf) {
        WriteFile(writeCl, &buf, sizeof(buf), &writeBytes, NULL);
        ReadFile(readCl, &result, sizeof(result), &readBytes, NULL);
        if (readBytes == 1) continue;
        cout << result << endl;
    }
    CloseHandle(readCl);
    CloseHandle(writeCl);
    CloseHandle(ProcessInfo.hThread);
    CloseHandle(ProcessInfo.hProcess);
    ExitProcess(ProcessInfo.dwProcessId);
    return 0;
}