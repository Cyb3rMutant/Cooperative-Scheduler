#pragma once

#include "../context/context.hpp"

class Fiber {
  public:
    bool auto_run;

    Fiber() = delete;
    Fiber(void (*function)(), void *data = nullptr, bool run = false);
    ~Fiber();

    Context *get_context();

    void *get_data();

  private:
    Context *context;
    char *stack_top;
    char *stack_bottom;
    void *data;
};
