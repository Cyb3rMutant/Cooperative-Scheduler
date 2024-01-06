
#include <cstdio>
#include <iostream>
#include <task-3/fibers.hpp>
void f1() {
    printf("1");
    yield();
    printf("2");
    fiber_exit();
}

void f2() {
    printf("3");
    yield();
    printf("4");
    fiber_exit();
}

void f3() {
    printf("5");
    fiber_exit();
}

int main(int argc, char *argv[]) {

    auto_run();
    spawn(f1);
    spawn(f2);
    spawn(f3);
    do_it();
}
