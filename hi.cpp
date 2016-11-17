#include <Windows.h>
#include <tchar.h>
#include <iostream>
#include <cstdio>

using namespace std;

int _tmain(int argc, _TCHAR* argv[]) {
    //cout << "Hi! :3" << endl;
    //DWORD tr;
    //cin >> tr;
    HANDLE inH = GetStdHandle(STD_INPUT_HANDLE);
    HANDLE outH = GetStdHandle(STD_OUTPUT_HANDLE);
    /*
    int buf;
    int result;
    DWORD readBytes, writeBytes;
    ReadFile(inH, &buf, sizeof(buf), &readBytes, NULL);
        result = buf + 1;
        */
        int result = 1234;
         DWORD readBytes, writeBytes;
        WriteFile(outH, &result, sizeof(result), &writeBytes, NULL);

    return 0;
}
