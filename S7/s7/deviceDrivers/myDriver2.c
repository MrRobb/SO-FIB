#include <linux/fs.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/cdev.h>
#include <linux/errno.h>
#include <asm/uaccess.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("SO");
MODULE_DESCRIPTION("A very simple device driver (2)");

// major and minors are the device driver identifiers. They are used to
// associate a logical device with its specific access code
#define MAJOR_DRIVER_2	250
#define MINOR_DRIVER_2	0

int read_driver_2 (struct file *f, char __user *buffer, size_t s, loff_t *off);

struct cdev *my_cdev;
dev_t dev;

struct file_operations fops_driver_2 = {
	owner: THIS_MODULE,
	read: read_driver_2,
};

/*
 * Parameters description:
 * f: OS structure that containes the characteristics of the device
 * buffer: parameter passed by the user. It contains the address in
 * 	the user address space to store the read data
 * s: parameter passed by the user. It contains the amount of data to read.
 * off: offset to use in the access to the device. It is implemented and
 * 	managed by each device driver.
 */

int read_driver_2 (struct file *f, char __user *buffer, size_t s, loff_t *off) {
char *localBuffer="DRIVER 2 READ OPERATION\nSPONSORED BY LABORATORIOS GELOCATAS SL\n";

int size=strlen(localBuffer)-*off;

if (size > s) size = s;

//this functions copies from system address space to user address space
copy_to_user(buffer, localBuffer+*off, size);

*off = *off+size;

return size;

}


static int __init driver2_init(void){
int ret;
	// Create a device identifier based on the selected major and minor pair
	dev=MKDEV(MAJOR_DRIVER_2, MINOR_DRIVER_2);

	// Register the device identifier
	ret = register_chrdev_region(dev,1,"myDriver2");

	if (ret<0) {
		printk(KERN_EMERG "myDriver2: Error registering device\n");
		return ret;
	}

	// Allocate a new structure to associate the device identifier 
	// and the specific operations
	
	my_cdev = cdev_alloc();
	if (my_cdev == NULL) {
		printk(KERN_EMERG "myDriver2: Error allocating cdev\n");
		unregister_chrdev_region(dev,1);
		return -1;
	}

	//Initialize the cdev structure. 
	my_cdev->owner = THIS_MODULE;
	my_cdev->ops = &fops_driver_2;

	// Associate the device identifier and the specific operations
	ret = cdev_add(my_cdev, dev, 1);
	if (ret < 0){
		printk(KERN_EMERG "myDriver2: Error adding cdev\n");
		unregister_chrdev_region(dev,1);
		return ret;
	}

	return 1;

}

static void __exit driver2_exit(void){
  unregister_chrdev_region(dev, 1);
  cdev_del(my_cdev);
}


module_init(driver2_init);
module_exit(driver2_exit);

