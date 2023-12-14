#include "fibers.hpp"
#include <cstdio>
#include <iostream>

void foo() {
    std::cout << "fiber 1 before";
    yield();
    std::cout << "fiber 1 after";
    fiber_exit();
}

void bar() {
    std::cout << "fiber 2";

    fiber_exit();
}

int main(int argc, char *argv[]) {
    spawn(foo);
    spawn(bar);

    do_it();
    return 0;
}
