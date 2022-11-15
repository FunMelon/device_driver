#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>

#define DEV_NAME "/dev/globalvar"

int main(int argc, char *argv[]) { 
  int ret;  // 返回值
  char buf[32];  // 4字节的变量

  // 1.open
  int fd = open(DEV_NAME, O_RDWR);
  if (fd < 0) {
    printf("Fail to open file %s\n", DEV_NAME);
    return -1;
  }

  // 2.read
  read(fd, buf, 32);
  for (int i = 0; i < 32; ++i)
    printf("%c", buf[i]);
  printf("\n");

  // 3.write
  ret = write(fd, buf, 32);
  printf("ret : %d\n", ret);

  close(fd);
  return 0;
}
