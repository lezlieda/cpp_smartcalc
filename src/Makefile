SHELL = /bin/sh
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Werror -Wextra -g -c -O2
LIBFLAGS = -lgtest
SRC = tests/test.cc
OBJ = *.o
EXE = test
APP = SmartCalc_v2.app
TEXI2DVI = texi2dvi

all: clean tests

tests: clean
	$(CXX) $(CXXFLAGS) $(SRC)
	$(CXX) -o $(EXE) $(OBJ) $(LIBFLAGS)
	./$(EXE)

install:
	rm -rf ${PWD}/build
	mkdir ${PWD}/build
	qmake -qt=qt5 gui/Qt/SmartCalc_v2.pro -o ${PWD}/build
	$(MAKE) -C ${PWD}/build

uninstall:
	rm -rf ${PWD}/build

dist:
	rm -rf SmartCalc_v2.0
	mkdir SmartCalc_v2.0
	cp -r gui headers Makefile tests texinfo SmartCalc_v2.0/
	tar cvzf SmartCalc_v2.0.tgz SmartCalc_v2.0/
	mv SmartCalc_v2.0.tgz $(HOME)/Desktop/
	rm -rf SmartCalc_v2.0/
	
dvi:
	$(TEXI2DVI) -p texinfo/SmartCalc_v2.texi
	open SmartCalc_v2.pdf

gcov_report:
	$(CXX) $(CXXFLAGS) $(SRC) --coverage
	$(CXX) -o $(EXE) --coverage $(OBJ) $(LIBFLAGS)
	./$(EXE)
	gcovr -r . --html --html-details -o report.html --exclude tests --exclude-throw-branches --exclude-unreachable-branches
	open report.html

clean:
	rm -rf *.o *.a test *.gcda *.gcno *.gcov *.html *.css *.out *.pdf *.log *.aux *.dvi *.toc
	rm -rf ${PWD}/../build/*.o ${PWD}/../build/*.cpp ${PWD}/../build/*.h

rebuild: clean all
