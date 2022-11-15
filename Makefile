ifneq ($(KERNELRELEASE),)
obj-m := globalvar.o
else
KDIR := /usr/src/linux-headers-$(shell uname -r)
all:
	make -C $(KDIR) M=$(PWD) modules
clean:
	rm -rf *.o *.mod *.mod.c *.mod.o *.ko *.order *symvers
endif
