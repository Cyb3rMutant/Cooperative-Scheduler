#include "scheduler.hpp"
#include <context/context.hpp>
#include <cstdio>
#include <cstdlib>
#include <deque>

// Initialize the singleton instance to nullptr.
Schedular *Schedular::instance = nullptr;

Schedular::Schedular() {
    // Initialize the context and data structures.
    context = Context();
    fibers = std::deque<Fiber *>();
    running_fibers = std::deque<Fiber *>();
    exit_flag = false;
    auto_run = false;
}

Schedular *Schedular::get_instance() {
    // Singleton pattern: Get an instance of the Scheduler class.
    if (instance == nullptr) {
        instance = new Schedular;
    }

    return instance;
}

Schedular::~Schedular() {}

void Schedular::spawn(Fiber *f) { fibers.push_front(f); }

void Schedular::do_it() {
    // create a checkpoint for `fiber_exit`
    get_context(&context);
    if (!fibers.empty()) {
        // Get the next fiber to execute.
        Fiber *f = fibers.back();

        // Check if auto-run is disabled and the fiber requires manual
        // execution.
        if (!auto_run) {
            if (f->auto_run) {
                exit_flag = false;
            }

            if (exit_flag) {
                exit_flag = false;
                return;
            }
        }

        // Move the fiber to the running fibers queue and pop it from the
        // priority queue.
        running_fibers.push_back(f);
        fibers.pop_back();

        // Set the context to the selected fiber's context.
        set_context(f->get_context());
    }
    exit_flag = false;
}

void Schedular::fiber_exit() {
    // check if other fibers yielded, so they are still running
    if (running_fibers.size() > 1) {
        // Pop the current running fiber and set the context to the previous
        // one.
        running_fibers.pop_back();
        Context *c = running_fibers.back()->get_context();
        set_context(c);
    }

    // Set the exit flag and delete the terminated fiber.
    exit_flag = true;
    Fiber *f = running_fibers.back();
    running_fibers.pop_back();
    delete f;

    // Set the context back to the scheduler's context and go back to `do_it`.
    set_context(&context);
}

void *Schedular::get_data() { return running_fibers.back()->get_data(); }

void Schedular::yield() {
    if (!fibers.empty()) {
        // Save the context of the current running fiber.
        Context *out = running_fibers.back()->get_context();

        // Switch to the context of the next fiber in the queue.
        running_fibers.push_back(fibers.back());
        fibers.pop_back();
        Context *in = running_fibers.back()->get_context();

        // Perform the context switch.
        swap_context(out, in);
    }
}

bool Schedular::is_running_task() { return !running_fibers.empty(); }

void Schedular::set_auto_run(bool val) { auto_run = val; }
