#include "fiber.hpp"
#include "../context/context.hpp"
#include <cstdint>

Fiber::Fiber(void (*function)()) {
    stack_bottom = new char[4096];

    stack_top = stack_bottom + 4096;
    stack_top =
        reinterpret_cast<char *>(reinterpret_cast<uintptr_t>(stack_top) & -16L);
    stack_top -= 128;

    context = Context();
    context.rip = (void *)function;
    context.rsp = stack_top;
}

Fiber::~Fiber() { delete[] stack_bottom; }

Context *Fiber::get_context() { return &context; }
