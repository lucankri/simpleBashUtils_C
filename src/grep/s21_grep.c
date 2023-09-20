#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <pcre.h>
#include "s21_grep.h"

int fontColor = 0;

int main(int argc, char** argv) {
    char** filenames = NULL;

    char** flag_e_results = NULL;
    int flag_e_results_count = 0;

    char** flag_f_results = NULL;
    int flag_f_results_count = 0;

    char* pattern = NULL;
    int pattern_malloced = 0;

    int flag_ret = 0;
    int filenamesLength = 0;
    int flag_e = 0;
    int state_read_e_result = 0;
    int flag_i = 0;
    int flag_v = 0;
    int flag_c = 0;
    int flag_l = 0;
    int flag_n = 0;
    int flag_h = 0;
    int flag_s = 0;
    int flag_f = 0;
    int state_read_f_result = 0;
    int flag_o = 0;

    int hasEmptyPattern = 0;

    size_t patternLength = BUFFER_GROW;

    if (pattern == NULL) {
        pattern = calloc(patternLength, sizeof(char));
        if (pattern == NULL) {
            printf("Failed to allocate memory");
            flag_ret = 1;
        } else {
            pattern_malloced = 1;
        }
    }

    for (int i = 1; i < argc; i++) {
        char* argument = argv[i];
        if (state_read_e_result == 1) {
            if (flag_e_results == NULL) {
                flag_e_results = calloc(200, sizeof(char*));
            }
            if (flag_e_results != NULL) {
                flag_e_results[flag_e_results_count++] = argument;
                state_read_e_result = 0;
            } else {
                printf("Failed to allocate memory");
                flag_ret = 1;
            }
        } else if (state_read_f_result == 1) {
            if (flag_f_results == NULL) {
                flag_f_results = calloc(200, sizeof(char*));
            }
            if (flag_f_results != NULL) {
                flag_f_results[flag_f_results_count++] = argument;
                state_read_f_result = 0;
            } else {
                printf("Failed to allocate memory");
                flag_ret = 1;
            }
        } else if (argument[0] == '-') {
            int len = strlen(argument);
            for (int x = 1; x < len; x++) {
                if (state_read_e_result == 1) {
                    if (flag_e_results == NULL) {
                        flag_e_results = calloc(200, sizeof(char*));
                    }
                    if (flag_e_results != NULL) {
                        flag_e_results[flag_e_results_count++] = argument + x;
                        state_read_e_result = 0;
                        break;
                    } else {
                        printf("Failed to allocate memory");
                        flag_ret = 1;
                    }
                } else if (state_read_f_result == 1) {
                    if (flag_f_results == NULL) {
                        flag_f_results = calloc(200, sizeof(char*));
                    }
                    if (flag_f_results != NULL) {
                        flag_f_results[flag_f_results_count++] = argument + x;
                        state_read_f_result = 0;
                        break;
                    } else {
                        printf("Failed to allocate memory");
                        flag_ret = 1;
                    }
                } else {
                    if (argument[x] == 'e') {
                        flag_e = 1;
                        state_read_e_result = 1;
                    } else if (argument[x] == 'i') {
                        flag_i = 1;
                    } else if (argument[x] == 'v') {
                        flag_v = 1;
                    } else if (argument[x] == 'c') {
                        flag_c = 1;
                    } else if (argument[x] == 'l') {
                        flag_l = 1;
                    } else if (argument[x] == 'n') {
                        flag_n = 1;
                    } else if (argument[x] == 'h') {
                        flag_h = 1;
                    } else if (argument[x] == 's') {
                        flag_s = 1;
                    } else if (argument[x] == 'f') {
                        flag_f = 1;
                        state_read_f_result = 1;
                    } else if (argument[x] == 'o') {
                        flag_o = 1;
                    } else {
                        printf("%s: invalid option -- '%c'\n", argv[0], argument[x]);
                        flag_ret = 1;
                    }
                }
            }
        } else if (strlen(pattern) == 0 && flag_e == 0 && flag_f == 0) {
            strcat(pattern, argument);

        } else {
            if (filenames == NULL) {
                filenames = (char**)calloc(argc, sizeof(char*));
                if (filenames == NULL) {
                    printf("Failed to allocate memory");
                    flag_ret = 1;
                }
            }
            filenames[filenamesLength] = calloc(strlen(argument) + 1, sizeof(char));
            strcpy(filenames[filenamesLength], argument);
            filenamesLength++;
        }
    }

    if (flag_ret == 0 && strlen(pattern) == 0 && (flag_e == 1 || flag_f == 1)) {
        strcat(pattern, "(");

        int firstStrcat = 1;

        if (flag_e == 1 && flag_ret == 0) {
            for (int i = 0; i < flag_e_results_count; i++) {
                if (patternLength <= strlen(pattern) + strlen(flag_e_results[i]) + 5/* ),|,(,),\0 */) {
                    patternLength += BUFFER_GROW;
                    char* p = realloc(pattern, patternLength * sizeof(char));
                    if (p != NULL) {
                        pattern = p;
                        pattern_malloced = 1;
                    } else {
                        free(pattern);
                        flag_ret = 1;
                        pattern_malloced = 0;
                    }
                }
                if (flag_ret == 0 && flag_e_results[i][0] != '\0' &&
                        !(flag_e_results[i][0] == '\n' && flag_e_results[i][1] == '\0')) {
                    // если паттерн непустой, а также не является символом \n
                    if (firstStrcat == 0) {
                        strcat(pattern, "|");
                    }
                    firstStrcat = 0;
                    strcat(pattern, "(");
                    strcat(pattern, flag_e_results[i]);
                    strcat(pattern, ")");
                } else if (flag_ret == 0) {
                    // пустой паттерн не присоединяем, а помечаем флагом
                    hasEmptyPattern = 1;
                }
            }
        }

        if (flag_f == 1 && flag_ret == 0) {
            for (int i = 0; i < flag_f_results_count && flag_ret == 0; i++) {
                FILE* file = fopen(flag_f_results[i], "r");
                if (file != NULL) {
                    while (readLine(file) != 0) {
                        size_t targetLength = strlen(pattern) +
                            strlen(readLineResult) + 5/* for ),|,(,),\0 */;
                        if (patternLength < targetLength) {
                            patternLength += targetLength;
                            pattern = realloc(pattern, patternLength * sizeof(char));
                            if (pattern != NULL) {
                                pattern_malloced = 1;
                            } else {
                                free(pattern);
                                flag_ret = 1;
                                pattern_malloced = 0;
                            }
                        }
                        if (readLineResult[0] != '\0') {
                            if (firstStrcat == 0) {
                                strcat(pattern, "|");
                            }
                            firstStrcat = 0;
                            strcat(pattern, "(");
                            strcat(pattern, readLineResult);
                            strcat(pattern, ")");
                        } else {
                            // пустой паттерн не присоединяем, а помечаем флагом
                            hasEmptyPattern = 1;
                        }
                    }
                    fclose(file);
                } else if (flag_s == 0) {
                    printf("%s: %s: %s\n", argv[0], flag_f_results[i], strerror(errno));
                    flag_ret = 1;
                }
            }
        }

        if (flag_ret == 0) {
            strcat(pattern, ")");
        }

        if (strcmp(pattern, "()") == 0) {
            pattern[0] = '\0';
        }
    }

    if (flag_ret == 0) {
        const char* error;
        int erroffset;
        pcre* re;
        if (flag_i == 0) {
            re = pcre_compile((char *) pattern, 0, &error, &erroffset, NULL);
        } else {
            re = pcre_compile((char *) pattern, PCRE_CASELESS, &error, &erroffset, NULL);
        }

        if (re == NULL) {
            printf("%d: %s\n", erroffset, error);
            flag_ret = 1;
        }


        for (int i = 0; i < filenamesLength && flag_ret == 0; i++) {
            processFile(filenames[i], (filenamesLength > 1 && flag_h == 0) ? 1 : 0,
                    argv[0], re, flag_v, flag_c, flag_l, flag_n, flag_s, flag_o, hasEmptyPattern);
        }
        if (re != NULL) {
            pcre_free(re);
        }
    }
    if (pattern != NULL && pattern_malloced == 1) {
        free(pattern);
    }
    if (flag_e_results != NULL && flag_e == 1) {
        free(flag_e_results);
    }
    if (flag_f_results != NULL && flag_f == 1) {
        free(flag_f_results);
    }
    if (filenames != NULL) {
        for (int i = 0; i < filenamesLength; ++i) {
            free(filenames[i]);
        }
        free(filenames);
    }
    if (readLineResult != NULL) {
        free(readLineResult);
    }

    return 0;
}

/**
 * функция ищет в строке str паттерн pattern, и записывает результаты в виде пар индексов [начало, конец) в matches
 * @param matches массив для записи в него результата (матчей). Длина должна быть кратна 2
 * @param matchesLength длина массива matches
 * @return 0 если функция успешно отработала
 *  1 если длины массива matches недостаточно для записи всех матчей,
 **/ 
int search_pattern(pcre* pattern, char* str, int* matches, int matchesLength) {
    int ovector[30];
    int continueIndex = 0;
    int pointMatches = 0;
    int loop = 1;
    while (pcre_exec(pattern, NULL, str, strlen(str),
            continueIndex, 0, ovector, 30) > 0 && loop == 1) {
        if (ovector[1] > 0) {
            // если матч существенен, фиксируем его в матчах
            if (pointMatches < matchesLength) {
                matches[pointMatches] = ovector[0];
            } else {
                return 1;
            }
            if (pointMatches + 1 <= matchesLength) {
                matches[pointMatches + 1] = ovector[1];
            } else {
                return 1;
            }
            pointMatches += 2;

            continueIndex = ovector[1];

        } else if (ovector[1] == 0 && strlen(str) == 0) {
            if (pointMatches + 2 <= matchesLength) {
                matches[pointMatches] = 0;
                matches[pointMatches + 1] = 0;
            } else {
                return 1;
            }
            pointMatches += 2;

            loop = 0;
        } else {
            loop = 0;
        }
    }

    // прихнак конца последовательности
    if (pointMatches < matchesLength) {
        matches[pointMatches] = -1;
    } else {
        return 1;
    }

    return 0;
}

void printFilenames(char* filename, int flag_l) {
    if (flag_l == 0) {
        if (fontColor == 1) {
            printf("\033[35m");
        }
        printf("%s", filename);
        if (fontColor == 1) {
            printf("\033[36m");
        }
        printf(":");
        if (fontColor == 1) {
            printf("\033[0m");
        }
    } else {
        if (fontColor == 1) {
            printf("\033[35m");
        }
        printf("%s", filename);
        if (fontColor == 1) {
            printf("\033[36m\033[0m");
        }
        printf("\n");
    }
}

/**
 * @param printFilename 1, если нужно печатать имена файлов в каждой строке, и 0, если не нужно
 **/ 
void processFile(char* filename, int printFilename, char* commandName, pcre* pattern,
        int flag_v, int flag_c, int flag_l, int flag_n, int flag_s, int flag_o, int hasEmptyPattern) {
    FILE* file = fopen(filename, "r");
    if (file != NULL) {
        int flag_c_result = 0;
        int flag_l_result = 0;
        int flag_n_result = 1;
        int matchesLength = 150;

        int* matches = calloc(matchesLength, sizeof(int));
        while ((readLine(file)) != 0) {
            // printf("///read from file: [%s]\n", readLineResult);
            processFile_recursion(printFilename == 1 ? filename : NULL, pattern,
                    &matchesLength, &matches, flag_v, flag_c, &flag_c_result, flag_l,
                            &flag_l_result, flag_n, &flag_n_result, flag_o, hasEmptyPattern);
        }

        if (flag_c == 1 && flag_l == 0) {
            if (printFilename == 1) {
                printFilenames(filename, flag_l);
            }
            printf("%d\n", flag_c_result);
        } else if (flag_l == 1 && flag_l_result == 1) {
            printFilenames(filename, flag_l);
        }

        if (matches != NULL) {
            free(matches);
            matches = NULL;
        }
        fclose(file);
    } else {
        if (flag_s == 0) {
            printf("%s: %s: %s\n", commandName, filename, strerror(errno));
        }
    }
}

/**
 * @param filename NULL, если не надо печатать имя файла в каждой строке; и имя файла, если надо
 * @param flag_c_result хранит подсчитанное количество совпадений только если flag_c = 1
 **/
void processFile_recursion(char* filename, pcre* pattern, int* matchesLength,
        int** matches, int flag_v, int flag_c, int* flag_c_result, int flag_l,
                int* flag_l_result, int flag_n, int* flag_n_result, int flag_o, int hasEmptyPattern) {
    int result = search_pattern(pattern, readLineResult, *matches, *matchesLength);
    if (result == 0) {
        if (flag_l == 0) {
            if (flag_c == 0) {
                print_matches(filename, *matches, readLineResult, flag_l,
                    flag_n, flag_n_result, flag_o, flag_v, hasEmptyPattern);
                if (flag_n == 1) {
                    (*flag_n_result)++;
                }
            } else if (flag_c == 1) {
                if (hasPrintableAnything(*matches, flag_v, hasEmptyPattern) == 1) {
                    (*flag_c_result)++;
                }
            }
        } else {
            if (hasPrintableAnything(*matches, flag_v, hasEmptyPattern) == 1) {
                (*flag_l_result) = 1;
            }
        }
    } else if (result == 1) {
        *matchesLength += 150;
        *matches = realloc(*matches, *matchesLength * sizeof(int));
        processFile_recursion(filename, pattern, matchesLength, matches, flag_v,
                flag_c, flag_c_result, flag_l, flag_l_result, flag_n, flag_n_result, flag_o, hasEmptyPattern);
    }
}

void print_matches(char* filename, int* matches, char* str,
        int flag_l, int flag_n, int* flag_n_result, int flag_o, int flag_v, int hasEmptyPattern) {
    if (flag_o == 1 && strlen(str) == 0) {
        // если -o и пустая строка, то не печатать её
    } else if (flag_v == 1 && flag_o == 1) {
        // если -o и -v то не печатать строки
    } else {
        if (flag_o == 0) {
            if (hasPrintableAnything(matches, flag_v, hasEmptyPattern) == 1) {
                if (filename != NULL) {
                    printFilenames(filename, flag_l);
                }
                if (flag_n == 1) {
                    printf("%d:", *flag_n_result);
                }
            }
        }

        if (matches[0] != -1 && flag_v == 0) {
            // блок 3:
            int* m = matches;
            int continueIndex = 0;
            while (*m != -1) {
                int start = *m;
                int end = *(m + 1);
                if (flag_o == 0) {
                    for (int i = continueIndex; i < start; i++) {
                        printf("%c", str[i]);
                    }
                }

                if (flag_o == 1) {
                    if (filename != NULL) {
                        printFilenames(filename, flag_l);
                    }
                    if (flag_n == 1) {
                        printf("%d:", *flag_n_result);
                    }
                }

                if (fontColor == 1) {
                    printf("\033[31m");
                }
                for (int i = start; i < end; i++) {
                    printf("%c", str[i]);
                }
                if (fontColor == 1) {
                    printf("\033[0m");
                }
                if (flag_o == 1) {
                    printf("\n");
                }
                m += 2;
                continueIndex = end;
            }
            if (flag_o == 0) {
                for (int i = continueIndex; i < (int)strlen(str); i++) {
                    printf("%c", str[i]);
                }
                printf("\n");
            }
        } else if (flag_o == 0 && (
                (matches[0] == -1 && flag_v == 1 && hasEmptyPattern == 0)
                || (matches[0] == -1 && flag_v == 0 && hasEmptyPattern == 1))) {
            // блок 2:
            printf("%s\n", str);
        } else {
            // ничего не печатать
        }
    }
}

/**
 * Считывает строку из файла file и помещает её в readLineResult
 * @return 0, если достуигнут конец файла, иначе не 0
 **/
int readLine(FILE* file) {
    int ret = -1;
    if (feof(file) == 0) {
        char* str = readLineResult;
        int length = 0;
        char ch;
        int loop = 1;
        while (loop == 1) {
            ch = getc(file);
            if (readLineBufferSize <= length + 1) {
                readLineBufferSize += BUFFER_GROW;
                readLineResult = realloc(readLineResult, readLineBufferSize);
                str = readLineResult + length;
            }
            if (ch != '\n' && ch != EOF) {
                *str = ch;
                str++;
                length++;
            } else {
                if (ch == EOF && length == 0) {
                    ret = 0;
                }
                loop = 0;
            }
        }
        *str = '\0';
        if (ret == -1) {
            ret = 1;
        }
    } else {
        ret = 0;
    }
    return ret;
}

/**
 * В зависимости от флагов и найденных матчей определяет, 
 * предстоит ли печатать что-либо как результат работы grep
 **/ 
int hasPrintableAnything(int* matches, int flag_v, int hasEmptyPattern) {
    // если матчесы найдены и инверсия выключена,
    // либо матчесов нет и инверсия включена,
    // либо матчесов нет, но есть пустой паттерн
    return ((matches[0] != -1 && flag_v == 0)
        || (matches[0] == -1 && flag_v == 1 && hasEmptyPattern == 0)
        || (matches[0] == -1 && flag_v == 0 && hasEmptyPattern == 1)) ? 1 : 0;
}
