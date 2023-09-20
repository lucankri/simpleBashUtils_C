GCC = gcc -Wall -Werror -Wextra -std=c11 -lm

all: clean s21_cat

clean:
	rm -rf */*.o ../grep/*.cfg *.cfg ../grep/*.o
	rm -rf s21_cat
	rm -rf ../grep/s21_grep
	rm -rf ../cat/0* */0*
	rm -rf *.o *.a ../grep/s21_GrepTest.txt ../grep/GrepTest.txt log.txt

s21_cat: clean s21_cat.c
	$(GCC) s21_cat.c -c -o s21_cat.o
	$(GCC) s21_cat.o -o s21_cat


check:
	cppcheck *.h *.c
	cppcheck ../grep/*.h ../grep/*.c
	cp ../../materials/linters/CPPLINT.cfg ../grep/CPPLINT.cfg
	cp ../../materials/linters/CPPLINT.cfg CPPLINT.cfg
	python3 ../../materials/linters/cpplint.py --extension=c ../grep/*.c ../grep/*.h
	python3 ../../materials/linters/cpplint.py --extension=c *.c *.h
