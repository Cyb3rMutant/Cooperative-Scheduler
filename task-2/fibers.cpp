#include "fibers.hpp"
#include "fiber.hpp"
#include "scheduler.hpp"

Schedular S;

void fiber_exit() { S.fiber_exit(); }

void *get_data();

void yield();

void spawn(void (*function)(), void *data) {
    Fiber *f = new Fiber(function);

    S.spawn(f);
}
void do_it() { S.do_it(); }
