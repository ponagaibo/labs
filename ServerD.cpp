#include <Windows.h>
#include <string>
#include <tchar.h>

int _tmain(int argc, _TCHAR* argv[]) {
    HANDLE inH = GetStdHandle(STD_INPUT_HANDLE);
    HANDLE outH = GetStdHandle(STD_OUTPUT_HANDLE);
    char buf[64];
    double result;
    DWORD readBytes, writeBytes;
    while (ReadFile(inH, &buf, sizeof(buf), &readBytes, NULL)) {
        try {
            result = std::stof(buf);
            WriteFile(outH, &result, sizeof(result), &writeBytes, NULL);
        } catch (std::invalid_argument) {
            WriteFile(outH, &result, 1, &writeBytes, NULL);
        } catch (std::out_of_range) {
            result = INFINITY;
            WriteFile(outH, &result, sizeof(result), &writeBytes, NULL);
        }
    }
    return 0;
}