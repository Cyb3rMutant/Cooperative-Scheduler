#include "freelist.hpp"
#include <cstdint>
#include <cstdio>
#include <iostream>

FiberStack::FiberStack(FiberStack *n) {

    stack_bottom = new char[4096];

    stack_top = stack_bottom + 4096;
    stack_top =
        reinterpret_cast<char *>(reinterpret_cast<uintptr_t>(stack_top) & -16L);
    stack_top -= 128;

    next = n;
}

FiberStack::~FiberStack() { delete[] stack_bottom; }

MemoryManager::MemoryManager(unsigned s) {
    head = new FiberStack();

    for (int i = 0; i < s; i++) {
        FiberStack *n = new FiberStack(head);
        head = n;
    }
}

FiberStack *MemoryManager::alloc() {
    if (!head)
        head = new FiberStack();
    FiberStack *n = head;
    head = head->next;
    return n;
}

void MemoryManager::dealloc(FiberStack *n) {
    n->next = head;
    head = n;
}
