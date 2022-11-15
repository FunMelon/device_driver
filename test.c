#include <fcntl.h>
#include <stdio.h>
#include <sys/ioctl.h>
#include <unistd.h>

#define DEV_NAME "/dev/globalvar"
#define LOGAL_LEN 4

int main(int argc, char *argv[]) {
  int ret;                             // 返回值
  unsigned char buf[10] = "123456789"; // 4字节的变量
  unsigned char res[10];
  // 1.open
  int fd = open(DEV_NAME, O_RDWR);
  if (fd < 0) {
    printf("\033[31mFail to open file %s\033[0m\n", DEV_NAME);
    return -1;
  }

  // 2.write
  ret = write(fd, &buf, 6);
  printf("ret : %d\n", ret);

  // 3.read
  read(fd, &res, 6);
  printf("\033[32mresult of read is: %s\033[0m\n", res);

  char order = 'c';
  int num;
  int isCycle = 1;

  printf("Please input order, q: exit, r: read, w: write\n");
  while (isCycle) {
    unsigned char str[10];

    scanf("%c", &order);
    if (order == ' ' || order == '\n')
      continue;

    switch (order) {
    case 'r': // 读
      printf("How number words do you want to read: ");
      scanf("%d", &num);
      num = num > 0 ? num : LOGAL_LEN;

      read(fd, &str, num);
      str[num] = '\0';
      printf("\033[32mresult of read is: %s\033[0m\n", str);
      break;
    case 'w': // 写
      printf("Please input the word to write: ");
      scanf("%s", str);
      printf("Try to write: %s\n", str);
      char *ptr = str;
      num = 0;
      while (*ptr != '\n' && *ptr != '\0') {
        ++ptr;
        ++num;
      }
      write(fd, &str, num);

      read(fd, &str, LOGAL_LEN);
      printf("\033[32mAfter writing, is %s\033[0m\n", str);
      break;
    case 'q':
      isCycle = 0;
      break;
    default:
      printf("\033[31mWrong order: %c\033[0m\n", order);
    }
  }
  close(fd);
  return 0;
}
