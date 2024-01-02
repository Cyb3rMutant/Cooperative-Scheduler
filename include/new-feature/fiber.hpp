#pragma once

#include <context/context.hpp>
#include <freelist/freelist.hpp>

class Fiber {
  public:
    bool auto_run;

    Fiber() = delete;
    Fiber(unsigned id, void (*function)(), void *data = nullptr,
          bool run = false, unsigned priority = 1);
    ~Fiber();

    Context *get_context();

    void *get_data();

    bool operator<(const Fiber &other) const;

  private:
    Context *context;
    FiberStack *stack;
    void *data;
    unsigned priority;
    unsigned id;
};

struct CompareFiber {
    bool operator()(const Fiber *lhs, const Fiber *rhs) const;
};
