# Linux Kernel Lab

**Learning what happens on the other side of a system call.**

A public record of my progress in Linux kernel and driver development: small experiments in C, the reasoning behind them, and the evidence that they work.

I’m starting with loadable kernel modules and working toward device drivers. Along the way, I want to understand how the kernel manages memory, exposes interfaces to userspace, coordinates concurrent execution, and cleans up when something fails.

**Current stage:** repository setup. The first milestone is building, loading, and unloading a minimal module inside a Linux VM.

> Educational code under active development. Run these experiments in a disposable Linux VM; faulty kernel code can crash or corrupt the guest.

## Approach

Each lab starts with a question:

- What runs when a module loads, and what must finish before it unloads?
- Who owns this allocation, and how long can another execution path access it?
- What happens when userspace supplies invalid input?
- What changes when two processes access the same device?
- How do I stop background work without leaving references to freed memory?

The goal is to answer these questions with code, tests, and explanations I can defend.

## Roadmap

These are planned milestones. Completed labs will gain links to their source, instructions, and test results.

| Stage | Experiment | Main question |
| --- | --- | --- |
| 01 | Module lifecycle | How does code enter and leave a running kernel? |
| 02 | Parameters and validation | How should a module handle configuration and reject invalid values? |
| 03 | Memory and cleanup | Who owns each resource, including when initialization fails? |
| 04 | Character device | How do userspace reads and writes reach kernel code? |
| 05 | Shared state and mutexes | What happens when multiple callers access the same buffer? |
| 06 | Debugging interfaces | Which internal state should be observable, and through which interface? |
| 07 | ioctl and UAPI | How do I define a predictable contract with userspace? |
| 08 | Wait queues and poll | How do readers wait for data and wake up correctly? |
| 09 | Workqueues and timers | How do I schedule work and shut it down safely? |
| 10 | Driver model | How does a driver bind to a device and manage its lifetime? |

Basic synchronization will be introduced with the first shared writable device. Later experiments will examine concurrency in more detail.

## What a completed lab includes

- **Purpose:** the question being investigated.
- **Implementation:** a small module focused on that question.
- **Design notes:** ownership, execution context, interface behavior, and tradeoffs.
- **Reproduction:** the tested environment and exact build and run commands.
- **Verification:** expected behavior, failure cases, and observed results.
- **References:** the documentation and source code used.

Where a lab exposes a userspace interface, it will include a small client or test program.

## Verification

Compiling is the first check.

As the experiments become more complex, verification will cover:

- Repeated loading and unloading.
- Invalid parameters and failed initialization.
- Empty, partial, and oversized I/O.
- Concurrent access to shared state.
- Cleanup with work still pending.
- Kernel warnings and unexpected behavior during testing.

Build checks and runtime checks will be reported separately. Compatibility claims will be limited to environments actually tested.

## Debugging notes

When something fails, I’ll document:

1. What I expected.
2. What happened.
3. How I reproduced it.
4. What evidence identified the cause.
5. What changed and how I checked the fix.

Unresolved problems will stay marked as unresolved. Deliberately broken experiments, if added, will be clearly identified and excluded from the normal test path.

## Development environment

The initial target is an ARM64 Linux VM on an Apple Silicon Mac.

The guest distribution, exact kernel release, compiler version, and relevant configuration will be recorded once the environment is running. Each lab will document its own tested setup.

## References

- [Linux kernel documentation](https://docs.kernel.org/)
- [Building external modules](https://docs.kernel.org/kbuild/modules.html)
- [Driver implementer’s API guide](https://docs.kernel.org/driver-api/index.html)
- [Kernel coding style](https://docs.kernel.org/process/coding-style.html)
- [Kernel testing guide](https://docs.kernel.org/dev-tools/testing-overview.html)

## Feedback

Corrections and focused code reviews are welcome, especially around resource lifetime, locking, userspace boundaries, and error handling.

If you spot a problem, an explanation of the failing execution path or a small reproducer would help me learn from it.
