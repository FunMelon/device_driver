#include <linux/module.h>
#include <linux/init.h>
#include <linux/kernel.h>
 
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Yige LIU");
MODULE_DESCRIPTION("hello module");
 
static int __init hello_init(void){
    /* 使用KERN_WARING参数，防止printk等级过低不能在控制台输出而被写入日志 */
    printk(KERN_WARNING "Hello Yige LIU! I'm installed.\n");
    return 0;
}
static void __exit hello_exit(void){
    printk(KERN_WARNING "Bye Yige LIU! I'm removed.\n");
    return;
}
 
module_init(hello_init);
module_exit(hello_exit);
