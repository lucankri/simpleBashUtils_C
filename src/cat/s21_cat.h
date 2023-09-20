#ifndef SRC_CAT_S21_CAT_H_
#define SRC_CAT_S21_CAT_H_

struct state {
    int count;
    // только для flag_b и flag_n
    // int strnumber;
    // только для flag_s
    int emptySequence;
};

int strnumber = 1;
void printfile(char* filename, char* commandName, int flag_b,
        int flag_e, int flag_n, int flag_s, int flag_t, int flag_v);
void processChar(struct state* a, unsigned char c, int flag_b, int flag_e,
        int flag_n, int flag_s, int flag_t, int flag_v, int newFile, int firstFile);
void processStdin(int flag_b, int flag_e, int flag_n, int flag_s, int flag_t, int flag_v);
void processFile(char* filename, char* commandName, int flag_b, int flag_e,
        int flag_n, int flag_s, int flag_t, int flag_v, int* newFile, int* firstFile);
void printPrintableChar(unsigned char ch);

#endif  // SRC_CAT_S21_CAT_H_
