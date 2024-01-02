//-------------------------------------------------------------------
// API for fibers
//-------------------------------------------------------------------
#include "scheduler.hpp"

/// @brief terminates a fiber
///
/// note call control flow within a fiber must terminate with a call
/// to fiber_exit. Returning from a fiber without a call fiber_exit is
/// undefined.
void fiber_exit();

/// @brief get pointer to data passed as part of fiber creation
/// @return pointer to data passed in at fiber creation
template <class T> T *get_data() {
    auto x = Schedular::get_instance()->get_data();
    return static_cast<T *>(x);
}

/// @brief yield control back to scheduler
/// once rescheduled fiber will restart directly following call to
// yield.
void yield();

/// @brief create a new task for execution
/// if called from outsite a task it will add task to run queue, but
/// nothing will happen until run() is called.
///
/// if called from within a task itself, then a new task is added to
/// the run queue and will execute when it is reached by the
/// scheduler, no need to call run().
///
/// @param function fiber execution body
/// @param data pointer acess from running fiber
void spawn(void (*function)(), void *data = nullptr);

/// @brief run with the current set of fibers queued.
///
/// returns only when all fiber have completed.
///
/// Calling do_it within a fiber is undefined.
void do_it();

void auto_run();
void manual_run();
