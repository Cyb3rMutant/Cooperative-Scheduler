#include <cstddef>
#include <simpletest/simpletest.h>
#include <string>
#include <task-extra/fibers.hpp>

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

void multi_yield_and_mult_2_between_them() {
    int *x = get_data<int>();
    (*x) *= 2;
    yield();
    (*x) *= 2;
    yield();
    (*x) *= 2;
    yield();
    (*x) *= 2;
    yield();
    fiber_exit();
}

void spawn_2_and_yield() {
    int *x = get_data<int>();
    spawn(add_2, x);
    yield();
    fiber_exit();
}

void multi_spawn_2() {
    int *x = get_data<int>();
    spawn(add_2, x);
    spawn(add_2, x);
    spawn(add_2, x);
    spawn(add_2, x);
    spawn(add_2, x);
    fiber_exit();
}

void mult_3_and_add_high_priority_7() {
    int *x = get_data<int>();
    (*x) *= 3;
    spawn(sub_7_and_task_2, x, 999);
    fiber_exit();
}

void add_a() {
    std::string *x = get_data<std::string>();
    x->push_back('a');
    fiber_exit();
}

void b_and_yield() {
    std::string *x = get_data<std::string>();
    x->push_back('b');
    yield();
    fiber_exit();
}

void c_and_task_a() {
    std::string *x = get_data<std::string>();
    x->push_back('c');

    spawn(add_a, x);
    fiber_exit();
}

void multi_yield_and_add_defg_between_them() {
    std::string *x = get_data<std::string>();
    x->push_back('d');
    yield();
    x->push_back('e');
    yield();
    x->push_back('f');
    yield();
    x->push_back('g');
    yield();
    fiber_exit();
}

void spawn_a_and_yield() {
    std::string *x = get_data<std::string>();
    spawn(add_a, x);
    yield();
    fiber_exit();
}

void multi_spawn_a() {
    std::string *x = get_data<std::string>();
    spawn(add_a, x);
    spawn(add_a, x);
    spawn(add_a, x);
    spawn(add_a, x);
    spawn(add_a, x);
    fiber_exit();
}

void y_and_add_high_priority_c() {
    std::string *x = get_data<std::string>();
    x->push_back('y');
    spawn(c_and_task_a, x, 999);
    fiber_exit();
}

// they can execute and use data
DEFINE_TEST_G(Test1a, fibers) {
    auto_run();
    int d = 10;
    int *dp = &d;
    spawn(add_2, dp);
    do_it();
    TEST_MESSAGE(d == 12, "function was not called");
    manual_run();
}

// they can execute and use data
DEFINE_TEST_G(Test1b, fibers) {
    auto_run();
    std::string d;
    std::string *dp = &d;
    spawn(add_a, dp);
    do_it();
    TEST_MESSAGE(d == "a", "function was not called");
    manual_run();
}

// yielding
DEFINE_TEST_G(Test2a, fibers) {
    auto_run();
    int d = 10;
    int *dp = &d;
    spawn(mult_5_and_yield, dp);
    spawn(add_2, dp);
    do_it();
    TEST_MESSAGE(d == 52, "function was not called");
    manual_run();
}

// yielding
DEFINE_TEST_G(Test2b, fibers) {
    auto_run();
    std::string d;
    std::string *dp = &d;
    spawn(b_and_yield, dp);
    spawn(add_a, dp);
    do_it();
    TEST_MESSAGE(d == "ba", "function was not called");
    manual_run();
}

// spawning a task from withing a task and it should execute when it finishes
DEFINE_TEST_G(Test3a, fibers) {
    auto_run();
    int d = 10;
    int *dp = &d;
    spawn(sub_7_and_task_2, dp);
    do_it();
    TEST_MESSAGE(d == 5, "function was not called");
    manual_run();
}

// spawning a task from withing a task and it should execute when it finishes
DEFINE_TEST_G(Test3b, fibers) {
    auto_run();
    std::string d;
    std::string *dp = &d;
    spawn(c_and_task_a, dp);
    do_it();
    TEST_MESSAGE(d == "ca", "function was not called");
    manual_run();
}

// when a task finishes its no longer on the queue
DEFINE_TEST_G(Test4a, fibers) {
    auto_run();
    int d = 10;
    int *dp = &d;
    spawn(add_2, dp);
    do_it();
    TEST_MESSAGE(d == 12, "function was not called");
    do_it();
    TEST_MESSAGE(d == 12, "function should not have been called");
    manual_run();
}

// when a task finishes its no longer on the queue
DEFINE_TEST_G(Test4b, fibers) {
    auto_run();
    std::string d;
    std::string *dp = &d;
    spawn(add_a, dp);
    do_it();
    TEST_MESSAGE(d == "a", "function was not called");
    do_it();
    TEST_MESSAGE(d == "a", "function should not have been called");
    manual_run();
}

DEFINE_TEST_G(Test5a, fibers) {
    auto_run();
    int d = 10;
    int *dp = &d;
    spawn(spawn_2_and_yield, dp);
    do_it();
    TEST_MESSAGE(d == 12, "function was ot called");
    manual_run();
}

DEFINE_TEST_G(Test5b, fibers) {
    auto_run();
    std::string d;
    std::string *dp = &d;
    spawn(spawn_a_and_yield, dp);
    do_it();
    TEST_MESSAGE(d == "a", "function was ot called");
    manual_run();
}

// spawning a task from withing a task and it should execute when it finishes
DEFINE_TEST_G(Test6a, fibers) {
    manual_run();

    int d = 10;
    int *dp = &d;
    spawn(sub_7_and_task_2, dp);
    spawn(mult_5_and_yield, dp);
    do_it();
    TEST_MESSAGE(d == 3, "function was not called");
    auto_run();
    do_it();
    TEST_MESSAGE(d == 17, "function was not called");
    manual_run();
}

// spawning a task from withing a task and it should execute when it finishes
DEFINE_TEST_G(Test6b, fibers) {
    manual_run();
    std::string d;
    std::string *dp = &d;
    spawn(c_and_task_a, dp);
    spawn(b_and_yield, dp);
    do_it();
    TEST_MESSAGE(d == "c", "function was not called");
    auto_run();
    do_it();
    TEST_MESSAGE(d == "cba", "function was not called");
    manual_run();
}

// Test for multiple fibers with different data
DEFINE_TEST_G(Test7a, fibers) {
    auto_run();
    int d1 = 10, d2 = 5;
    int *dp1 = &d1, *dp2 = &d2;

    spawn(mult_5_and_yield, dp2);
    spawn(add_2, dp1);

    do_it();

    TEST_MESSAGE(d1 == 12 && d2 == 25, "functions were not called correctly");
    manual_run();
}

// Test for multiple fibers with different data
DEFINE_TEST_G(Test7b, fibers) {
    auto_run();
    std::string d1, d2;
    std::string *dp1 = &d1, *dp2 = &d2;

    spawn(b_and_yield, dp2);
    spawn(add_a, dp1);

    do_it();

    TEST_MESSAGE(d1 == "a" && d2 == "b", "functions were not called correctly");
    manual_run();
}

// Test for a large number of fibers
DEFINE_TEST_G(Test8a, fibers) {
    auto_run();
    const int num_fibers = 1000;
    int d = 0;
    int *dp = &d;

    for (int i = 0; i < num_fibers; ++i) {
        spawn(add_2, dp);
    }

    do_it();

    TEST_MESSAGE(d == 2 * num_fibers, "functions were not called correctly");
    manual_run();
}

// Test for a large number of fibers
DEFINE_TEST_G(Test8b, fibers) {
    auto_run();
    std::string d;
    std::string *dp = &d;
    int num_fibers = 1000;

    for (int i = 0; i < num_fibers; ++i) {
        spawn(add_a, dp);
    }

    do_it();

    TEST_MESSAGE(d == std::string(num_fibers, 'a'),
                 "functions were not called correctly");
    manual_run();
}

// order of spawning matters (check with next)
DEFINE_TEST_G(Test9a, fibers) {
    auto_run();
    int d = 0;
    int *dp = &d;

    spawn(add_2, dp);
    spawn(mult_5_and_yield, dp);
    spawn(sub_7_and_task_2, dp);

    do_it();

    TEST_MESSAGE(d == 5, "functions were not called correctly");
    manual_run();
}

// order of spawning matters (check with next)
DEFINE_TEST_G(Test9b, fibers) {
    auto_run();
    std::string d;
    std::string *dp = &d;

    spawn(add_a, dp);
    spawn(b_and_yield, dp);
    spawn(c_and_task_a, dp);

    do_it();

    TEST_MESSAGE(d == "abca", "functions were not called correctly");
    manual_run();
}

// order of spawning matters (check with previous)
DEFINE_TEST_G(Test10a, fibers) {
    auto_run();
    int d = 0;
    int *dp = &d;

    spawn(sub_7_and_task_2, dp);
    spawn(mult_5_and_yield, dp);
    spawn(add_2, dp);

    do_it();

    TEST_MESSAGE(d == -31, "functions were not called correctly");
    manual_run();
}

// order of spawning matters (check with previous)
DEFINE_TEST_G(Test10b, fibers) {
    auto_run();
    std::string d;
    std::string *dp = &d;

    spawn(c_and_task_a, dp);
    spawn(b_and_yield, dp);
    spawn(add_a, dp);

    do_it();

    TEST_MESSAGE(d == "cbaa", "functions were not called correctly");
    manual_run();
}

// nested yielding
DEFINE_TEST_G(Test11a, fibers) {
    auto_run();
    int d = 1;
    int *dp = &d;

    for (int i = 0; i < 10; i++)
        spawn(mult_5_and_yield, dp);

    do_it();

    TEST_MESSAGE(d == 9765625, "functions were not called correctly");
    manual_run();
}

// nested yielding
DEFINE_TEST_G(Test11b, fibers) {
    auto_run();
    std::string d;
    std::string *dp = &d;

    for (int i = 0; i < 10; i++)
        spawn(b_and_yield, dp);

    do_it();

    TEST_MESSAGE(d == std::string(10, 'b'),
                 "functions were not called correctly");
    manual_run();
}

// multi yield in one function
DEFINE_TEST_G(Test12a, fibers) {
    auto_run();
    int d = 1;
    int *dp = &d;
    spawn(multi_yield_and_mult_2_between_them, dp);
    spawn(add_2, dp);
    spawn(add_2, dp);
    spawn(add_2, dp);
    spawn(add_2, dp);

    do_it();

    TEST_MESSAGE(d == 80, "functions were not called correctly");
    manual_run();
}

// multi yield in one function
DEFINE_TEST_G(Test12b, fibers) {
    auto_run();
    std::string d;
    std::string *dp = &d;
    spawn(multi_yield_and_add_defg_between_them, dp);
    spawn(add_a, dp);
    spawn(add_a, dp);
    spawn(add_a, dp);
    spawn(add_a, dp);

    do_it();

    TEST_MESSAGE(d == "daaaaefg", "functions were not called correctly");
    manual_run();
}

DEFINE_TEST_G(Test13a, fibers) {
    auto_run();
    const int num_fibers = 10000;
    int d = 0;
    int *dp = &d;

    for (int i = 0; i < num_fibers; ++i) {
        spawn(add_2, dp);
        spawn(mult_5_and_yield, dp);
    }
    do_it();

    TEST_MESSAGE(d == 1596707168, "functions were not called correctly");
    manual_run();
}

DEFINE_TEST_G(Test13b, fibers) {
    auto_run();
    std::string d;
    std::string *dp = &d;
    const int num_fibers = 10000;

    for (int i = 0; i < num_fibers; ++i) {
        spawn(add_a, dp);
        spawn(b_and_yield, dp);
    }
    do_it();
    std::string out;
    for (int i = 0; i < num_fibers; ++i) {
        out += "ab";
    }

    TEST_MESSAGE(d == out, "functions were not called correctly");
    manual_run();
}

// testing auto and manual run
DEFINE_TEST_G(Test14a, fibers) {
    const int num_fibers = 1000;
    int d = 0;
    int *dp = &d;

    for (int i = 0; i < num_fibers; ++i) {
        spawn(add_2, dp);
    }

    do_it();
    TEST_MESSAGE(d == 2, "functions were not called correctly");

    auto_run();
    do_it();
    TEST_MESSAGE(d == 2 * num_fibers, "functions were not called correctly");

    manual_run();
}

// testing auto and manual run
DEFINE_TEST_G(Test14b, fibers) {
    std::string d;
    std::string *dp = &d;
    const int num_fibers = 1000;

    for (int i = 0; i < num_fibers; ++i) {
        spawn(add_a, dp);
    }

    do_it();
    TEST_MESSAGE(d == "a", "functions were not called correctly");

    auto_run();
    do_it();
    TEST_MESSAGE(d == std::string(num_fibers, 'a'),
                 "functions were not called correctly");

    manual_run();
}

DEFINE_TEST_G(Test15a, fibers) {
    auto_run();
    int d = 10;
    int *dp = &d;
    spawn(multi_spawn_2, dp);
    do_it();
    TEST_MESSAGE(d == 20, "function was ot called");
    manual_run();
}

DEFINE_TEST_G(Test15b, fibers) {
    auto_run();
    std::string d;
    std::string *dp = &d;
    spawn(multi_spawn_a, dp);
    do_it();
    TEST_MESSAGE(d == "aaaaa", "function was ot called");
    manual_run();
}

DEFINE_TEST_G(Test16a, fibers) {
    auto_run();
    int d = 10;
    int *dp = &d;
    spawn(mult_5_and_yield, dp, 1);
    spawn(sub_7_and_task_2, dp, 3);
    spawn(mult_5_and_yield, dp, 3);
    spawn(add_2, dp, 2);
    do_it();
    TEST_MESSAGE(d == 87, "function was ot called");
    manual_run();
}

DEFINE_TEST_G(Test16b, fibers) {
    auto_run();
    std::string d;
    std::string *dp = &d;
    spawn(b_and_yield, dp, 1);
    spawn(c_and_task_a, dp, 3);
    spawn(b_and_yield, dp, 3);
    spawn(add_a, dp, 2);
    do_it();
    TEST_MESSAGE(d == "cbaba", "function was ot called");
    manual_run();
}

DEFINE_TEST_G(Test17a, fibers) {
    auto_run();
    int d = 10;
    int *dp = &d;
    spawn(add_2, dp, 4);
    spawn(mult_3_and_add_high_priority_7, dp, 4);
    spawn(mult_5_and_yield, dp, 4);
    spawn(add_2, dp, 1);
    do_it();
    TEST_MESSAGE(d == 149, "function was ot called");
    manual_run();
}

DEFINE_TEST_G(Test17b, fibers) {
    auto_run();
    std::string d;
    std::string *dp = &d;
    spawn(add_a, dp, 4);
    spawn(y_and_add_high_priority_c, dp, 4);
    spawn(b_and_yield, dp, 4);
    spawn(add_a, dp, 1);
    do_it();
    TEST_MESSAGE(d == "aycbaa", "function was ot called");
    manual_run();
}

int main() {
    bool pass = true;

    for (auto group : groups) {
        pass &= TestFixture::ExecuteTestGroup(group, TestFixture::Verbose);
    }

    return pass ? 0 : 1;
}
