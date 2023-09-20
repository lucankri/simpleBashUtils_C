GCC = gcc -Wall -Werror -Wextra -std=c11 -lm

all: clean s21_cat s21_grep

clean:
	rm -rf grep/*.o cat/*.cfg grep/*.cfg cat/*.o
	rm -rf cat/s21_cat
	rm -rf grep/s21_grep
	rm -rf cat/0* grep/0*
	rm -rf *.o *.a */0* grep/s21_GrepTest.txt grep/GrepTest.txt cat/log.txt

s21_cat: clean cat/s21_cat.c
	$(GCC) cat/s21_cat.c -c -o cat/s21_cat.o
	$(GCC) cat/s21_cat.o -o cat/s21_cat

s21_grep: clean grep/s21_grep.c
	$(GCC) grep/s21_grep.c -lpcre -o grep/s21_grep.o
	$(GCC) grep/s21_grep.c -lpcre -o grep/s21_grep

check:
	cppcheck cat/*.h cat/*.c
	cppcheck grep/*.h grep/*.c
	cp ../materials/linters/CPPLINT.cfg grep/CPPLINT.cfg
	cp ../materials/linters/CPPLINT.cfg cat/CPPLINT.cfg
	python3 ../materials/linters/cpplint.py --extension=c grep/*.c grep/*.h
	python3 ../materials/linters/cpplint.py --extension=c cat/*.c cat/*.h
