GCC = gcc -Wall -Werror -Wextra -std=c11 -lm

all: clean s21_grep

clean:
	rm -rf */*.o ../cat/*.cfg *.cfg ../cat/*.o
	rm -rf ../cat/s21_cat
	rm -rf s21_grep
	rm -rf ../cat/0* */0*
	rm -rf *.o *.a s21_GrepTest.txt GrepTest.txt ../cat/log.txt

s21_grep: clean s21_grep.c
	$(GCC) s21_grep.c -lpcre -c -o s21_grep.o
	$(GCC) s21_grep.o -lpcre -o s21_grep

check:
	cppcheck ../cat/*.h ../cat/*.c
	cppcheck *.h *.c
	cp ../../materials/linters/CPPLINT.cfg ../cat/CPPLINT.cfg
	cp ../../materials/linters/CPPLINT.cfg CPPLINT.cfg
	python3 ../../materials/linters/cpplint.py --extension=c ../cat/*.c ../cat/*.h
	python3 ../../materials/linters/cpplint.py --extension=c *.c *.h

t: s21_grep
	sh tests.sh