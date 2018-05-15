# timer-kernel
A simple kernel timer module

## INTRO

This is a simple kernel module that prints a message every 300ms.

## USAGE

As root do the following to test the module:

```
insmod mymodule.ko
sleep 10
rmmod mymodule.ko
dmesg
```

## TODO

Need to add config file for time period, message, etc.
