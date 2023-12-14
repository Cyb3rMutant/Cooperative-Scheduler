#pragma once

#include "../context/context.hpp"
#include "fiber.hpp"
#include <deque>

class Schedular {
  public:
    Schedular();
    ~Schedular();

    void spawn(Fiber *f);
    void do_it();
    void fiber_exit();
    void *get_data();

    void yield();

  private:
    std::deque<Fiber *> fibers;
    std::deque<Fiber *> running_fibers;
    Context context;
    bool exit_flag;
    bool yield_flag;
};
