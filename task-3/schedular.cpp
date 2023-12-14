#include "../context/context.hpp"
#include "scheduler.hpp"
#include <cstdio>
#include <cstdlib>
#include <deque>

Schedular::Schedular() {
    context = Context();
    fibers = std::deque<Fiber *>();
    exit_flag = false;
}

Schedular::~Schedular() {}

void Schedular::spawn(Fiber *f) { fibers.push_front(f); }

void Schedular::do_it() {
    get_context(&context);
    if (exit_flag) {
        exit_flag = false;
        return;
    }
    if (!fibers.empty()) {
        running_fibers.push_back(fibers.back());
        fibers.pop_back();

        Context *c = running_fibers.back()->get_context();

        set_context(c);
    }
}

void Schedular::fiber_exit() {

    if (running_fibers.size() > 1) {
        running_fibers.pop_back();
        Context *c = running_fibers.back()->get_context();
        set_context(c);
    }

    exit_flag = true;
    running_fibers.pop_back();
    set_context(&context);
}

void *Schedular::get_data() { return running_fibers.back()->get_data(); }

void Schedular::yield() {
    if (!fibers.empty()) {
        Context *out = running_fibers.back()->get_context();

        running_fibers.push_back(fibers.back());
        fibers.pop_back();

        Context *in = running_fibers.back()->get_context();

        swap_context(out, in);
    }
}
