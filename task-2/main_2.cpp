#include "fiber.hpp"
#include "scheduler.hpp"
#include <iostream>

Schedular S;

void foo() {
    std::cout << "called foo\n";
    S.fiber_exit();
}

void bar() {
    std::cout << "called bar\n";

    S.fiber_exit();
}

int main(int argc, char *argv[]) {
    Fiber f2(bar);
    Fiber f1(foo);

    S.spawn(&f1);
    S.spawn(&f2);
    S.spawn(&f2);

    S.do_it();
    S.do_it();
    S.do_it();
    return 0;
}
