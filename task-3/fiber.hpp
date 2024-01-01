#pragma once

#include "../context/context.hpp"

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
     */
    Fiber(void (*function)(), void *data = nullptr, bool run = false);

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
     * @brief Gets the user-defined data associated with the fiber.
     * @return A pointer to the user-defined data associated with the fiber.
     */
    void *get_data();

  private:
    Context *context;   ///< The execution context of the fiber.
    char *stack_top;    ///< The top of the fiber's stack.
    char *stack_bottom; ///< The bottom of the fiber's stack.
    void *data;         ///< User-defined data associated with the fiber.
};
