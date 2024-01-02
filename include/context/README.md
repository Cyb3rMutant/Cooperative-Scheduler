# Context

This small library for saving and restoring a fiber's context. It is for use in the module Advanced Systems Programming Worksheet 1.

It requires an platform that supports System V ABI.

This API is derived from the excellent blog post: https://graphitemaster.github.io/fibers/. Well worth a read!

## API

The following API is defined:

```c++
struct Context {
  void *rip, *rsp;
  void *rbx, *rbp, *r12, *r13, *r14, *r15;
};

extern "C" int get_context(Context *c);
extern "C" void set_context(Context *c);
extern "C" void swap_context(Context *out, Context *in);
```

## Building

```bash
clang++ -c context.s
```

Then link in the resulting ```context.o``` to an application using the API.



