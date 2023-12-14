#include "fibers.hpp"
#include <cstdio>
#include <iostream>

void foo() {
    std::cout << "fiber 1 before\n";
    yield();
    std::cout << "fiber 1 after\n";
    fiber_exit();
}

void bar() {
    std::cout << "fiber 2\n";

    fiber_exit();
}

int main(int argc, char *argv[]) {
    spawn(foo);
    spawn(foo);
    spawn(bar);
    spawn(bar);

    do_it();
    do_it();

    return 0;
}
