/*
  Access to mini2440's leds, written as an lkm instead of compiled into the kernel.
  Based on code from this download: linux-2.6.32.2-mini2440-20110413.tar.gz.
  Updated to work with linux's gpiolib.
 */

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/miscdevice.h>
#include <linux/fs.h>
#include <linux/ioctl.h>
#include <linux/gpio.h>

// Stuff specific to s3c24xx
#include <mach/regs-gpio.h>
#include <mach/gpio-samsung.h>

#define DEVICE_NAME "leds"

static unsigned long led_table[] = {
  S3C2410_GPB(5),
  S3C2410_GPB(6),
  S3C2410_GPB(7),
  S3C2410_GPB(8)
};

static long leds_ioctl(struct file* filp, unsigned int cmd, unsigned long arg)
{
  switch(cmd) {
  case 0:
  case 1:
    if (arg > 4) {
      return -EINVAL;
    }
    // invert cmd (!) because leds are active low
    gpio_set_value(led_table[arg], !cmd);
    return 0;
  default:
    return -EINVAL;
  }
}

static struct file_operations dev_fops = {
  .owner = THIS_MODULE,
  .unlocked_ioctl = leds_ioctl,
};
static struct miscdevice misc = {
  .minor = MISC_DYNAMIC_MINOR,
  .name = DEVICE_NAME,
  .fops = &dev_fops,
};

static int __init dev_init(void)
{
  int ret;
  int i;

  for (i = 0; i < 4; i++) {
    // The leds are active low, so we set it to 1 to switch it off
    gpio_direction_output(led_table[i], 1);
  }

  ret = misc_register(&misc);

  printk(DEVICE_NAME" insmodded\n");

  return ret;
}

static void __exit dev_exit(void)
{
  int i;

  // Set it all back to 0
  for (i = 0; i < 4; i++) {
    gpio_direction_output(led_table[i], 1);
  }

  misc_deregister(&misc);
  printk(DEVICE_NAME" rmmodded\n");
}

module_init(dev_init);
module_exit(dev_exit);
MODULE_LICENSE("GPL");
