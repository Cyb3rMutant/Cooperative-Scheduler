#pragma once

#include "../context/context.hpp"

class Fiber {
  public:
    Fiber() = delete;
    Fiber(void (*function)());
    ~Fiber();

    Context *get_context();

  private:
    Context context;
    char *stack_top;
    char *stack_bottom;
};
