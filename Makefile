.PHONY = example unit_test

CC = clang++
FLAGS = -I./include -g -std=c++17

TASK ?= task-3
MAIN ?= main_1

SRCS = $(wildcard include/$(TASK)/*.cpp)
CONTEXT = include/context/context.cpp
SIMPLETEST = include/simpletest/simpletest.cpp
FREELIST = include/freelist/freelist.cpp

example:
		$(CC) $(FLAGS) -o main examples/$(TASK)/$(MAIN).cpp $(SRCS) $(CONTEXT) $(FREELIST); ./main

unit_test:
		$(CC) $(FLAGS) -o main unit-tests/$(TASK).cpp $(SRCS) $(CONTEXT) $(SIMPLETEST) $(FREELIST); ./main
