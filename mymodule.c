#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/timer.h>


static struct timer_list my_timer;

static unsigned long d = 10;
void my_timer_callback(unsigned long data){
	printk("%s called (%ld), data=%lu.\n", __FUNCTION__, jiffies, d);
	int retval;
	if(d--){
		retval = mod_timer( &my_timer, jiffies + msecs_to_jiffies(300) );
		if (retval) printk("Timer firing failed \n");
	}
}

static int __init my_init(void){
	int retval;
	printk("Timer module loaded\n");

	setup_timer(&my_timer, my_timer_callback, 11);
	printk("Setup timer to fire in 300ms (%ld)\n", jiffies);

	retval = mod_timer( &my_timer, jiffies + msecs_to_jiffies(300) );
	if (retval) printk("Timer firing failed \n");
	return 0;
}

static void my_exit(void){
	int retval;
	retval = del_timer(&my_timer);
	if(retval) printk("The timer is still in use...\n");
	pr_info("timer module unloaded\n");
}

module_init(my_init);
module_exit(my_exit);
MODULE_AUTHOR("Dmitri Roukin");
MODULE_DESCRIPTION("Standard timer");
MODULE_LICENSE("GPL");
