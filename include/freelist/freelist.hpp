#pragma once
#include <cstdint>
#include <cstdio>
#include <iostream>

struct FiberStack {
    char *stack_bottom;
    char *stack_top;
    FiberStack *next;

    FiberStack(FiberStack *n = nullptr);

    ~FiberStack();
};

class MemoryManager {
  public:
    MemoryManager(unsigned s);

    FiberStack *alloc();

    void dealloc(FiberStack *n);

  private:
    FiberStack *head;
};
