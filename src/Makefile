CC=gcc -std=c11
CFLAGS= -Wall -Wextra -Werror
GCOV_LIBS=--coverage
BUILD_PATH=./
SOURCES=main_test.c s21_matrix.c parser_2.0.c support_func.c
H=s21_matrix.h parser.h
LIBO=s21_calc.o
LIBA=s21_calc.a
EXE=test.out
MKF = makefile.qt # создаю файл чтоб читался как makefile для install

OS = $(shell uname)

ifeq ($(OS), Darwin)
	TST_LIBS=-lcheck -lm -g
else
	TST_LIBS=-lcheck -pthread -lrt -lm -D_GNU_SOURCE -lsubunit -lpthread -g
endif

all: install

build:
	mkdir build
	cd ./build/ && qmake ../ && make

install:
	make clean
	mkdir build
	qmake -o $(MKF) && make -f $(MKF) && make clean -f $(MKF) && rm $(MKF) && mv SmartCalc.app build  

uninstall:
	rm -rf build*

dist:
	rm -rf Archive_SmartCalc_v1.0/
	mkdir Archive_SmartCalc_v1.0/
	mkdir Archive_SmartCalc_v1.0/src
	cp Makefile *.c *.h *.pro *.cpp *.ui *.user Archive_SmartCalc_v1.0/src/
	tar cvzf Archive_SmartCalc_v1.0.tgz Archive_SmartCalc_v1.0/
	# mv Archive_SmartCalc_v1.0.tgz $(HOME)/Desktop/
	rm -rf Archive_SmartCalc_v1.0/

dvi: 
	open dvi.html

clean:
	@rm -rf *.a && rm -rf *.o *.out
	@rm -rf *.info && rm -rf *.gcda && rm -rf *.gcno &&  rm -rf *.gcov
	@rm -rf report/ && rm -rf *.
	@rm -rf main
	@rm -rf .qmake.stash	
	@rm -rf s21_calc
	@rm -rf ./build*
	@rm -rf SmartCalc
	@rm -rf SmartCalc Archive_SmartCalc_v1.0.tgz
	@rm -rf ./qt/build*

test: s21_calc.a
	$(CC) $(CFLAGS) tests.c -L. $(LIBA) $(TST_LIBS) -o $(BUILD_PATH)$(EXE)
	$(BUILD_PATH)$(EXE)

d: clean # dont use!
	$(CC) $(CFLAGS) $(TST_LIBS) $(SOURCES) -o main
	$(BUILD_PATH)main

rebuild: clean all

s21_calc.a: clean
	$(CC) $(CFLAGS) -c $(SOURCES) -o $(BUILD_PATH)$(LIBO)
	ar rcs $(LIBA) $(LIBO)
	ranlib $(LIBA)

gcov_report: s21_calc.a
	$(CC) $(CFLAGS) $(GCOV_LIBS) tests.c $(SOURCES) $(LIBA) -L. $(LIBA) $(TST_LIBS) -o $(BUILD_PATH)$(EXE)
	$(BUILD_PATH)$(EXE)
	lcov -t "test" -c -d $(BUILD_PATH) --output-file $(BUILD_PATH)coverage.info
	genhtml $(BUILD_PATH)coverage.info --output-directory $(BUILD_PATH)report/
	open ./report/index.html


leaks:
	CK_FORK=no valgrind --vgdb=no --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose --log-file=RESULT_VALGRIND.txt 	$(BUILD_PATH)$(EXE)

check:
	@echo
	@echo ===STYLE TEST===
	cp ../materials/linters/CPPLINT.cfg CPPLINT.cfg
	python3 ../materials/linters/cpplint.py --extension=c *.c *.h
	rm CPPLINT.cfg

rebuild: clean uninstall all

reinstall: clean uninstall install
