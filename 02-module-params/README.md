# 02: Module parameters and validation

A loadable kernel module that accepts an integer `count` parameter
and logs that many greetings. The default is 1; accepted values
are 1 through 5.

## Concepts

- module_param registers a parameter and its type.
- MODULE_PARM_DESC provides its description.
- Permissions 0444 expose the value as read-only through sysfs.
- The kernel parses the integer before initialization.
- The module validates the range inside its initialization function.
- Returning -EINVAL rejects loading.
- Failed initialization does not automatically call the exit function.

## Build

    make
    modinfo -p ./params.ko

## Load, inspect, and unload

    sudo insmod ./params.ko count=3
    cat /sys/module/params/parameters/count
    sudo dmesg | tail -n 10
    sudo rmmod params

Unload after each successful load before trying another value.

## Validation results

| Input | Observed result |
| --- | --- |
| count=0 | Rejected |
| count=1 | Loaded, one greeting, sysfs reported 1 |
| count=5 | Loaded, five greetings, sysfs reported 5 |
| count=6 | Rejected |
| count=8 | Rejected by the module's range check |
| count=abc | Rejected by the kernel's integer parser |

Failed loads left the module absent from lsmod.

## Debugging notes

I initially wrote MODULE_PARAM_DESC instead of MODULE_PARM_DESC.
Correcting the macro name fixed the compilation error.

## Cleanup rule

Initialization must release any resources it acquired before
returning an error. The exit callback handles cleanup when a
successfully loaded module is unloaded.

## Tested environment

- Architecture: x86_64
- Kernel: 6.8.0-142-generic
- Compiler: GCC 13.3.0
