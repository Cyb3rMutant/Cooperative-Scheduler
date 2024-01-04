#include "freelist.hpp"
#include <cstdint>
#include <cstdio>
#include <iostream>

FiberStack::FiberStack(FiberStack *n) {
    // Allocate a new char array as the stack and set the bottom pointer.
    stack_bottom = new char[4096];

    // Set the top pointer to the end of the stack and align it to a 16-byte
    // boundary.
    stack_top = stack_bottom + 4096;
    stack_top =
        reinterpret_cast<char *>(reinterpret_cast<uintptr_t>(stack_top) & -16L);
    stack_top -= 128;

    // Set the next pointer to the provided value.
    next = n;
}

FiberStack::~FiberStack() {
    // Deallocate the memory allocated for the stack.
    delete[] stack_bottom;
}

MemoryManager::MemoryManager(unsigned s) {
    // Initialize the head with a new FiberStack.
    head = new FiberStack();

    // Create additional FiberStacks and link them in a linked list.
    for (int i = 0; i < s; i++) {
        FiberStack *n = new FiberStack(head);
        head = n;
    }
}

FiberStack *MemoryManager::alloc() {
    // Create a new FiberStack if the head is null.
    if (!head)
        head = new FiberStack();

    // Get the current head and update it to the next FiberStack in the list.
    FiberStack *n = head;
    head = head->next;

    return n;
}

void MemoryManager::dealloc(FiberStack *n) {
    // Link the provided FiberStack to the head of the list.
    n->next = head;
    head = n;
}
