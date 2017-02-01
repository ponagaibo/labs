#include <stdio.h>
#include <stdio_ext.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <ctype.h>

// убраны комментарии

const int MAXPATH = 255;
static int pageSize;

int totalLines = -1;
int totalBytes = -1;
unsigned int modified = 1;
unsigned int curNumOfSymbols = 0;
int minFileSize = -1;
int maxFileSize = -1;

char** SplitString(char* str, int* count) {
    char** res;
    int line = 0;
    char input[255];
    int inputPos = 0;
    int i;
    for (i = 0; i <= strlen(str); i++) {
        int delim = 0;
        if (i == strlen(str)) {
            delim = 1;
        } else if (str[i] == 32) {
            delim = 1;
        }
        if (delim == 1) {
            if (inputPos > 0) {
                if (line == 0) {
                    res = malloc(sizeof(char*));
                } else {
                    res = realloc(res, sizeof(char*) * (line + 1)); 
                }
                input[inputPos] = 0;
                res[line] = malloc(inputPos + 1);
                strcpy(res[line], input);
                inputPos = 0;
                line++;
            }
        } else { 
            if (i < strlen(str)) {
                input[inputPos++] = str[i];
            }
        }
    }
    *count = line;
    return res;
}

void PrintLineOfFile(char* filename, int lineToPrint) {
    int fd = open(filename, O_RDONLY);
    struct stat stbuf;
    fstat(fd, &stbuf);
    int pageNum = stbuf.st_size / pageSize;
    if (stbuf.st_size > pageNum * pageSize) {
        pageNum++;
    }
    int page;
    int curPos = 0;
    int curLine = 1;
    curNumOfSymbols = 0;
    for (page = 0; page < pageNum; page++) {
        void* map = mmap(0, pageSize, PROT_READ, MAP_SHARED, fd, pageSize * page);
        if (map == MAP_FAILED) {
            printf("Error maping!\n");
        }
        int i;
        for (i = 0; i < pageSize; i++) {
            char c = *(char*)(map + i);
            if (curLine == lineToPrint) {
                printf("%c", c);
                curNumOfSymbols++;
            }
            if (c == 10) {
                curLine++;
            }
            curPos++;
            if (curPos == stbuf.st_size) {
                break;
            }
        }
        munmap(map, pageSize);
    }
    close(fd);
}

void FindLine(char* filename, char* pattern, char* searchType) {
    int fd = open(filename, O_RDONLY);
    struct stat stbuf;
    fstat(fd, &stbuf);
    int pageNum = stbuf.st_size / pageSize;
    if (stbuf.st_size > pageNum * pageSize) {
        pageNum++;
    }
    int page;
    int pos = 0;
    char curLine[255];
    char orig[255];
    int curPos = 0;
    for (page = 0; page < pageNum; page++) {
        void* map = mmap(0, pageSize, PROT_READ, MAP_SHARED, fd, pageSize * page);
        if (map == MAP_FAILED) {
            printf("Error maping!\n");
        }
        int i;
        for (i = 0; i < pageSize; i++) {
            char c = *(char*)(map + i);
            if ((c == 32) || (c == 10) || (pos == stbuf.st_size - 1)) {
                curLine[curPos] = 0;
                orig[curPos] = 0;
                if (strlen(searchType) == 0) {
                    if (strstr(curLine, pattern) != 0) {
                        printf("%s\n", orig);
                    }
                }
                if (searchType[0] == '^') {
                    if (strlen(pattern) <= strlen(curLine)) {
                        if (strncmp(curLine, pattern, strlen(pattern)) == 0) {
                            printf("%s\n", orig);
                        }
                    }
                }
                if (searchType[0] == '$') {
                    if (strlen(pattern) <= strlen(curLine)) {
                        if (strncmp(curLine + strlen(curLine) - strlen(pattern), pattern, strlen(pattern)) == 0) {
                            printf("%s\n", orig);
                        }
                    }
                }
                curPos = 0;
            } else {
                curLine[curPos] = (char)tolower(c);
                orig[curPos] = c;
                curPos++;
            }
            pos++;
            if (pos == stbuf.st_size) {
                break;
            }
        }
        munmap(map, pageSize);
    }
    close(fd);
}

int InsertText(char* filename, int lineToIns, int posToIns, char* text) {

    char tmpName[255];
    strcpy(tmpName, "IHopeThereIsNoFileWithSuchName");

    int fdTmp = open(tmpName, O_CREAT | O_RDWR | O_TRUNC, S_IRUSR | S_IWUSR);
    if (fdTmp == -1) {
        printf("Error! Can not create temporary file.\n");
    }
    int fdOrig = open(filename, O_RDONLY);
    struct stat stbuf;
    fstat(fdOrig, &stbuf);

    int pageNum = stbuf.st_size / pageSize;
    if (stbuf.st_size > pageNum * pageSize) {
        pageNum++;
    }
    int page;
    int curPos = 1;
    int curLine = 1;
    int findPos = 0;
    printf("got line %d, pos %d, text: \"%s\"\n", lineToIns, posToIns, text);
    for (page = 0; page < pageNum; page++) {
        void* map = mmap(0, pageSize, PROT_READ, MAP_SHARED, fdOrig, pageSize * page);
        if (map == MAP_FAILED) {
            printf("Error maping!\n");
        }
        int i;

        for (i = 0; i < pageSize; i++) {
            char c = *(char*)(map + i);

            if (curPos == posToIns && curLine == lineToIns) {
                int j;
                //printf("len of test: %d\n", strlen(text));
                for (j = 0; j < strlen(text); j++) {
                    char cur = text[j];
                    //printf("add: %c\n", cur);
                    if (cur != 0) write(fdTmp, &cur, sizeof(char));
                }
            }
            if (c != 0) write(fdTmp, &c, sizeof(char));
            if (c == 10) {
                curLine++;
                curPos = 0;
            }
            curPos++;
            if (curPos == stbuf.st_size) {
                break;
            }
        }
        munmap(map, pageSize);
    }
    close(fdOrig);
    close(fdTmp);
    if (remove(filename) != 0) {
        printf("Error! Can not remove original file.\n");
        return 1;
    }
    if (rename(tmpName, filename) != 0) {
        printf("Error! Can not rename temporary file.\n");
        return 1;
    }
}

int RemoveText(char* filename, int lineToRem, int posToRem, int lenToRem) { // все проверки в ExecCmd
    char tmpName[255];
    strcpy(tmpName, "IHopeThereIsNoFileWithSuchName");
    int fdTmp = open(tmpName, O_CREAT | O_RDWR | O_TRUNC, S_IRUSR | S_IWUSR);
    if (fdTmp == -1) {
        printf("Error! Can not create temporary file.\n");
    }
    int fdOrig = open(filename, O_RDONLY);
    struct stat stbuf;
    fstat(fdOrig, &stbuf);
    int pageNum = stbuf.st_size / pageSize;
    if (stbuf.st_size > pageNum * pageSize) {
        pageNum++;
    }
    int page;
    int curPos = 1;
    int curLine = 1;
    int findPos = 0;
    for (page = 0; page < pageNum; page++) {
        void* map = mmap(0, pageSize, PROT_READ, MAP_SHARED, fdOrig, pageSize * page);
        if (map == MAP_FAILED) {
            printf("Error maping!\n");
        }
        int i;
        for (i = 0; i < pageSize; i++) {
            char c = *(char*)(map + i);
            if (curPos == posToRem && curLine == lineToRem) {
                findPos = 1;
            }
            if (!findPos && c != 0) {
                write(fdTmp, &c, sizeof(char));
            } 
            if (findPos) {
                lenToRem--;
                if (lenToRem == 0) {
                    findPos = 0;
                }
            }
            if (c == 10) {
                curLine++;
                curPos = 0;
            }
            curPos++;
            if (curPos == stbuf.st_size) {
                break;
            }
        }
        munmap(map, pageSize);
    }
    close(fdOrig);
    close(fdTmp);
    if (remove(filename) != 0) {
        printf("Error! Can not remove original file.\n");
        return 1;
    }
    if (rename(tmpName, filename) != 0) {
        printf("Error! Can not rename temporary file.\n");
        return 1;
    }
}

void LinesInFile(char* filename) {
    int fd = open(filename, O_RDONLY);
    struct stat stbuf;
    fstat(fd, &stbuf);
    int pageNum = stbuf.st_size / pageSize;
    if (stbuf.st_size > pageNum * pageSize) {
        pageNum++;
    }
    int page;
    int pos = 0;
    int lines = 1;
    int bytes = 0;
    for (page = 0; page < pageNum; page++) {
        void* map = mmap(0, pageSize, PROT_READ, MAP_SHARED, fd, pageSize * page);
        if (map == MAP_FAILED) {
            printf("Error maping!\n");
        }
        int i;
        for (i = 0; i < pageSize; i++) {
            char c = *(char*)(map + i);
            if (c == 10) {
                lines++;
            }
            pos++;
            if (pos == stbuf.st_size) {
                break;
            }
            bytes++;
        }
        munmap(map, pageSize);
    }
    close(fd);
    totalLines = lines;
    totalBytes = bytes;
}

void PrintFileInfo(char* filename) {
    if (strlen(filename) == 0) {
        printf("File name not set!\n");
    } else {
        if (modified) {
            LinesInFile(filename);
            modified = 0;
        }
        int fd = open(filename, O_RDONLY);
        struct stat stbuf;
        fstat(fd, &stbuf);
        close(fd);
        printf("File name: %s, size: %d, lines: %d\n", filename, (int)stbuf.st_size, totalLines);
        if ((minFileSize != -1) && (minFileSize > stbuf.st_size)) {
            printf("Warning: file size less then minimal allowed: %d\n", minFileSize);
        }
        if ((maxFileSize != -1) && (maxFileSize < stbuf.st_size)) {
            printf("Warning: file size great then maximal allowed: %d\n", maxFileSize);
        }
    }
}

void PrintHelp() {
    printf("\t-- Command line mode: --\n./editor [/file FILE_NAME] [/command COMMAND_NAME] [/help]\n");
    printf("[/memsize PAGE_SIZE] [/minfilesize MIN_SIZE] [/maxfilesize MAX_SIZE]\n\n");
    printf("PAGE_SIZE - size of page for mapping.\n");
    printf("MIN_SIZE - minimum available size of file\n");
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
    printf("> help - print this message\n");
    printf("\n\t-- Available interactive mode commands: --\n");
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
    printf("cnt is %d\n", cnt);
    if (modified) {
        LinesInFile(filename);
        modified = 0;
    }
    if (!strcmp(data[0], "memsize")) {
        int newSize = atoi(data[1]);
        if (newSize > 0 && (newSize % pageSize) != 0)
            printf("Memory size must be multiple of PAGESIZE: %d\n", pageSize);
        else {
            pageSize = newSize;
            printf("Set new memory size: %d\n", pageSize);
        }
    }
    if (!strcmp(data[0], "minfilesize")) {
        minFileSize = atoi(data[1]);
    }
    if (!strcmp(data[0], "maxfilesize")) {
        maxFileSize = atoi(data[1]);
    }
    if (!strcmp(data[0], "getline")) {
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
        PrintLineOfFile(filename, lineToFind);
        return 0;
    }
    if (!strcmp(data[0], "remove")) {
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
        } else {
            printf("Wrong number of arguments! ");
            printf("Enter line number, position number and lenght of string you want to delete.\n");
            return 1;
        }
        return 0;
    }
    
    if (!strcmp(data[0], "insert")) {
        if (strlen(filename) == 0) {
            printf("Set filename first!\n");
            return 1;
        }
        int k;
        for (k = 0; k < cnt; k++) {
            //printf("%d: \"%s\"\n", k, data[k]);
        }
        if (cnt >= 4) { // command and one arg
            
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

            int count = 0;
            int q = 0;
            int begin = -1;
            int len = -1;
            int skip = 3;
            
            for (count = 0; count < strlen(cmd); count++) {
                char curCmd = cmd[count];
                //printf("curCmd: %c\n", curCmd);
                if (cmd[count] == 34) ++q;
                if (cmd[count] == 32) --skip;
                if (q == 1 || !skip) {
                    //printf("first quote, count: %d\n", count);
                    begin = count + 1;
                    //if (!skip) begin--;
                    --skip;
                    if (q == 1) ++q;
                }
                if (q == 3) {
                    //printf("second quote, count: %d\n", count);
                    len = count - begin;
                }
            }
            char trueText[20];
            strcpy(trueText, "");
            //printf("cmd: %s\nbegin = %d, len = %d\n", cmd, begin, len);
            strncat(trueText, cmd + begin, len);
            //printf("true text: \"%s\"\n", trueText);
            //printf("I'm gonna insert that text: \"%s\"\n", trueText);
            InsertText(filename, lineToIns, posToIns, trueText);
            
            
            
            modified = 1;
            
        } else {
            printf("Wrong number of arguments! ");
            printf("Enter line number, position number and text you want to insert.\n");
        }
        return 0;
    }

    if (!strcmp(data[0], "findline")) {
        if (strlen(filename) == 0) {
            printf("Set filename first!\n");
            return 1;
        }
        if (cnt == 2) { // command and one arg
            FindLine(filename, data[1], "");
        }
        else {
            FindLine(filename, data[2], data[1]);
        }
        return 0;
    }
    if (!strcmp(data[0], "fileinfo")) {
        if (strlen(filename) == 0) {
            printf("Set filename first!\n");
            return 1;
        }
        PrintFileInfo(filename);
        return 0;
    }
    if (!strcmp(data[0], "setfile")) {
        modified = 1;
        strcpy(filename, cmd + strlen(data[0]) + 1);
        if (maxFileSize != -1 && minFileSize != -1 && (totalBytes > maxFileSize || totalBytes < minFileSize) ) {
            printf("Error! Invalid file size.\n");
            return 1;
        }
        PrintFileInfo(filename);
        return 0;
    }
    printf("Unknown command: %s\n", data[0]);
    return 1;
}

//           MAIN FUCTION                //

int main(int argc, char** argv) {
    char filename[MAXPATH];
    char cmd[255];
    pageSize = sysconf(_SC_PAGESIZE);


    strcpy(filename, "");
    strcpy(cmd, "");
    __fpurge(stdin);
    //fflush(stdin);
    int i;
    int ins = -1;
    for (i = 0; i < argc; i++) {
        if (!strcmp(argv[i], "/file")) {
            strcpy(filename, argv[i + 1]);
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
            minFileSize = atoi(argv[i + 1]);
            i++;
        }
        if (!strcmp(argv[i], "/maxfilesize")) {
            maxFileSize = atoi(argv[i + 1]);
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
// findline [type] str
// sample: /file test.txt /command findline ^ mew
            if (!strcmp(cmd, "findline")) {
                strcat(cmd, " ");
                strcat(cmd, argv[i + 1]);
                i++;
                if (i < argc - 1) { // not last arg, i.e. read type but didn't read str
                                    // or may be there is a command
                    if (argv[i + 1][0] != '/') { // if next word is not a command 
                                                 // thus it is a str to find
                        strcat(cmd, " ");
                        strcat(cmd, argv[i + 1]);
                        i++;
                    }
                }
            }
// remove str pos len
// sample: /file test.txt /command remove 3 5 6
            if (!strcmp(cmd, "remove")) {
                strcat(cmd, " ");
                strcat(cmd, argv[i + 1]);
                i++;
                strcat(cmd, " ");
                strcat(cmd, argv[i + 1]);
                i++;
                strcat(cmd, " ");
                strcat(cmd, argv[i + 1]);
                i++;
            }
// insert str pos str
// sample: /file test.txt /command insert 3 5 "mda"
            if (!strcmp(cmd, "insert")) {
                strcat(cmd, " ");
                strcat(cmd, argv[i + 1]);
                i++;
                strcat(cmd, " ");
                strcat(cmd, argv[i + 1]);
                i++;
                strcat(cmd, " ");
                printf("text to ins: %s\n", argv[i + 1]);
                strcat(cmd, argv[i + 1]);
                ins = i + 1;
                i++;
            }
        }
        if (!strcmp(argv[i], "/help")) {
            PrintHelp();
        }
    }

    if ((strlen(cmd) > 0) && (strlen(filename) > 0)) {
        return ExecCmd(filename, cmd);
    }
    printf("\n *** Interactive mode ***\n");
    PrintFileInfo(filename);
    while (1) {
        printf("\nEnter command or 'help' for info:\n>");
        //fflush(stdin);
        __fpurge(stdin);
        fgets(cmd, 254, stdin);
        __fpurge(stdin);
        //fflush(stdin);
        if (cmd[strlen(cmd) - 1] == 10) { // new line
            cmd[strlen(cmd) - 1] = 0;
        }

        if (!strcmp(cmd, "exit")) {
            return 0;
        }
        if (!strcmp(cmd, "help")) {
            PrintHelp(); 
        } else if (ExecCmd(filename, cmd) > 0) {
            printf("Error executing command!\n");
        }
    }

    return 0;
}


////////////////////////////////////////////////////////////////////
/*                            INFO
Параметры командной строки:

/file имя_файла — позволяет задать имя файла для обработки. 
Если параметр не задан, в интерактивном режиме потребуется сначала выбрать файл.

/command команда — позволяет задать команду для выполнения сразу же после запуска программы. 
Если параметр не задан, то стартует интерактивный режим.

/memsize размер — позволяет указать размер окна для отображения файла в оперативную память. 
Он должен быть кратен размеру страницы памяти (обычно это 4096 байт). 
Если не задан, то размер окна по умолчанию равен размеру страницы.

/minfilesize размер — минимальный размер файла в байтах. 
Если задан, то при попытке открыть файл меньшего размера, будет предупреждение.

/maxfilesize размер — максимальный размер файла в байтах. 
Если задан, то при попытке открыть файл большего размера, будет предупреждение.

Справочник команд интерактивного режима:

help – вывод справки
exit – выход из программы
setfile – установка текущего файла, параметр — имя файла
fileinfo – вывести информацию текущего файла (имя, размер, число строк)
getline n – вывести строку номером n файла
findline [type] str – поиск строки str в файле. 
Если параметр type пропущен, то поиск идет в любом месте строки. 
Если параметр type равен символу «^» , то поиск идет только с начала строки. 
Если параметр type равен символу «$» , то поиск идет только с конца строки. 

*/
/////////////////////////////////////////////////////////////////////