#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include "s21_cat.h"

int main(int argc, char** argv) {
    char** inputFilenames = NULL;
    int inputFilenamesLength = 0;
    int flag_b = 0;
    int flag_e = 0;
    int flag_n = 0;
    int flag_s = 0;
    int flag_t = 0;
    int flag_v = 0;
    int newFile = 0;
    int firstFile = 1;
    int flag_return = 0;

    for (int x = 1; x < argc && flag_return == 0; x++) {
        char* argument = argv[x];
        // проверяем константы
        if (strcmp(argument, "--number-nonblank") == 0) {
            flag_b = 1;
        } else if (strcmp(argument, "--number") == 0) {
            flag_n = 1;
        } else if (strcmp(argument, "--squeeze-blank") == 0) {
            flag_s = 1;
        } else if (strncmp("--", argument, 2) == 0) {
            printf("%s: unrecognized option '%s'\n", argv[0], argument);
            flag_return = 1;
        } else if (argument[0] == '-' && flag_return == 0) {
            int len = strlen(argument);
            for (int i = 1; i < len && flag_return == 0; i++) {
                if (argument[i] == 'b') {
                    flag_b = 1;
                } else if (argument[i] == 'e') {
                    flag_e = 1;
                    flag_v = 1;
                } else if (argument[i] == 'E') {
                    flag_e = 1;
                } else if (argument[i] == 'n') {
                    flag_n = 1;
                } else if (argument[i] == 's') {
                    flag_s = 1;
                } else if (argument[i] == 't') {
                    flag_t = 1;
                    flag_v = 1;
                } else if (argument[i] == 'T') {
                    flag_t = 1;
                } else if (argument[i] == 'v') {
                    flag_v = 1;
                } else {
                    printf("%s: invalid option -- '%c'\n", argv[0], argument[i]);
                    flag_return = 1;
                }
            }
        } else {
            if (flag_return == 0) {
                if (inputFilenames == NULL) {
                    inputFilenames = (char**)malloc(argc * sizeof(char*));
                    if (inputFilenames == NULL) {
                        printf("Failed to allocate memory");
                        flag_return = 1;
                    }
                }
                if (flag_return == 0) {
                    inputFilenames[inputFilenamesLength] = argument;
                    inputFilenamesLength++;
                }
            }
        }
    }
    if (flag_return == 0) {
        if (inputFilenamesLength == 0) {
            processStdin(flag_b, flag_e, flag_n, flag_s, flag_t, flag_v);
        }
        for (int i = 0; i < inputFilenamesLength; i++) {
            processFile(inputFilenames[i], argv[0], flag_b, flag_e,
                    flag_n, flag_s, flag_t, flag_v, &newFile, &firstFile);
        }
        if (inputFilenames != NULL) {
            free(inputFilenames);
        }
    }
    return 0;
}


void processFile(char* filename, char* commandName, int flag_b,
        int flag_e, int flag_n, int flag_s, int flag_t, int flag_v, int* newFile, int* firstFile) {
    FILE* file = fopen(filename, "r");
    if (file != NULL) {
        unsigned char ch;

        struct state a;
        a.count = 0;
        a.emptySequence = 0;

        *newFile = 1;

        ch = getc(file);
        while (!feof(file)) {
            processChar(&a, ch, flag_b, flag_e, flag_n, flag_s, flag_t, flag_v, *newFile, *firstFile);
            ch = getc(file);
            *newFile = 0;
        }
        fclose(file);

        *firstFile = 0;
    } else {
        printf("%s: %s: %s\n", commandName, filename, strerror(errno));
    }
}

void processStdin(int flag_b, int flag_e, int flag_n, int flag_s, int flag_t, int flag_v) {
    unsigned char ch;

    struct state a;
    a.count = 0;
    a.emptySequence = 0;

    ch = getchar();
    while (1) {
        processChar(&a, ch, flag_b, flag_e, flag_n, flag_s, flag_t, flag_v, 0, 1);
        ch = getchar();
    }
}

void processChar(struct state* a, unsigned char ch, int flag_b,
            int flag_e, int flag_n, int flag_s, int flag_t, int flag_v, int newFile, int firstFile) {
    int continueWhile = 1;

    if (flag_s == 1) {
        if (a->count == 0 && ch == '\n') {
            if (a->emptySequence == 1) {
                continueWhile = 0;
            }
            a->emptySequence = 1;
        } else {
            a->emptySequence = 0;
        }
    }
    if (continueWhile == 1) {
        if (flag_b == 1 || flag_n == 1) {
            if (a->count == 0
                    && ((ch != '\n' && flag_b == 1) || (flag_n == 1 && flag_b == 0))
                    && (newFile == 0 || firstFile == 1)) {
                printf("%6d\t", strnumber);
                strnumber++;
            }
        }

        if (flag_e == 1 && ch == '\n') {
            printf("$");
        }

        if (ch == '\n') {
            a->count = 0;
        } else {
            a->count++;
        }
        if (flag_t == 1 && ch == '\t') {
            printf("^I");
        } else if (flag_v == 1) {
            printPrintableChar(ch);
        } else {
            printf("%c", ch);
        }
    }
}

void printPrintableChar(unsigned char ch) {
    if (ch < 32) {
        if (ch == '\t') {
            printf("\t");
        } else if (ch == '\n') {
            printf("\n");
        } else {
            printf("^%c", ch + 64);
        }
    } else if (ch >= 32 && ch < 128) {
        if (ch == 127) {
            printf("^%c", ch - 64);
        } else {
            printf("%c", ch);
        }
    } else if (ch >= 128 && ch < (128 + 32)) {
        printf("M-^%c", ((int)ch - 64));

    } else {
       printf("%c", ch);
    }
}
