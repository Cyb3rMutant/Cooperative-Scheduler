#include "context/context.hpp"
#include <cstdint>
#include <iostream>

Context main_context;

void bar() {
    std::cout << "you called bar\n";

    exit(2);
}

void foo() {
    std::cout << "you called foo\n";
    set_context(&main_context);
    exit(1);
}

int main() {
    char *foo_data = new char[4096];

    char *foo_sp = foo_data + 4096;

    foo_sp =
        reinterpret_cast<char *>(reinterpret_cast<uintptr_t>(foo_sp) & -16L);
    foo_sp = foo_sp - 128;

    Context foo_context;
    foo_context.rip = (void *)foo;
    foo_context.rsp = foo_sp;

    char *bar_data = new char[4096];

    char *bar_sp = bar_data + 4096;

    bar_sp =
        reinterpret_cast<char *>(reinterpret_cast<uintptr_t>(bar_sp) & -16L);
    bar_sp = bar_sp - 128;

    Context bar_context;
    bar_context.rip = (void *)bar;
    bar_context.rsp = bar_sp;

    volatile int x = 0;

    get_context(&main_context);

    if (x == 0) {
        x++;
        set_context(&foo_context);
    } else {
        set_context(&bar_context);
    }
}
