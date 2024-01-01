#include "fiber.hpp"
#include "../context/context.hpp"
#include "../freelist.cpp"
#include <cstdint>
#include <cstdio>
#include <cstring>

MemoryManager manager(10);

Fiber::Fiber(unsigned id, void (*function)(), void *data, bool run,
             unsigned priority) {
    auto_run = run;

    stack = manager.alloc();

    this->id = id;
    this->data = data;
    this->priority = priority;

    context = new Context;
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
