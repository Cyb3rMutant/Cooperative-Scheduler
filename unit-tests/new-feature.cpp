#include <cstddef>
#include <cstdio>
#include <iostream>
#include <new-feature/fibers.hpp>
#include <simpletest/simpletest.h>

char const *groups[] = {"fibers"};

void add_2() {
    int *x = get_data<int>();
    (*x) += 2;
    fiber_exit();
}

void mult_5_and_yield() {
    int *x = get_data<int>();
    (*x) *= 5;
    yield();
    fiber_exit();
}

void sub_7_and_task_2() {
    int *x = get_data<int>();
    (*x) -= 7;

    spawn(add_2, x);
    fiber_exit();
}

// they can execute and use data
DEFINE_TEST_G(Test1, fibers) {
    int d = 10;
    int *dp = &d;
    spawn(add_2, dp);
    do_it();
    TEST_MESSAGE(d == 12, "function was not called");
}

// yielding
DEFINE_TEST_G(Test2, fibers) {
    int d = 10;
    int *dp = &d;
    spawn(mult_5_and_yield, dp);
    spawn(add_2, dp);
    do_it();
    TEST_MESSAGE(d == 52, "function was not called");
}

// spawning a task from withing a task and it should execute when it finishes
DEFINE_TEST_G(Test3, fibers) {
    int d = 10;
    int *dp = &d;
    spawn(sub_7_and_task_2, dp);
    do_it();
    TEST_MESSAGE(d == 5, "function was not called");
}

// when a task finishes its no longer on the queue
DEFINE_TEST_G(Test4, fibers) {
    int d = 10;
    int *dp = &d;
    spawn(add_2, dp);
    do_it();
    TEST_MESSAGE(d == 12, "function was not called");
    do_it();
    TEST_MESSAGE(d == 12, "function should not have been called");
}

DEFINE_TEST_G(Test5, fibers) {
    int d = 10;
    int *dp = &d;
    spawn(add_2, dp);
    do_it();
    TEST_MESSAGE(d == 12, "function was not called");
    do_it();
    TEST_MESSAGE(d == 12, "function should not have been called");
}

// spawning a task from withing a task and it should execute when it finishes
DEFINE_TEST_G(Test6, fibers) {
    int d = 10;
    int *dp = &d;
    spawn(sub_7_and_task_2, dp);
    spawn(mult_5_and_yield, dp);
    std::cout << d;
    do_it();
    std::cout << d;
    TEST_MESSAGE(d == 3, "function was not called");
    std::cout << d;
    do_it();
    std::cout << d;
    TEST_MESSAGE(d == 17, "function was not called");
}

int main() {
    bool pass = true;

    for (auto group : groups) {
        pass &= TestFixture::ExecuteTestGroup(group, TestFixture::Verbose);
    }

    return pass ? 0 : 1;
}
