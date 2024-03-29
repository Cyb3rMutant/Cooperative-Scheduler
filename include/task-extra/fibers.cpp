#include "fibers.hpp"
#include "fiber.hpp"
#include "scheduler.hpp"
#include <cstdio>

void fiber_exit() { Schedular::get_instance()->fiber_exit(); }

void yield() { Schedular::get_instance()->yield(); }

void spawn(void (*function)(), void *data, unsigned priority) {
    Fiber *f = new Fiber(
        function, data, Schedular::get_instance()->is_running_task(), priority);
    Schedular::get_instance()->spawn(f);
}
void do_it() { Schedular::get_instance()->do_it(); }

void auto_run() { Schedular::get_instance()->set_auto_run(true); }

void manual_run() { Schedular::get_instance()->set_auto_run(false); }
