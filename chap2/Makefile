.PHONY: dirs clean

DEPEND = $(shell ls **/*.hpp)

all: dirs mbin/main

bin/ut_main: unittest/ut_main.cpp $(DEPEND)
	g++ -o $@ $< -lgtest -lpthread

bin/main: main.cpp $(DEPEND)
	g++ -o $@ $<

dirs:
	mkdir -p bin

clean:
	rm -r bin/*
