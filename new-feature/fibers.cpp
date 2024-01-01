#include "fibers.hpp"
#include "fiber.hpp"
#include "scheduler.hpp"
#include <cstdio>

void fiber_exit() { Schedular::get_instance()->fiber_exit(); }

void yield() { Schedular::get_instance()->yield(); }

void spawn(void (*function)(), void *data, unsigned priority) {
    Schedular::get_instance()->spawn(function, data, priority);
}
void do_it() { Schedular::get_instance()->do_it(); }
