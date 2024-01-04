#include <cstdio>
#include <iostream>
#include <task-2/fiber.hpp>
#include <task-2/scheduler.hpp>

Schedular s;

void foo() {
    std::cout << "called foo\n";
    int *x = (int *)s.get_data();
    printf("%d\n", (*x)++);
    s.fiber_exit();
}

void bar() {
    std::cout << "called bar\n";
    int *x = (int *)s.get_data();
    printf("%d\n", (*x)++);

    s.fiber_exit();
}

int main(int argc, char *argv[]) {
    int d = 10;
    int *dp = &d;
    Fiber *f1 = new Fiber(foo, dp);
    Fiber *f2 = new Fiber(bar, dp);
    s.spawn(f1);
    s.spawn(f2);

    s.do_it();
    printf("main\n%d\n", d);
    return 0;
}
