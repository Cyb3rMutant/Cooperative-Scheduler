#pragma once

#include "../context/context.hpp"
#include "fiber.hpp"
#include <deque>

class Schedular {
  public:
    static Schedular *get_instance();

    Schedular(Schedular &other) = delete;
    void operator=(const Schedular &) = delete;
    ~Schedular();

    void spawn(Fiber *f);
    void do_it();
    void fiber_exit();
    void *get_data();

    void yield();

    bool is_running_task();

    static Schedular *instance;

  private:
    Schedular();

    std::deque<Fiber *> fibers;
    std::deque<Fiber *> running_fibers;
    Context context;
    bool exit_flag;
    bool yield_flag;
};
