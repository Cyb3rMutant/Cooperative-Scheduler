#include "fibers.hpp"
#include <cstdio>
#include <iostream>

void foo() {
    std::cout << "called foo\n";
    int *x = (int *)get_data();
    printf("%d\n", (*x)++);
    fiber_exit();
}

void bar() {
    std::cout << "called bar\n";
    int *x = (int *)get_data();
    printf("%d\n", (*x)++);

    fiber_exit();
}

int main(int argc, char *argv[]) {
    int d = 10;
    int *dp = &d;
    spawn(foo, dp);
    spawn(bar, dp);

    do_it();
    return 0;
}
