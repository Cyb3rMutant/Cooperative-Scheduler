#include <cstddef>
#include <cstdio>
#include <iostream>
#include <ostream>
#include <simpletest/simpletest.h>
#include <string>
#include <task-2/fibers.hpp>

char const *groups[] = {"fibers"};

void add_2() {
    int *x = (int *)get_data();
    (*x) += 2;
    fiber_exit();
}

void sub_7_and_task_2() {
    int *x = (int *)get_data();
    (*x) -= 7;

    spawn(add_2, x);
    fiber_exit();
}

void multi_spawn_2() {
    int *x = (int *)get_data();
    spawn(add_2, x);
    spawn(add_2, x);
    spawn(add_2, x);
    spawn(add_2, x);
    spawn(add_2, x);
    fiber_exit();
}

void add_a() {
    std::string *x = (std::string *)get_data();
    x->push_back('a');
    fiber_exit();
}

void c_and_task_a() {
    std::string *x = (std::string *)get_data();
    x->push_back('c');

    spawn(add_a, x);
    fiber_exit();
}

void multi_spawn_a() {
    std::string *x = (std::string *)get_data();
    spawn(add_a, x);
    spawn(add_a, x);
    spawn(add_a, x);
    spawn(add_a, x);
    spawn(add_a, x);
    fiber_exit();
}

// they can execute and use data
DEFINE_TEST_G(Test1a, fibers) {
    int d = 10;
    int *dp = &d;
    spawn(add_2, dp);
    do_it();
    TEST_MESSAGE(d == 12, "function was not called");
}

// they can execute and use data
DEFINE_TEST_G(Test1b, fibers) {
    std::string d;
    std::string *dp = &d;
    spawn(add_a, dp);
    do_it();
    TEST_MESSAGE(d == "a", "function was not called");
}

// spawning a task from withing a task and it should execute when it finishes
DEFINE_TEST_G(Test2a, fibers) {
    int d = 10;
    int *dp = &d;
    spawn(sub_7_and_task_2, dp);
    do_it();
    TEST_MESSAGE(d == 5, "function was not called");
}

// spawning a task from withing a task and it should execute when it finishes
DEFINE_TEST_G(Test2b, fibers) {
    std::string d;
    std::string *dp = &d;
    spawn(c_and_task_a, dp);
    do_it();
    TEST_MESSAGE(d == "ca", "function was not called");
}

// when a task finishes its no longer on the queue
DEFINE_TEST_G(Test3a, fibers) {
    int d = 10;
    int *dp = &d;
    spawn(add_2, dp);
    do_it();
    TEST_MESSAGE(d == 12, "function was not called");
    do_it();
    TEST_MESSAGE(d == 12, "function should not have been called");
}

// when a task finishes its no longer on the queue
DEFINE_TEST_G(Test3b, fibers) {
    std::string d;
    std::string *dp = &d;
    spawn(add_a, dp);
    do_it();
    TEST_MESSAGE(d == "a", "function was not called");
    do_it();
    TEST_MESSAGE(d == "a", "function should not have been called");
}

// Test for a large number of fibers
DEFINE_TEST_G(Test4a, fibers) {
    const int num_fibers = 1000;
    int d = 0;
    int *dp = &d;

    for (int i = 0; i < num_fibers; ++i) {
        spawn(add_2, dp);
    }

    do_it();

    TEST_MESSAGE(d == 2 * num_fibers, "functions were not called correctly");
}

// Test for a large number of fibers
DEFINE_TEST_G(Test4b, fibers) {
    std::string d;
    std::string *dp = &d;
    int num_fibers = 1000;

    for (int i = 0; i < num_fibers; ++i) {
        spawn(add_a, dp);
    }

    do_it();

    TEST_MESSAGE(d == std::string(num_fibers, 'a'),
                 "functions were not called correctly");
}

DEFINE_TEST_G(Test5a, fibers) {
    int d = 10;
    int *dp = &d;
    spawn(multi_spawn_2, dp);
    do_it();
    TEST_MESSAGE(d == 20, "function was ot called");
}

DEFINE_TEST_G(Test5b, fibers) {
    std::string d;
    std::string *dp = &d;
    spawn(multi_spawn_a, dp);
    do_it();
    TEST_MESSAGE(d == "aaaaa", "function was ot called");
}

// for auto run, spawn a task and it should auto run as well

int main() {
    bool pass = true;

    for (auto group : groups) {
        pass &= TestFixture::ExecuteTestGroup(group, TestFixture::Verbose);
    }

    return pass ? 0 : 1;
}
