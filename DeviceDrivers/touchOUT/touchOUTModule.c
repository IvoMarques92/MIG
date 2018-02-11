#include <linux/module.h>
#include <asm/io.h>
#include <linux/ioport.h>
#include <mach/platform.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/device.h>

#define DECODER_2A0 15
#define DECODER_2A1 18

#define DEVICE_NAME "MIGTouchOUT"
#define CLASS_NAME  "touchOUTClass"

MODULE_LICENSE("GPL");

/* Device variables */
static struct class* MIG4LedsDevice_class = NULL;
static dev_t MIG4LedsDevice_majorminor;
static struct cdev c_dev;  // Character device structure
void __iomem *base;

#define GPIOFSEL(x) (0x00+(x)*4)
#define GPIOSET(x)  (0x1c+(x)*4)
#define GPIOCLR(x)  (0x28+(x)*4)

static const int LedGpioPin[2] = {DECODER_2A0, DECODER_2A1};;

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

static void SetGPIOOutputValue(int GPIO, bool outputValue) {
	unsigned gpio_pin = GPIO / 32;
	unsigned gpio_field_offset = (GPIO - 32 * gpio_pin);

	if (outputValue)
		iowrite32(1 << gpio_field_offset, base + GPIOSET(gpio_pin));
	else
		iowrite32(1 << gpio_field_offset, base + GPIOCLR(gpio_pin));
}

static ssize_t MIG4LedsDeviceWrite(struct file *f, const char __user *buf, size_t len, loff_t *off) {
	switch (buf[0]){
	    case '2':
	        SetGPIOOutputValue(LedGpioPin[0], 0);
	        SetGPIOOutputValue(LedGpioPin[1], 0);
	        break;
	    case '0':
	        SetGPIOOutputValue(LedGpioPin[0], 0);
	        SetGPIOOutputValue(LedGpioPin[1], 1);
	        break;
	    case '3':
	        SetGPIOOutputValue(LedGpioPin[0], 1);
	        SetGPIOOutputValue(LedGpioPin[1], 0);
	        break;
	    case '1':
	        SetGPIOOutputValue(LedGpioPin[0], 1);
	        SetGPIOOutputValue(LedGpioPin[1], 1);
	        break;
	    default:
	        break;                
	    }
	return len;
}

static struct file_operations MIG4LedsDevice_fops = {
	.owner = THIS_MODULE,
	.write = MIG4LedsDeviceWrite
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
	
	if (IS_ERR(request_mem_region(GPIO_BASE, 0x2f, "MIGTouchOUT"))) {
		pr_err("Error in request_mem_region");
		goto failure_requestmem;
	}

	base = ioremap(GPIO_BASE, 0x2f);
	SetGPIOFunction(LedGpioPin[0], 0b001); // Configure the pin DECODER_1A0 as output
	SetGPIOFunction(LedGpioPin[1], 0b001); // Configure the pin DECODER_1A1 as output
		
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
	SetGPIOFunction(LedGpioPin[0], 0); //Configure the pin DECODER_1A0 as input
	SetGPIOFunction(LedGpioPin[1], 0); //Configure the pin DECODER_1A1 as input
	cdev_del(&c_dev);	
	device_destroy(MIG4LedsDevice_class, MIG4LedsDevice_majorminor);
	class_destroy(MIG4LedsDevice_class);
	unregister_chrdev_region(MIG4LedsDevice_majorminor, 1);
}

module_init(MIG4LedsModule_init);
module_exit(MIG4LedsModule_exit);

