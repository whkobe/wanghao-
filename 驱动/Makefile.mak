ifneq  ($(KERNELRELEASE),)

obj-m:=hello.o

else

KDIR := /lib/modules/$(shell uname -r)/build

#KDIR := /home/linux/kernel/linux-3.14

PWD:= $(shell pwd)

all:

	make -C $(KDIR) M=$(PWD) modules

clean:

	rm -r *.ko *.o  *.mod.c *.order *.symvers

endif