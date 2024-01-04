#include "fiber.hpp"
#include <context/context.hpp>
#include <cstdint>
#include <cstdio>
#include <cstring>
#include <freelist/freelist.hpp>
#include <iostream>

unsigned Fiber::next_id = 1;

MemoryManager manager(10);

Fiber::Fiber(void (*function)(), void *data, bool run, unsigned priority) {
    auto_run = run;

    // Allocating a fiber stack from the memory manager.
    stack = manager.alloc();

    // Assigning a unique identifier to the fiber.
    id = next_id++;

    // Assigning user-defined data and priority to the fiber.
    this->data = data;
    this->priority = priority;

    // Creating a new execution context for the fiber.
    context = new Context;

    // Setting the instruction pointer and stack pointer for the execution
    // context.
    context->rip = (void *)function;
    context->rsp = stack->stack_top;
}

Fiber::~Fiber() { manager.dealloc(stack); }

Context *Fiber::get_context() { return context; }

void *Fiber::get_data() { return data; }

bool Fiber::operator<(const Fiber &other) const {
    if (priority == other.priority) {
        return id > other.id;
    }
    return priority < other.priority;
}

bool CompareFiber::operator()(const Fiber *lhs, const Fiber *rhs) const {
    return *lhs < *rhs;
}
