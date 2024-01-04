#include <cstdio>
#include <iostream>
#include <task-extra/fibers.hpp>

void f() { fiber_exit(); }

int main(int argc, char *argv[]) {
    spawn(f);
    spawn(f);
    spawn(f);
    spawn(f);
    spawn(f);
    spawn(f);
    spawn(f);
    spawn(f);
    spawn(f);
    spawn(f);
    spawn(f);
    spawn(f);

    do_it();
    do_it();
    do_it();
    do_it();
    do_it();
    do_it();
    do_it();
    do_it();
    do_it();
    do_it();
    do_it();
    do_it();

    std::cout << "hello";

    return 0;
}
