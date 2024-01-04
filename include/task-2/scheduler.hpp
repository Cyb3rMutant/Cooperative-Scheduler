#pragma once

#include "fiber.hpp"
#include <context/context.hpp>
#include <deque>

/**
 * @class Schedular
 * @brief Represents a simple cooperative scheduler for managing fibers.
 *
 * This class provides functionality to spawn fibers, schedule their execution,
 * and perform context switches between fibers in a cooperative multitasking
 * environment.
 */
class Schedular {
  public:
    /**
     * @brief Constructor for the scheduler.
     */
    Schedular();

    /**
     * @brief Destructor for the scheduler.
     * Cleans up resources associated with the scheduler.
     */
    ~Schedular();

    /**
     * @brief Spawns a new fiber to be managed by the scheduler.
     * @param f A pointer to the Fiber object to be spawned.
     */
    void spawn(Fiber *f);

    /**
     * @brief Executes the next scheduled fiber.
     */
    void do_it();

    /**
     * @brief Signals the exit of the currently running fiber.
     */
    void fiber_exit();

    /**
     * @brief Gets the user-defined data associated with the currently running
     * fiber.
     * @return A pointer to the user-defined data associated with the currently
     * running fiber.
     */
    void *get_data();

  private:
    std::deque<Fiber *> fibers; ///< Queue of fibers waiting to be executed.
    Context context;            ///< The context for the scheduler itself.
    Fiber *current_fiber;       ///< Pointer of currently running fiber.
};
