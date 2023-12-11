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

  private:
    std::deque<Fiber *> fibers;
    Context context;
};
