这是Linux实验课程的设备驱动程序<br>
Linux版本为: WSL2-Linux-Kernel-linux-msft-wsl-5.10.102.1<br>
设备驱动为globalvar<br>

### 驱动装载
请运行以下代码来加载驱动
```bash
sudo insmod globalvar.ko
```
运行以下代码来卸载驱动
```bash
sudo rmmod globalvar
```
### 查看日志
运行以下代码清除开机日志
```bash
sudo dmesg -C
```
运行以下代码来查看日志末尾以进行驱动校验
```bash
dmesg | tail
```
### 驱动测试
提供了test.c作为驱动校验的C语言程序
