.PHONY: dirs clean

SRC = $(shell ls src/*)
TEST = $(shell ls test/*)

all: dirs bin/ut_main

CXXFLAG = -Wfatal-errors
bin/ut_main: test/ut_main.cpp $(SRC) $(TEST)
	g++ -std=c++17 $< -o $@ -lgtest -pthread $(CXXFLAG)

test: all
	bin/ut_main

dirs:
	mkdir -p bin

clean:
	rm -f bin/*
