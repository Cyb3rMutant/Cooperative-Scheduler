#include "scheduler.hpp"
#include <context/context.hpp>
#include <cstdio>
#include <cstdlib>
#include <deque>

Schedular::Schedular() {
    context = Context();
    fibers = std::deque<Fiber *>();
}

Schedular::~Schedular() {}

void Schedular::spawn(Fiber *f) { fibers.push_front(f); }

void Schedular::do_it() {
    get_context(&context);
    if (!fibers.empty()) {
        current_fiber = fibers.back();
        fibers.pop_back();

        Context *c = current_fiber->get_context();

        set_context(c);
    }
}

void Schedular::fiber_exit() { set_context(&context); }

void *Schedular::get_data() { return current_fiber->get_data(); }
