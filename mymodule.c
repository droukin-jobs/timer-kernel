#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/timer.h>


static struct timer_list my_timer;

/* set the timer period */

#define TIMEOUT 300

/* limit the execution times to 10 */

#define LIMIT 10
static unsigned long d = LIMIT;
void my_timer_callback(unsigned long data){
	printk("%s called (%ld), data=%lu.\n", __FUNCTION__, jiffies, d);
	int retval;
	if(d--){
		retval = mod_timer( &my_timer, jiffies + msecs_to_jiffies(TIMEOUT) );
		if (retval) printk("Timer firing failed \n");
	}
}

static int __init my_init(void){
	int retval;
	printk("Timer module loaded\n");

	setup_timer(&my_timer, my_timer_callback, 0);
	printk("Setup timer to fire in %dms (%ld)\n", TIMEOUT, jiffies);

	retval = mod_timer( &my_timer, jiffies + msecs_to_jiffies(TIMEOUT) );
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
