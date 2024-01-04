#include <context/context.hpp>
#include <iostream>
#include <task-2/fiber.hpp>

Fiber main_f(nullptr);

void foo() {
    std::cout << "you called foo";

    set_context(main_f.get_context());
}

void bar() {
    std::cout << "you called bar";

    set_context(main_f.get_context());
}

int main(int argc, char *argv[]) {
    Fiber f1(foo);
    Fiber f2(bar);

    volatile int x = 0;

    get_context(main_f.get_context());

    if (x == 0) {
        x++;
        set_context(f1.get_context());
    } else if (x == 1) {
        x++;
        set_context(f2.get_context());
    }

    return 0;
}
