#include <linux/module.h>
#include <asm/io.h>
#include <asm/uaccess.h>
#include <linux/ioport.h>
#include <mach/platform.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/device.h>

#define CAP0 5
#define CAP1 6
#define CAP2 13
#define CAP3 19

#define DEVICE_NAME "capSensors"
#define CLASS_NAME  "capSensorsClass"

MODULE_LICENSE("GPL");

/* Device variables */
static struct class* MIG4LedsDevice_class = NULL;
static dev_t MIG4LedsDevice_majorminor;
static struct cdev c_dev;  // Character device structure
void __iomem *base;

#define GPIOFSEL(x) (0x00+(x)*4)
#define GPIOSET(x)  (0x1c+(x)*4)
#define GPIOCLR(x)  (0x28+(x)*4)
#define GPIOLEV(x)  (0x34+(x)*4)

static const int GpioPin[4] = {CAP0, CAP1, CAP2, CAP3};

static void SetGPIOFunction(int GPIO, int functionCode) {
	int registerIndex = GPIO / 10;
	int bit = (GPIO % 10) * 3;
	unsigned long gpiodir;

	gpiodir = ioread32(base + GPIOFSEL(registerIndex));
	gpiodir &= ~(0b111 << bit);
	gpiodir |= functionCode << bit;
	iowrite32(gpiodir, base + GPIOFSEL(registerIndex));
	gpiodir = ioread32(base + GPIOFSEL(registerIndex));
}

static unsigned int readGPIO(int GPIO) {
	unsigned gpio_pin = GPIO / 32;
	unsigned int pinValue;


	pinValue = ioread32(base + GPIOLEV(gpio_pin));
	
	return pinValue;
}

static ssize_t MIG4LedsDeviceRead(struct file *f, char __user *buf, size_t len, loff_t *off) {
	
	int i = 0, res;
	char value[4], *buffer;
	
	while(i <4) //read 4 pins
	{
    	res = readGPIO(GpioPin[i]);
	    value[i] = (char)(res >> GpioPin[i])  & 0x01; //read cap 0, cap 1, cap 2 and cap 3
	    i++;
	}
	    
    buffer = value;
    copy_to_user(buf,buffer,4); 
	
	return len;
	
}

static struct file_operations MIG4LedsDevice_fops = {
	.owner = THIS_MODULE,
	.read  = MIG4LedsDeviceRead
};


static int __init MIG4LedsModule_init(void) {
	int ret;
	struct device *MIG4LedsDevice_object;
	
	printk(KERN_INFO "DEVICE REGISTERING...");
	if ((ret = alloc_chrdev_region(&MIG4LedsDevice_majorminor, 0, 1, DEVICE_NAME)) < 0) {
		pr_err("Error in alloc_chrdev_region(): %d", ret);
		goto failure_registerchrdevregion;
	}

	if (IS_ERR(MIG4LedsDevice_class = class_create(THIS_MODULE, CLASS_NAME))) {
		pr_err("Error in class_create(): %p", PTR_ERR(MIG4LedsDevice_class));
		goto failure_classcreate;
	}
	
	if (IS_ERR(MIG4LedsDevice_object = device_create(MIG4LedsDevice_class, NULL, MIG4LedsDevice_majorminor, NULL, DEVICE_NAME))) {
		pr_err("Error in device_create(): %p", PTR_ERR(MIG4LedsDevice_object));
		goto failure_devicecreate;
	}
	
	cdev_init(&c_dev, &MIG4LedsDevice_fops);
	c_dev.owner = THIS_MODULE;
	c_dev.ops = &MIG4LedsDevice_fops;
	
	if ((ret = cdev_add(&c_dev, MIG4LedsDevice_majorminor, 1)) < 0) {
		pr_err("Error %d adding device", ret);
		goto failure_chrdevregister;
	}
	
	if (IS_ERR(request_mem_region(GPIO_BASE, 0x2f, "capSensors"))) {
		pr_err("Error in request_mem_region");
		goto failure_requestmem;
	}

	base = ioremap(GPIO_BASE, 0x2f);
	SetGPIOFunction(GpioPin[0], 0b000); // Configure the pin as input
	SetGPIOFunction(GpioPin[1], 0b000); // Configure the pin as input
	SetGPIOFunction(GpioPin[2], 0b000); // Configure the pin as input
	SetGPIOFunction(GpioPin[3], 0b000); // Configure the pin as input

	return 0;
	
	failure_requestmem:
		cdev_del(&c_dev);
	failure_chrdevregister:
	failure_devicecreatefile:
		device_destroy(MIG4LedsDevice_class, MIG4LedsDevice_majorminor);
	failure_devicecreate:
		class_destroy(MIG4LedsDevice_class);
	failure_classcreate:
		unregister_chrdev_region(MIG4LedsDevice_majorminor, 1);
	failure_registerchrdevregion:
		return -1;
}

static void __exit MIG4LedsModule_exit(void) {
	cdev_del(&c_dev);	
	device_destroy(MIG4LedsDevice_class, MIG4LedsDevice_majorminor);
	class_destroy(MIG4LedsDevice_class);
	unregister_chrdev_region(MIG4LedsDevice_majorminor, 1);
}

module_init(MIG4LedsModule_init);
module_exit(MIG4LedsModule_exit);
