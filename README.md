# mini2440-lkms
This repo contains Linux loadable kernel modules and the corresponding userland programs for the mini2440. 

There seems to be plenty of code online dependent on forks of the Linux kernel. 
I hope that these loadable kernel modules for the mini2440 will make it easier 
for these modules to be ported to newer versions of Linux.

Hopefully, these will make it easy for people to use buildroot to bring up the mini2440 :)

The `lkms` directory contains the loadable kernel modules. Change `KERNELDIR` before compiling.

The `userland` directory contains the programs that interact with the kernel modules in `lkms/`
