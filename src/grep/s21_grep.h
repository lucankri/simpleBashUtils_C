#ifndef SRC_GREP_S21_GREP_H_
#define SRC_GREP_S21_GREP_H_
#include <stdio.h>
#include <pcre.h>

#define BUFFER_GROW 100

char* readLineResult = NULL;
int readLineBufferSize = 0;

int readLine(FILE* file);
void processFile(char* filename, int printFilename, char* commandName, pcre* pattern,
        int flag_v, int flag_c, int flag_l, int flag_n, int flag_s, int flag_o, int hasEmptyPattern);
int search_pattern(pcre* pattern, char* str, int* matches, int matchesLength);
void print_matches(char* filename, int* matches, char* str, int flag_l,
        int flag_n, int* flag_n_result, int flag_o, int flag_v, int hasEmptyPattern);
void processFile_recursion(char* filename, pcre* pattern, int* matchesLength,
        int** matches, int flag_v, int flag_c, int* flag_c_result, int flag_l, int* flag_l_result,
                int flag_n, int* flag_n_result, int flag_o, int hasEmptyPattern);
void printFilenames(char* filename, int flag_l);
int hasPrintableAnything(int* matches, int flag_v, int hasEmptyPattern);

#endif  // SRC_GREP_S21_GREP_H_
