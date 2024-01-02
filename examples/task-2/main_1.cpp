#include <context/context.hpp>
#include <iostream>
#include <task-2/fiber.hpp>

void foo() {
    std::cout << "you called foo";

    exit(0);
}

int main(int argc, char *argv[]) {
    Fiber f(foo);

    set_context(f.get_context());

    return 0;
}
