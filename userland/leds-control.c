/*
  Modified from examples provided with the mini2440 board
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>

#define LED_DEVICE "/dev/leds"

int main(int argc, char **argv)
{
  int on;
  int led_no;
  int fd;

  if (argc != 3 || sscanf(argv[1], "%d", &led_no) != 1 || sscanf(argv[2],"%d", &on) != 1 ||
      on < 0 || on > 1 || led_no < 0 || led_no > 3) {
    fprintf(stderr, "Usage: %s led_no 0|1\n", argv[0]);
    return 1;
  }
  
  fd = open(LED_DEVICE, 0);
  
  if (fd < 0) {
    fprintf(stderr, "Can't open " LED_DEVICE "\n");
    return 1;
  }
  
  ioctl(fd, on, led_no);
  close(fd);
  
  return 0;
}
