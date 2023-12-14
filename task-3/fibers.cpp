#include "fibers.hpp"
#include "fiber.hpp"
#include "scheduler.hpp"
#include <cstdio>

Schedular S;

void fiber_exit() { S.fiber_exit(); }

void *get_data() {
    auto x = S.get_data();
    return x;
}

void yield() { S.yield(); }

void spawn(void (*function)(), void *data) {
    Fiber *f = new Fiber(function, data);

    S.spawn(f);
}
void do_it() { S.do_it(); }
