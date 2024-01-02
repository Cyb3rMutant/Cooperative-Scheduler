CC = clang++
FLAGS = -g -std=c++17 
TASK = task-3

build_it:
		$(CC) $(FLAGS) -o main $(TASK)/unit.cpp  $(TASK)/fibers.cpp $(TASK)/fiber.cpp $(TASK)/schedular.cpp context/context.cpp simpletest/simpletest.cpp; ./main
