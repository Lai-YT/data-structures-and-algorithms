SRC = $(shell ls src/*)
TEST = $(shell ls test/*)

CXXFLAG = #-Wfatal-errors
bin/ut_main: test/ut_main.cpp $(SRC) $(TEST)
	g++ -std=c++17 $< -o $@ -lgtest -pthread $(CXXFLAG)
