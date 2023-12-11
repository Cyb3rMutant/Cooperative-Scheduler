#include "fibers.hpp"
#include <iostream>

void foo() {
    std::cout << "called foo\n";
    fiber_exit();
}

void bar() {
    std::cout << "called bar\n";

    fiber_exit();
}

int main(int argc, char *argv[]) {
    spawn(foo);
    spawn(bar);
    spawn(foo);

    do_it();
    do_it();
    do_it();
    return 0;
}
