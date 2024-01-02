This idea of fibers yielding to each other is what is known as cooperative scheduling. Fibers effectively move the idea of context switching from kernel-space to user-space and then make those switches a fundamental part of computation, that is, they’re a deliberate and explicitly done thing, by the fibers themselves. The benefit of this is that a lot of the previously mentioned overhead can be entierly eliminated while still permitting an excess count of threads of execution, just in the form of these fibers now.

There’s many problems related to multi-threading, most obviously that it’s difficult to get right. Most proponents of fibers make false claims about how this problem goes away when you use fibers because you don’t have parallel threads of execution. Instead, you have these cooperatively scheduled fibers which yield to each other. This means it’s not possible to race data, dead lock, live lock, etc. While this statement is true when you look at fibers as a N:1 proposition, the story is entierly different when you introduce M:N.

using a single thread given to you by the OS, then sharing it among multiple fibers that cooperatively yield and run all your asynchronous code. This is called N:1 (“N to one”). N fibers to 1 thread, and it’s the most prevalent form of fibers. This is how Lua coroutines work, how Javascript’s and Python’s async/await work

- they dont work with lambdas

You may be wondering why we need custom stacks for our fibers. Functions have locals that live on the stack, when we switch between fibers, we need to preserve the contents of those locals so when we resume they’ll still be there. Similarly, in the case of languages like C++, the objects that live on the stack will have their destructors called upon return of the function. Those destructors reference the object on the stack directly through their this pointer which will point into the stack.

- in task 1 main 3, the `set_context(main)` acts as a fiber_exit
- in task 1 main 4, the `swap_context` acts as a yield from main to the other functions, if we make all the contexts global, we can yield from any function to another, but instead of calling set_context(main) at the end we will need to know the yielder
