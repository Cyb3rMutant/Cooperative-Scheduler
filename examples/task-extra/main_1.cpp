#include <cstdio>
#include <iostream>
#include <task-extra/fibers.hpp>

void f1() {
    std::cout << "f1\n";
    fiber_exit();
}

void f2() {
    std::cout << "f2\n";
    fiber_exit();
}
void f3() {
    std::cout << "f3\n";
    fiber_exit();
}
void f4() {
    std::cout << "f4\n";
    fiber_exit();
}

int main(int argc, char *argv[]) {
    spawn(f1, nullptr, 1);
    spawn(f2, nullptr, 3);
    spawn(f1, nullptr, 3);
    spawn(f4, nullptr, 1);
    spawn(f3, nullptr, 2);
    spawn(f4, nullptr, 4);

    do_it();
    do_it();
    do_it();
    do_it();
    do_it();
    do_it();

    std::cout << "hello";

    return 0;
}
