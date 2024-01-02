#include <cstdio>
#include <iostream>
#include <task-3/fibers.hpp>

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

void f() {
    std::cout << "f2\n";
    spawn(bar);
    fiber_exit();
}

int main(int argc, char *argv[]) {
    spawn(foo);
    spawn(foo);
    spawn(bar);
    spawn(bar);

    do_it();
    do_it();

    spawn(f);
    do_it();
    std::cout << "hello";

    return 0;
}
