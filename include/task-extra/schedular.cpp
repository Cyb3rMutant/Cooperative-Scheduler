#include "scheduler.hpp"
#include <context/context.hpp>
#include <cstdio>
#include <cstdlib>
#include <deque>
#include <queue>

// Initialize the singleton instance to nullptr.
Schedular *Schedular::instance = nullptr;

Schedular::Schedular() {
    // Initialize the context and data structures.
    context = Context();
    fibers = std::priority_queue<Fiber *, std::vector<Fiber *>, CompareFiber>();
    current_fiber = nullptr;
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

void Schedular::spawn(Fiber *f) { fibers.push(f); }

void Schedular::do_it() {
    // create a checkpoint for `fiber_exit`
    get_context(&context);
    if (!fibers.empty()) {
        // Get the next fiber to execute.
        Fiber *f = fibers.top();

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
        current_fiber = f;
        fibers.pop();

        // Set the context to the selected fiber's context.
        set_context(f->get_context());
    }
    exit_flag = false;
}

void Schedular::fiber_exit() {
    // Set the exit flag and delete the terminated fiber.
    exit_flag = true;
    delete current_fiber;
    current_fiber = nullptr;

    // Set the context back to the scheduler's context and go back to `do_it`.
    set_context(&context);
}

void *Schedular::get_data() { return current_fiber->get_data(); }

void Schedular::yield() {
    if (!fibers.empty()) {
        // Save the context of the current running fiber.
        current_fiber->update_id();
        spawn(current_fiber);
        Context *out = current_fiber->get_context();

        // Switch to the context of the next fiber in the queue.
        current_fiber = fibers.top();
        fibers.pop();
        Context *in = current_fiber->get_context();

        // Perform the context switch.
        swap_context(out, in);
    }
}

bool Schedular::is_running_task() { return current_fiber != nullptr; }

void Schedular::set_auto_run(bool val) { auto_run = val; }
