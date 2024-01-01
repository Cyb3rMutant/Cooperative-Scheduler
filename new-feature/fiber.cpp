#include "fiber.hpp"
#include "../context/context.hpp"
#include <cstdint>
#include <cstdio>
#include <cstring>

Fiber::Fiber(unsigned id, void (*function)(), void *data, bool run,
             unsigned priority) {
    auto_run = run;

    stack_bottom = new char[4096];

    stack_top = stack_bottom + 4096;
    stack_top =
        reinterpret_cast<char *>(reinterpret_cast<uintptr_t>(stack_top) & -16L);
    stack_top -= 128;

    this->id = id;
    this->data = data;
    this->priority = priority;

    context = new Context;
    context->rip = (void *)function;
    context->rsp = stack_top;
}

Fiber::~Fiber() { delete[] stack_bottom; }

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
