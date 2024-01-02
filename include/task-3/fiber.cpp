#include "fiber.hpp"
#include <context/context.hpp>
#include <cstdint>
#include <cstdio>
#include <cstring>

Fiber::Fiber(void (*function)(), void *data, bool run) {
    auto_run = run;

    // Allocate memory for the fiber's stack
    stack_bottom = new char[4096];

    // Set the stack top, aligning to a 16-byte boundary
    stack_top = stack_bottom + 4096;
    stack_top =
        reinterpret_cast<char *>(reinterpret_cast<uintptr_t>(stack_top) & -16L);
    stack_top -= 128;

    // Save the user-defined data
    this->data = data;

    // Create a new execution context for the fiber
    context = new Context;

    // Set the instruction pointer to the provided function
    context->rip = (void *)function;

    // Set the stack pointer to the top of the stack
    context->rsp = stack_top;
}

Fiber::~Fiber() { delete[] stack_bottom; }

Context *Fiber::get_context() { return context; }

void *Fiber::get_data() { return data; }
