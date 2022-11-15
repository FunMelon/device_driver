#include <linux/cdev.h>
#include <linux/fs.h>
#include <linux/gfp.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/slab.h>

#define OK 0
#define ERROR -1
#define BUFFER_MAX 4

#define DEVNAME "globalvat"

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Fun Melon");
MODULE_DESCRIPTION("globalvar module");
MODULE_VERSION("1.0");

struct Globalvar {
  struct cdev *gDev;           // 字符设备指针
  char buffer[BUFFER_MAX]; // 字符缓冲区
};

struct Globalvar *globalvar;
struct file_operations *gFile; // 操作字符设备指针
dev_t devNum;                  // 起始设备号
unsigned int count = 1;        // 设备范围号大小
int reg_major = 222;           // 主设备号
int reg_minor = 0;             // 从设备号
struct class *dev_class;       // 驱动设备

int globalvar_open(struct inode *p, struct file *f) {
  printk(KERN_EMERG "gobalvar_open.\n");
  return 0;
}

ssize_t globalvar_write(struct file *f, const char *buf, size_t len,
                        loff_t *l) {
  if (len > BUFFER_MAX){ // 防止缓冲区溢出
    printk(KERN_EMERG"Fail to copy, %d is out of range", (int)len);
    return 0;
  }
  copy_from_user(globalvar->buffer, buf, len);
  printk(KERN_EMERG "gobalvar_write.\n");
  return len;
}

ssize_t globalvar_read(struct file *f, char *buf, size_t len, loff_t *l) {
  len = len > BUFFER_MAX ? BUFFER_MAX : len;
  copy_to_user(buf, globalvar->buffer, len);
  printk(KERN_EMERG "gobalvar_read.\n");
  return 0;
}

// 驱动注册函数
int __init globalvar_init(void) {
  // 获取在设备表中位置，高12位为主设备号，低20位为次设备号
  devNum = MKDEV(reg_major, reg_minor);
  // 分配指定的设备号范围
  if (register_chrdev_region(devNum, count, DEVNAME) == OK)
    printk(KERN_EMERG "Successfully register gobalvar.\n"); // 注册成功
  else {
    printk(KERN_EMERG "Fail to register gobalvar.\n"); // 注册失败
    return ERROR;
  }

  // 分配内存空间，标志位代表分配运行在内核空间进程
  globalvar = kzalloc(sizeof(struct Globalvar), GFP_KERNEL);
  strcpy(globalvar->buffer, "abcd");
  globalvar->gDev = kzalloc(sizeof(struct cdev), GFP_KERNEL);
  gFile = kzalloc(sizeof(struct file_operations), GFP_KERNEL);

  gFile->open = globalvar_open;
  gFile->read = globalvar_read;
  gFile->write = globalvar_write;
  gFile->owner = THIS_MODULE; // 指向自己的模块
  // 初始化驱动设备
  cdev_init(globalvar->gDev, gFile);
  // 加入内核空间
  cdev_add(globalvar->gDev, devNum, count);

  // 创建驱动
  dev_class = class_create(THIS_MODULE, "globalvar");
  if (dev_class == NULL) {
    printk(KERN_EMERG "Fail to create struct class.\n");
    unregister_chrdev_region(devNum, 1);
    return ERROR;
  }
  if (device_create(dev_class, NULL, devNum, NULL, "globalvar") == NULL) {
    class_destroy(dev_class);
    unregister_chrdev_region(devNum, 1);
  }
  printk(KERN_EMERG "Successfully init globalvar, major: %d, minor: %d\n",
         MAJOR(devNum), MINOR(devNum));
  return 0;
}

// 驱动注销函数
void __exit globalvar_exit(void) {
  // 注销设备
  device_destroy(dev_class, devNum);
  class_destroy(dev_class);
  cdev_del(globalvar->gDev);
  unregister_chrdev_region(devNum, 1);
  printk(KERN_EMERG "Successfully exit gobalvar.\n");
}

module_init(globalvar_init);
module_exit(globalvar_exit);
