#!/bin/sh

# Add modules to the Linux Kernel
modprobe i2c-bcm2708
modprobe spi-bcm2835

# Insert a module into the Linux Kernel
insmod /root/DevDriver/capSensorsModule.ko
insmod /root/DevDriver/4LedModule.ko
insmod /root/DevDriver/touchINModule.ko
insmod /root/DevDriver/touchOUTModule.ko


# Execute Main Process
/root/MainProcess
# Edit Priority?

# Execute Daemon
#/root/DaemonProcess
# Edit Priority?

