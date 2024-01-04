#pragma once

#include <context/context.hpp>

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
    Fiber() = delete;

    /**
     * @brief Constructor for Fiber class.
     * @param function A pointer to the function that the fiber will execute.
     * @param data Optional data to associate with the fiber.
     */
    Fiber(void (*function)(), void *data = nullptr);

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

  private:
    Context *context;   ///< The execution context of the fiber.
    char *stack_top;    ///< The top of the fiber's stack.
    char *stack_bottom; ///< The bottom of the fiber's stack.
    void *data;         ///< User-defined data associated with the fiber.
};
