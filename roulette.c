// SPDX-License-Identifier: GPL-2.0

/*
 * Copyright (C) 2023 Rebecca White <rwhitedev4@gmail.com>
 */

#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/timer.h>

MODULE_AUTHOR("Rebecca White");
MODULE_DESCRIPTION("The Kernel Panic Russian Roulette");
MODULE_LICENSE("GPL");

struct timer_list timer;

void timer_callback(struct timer_list *t_list)
{
	int i, x;
	get_random_bytes(&i, sizeof(i));
	x = i % 25;
	
	if (x == 0) {
		printk("==[ Kernel Panic ]==");
		panic("roulette - Kernel Panic");
	}

	printk("panic: %d", x);
	mod_timer(&timer, jiffies + msecs_to_jiffies(2000));
}

static int __init panic_init(void)
{
	pr_info("RUSSIAN ROULETTE BEGINS!");
	timer_setup(&timer, timer_callback, 0);
	mod_timer(&timer, jiffies + msecs_to_jiffies(2000));
	return 0;
}

static void __exit panic_leave(void)
{
	pr_info("THE RUSSIAN ROULETTE HAS ENDED!");
	del_timer(&timer);
	return;
}

module_init(panic_init);
module_exit(panic_leave);
