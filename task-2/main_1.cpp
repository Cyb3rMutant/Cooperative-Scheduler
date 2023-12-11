#include "../context/context.hpp"
#include "fiber.hpp"
#include <iostream>

void foo() {
    std::cout << "you called foo";

    exit(1);
}

int main(int argc, char *argv[]) {
    Fiber f(foo);

    set_context(f.get_context());

    return 0;
}
