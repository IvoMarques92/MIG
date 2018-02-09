#Attention

To make the device drivers, it is necessary change the path to buildroot correctly in the Makefile in each folder.

#Generate Device Driver

To make the DeviceDriver, after edit the makefile, just do make in the path and send the "file".ko to the target(Raspberry Pi 3 Mode B+).
To use the device driver, inside the target use the cmd: insmod to insert the module in the kernel.


To change the priority in each process: https://www.nixtutor.com/linux/changing-priority-on-linux-processes/
To Execute the process with specific priority: https://serverfault.com/questions/809648/how-to-start-a-process-with-a-high-priority