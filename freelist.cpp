#pragma once
#include <cstdint>

struct FiberStack {
    char *stack_bottom;
    char *stack_top;
    FiberStack *next;

    FiberStack(FiberStack *n = nullptr) {

        stack_bottom = new char[4096];

        stack_top = stack_bottom + 4096;
        stack_top = reinterpret_cast<char *>(
            reinterpret_cast<uintptr_t>(stack_top) & -16L);
        stack_top -= 128;

        next = n;
    }

    ~FiberStack() { delete[] stack_bottom; }
};

class MemoryManager {
  public:
    MemoryManager(unsigned s) {
        head = new FiberStack();

        for (int i = 0; i < s; i++) {
            FiberStack *n = new FiberStack(head);
            head = n;
        }
    }

    FiberStack *alloc() {
        FiberStack *n = head;
        head = head->next;
        return n;
    }

    void dealloc(FiberStack *n) {
        n->next = head;
        head = n;
    }

  private:
    FiberStack *head;
};
