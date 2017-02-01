#include <stdio.h>
#include <stdio_ext.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <ctype.h>

const int MAXPATH = 50;
int pageSize;
int totalLines = -1;
int totalBytes = -1;
int modified = 1;
int minFS = -1;
int maxFS = -1;
int findLine = -1;

char** SplitString(char* str, int* count) {
    char** res;
    int line = 0;
    char input[255];
    int inputPos = 0;
    int i;
    for (i = 0; i <= strlen(str); i++) {
        int delim = 0;
        if (i == strlen(str) || str[i] == 32) delim = 1;
        if (delim && inputPos > 0) {
            if (line == 0) res = malloc(sizeof(char*));
            else res = realloc(res, sizeof(char*) * (line + 1)); 
            input[inputPos] = 0;
            res[line] = malloc(inputPos + 1);
            strcpy(res[line], input);
            inputPos = 0;
            line++;
        }
        if (!delim && i < strlen(str)) input[inputPos++] = str[i];
    }
    *count = line;
    return res;
}

void FindLine(char* filename, char* patt, char* searchType) {
    int fd = open(filename, O_RDONLY);
    if (fd == -1) {
        printf("Error! Can not open file.\n");
        return;
    }
    struct stat stbuf;
    fstat(fd, &stbuf);
    int pageNum = stbuf.st_size / pageSize;
    if (stbuf.st_size > pageNum * pageSize) pageNum++;
    int page, i;
    int pos = 0;
    char curLine[255];
    char orig[255];
    int curPos = 0;
    for (page = 0; page < pageNum; page++) {
        void* map = mmap(0, pageSize, PROT_READ, MAP_SHARED, fd, pageSize * page);
        if (map == MAP_FAILED) printf("Error maping!\n");
        for (i = 0; i < pageSize; i++) {
            char c = *(char*)(map + i);
            if ((c == 32) || (c == 10) || (pos == stbuf.st_size - 1)) {
                curLine[curPos] = 0;
                orig[curPos] = 0;
                if (strlen(searchType) == 0 && strstr(curLine, patt) != 0) 
                    printf("%s\n", orig);
                if (searchType[0] == '^' && strlen(patt) <= strlen(curLine))
                    if (strncmp(curLine, patt, strlen(patt)) == 0) 
                        printf("%s\n", orig);
                if (searchType[0] == '$' && strlen(patt) <= strlen(curLine))
                    if (strncmp(curLine + strlen(curLine) - strlen(patt), patt, strlen(patt)) == 0)
                        printf("%s\n", orig);
                curPos = 0;
            } else {
                curLine[curPos] = (char)tolower(c);
                orig[curPos] = c;
                curPos++;
            }
            pos++;
            if (pos == stbuf.st_size) break;
        }
        munmap(map, pageSize);
    }
    close(fd);
}

void InsertText(char* filename, int lineToIns, int posToIns, char* text) {
    char tmpName[255];
    strcpy(tmpName, "IHopeThereIsNoFileWithSuchName");
    int fdTmp = open(tmpName, O_CREAT | O_RDWR | O_TRUNC, S_IRUSR | S_IWUSR);
    if (fdTmp == -1) {
        printf("Error! Can not create temporary file.\n");
        return;
    }
    int fdOrig = open(filename, O_RDONLY);
    if (fdOrig == -1) {
        printf("Error! Can not open file.\n");
        return;
    }
    struct stat stbuf;
    fstat(fdOrig, &stbuf);
    int pageNum = stbuf.st_size / pageSize;
    if (stbuf.st_size > pageNum * pageSize) pageNum++;
    int page, i, j;
    int curPos = 1;
    int curLine = 1;
    int totalPos = 0;
    for (page = 0; page < pageNum; page++) {
        void* map = mmap(0, pageSize, PROT_READ, MAP_SHARED, fdOrig, pageSize * page);
        if (map == MAP_FAILED) printf("Error maping!\n");
        for (i = 0; i < pageSize; i++) {
            char c = *(char*)(map + i);
            if (curPos == posToIns && curLine == lineToIns) {
                for (j = 0; j < strlen(text); j++) {
                    char cur = text[j];
                    if (cur != 0) write(fdTmp, &cur, sizeof(char));
                }
            }
            if (c != 0) write(fdTmp, &c, sizeof(char));
            if (c == 10) {
                curLine++;
                curPos = 0;
            }
            curPos++;
            totalPos++;
            if (totalPos == stbuf.st_size) break;
        }
        munmap(map, pageSize);
    }
    close(fdOrig);
    close(fdTmp);
    if (remove(filename) != 0) {
        printf("Error! Can not remove original file.\n");
        return;
    }
    if (rename(tmpName, filename) != 0) printf("Error! Can not rename temporary file.\n");
}

void RemoveText(char* filename, int lineToRem, int posToRem, int lenToRem) {
    char tmpName[255];
    strcpy(tmpName, "IHopeThereIsNoFileWithSuchName");
    int fdTmp = open(tmpName, O_CREAT | O_RDWR | O_TRUNC, S_IRUSR | S_IWUSR);
    if (fdTmp == -1) {
        printf("Error! Can not create temporary file.\n");
        return;
    }
    int fdOrig = open(filename, O_RDONLY);
    if (fdOrig == -1) {
        printf("Error! Can not open file.\n");
        return;
    }
    struct stat stbuf;
    fstat(fdOrig, &stbuf);
    int pageNum = stbuf.st_size / pageSize;
    if (stbuf.st_size > pageNum * pageSize) pageNum++;
    int page, i;
    int curPos = 1;
    int curLine = 1;
    int findPos = 0;
    for (page = 0; page < pageNum; page++) {
        void* map = mmap(0, pageSize, PROT_READ, MAP_SHARED, fdOrig, pageSize * page);
        if (map == MAP_FAILED) printf("Error maping!\n");
        for (i = 0; i < pageSize; i++) {
            char c = *(char*)(map + i);
            if (curPos == posToRem && curLine == lineToRem) findPos = 1;
            if (!findPos && c != 0) write(fdTmp, &c, sizeof(char));
            if (findPos) {
                lenToRem--;
                if (!lenToRem) findPos = 0;
            }
            if (c == 10) {
                curLine++;
                curPos = 0;
            }
            curPos++;
            if (curPos == stbuf.st_size) break;
        }
        munmap(map, pageSize);
    }
    close(fdOrig);
    close(fdTmp);
    if (remove(filename) != 0) {
        printf("Error! Can not remove original file.\n");
        return;
    }
    if (rename(tmpName, filename) != 0) printf("Error! Can not rename temporary file.\n");
}

void LinesInFile(char* filename) {
    if (strlen(filename) < 1) {
        printf("Empty name!\n");
        return ;
    }
    int fd = open(filename, O_RDONLY);
    if (fd == -1) {
        printf("Error! Can not open file. In LinesInFile\n");
        return;
    }
    struct stat stbuf;
    fstat(fd, &stbuf);
    int pageNum = stbuf.st_size / pageSize;
    if (stbuf.st_size > pageNum * pageSize) pageNum++;
    int page, i;
    int pos = 0;
    int lines = 1;
    int bytes = 0;
    for (page = 0; page < pageNum; page++) {
        void* map = mmap(0, pageSize, PROT_READ, MAP_SHARED, fd, pageSize * page);
        if (map == MAP_FAILED) printf("Error maping!\n");
        for (i = 0; i < pageSize; i++) {
            char c = *(char*)(map + i);
            if (findLine != -1 && lines == findLine) printf("%c", c);
            if (c == 10) lines++;
            pos++;
            if (pos == stbuf.st_size) break;
            bytes++;
        }
        munmap(map, pageSize);
    }
    close(fd);
    totalLines = lines;
    totalBytes = bytes;
    modified = 0;
    findLine = -1;
}

void PrintFileInfo(char* filename) {
    if (modified) LinesInFile(filename);
    int fd = open(filename, O_RDONLY);
    if (fd == -1) {
        printf("Error! Can not open file.\n");
        return;
    }
    struct stat stbuf;
    fstat(fd, &stbuf);
    close(fd);
    printf("File name: %s, size: %d, lines: %d\n", filename, (int)stbuf.st_size, totalLines);
    if ((minFS != -1) && (minFS > stbuf.st_size))
        printf("Warning: file size less then minimal allowed: %d\n", minFS);
    if ((maxFS != -1) && (maxFS < stbuf.st_size))
        printf("Warning: file size great then maximal allowed: %d\n", maxFS);
}

void PrintHelp() {
    printf("\t-- Command line mode: --\n./editor [/file FILE_NAME] [/command COMMAND_NAME] [/help]\n");
    printf("[/memsize PAGE_SIZE] [/minfilesize MIN_SIZE] [/maxfilesize MAX_SIZE]\n\n");
    printf("PAGE_SIZE - size of page for mapping.\nMIN_SIZE - minimum available size of file\n");
    printf("MAX_SIZE - maximum available size of file\n\n");
    printf("If filename doesn't set, the interactive mode is activates.\n");
    printf("You should select a file at the beginning of work in the interactive mode.\n\n");
    printf("\t-- Available command line commands (COMMAND_NAME): --\n");
    printf("> fileinfo - print information about the file\n");
    printf("> getline N - print Nth line from file (starting from 1)\n");
    printf("> findline [TYPE] STR - find STR in file\n    if TYPE skipped, the search starts at any position\n");
    printf("    if TYPE = ^, the search starts at the word beginning\n");
    printf("    if TYPE = $, the search starts at the word end\n");
    printf("> remove LINE POS LENGTH - remove LENGTH symbols from POSth position in LINEth line\n");
    printf("> insert LINE POS \"STR\" - insert STR at POSth position in LINEth line (STR should be quoted)\n");
    printf("> help - print this message\n\n\t-- Available interactive mode commands: --\n");
    printf("> memsize PAGE_SIZE - set page size for mapping at PAGE_SIZE\n");
    printf("    (PAGE_SIZE should be multiple of the default page size)\n");
    printf("> minfilesize MIN_SIZE - set minimum available file size at MIN_SIZE,\n");
    printf("    files less than MIN_SIZE will not be open\n");
    printf("> minfilesize MAX_SIZE - set maximum available file size at MAX_SIZE,\n");
    printf("    files greater than MAX_SIZE will not be open\n");
    printf("> exit - quit the editor\n> setfile - select file\n");
    printf("Command line commands is also available in the interactive mode\n");
}

int ExecCmd(char* filename, char* cmd) {
    int cnt = 0;
    char** data = SplitString(cmd, &cnt);
    if (modified && strlen(filename) > 0) LinesInFile(filename);
    if (!strcmp(data[0], "memsize")) {
        int newSize = atoi(data[1]);
        if (newSize > 0 && (newSize % pageSize) != 0) 
            printf("Memory size must be multiple of PAGESIZE: %d\n", pageSize);
        else {
            pageSize = newSize;
            printf("Set new memory size: %d\n", pageSize);
        }
    } else if (!strcmp(data[0], "minfilesize")) minFS = atoi(data[1]);
    else if (!strcmp(data[0], "maxfilesize")) maxFS = atoi(data[1]);
    else if (!strcmp(data[0], "getline")) {
        if (strlen(filename) == 0) {
            printf("Set filename first!\n");
            return 1;
        }
        int lineToFind = atoi(data[1]);
        if (lineToFind <= 0) {
            printf("Line number must be the positive integer.\n");
            return 1;
        }
        if (lineToFind > totalLines) {
            printf("Line number must be less than number of lines in a file.\n");
            return 1;
        }
        findLine = lineToFind;
        LinesInFile(filename);
    } else if (!strcmp(data[0], "remove")) {
        if (strlen(filename) == 0) {
            printf("Set filename first!\n");
            return 1;
        }
        if (cnt == 4) {
            int lineToRem = atoi(data[1]);
            int posToRem = atoi(data[2]);
            int lenToRem = atoi(data[3]);
            if (lineToRem <= 0) {
                printf("Line number must be the positive integer.\n");
                return 1;
            }
            if (lineToRem > totalLines) {
                printf("Line number must be less than number of lines in a file.\n");
                return 1;
            }
            RemoveText(filename, lineToRem, posToRem, lenToRem);
            modified = 1;
        } else printf("Wrong number of arguments!\n");
    } else if (!strcmp(data[0], "insert")) {
        if (strlen(filename) == 0) {
            printf("Set filename first!\n");
            return 1;
        }
        if (cnt >= 4) {
            int lineToIns = atoi(data[1]);
            int posToIns = atoi(data[2]);
            if (lineToIns <= 0) {
                printf("Line number must be the positive integer.\n");
                return 1;
            }
            if (lineToIns > totalLines) {
                printf("Line number must be less than number of lines in a file.\n");
                return 1;
            }
            int count, begin, len;
            int q = 0;
            int skip = 3;
            for (count = 0; count < strlen(cmd); count++) {
                char curCmd = cmd[count];
                if (cmd[count] == 34) ++q;
                if (cmd[count] == 32) --skip;
                if (q == 1 || !skip) {
                    begin = count + 1;
                    --skip;
                    if (q == 1) ++q;
                }
                if (q == 3) len = count - begin;
            }
            char textToIns[50];
            strcpy(textToIns, "");
            strncat(textToIns, cmd + begin, len);
            InsertText(filename, lineToIns, posToIns, textToIns);
            modified = 1;
        } else printf("Wrong number of arguments!\n");
    } else if (!strcmp(data[0], "findline")) {
        if (strlen(filename) == 0) {
            printf("Set filename first!\n");
            return 1;
        }
        if (cnt == 2) FindLine(filename, data[1], "");
        else FindLine(filename, data[2], data[1]);
    } else if (!strcmp(data[0], "fileinfo")) {
        if (strlen(filename) == 0) {
            printf("Set filename first!\n");
            return 1;
        } else PrintFileInfo(filename);
    } else if (!strcmp(data[0], "setfile")) {
        char tmp[50];
        strcpy(tmp, cmd + strlen(data[0]) + 1);
        LinesInFile(tmp);
        modified = 1;
        if ((maxFS != -1 && totalBytes > maxFS) || (minFS != -1 && totalBytes < minFS) ) {
            printf("Invalid file size.\n");
            if (maxFS != -1) printf("Maxumum available size: %d\n", maxFS);
            if (minFS != -1) printf("Minimum available size: %d\n", minFS);
            printf("Size of selected file is %d\n", totalBytes);
            strcpy(filename, "");
            return 1;
        }
        strcpy(filename, tmp);
    } else {
        printf("Unknown command: %s\n", data[0]);
        return 1;
    }
    return 0;
}

int main(int argc, char** argv) {
    char filename[MAXPATH];
    char cmd[75];
    pageSize = sysconf(_SC_PAGESIZE);
    strcpy(filename, "");
    strcpy(cmd, "");
    __fpurge(stdin);
    int i;
    for (i = 0; i < argc; i++) {
        if (!strcmp(argv[i], "/file")) {
            char tmp[50];
            strcpy(tmp, argv[i + 1]);
            LinesInFile(tmp);
            modified = 1;
            if ((maxFS != -1 && totalBytes > maxFS) || (minFS != -1 && totalBytes < minFS) ) {
                printf("Invalid file size.\n");
                if (maxFS != -1) printf("Maxumum available size: %d\n", maxFS);
                if (minFS != -1) printf("Minimum available size: %d\n", minFS);
                printf("Size of selected file is %d\n", totalBytes);
                strcpy(filename, "");
                return 1;
            }
            strcpy(filename, tmp);
            i++;
        }
        if (!strcmp(argv[i], "/memsize")) {
            int newSize = atoi(argv[i + 1]);
            if (newSize > 0 && (newSize % pageSize) != 0) 
                printf("Memory size must be multiple of PAGESIZE: %d\n", pageSize);
            else {
                pageSize = newSize;
                printf("Set new memory size: %d\n", pageSize);
            }
            i++;
        }
        if (!strcmp(argv[i], "/minfilesize")) {
            minFS = atoi(argv[i + 1]);
            i++;
        }
        if (!strcmp(argv[i], "/maxfilesize")) {
            maxFS = atoi(argv[i + 1]);
            i++;
        }
        if (!strcmp(argv[i], "/command")) {
            strcpy(cmd, argv[i + 1]);
            i++;
            if (!strcmp(cmd, "getline")) {
                strcat(cmd, " ");
                strcat(cmd, argv[i + 1]);
                i++;
            }
            if (!strcmp(cmd, "findline")) {
                strcat(cmd, " ");
                strcat(cmd, argv[i + 1]);
                i++;
                if (i < argc - 1) {
                    if (argv[i + 1][0] != '/') {
                        strcat(cmd, " ");
                        strcat(cmd, argv[i + 1]);
                        i++;
                    }
                }
            }
            if (!strcmp(cmd, "remove")) {
                strcat(cmd, " ");
                strcat(cmd, argv[i + 1]);
                strcat(cmd, " ");
                strcat(cmd, argv[i + 2]);
                strcat(cmd, " ");
                strcat(cmd, argv[i + 3]);
                i += 3;
            }
            if (!strcmp(cmd, "insert")) {
                strcat(cmd, " ");
                strcat(cmd, argv[i + 1]);
                strcat(cmd, " ");
                strcat(cmd, argv[i + 2]);
                strcat(cmd, " ");
                strcat(cmd, argv[i + 3]);
                i += 3;
            }
        }
        if (!strcmp(argv[i], "/help")) PrintHelp();
    }
    if ((strlen(cmd) > 0) && (strlen(filename) > 0)) return ExecCmd(filename, cmd);
    printf("\n\t*** Interactive mode ***\n");
    if (strlen(filename) > 0) PrintFileInfo(filename);
    while (1) {
        printf("\nEnter command or 'help' for info:\n>");
        __fpurge(stdin);
        fgets(cmd, 74, stdin);
        __fpurge(stdin);
        if (cmd[strlen(cmd) - 1] == 10) cmd[strlen(cmd) - 1] = 0;
        if (!strcmp(cmd, "exit")) return 0;
        if (!strcmp(cmd, "help")) PrintHelp(); 
        else if (ExecCmd(filename, cmd) > 0) printf("Error executing command!\n");
    }
    return 0;
}