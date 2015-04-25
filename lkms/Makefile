obj-m := mini2440_leds.o

KERNELDIR := /home/tngfamily/Documents/pidtester/output/build/linux-3.18.6

all:
	make ARCH=arm CROSS_COMPILE=arm-linux- -C $(KERNELDIR) M=$(PWD) modules

clean:
	make ARCH=arm CROSS_COMPILE=arm-linux- -C $(KERNELDIR) M=$(PWD) clean
