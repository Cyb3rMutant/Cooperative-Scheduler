#include "fiber.hpp"
#include "../context/context.hpp"
#include <cstdint>
#include <cstdio>
#include <cstring>

Fiber::Fiber(void (*function)(), void *data, bool run) {
    auto_run = run;

    stack_bottom = new char[4096];

    stack_top = stack_bottom + 4096;
    stack_top =
        reinterpret_cast<char *>(reinterpret_cast<uintptr_t>(stack_top) & -16L);
    stack_top -= 128;

    this->data = data;

    context = new Context;
    context->rip = (void *)function;
    context->rsp = stack_top;
}

Fiber::~Fiber() { delete[] stack_bottom; }

Context *Fiber::get_context() { return context; }

void *Fiber::get_data() { return data; }
