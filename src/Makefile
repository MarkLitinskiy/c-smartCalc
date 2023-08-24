CC=gcc
CFLAGS=-std=c11 -Wall -Werror -Wextra -g -pedantic
PROFILE_FLAGS = -fprofile-arcs -ftest-coverage
OS = $(shell uname)

ifeq ($(OS), Linux)
#-lsubunit
	CHECKFLAGS=-lpthread -lcheck -pthread -lrt -lm
else
	CHECKFLAGS=-lcheck -lm -lpthread
endif

all: clean install dist dvi gcov_report check_style leaks clean

rebuild: clean all

install: uninstall
	mkdir build
	cp -rf calcFront.pro build
	cp -rf c build
	cp -rf cpp build
	cp -rf cpp/qcustomplot.h build
	cp -rf ui build
	cd build && qmake calcFront.pro
	make -C build
	cd build && make clean
	open ./build/calcFront.app/Contents/MacOS/calcFront

uninstall:
	rm -rf build
	make clean

dvi:
	open ./dvi_readme/readme.txt

dist:
	tar -cvf build/calculator.tar build
	gzip build/calculator.tar
	mv build/calculator.tar.gz ./

test:
	checkmk clean_mode=1 tests.check > tests.c
	$(CC) $(CFLAGS) $(CHECKFLAGS) c/*.c tests.c -o tests.out -lgcov --coverage
	./tests.out >> logfile.log

gcov_report: test
	lcov -t "test" -o report.info -c -d . 
	genhtml -o gcov_report/ report.info
	rm -f *.gcno *.gcda *.info report.out *.gcov
	open ./gcov_report/index.html

style:
	cp ../materials/linters/.clang-format ./
	clang-format -i ./c/*.c
	clang-format -i ./c/*.h
	clang-format -i ./cpp/*.cpp
	clang-format -i ./cpp/*.h
	rm -rf .clang-format

check_style:
	cp ../materials/linters/.clang-format ./
	clang-format -n c/*.c >> logfile.log
	clang-format -n c/*.h >> logfile.log
	clang-format -n cpp/*.cpp >> logfile.log
	clang-format -n cpp/*.h >> logfile.log
	rm -rf .clang-format

# запуск через sh run.sh с запущенным докером
valgrind:
	$(CC) $(CFLAGS) c/*.c c/creditCalculation/*.c c/depositCalculation/*.c tests.c -o tests.out $(CHECKFLAGS)
	 CK_FORK=no valgrind --vgdb=no --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose ./tests.out
	 make clean

leaks: test
	CK_FORK=no leaks --atExit -- ./tests.out >> logfile.log
	make clean

clean:
	rm -rf *.o \
		*.a \
		*.app \
		*.so \
		*.gcno \
		*gcda \
		*.gcov \
		gcov_report.* \
		*.dSYM \
        RESULT_VALGRIND.txt \
		*.out \
        unit-test \
        vtests_run \
		run \
		gcov \
		report/ \
		gcov_report/ \
		report.info \
		gcov_report \
		gcov_test \
