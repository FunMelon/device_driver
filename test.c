#include <fcntl.h>
#include <stdio.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <stdint.h>

#define DEV_NAME "/dev/globalvar"

int main(int argc, char *argv[]) {
  int ret;          // 返回值
  int32_t buf = 114514; // 4字节的变量

  // 1.open
  int fd = open(DEV_NAME, O_RDWR);
  if (fd < 0) {
    printf("Fail to open file %s\n", DEV_NAME);
    return -1;
  }

  // 2.write
  ret = write(fd, &buf, 4);
  printf("ret : %d\n", ret);

  // 3.read
  read(fd, &buf, 4);
  printf("result of read is: %d", buf);
  printf("\n");

  close(fd);
  return 0;
}
