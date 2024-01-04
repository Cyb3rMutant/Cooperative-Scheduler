#pragma once
/**
 * @struct FiberStack
 * @brief Represents the stack associated with a fiber for managing its
 * execution context.
 */
struct FiberStack {
    char *stack_bottom; ///< Pointer to the bottom of the fiber stack.
    char *stack_top;    ///< Pointer to the top of the fiber stack.
    FiberStack *next;   ///< Pointer to the next FiberStack in the memory
                        ///< manager's linked list.

    /**
     * @brief Constructor for FiberStack.
     * @param n Pointer to the next FiberStack in the linked list (default is
     * nullptr).
     */
    FiberStack(FiberStack *n = nullptr);

    /**
     * @brief Destructor for FiberStack.
     * Cleans up resources associated with the fiber stack.
     */
    ~FiberStack();
};

/**
 * @class MemoryManager
 * @brief Manages the allocation and deallocation of FiberStacks.
 */
class MemoryManager {
  public:
    /**
     * @brief Constructor for MemoryManager.
     * @param s The initial capacity of the memory manager.
     */
    MemoryManager(unsigned s);

    /**
     * @brief Allocates a new FiberStack.
     * @return A pointer to the allocated FiberStack.
     */
    FiberStack *alloc();

    /**
     * @brief Deallocates a FiberStack.
     * @param n Pointer to the FiberStack to be deallocated.
     */
    void dealloc(FiberStack *n);

  private:
    FiberStack *head; ///< Pointer to the head of the linked list of available
                      ///< FiberStacks.
};
