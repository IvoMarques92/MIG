#!/bin/sh

# Add modules to the Linux Kernel
modprobe i2c-bcm2708
modprobe spi-bcm2835

# Insert a module into the Linux Kernel
insmod capSensorsModule.ko
insmod 4LedModule.ko
insmod touchINModule.ko
insmod touchOUTModule.ko

# Execute Daemon

# Edit Priority?

# Execute Main Process

# Edit Priority?