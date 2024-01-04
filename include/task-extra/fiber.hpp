#pragma once

#include <context/context.hpp>
#include <freelist/freelist.hpp>

/**
 * @class Fiber
 * @brief Represents a lightweight fiber (or coroutine) for cooperative
 * multitasking.
 *
 * This class provides a simple interface to create and manage fibers. Fibers
 * are user-mode threads that can be cooperatively scheduled, allowing for
 * non-preemptive multitasking.
 */
class Fiber {
  public:
    bool auto_run; ///< used by the scheduler to whether auto run it or wait for
                   ///< a `do_it` call

    Fiber() = delete;

    /**
     * @brief Constructor for Fiber class.
     * @param function A pointer to the function that the fiber will execute.
     * @param data Optional data to associate with the fiber.
     * @param run If set to true, the fiber will be scheduled to run immediately
     * upon creation.
     * @param priority Priority level of the fiber.
     */
    Fiber(void (*function)(), void *data = nullptr, bool run = false,
          unsigned priority = 1);

    /**
     * @brief Destructor for Fiber class.
     * Cleans up resources associated with the fiber.
     */
    ~Fiber();

    /**
     * @brief Gets the context of the fiber.
     * @return A pointer to the Context object representing the fiber's
     * execution context.
     */
    Context *get_context();

    /**
     * @brief gets the user-defined data associated with the fiber.
     * @return a pointer to the user-defined data associated with the fiber.
     */
    void *get_data();

    /**
     * @brief Overloaded less-than operator to enable comparison between fibers
     * based on their priority.
     * @param other Another Fiber object to compare with.
     * @return True if the current fiber's priority is less than the other
     * fiber's priority; otherwise, false.
     */
    bool operator<(const Fiber &other) const;

  private:
    Context *context;  ///< The execution context of the fiber.
    FiberStack *stack; ///< The stack associated with the fiber for managing its
                       ///< execution context.
    void *data;        ///< User-defined data associated with the fiber.
    unsigned priority; ///< Priority level of the fiber during execution.
    unsigned id;       ///< Unique identifier for the fiber.

    static unsigned next_id; ///< Static variable to track the next available ID
                             ///< for fiber instances.
};

/**
 * @struct CompareFiber
 * @brief Functor to compare Fiber objects for ordering in a priority queue.
 */
struct CompareFiber {
    /**
     * @brief Overloaded function call operator to compare two Fiber objects.
     * @param lhs The left-hand side Fiber object.
     * @param rhs The right-hand side Fiber object.
     * @return True if the priority of lhs is less than the priority of rhs;
     * otherwise, false.
     */
    bool operator()(const Fiber *lhs, const Fiber *rhs) const;
};
