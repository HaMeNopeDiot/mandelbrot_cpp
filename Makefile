SRC_DIR = src
OBJ_DIR = objs
TESTS_DIR = tests
TEST_MFS := $(wildcard $(TESTS_DIR)/*/Makefile)
TESTS := $(foreach mkf, $(TEST_MFS), $(notdir $(patsubst %/,%, $(dir $(mkf)))))

SOURCES = $(wildcard $(SRC_DIR)/*.cpp $(TESTS_DIR)/*.cpp)
OBJECTS = $(foreach src_file, $(SOURCES), $(OBJ_DIR)/$(notdir $(src_file:.cpp=.o)))

BASE = mandelbrot_cpp

CC = clang++

CFLAGS = -Og -g3 -Wall -I$(SRC_DIR)
LDFLAGS = 

OBJ_DIR_EX := $(shell mkdir -p $(OBJ_DIR) && echo $(OBJ_DIR))

all: $(BASE)

$(BASE): .depend $(OBJECTS)
	$(CC) $(filter-out .depend,$^) -Og -g -o "$@" $(LDFLAGS)  # Добавляем линковочные флаги

.depend: $(SOURCES)
	rm -f "$@"
	$(CC) $(CFLAGS) -MM $^ -MF "$@"

include .depend

$(OBJ_DIR_EX)/%.o: $(SRC_DIR)/%.cpp
	$(CC) $(CFLAGS) -c -o $@ $<

$(OBJ_DIR_EX)/%.o: $(TESTS_DIR)/%.cpp
	$(CC) $(CFLAGS) -c -o $@ $<

CLEANFILES = $(BASE) .depend $(OBJ_DIR)/*.o

.PHONY: clean
clean:
	rm -f $(CLEANFILES)