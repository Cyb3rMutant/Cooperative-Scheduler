.PHONY = example unit_test

CC = clang++
FLAGS = -I./include -g -std=c++17

TASK ?= 3
MAIN ?= 1

SRCS = $(wildcard include/task-$(TASK)/*.cpp)
CONTEXT = include/context/context.s
SIMPLETEST = include/simpletest/simpletest.cpp
FREELIST = include/freelist/freelist.cpp

example:
		$(CC) $(FLAGS) -o main examples/task-$(TASK)/main_$(MAIN).cpp $(SRCS) $(CONTEXT) $(FREELIST); ./main

unit_test:
		$(CC) $(FLAGS) -o main unit-tests/task-$(TASK).cpp $(SRCS) $(CONTEXT) $(SIMPLETEST) $(FREELIST); ./main
