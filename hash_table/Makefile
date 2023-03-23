.PHONY: valgrind fmt clean help

#Color definition for print purpose
COLOR_PREFIX := e
YELLOW=\$(COLOR_PREFIX)[0;33m
BLUE=\$(COLOR_PREFIX)[1;34m
END_COLOR=\$(COLOR_PREFIX)[0m

BINDIR := build
SRCDIR := src
LOGDIR := log
LIBDIR := lib
TESTDIR := test


BINARY := main
TEST_BINARY := ut_$(BINARY)

CC := gcc
STD := -std=gnu99
WARNS := -Wall -Wextra -pedantic
CFLAGS := -O3 $(STD) $(WARNS)
DEBUG := -g3 -DDEBUG=1
# Dependency libraries
LIBS := -lm
# Test libraries
TEST_LIBS :=

SRCEXT := c
#%.o file names
NAMES := $(notdir $(basename $(wildcard $(SRCDIR)/*.$(SRCEXT))))
OBJECTS := $(patsubst %,$(LIBDIR)/%.o,$(NAMES))

default: all

DESCRIPTION := An open-addressed, double hashed hash table in C.
# Help message
help:
	@echo "$(YELLOW)Hash Table$(END_COLOR)"
	@echo "    $(DESCRIPTION)"
	@echo
	@echo "Target rules:"
	@echo "    all      - Compiles and generates binary file"
	@echo "    tests    - Compiles and runs tests binary file"
	@echo "    valgrind - Runs test binary file using valgrind tool"
	@echo "    fmt      - Formats the source and test files"
	@echo "    clean    - Cleans the project by removing binaries"
	@echo "    help     - Prints a help message with target rules"

# Rule for link and generate the binary file
all: $(OBJECTS)
	@echo -n "$(YELLOW)LD $(END_COLOR)"
	$(CC) -o $(BINDIR)/$(BINARY) $+ $(DEBUG) $(CFLAGS) $(LIBS)
	@echo "\n--\nBinary file placed at" \
			  "$(BINDIR)/$(BINARY)"

# Rule for object binaries compilation
$(LIBDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
	@echo -n "$(YELLOW)CC $(END_COLOR)"
	$(CC) -c $^ -o $@ $(DEBUG) $(CFLAGS) $(LIBS)

# Compile tests and run the test binary
tests: all
	@echo -n "$(YELLOW)CC $(END_COLOR)"
	$(CC) $(TESTDIR)/$(TEST_BINARY).c -o $(BINDIR)/$(TEST_BINARY) \
		$(shell find $(LIBDIR) -name *.o ! -name main.o) $(DEBUG) $(CFLAGS) $(LIBS)
	@echo -n "\n--\nRunning tests: "
	./$(BINDIR)/$(TEST_BINARY)

# Rule for run valgrind tool
valgrind:
	valgrind \
		--track-origins=yes \
		--leak-check=full \
		--leak-resolution=high \
		--log-file=$(LOGDIR)/$@.log \
		$(BINDIR)/$(TEST_BINARY)
	@echo "\nCheck the log file: $(LOGDIR)/$@.log"

# Rule for formatting the source code using clang-format
fmt:
	@clang-format -i \
		-style=file \
		$(SRCDIR)/* $(TESTDIR)/*

# Rule for cleaning the project
clean:
	@rm -rvf $(BINDIR)/* $(LIBDIR)/* $(LOGDIR)/*
