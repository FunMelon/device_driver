ifneq ($(KERNELRELEASE),)
obj-m := globalvar.o
else
KDIR := /usr/src/linux-headers-$(shell uname -r)
all:
	make -C $(KDIR) M=$(PWD) modules
clean:
	make -C $(KDIR) M=$(PWD) clean 
endif
