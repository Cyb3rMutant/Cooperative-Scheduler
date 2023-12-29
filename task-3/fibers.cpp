#include "fibers.hpp"
#include "fiber.hpp"
#include "scheduler.hpp"
#include <cstdio>

void fiber_exit() { Schedular::get_instance()->fiber_exit(); }

void yield() { Schedular::get_instance()->yield(); }

void spawn(void (*function)(), void *data) {
    Fiber *f =
        new Fiber(function, data, Schedular::get_instance()->is_running_task());

    Schedular::get_instance()->spawn(f);
}
void do_it() { Schedular::get_instance()->do_it(); }
