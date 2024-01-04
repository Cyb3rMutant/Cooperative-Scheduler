#include "scheduler.hpp"
#include <context/context.hpp>
#include <cstdio>
#include <cstdlib>
#include <deque>

Schedular::Schedular() {
    // Initialize the context and data structures.
    context = Context();
    fibers = std::deque<Fiber *>();
}

Schedular::~Schedular() {}

void Schedular::spawn(Fiber *f) { fibers.push_front(f); }

void Schedular::do_it() {
    // create a checkpoint for `fiber_exit`
    get_context(&context);
    if (!fibers.empty()) {
        // Get the next fiber to execute and pop it from the queue.
        current_fiber = fibers.back();
        fibers.pop_back();

        // Set the context to the selected fiber's context.
        set_context(current_fiber->get_context());
    }
}

// Set the context back to the scheduler's context and go back to `do_it`.
void Schedular::fiber_exit() { set_context(&context); }

void *Schedular::get_data() { return current_fiber->get_data(); }
