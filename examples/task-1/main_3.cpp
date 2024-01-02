#include <context/context.hpp>
#include <cstdint>
#include <iostream>

Context main_context;

void bar() {
    std::cout << "you called bar\n";

    set_context(&main_context);
}

void foo() {
    std::cout << "you called foo\n";
    set_context(&main_context);
}

char *create_stack() {
    char *data = new char[4096];
    char *sp = data + 4096;
    sp = reinterpret_cast<char *>(reinterpret_cast<uintptr_t>(sp) & -16L);
    sp = sp - 128;
    return sp;
}

int main() {
    Context foo_context;
    foo_context.rip = (void *)foo;
    foo_context.rsp = create_stack();

    Context bar_context;
    bar_context.rip = (void *)bar;
    bar_context.rsp = create_stack();

    volatile int x = 0;

    get_context(&main_context);

    if (x == 0) {
        x++;
        set_context(&foo_context);
    } else if (x == 1) {
        x++;
        set_context(&bar_context);
    }
}
