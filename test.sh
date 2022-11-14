# 测试脚本
# 安装模块
insmod device.ko
# 卸载模块
rmmod device.ko
# 查看内核态输出
dmesg | tail
