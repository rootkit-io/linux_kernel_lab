# 01: Hello kernel module

My first loadable Linux kernel module. It writes a kernel log
message when loaded and another when unloaded.

## Tested environment

- Architecture: x86_64
- Kernel: 6.8.0-142-generic
- Compiler: GCC 13.3.0
- Build tool: GNU Make 4.3

## Build

    make

## Load and inspect

    sudo insmod ./hello.ko
    lsmod | grep '^hello '
    sudo dmesg | tail -n 20

## Unload and inspect

    sudo rmmod hello
    sudo dmesg | tail -n 20

## Result

Successfully built, loaded, and unloaded on the environment above.

## Problems encountered

1. My source was named main.c, but the Makefile specified hello.o.
   Renaming the source to hello.c fixed the build dependency error.

2. I wrote exit instead of __exit in the cleanup function declaration.
   Fixing that typo resolved the subsequent undefined-function errors.

## What I learned

- Kbuild compiles the source into a .ko module.
- module_init registers the initialization function.
- module_exit registers the cleanup function.
- pr_info writes to the kernel log.
- insmod takes a file path; rmmod takes a loaded module name.
