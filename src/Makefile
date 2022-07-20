CC = gcc
CFLAGS =-Wall -Wextra -Werror -pedantic -std=c11
CFLAGS_TEST =`pkg-config --cflags --libs check`
CFLAGS_GCOV =-fprofile-arcs -ftest-coverage
ALL_SOURCES_C = polish/polish_tests.c polish/structures.c polish/polish.c
ALL_SOURCES_H = polish/structures.h polish/polish.h
OUTFILE_TEST = polish/polish_tests

all: prepare
	make -f qMakefile

install: all
	@test -d bin || mkdir -p bin
	rm -f -r bin/SmartCalc.app
	/usr/local/bin/qmake -install qinstall SmartCalc.app bin/SmartCalc.app
	-strip bin/SmartCalc.app/Contents/MacOS/SmartCalc

uninstall: prepare
	-rm -f -r bin/SmartCalc.app
	-rmdir bin/

clean: prepare
	@-rm polish/*.gcov polish/*.gcda polish/*.gcno polish/*.info 2>/dev/null
	@-rm polish/polish_tests 2>/dev/null
	@-rm -rf polish/lcov_report 2>/dev/null
	@# @make -f qMakefile clean
	@-rm -rf SmartCalc.app
	@-rm qMakefile

dvi:
	# brew install doxygen
	cd doc && doxygen doxygen.conf

dist:
	tar -czpf smartcalc.tar.gz polish *.cpp *.h *.ui Makefile SmartCalc.pro SmartCalc.pro.user

tests:
	@ echo
	@ echo "*** TESTS ***"
	$(CC) $(CFLAGS) $(CFLAGS_TEST) $(ALL_SOURCES_C) -o $(OUTFILE_TEST)
	polish/polish_tests

gcov_report:
	@$(CC) $(CFLAGS) $(CFLAGS_TEST) $(CFLAGS_GCOV) $(ALL_SOURCES_C) -o $(OUTFILE_TEST)
	@$(OUTFILE_TEST)
	@cd polish
	@gcov polish_tests
	@mv *.gcov polish
	@mv *.gcda polish
	@mv *.gcno polish
	@lcov --capture --directory polish --output-file polish/main_coverage.info
	@genhtml polish/main_coverage.info --output-directory polish/lcov_report

prepare:
	qmake -o qMakefile

checkall: style check leaks

style:
	@ echo
	@ echo "*** STYLE ***"
	cp ../materials/linters/CPPLINT.cfg .
	python3 ../materials/linters/cpplint.py --extensions=c $(ALL_SOURCES_C) $(ALL_SOURCES_H)

check:
	@ echo
	@ echo "*** CHECK ***"
	cppcheck --enable=all --suppress=missingIncludeSystem --suppress=unusedFunction $(ALL_SOURCES_C) $(ALL_SOURCES_H)

leaks: tests
	@ echo
	@ echo "*** LEAKS ***"
	CK_FORK=no leaks --atExit -- polish/polish_tests

brew:
	# cd ~/goinfre
	# git clone https://github.com/Homebrew/brew homebrew
	# eval "$(~/goinfre/homebrew/bin/brew shellenv)"
	# brew install lcov
