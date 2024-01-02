#include "scheduler.hpp"
#include <context/context.hpp>
#include <cstdio>
#include <cstdlib>
#include <deque>

Schedular::Schedular() {
    context = Context();
    fibers = std::deque<Fiber *>();
    exit_flag = false;
    auto_run = false;
}

Schedular *Schedular::get_instance() {
    if (instance == nullptr) {
        instance = new Schedular;
    }

    return instance;
}

Schedular::~Schedular() {}

void Schedular::spawn(Fiber *f) { fibers.push_front(f); }

void Schedular::do_it() {
    get_context(&context);
    if (!fibers.empty()) {
        Fiber *f = fibers.back();

        if (!auto_run) {
            if (f->auto_run) {
                exit_flag = false;
            }

            if (exit_flag) {
                exit_flag = false;
                return;
            }
        }
        running_fibers.push_back(f);
        fibers.pop_back();

        Context *c = f->get_context();

        set_context(c);
    }
    exit_flag = false;
}

void Schedular::fiber_exit() {
    if (running_fibers.size() > 1) {
        running_fibers.pop_back();
        Context *c = running_fibers.back()->get_context();
        set_context(c);
    }

    exit_flag = true;
    Fiber *f = running_fibers.back();
    running_fibers.pop_back();
    delete f;
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

bool Schedular::is_running_task() { return !running_fibers.empty(); }

void Schedular::set_auto_run(bool val) { auto_run = val; }

Schedular *Schedular::instance = nullptr;
