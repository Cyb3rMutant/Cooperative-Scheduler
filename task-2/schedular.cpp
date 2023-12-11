#include "../context/context.hpp"
#include "scheduler.hpp"
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
        Fiber *f = fibers.back();
        fibers.pop_back();

        Context *c = f->get_context();

        set_context(c);
    } else {
        exit(0);
    }
}

void Schedular::fiber_exit() { set_context(&context); }
