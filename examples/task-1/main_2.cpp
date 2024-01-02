#include <context/context.hpp>
#include <cstdint>
#include <iostream>

void foo() {
    std::cout << "you called foo";

    exit(0);
}

int main() {
    char *data = new char[4096];

    char *sp = data + 4096;

    sp = reinterpret_cast<char *>(reinterpret_cast<uintptr_t>(sp) & -16L);
    sp = sp - 128;

    Context c;
    c.rip = (void *)foo;
    c.rsp = sp;

    set_context(&c);
}
