#pragma once

#include "fiber.hpp"
#include <context/context.hpp>
#include <deque>
#include <queue>
#include <vector>

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
     * @brief Gets the singleton instance of the scheduler.
     * @return A pointer to the singleton instance of the scheduler.
     */
    static Schedular *get_instance();

    Schedular(Schedular &other) = delete;
    void operator=(const Schedular &) = delete;

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

    /**
     * @brief Yields the execution to the next scheduled fiber.
     */
    void yield();

    /**
     * @brief Checks if there is any running task.
     * @return True if there is a running task, false otherwise.
     */
    bool is_running_task();

    void set_auto_run(bool val);

  private:
    /**
     * @brief Private constructor for the singleton pattern.
     */
    Schedular();

    /**
     * @brief The singleton instance of the scheduler.
     */
    static Schedular *instance;

    std::priority_queue<Fiber *, std::vector<Fiber *>, CompareFiber>
        fibers;           ///< Priority queue of fibers waiting to be executed.
    Fiber *current_fiber; ///< Pointer of currently running fiber.
    Context context;      ///< The context for the scheduler itself.
    bool exit_flag;       ///< Flag indicating if the scheduler should exit.
    bool auto_run;        ///< Flag indicating manual or auto running
};
