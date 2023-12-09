#include "context/context.hpp"
#include <cstdint>
#include <iostream>

int main(int argc, char *argv[]) {
    volatile int x = 0;
    Context c;
    get_context(&c);
    std::cout << x << " hello world\n";

    if (x < 5) {
        x++;
        set_context(&c);
    }
    std::cout << "done";
    return 0;
}
