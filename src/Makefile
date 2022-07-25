CC = gcc
CFLAGS =-Wall -Wextra -Werror -pedantic -std=c11
CFLAGS_TEST =`pkg-config --cflags --libs check`
CFLAGS_GCOV =-fprofile-arcs -ftest-coverage
ALL_SOURCES_C = cfiles/tests.c cfiles/objfiles.c cfiles/affine.c
ALL_SOURCES_H = cfiles/objfiles.h cfiles/affine.h
OUTFILE_TEST = cfiles/tests

all: prepare
	make -f qMakefile

install: all
	@test -d bin || mkdir -p bin
	rm -f -r bin/3DViewer.app
	/usr/local/bin/qmake -install qinstall 3DViewer.app bin/3DViewer.app
	-strip bin/3DViewer.app/Contents/MacOS/3DViewer

uninstall: prepare
	-rm -f -r bin/3DViewer.app
	-rmdir bin/

clean: prepare
	@-rm cfiles/*.gcov cfiles/*.gcda cfiles/*.gcno cfiles/*.info 2>/dev/null
	@-rm cfiles/tests 2>/dev/null
	@-rm -rf cfiles/lcov_report 2>/dev/null
	@# @make -f qMakefile clean
	@-rm -rf 3DViewer.app
	@-rm qMakefile

dvi:
	# brew install doxygen
	cd doc && doxygen doxygen.conf

dist:
	tar -czpf 3dviewer.tar.gz cfiles *.cpp *.h *.ui Makefile 3DViewer.pro 3DViewer.pro.user

tests:
	@ echo
	@ echo "*** TESTS ***"
	$(CC) $(CFLAGS) $(CFLAGS_TEST) $(ALL_SOURCES_C) -o $(OUTFILE_TEST)
	$(OUTFILE_TEST)

gcov_report:
	@$(CC) $(CFLAGS) $(CFLAGS_TEST) $(CFLAGS_GCOV) $(ALL_SOURCES_C) -o $(OUTFILE_TEST)
	@$(OUTFILE_TEST)
	@cd cfiles
	@gcov tests
	@mv *.gcov cfiles
	@mv *.gcda cfiles
	@mv *.gcno cfiles
	@lcov --capture --directory cfiles --output-file cfiles/main_coverage.info
	@genhtml cfiles/main_coverage.info --output-directory cfiles/lcov_report

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
	CK_FORK=no leaks --atExit -- $(OUTFILE_TEST)

brew:
	# cd ~/goinfre
	# git clone https://github.com/Homebrew/brew homebrew
	# eval "$(~/goinfre/homebrew/bin/brew shellenv)"
	# brew install lcov
