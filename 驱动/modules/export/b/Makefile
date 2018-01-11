ifneq  ($(KERNELRELEASE),)
$(info "2nd")
obj-m:=b.o
else
KDIR := /lib/modules/$(shell uname -r)/build
PWD:= $(shell pwd)
all:
	$(info "1st")
	make -C $(KDIR) M=$(PWD) modules
clean:
	rm -r *.ko *.o  *.mod.c *.order *.symvers
endif