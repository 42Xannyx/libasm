#include <errno.h>
#include <fcntl.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "libasm.h"

void t_strlen() {
  const char *strings[] = {"Hello world", "", "a", "12839\0asdas", NULL};

  for (int32_t i = 0; strings[i]; i++) {
    if (strlen(strings[i]) != ft_strlen(strings[i])) {
      printf("Something wrong with ft_strlen");
      exit(1);
    }
  }
}

void t_write() {
  ssize_t len1 = 0;
  ssize_t len2 = 0;
  const char *strings[] = {"Hello world\n", "", "a\n", NULL};

  for (int32_t i = 0; strings[i]; i++) {
    printf("-- FT_WRITE --\n");
    len1 = ft_write(STDOUT_FILENO, strings[i], strlen(strings[i]));

    printf("-- WRITE --\n");
    len2 = write(STDOUT_FILENO, strings[i], strlen(strings[i]));

    if (len1 != len2) {
      printf("Something wrong with ft_write\n");
      exit(1);
    }
  }

  ssize_t ret = ft_write(-1, strings[0], strlen(strings[0]));
  printf("Return value: %zd with errno %d\n", ret, errno);
  if (ret != (ssize_t)strlen(strings[0])) {
    printf("Something wrong with ft_write\n");
    printf("Oh dear, something went wrong with ft_write()! %s\n",
           strerror(errno));
  }

  printf("\n\n---\n\n");

  ret = write(-1, strings[0], strlen(strings[0]));
  printf("Return value: %zd with errno %d\n", ret, errno);
  if (ret != (ssize_t)strlen(strings[0])) {
    printf("Something wrong with write\n");
    printf("Oh dear, something went wrong with write()! %s\n", strerror(errno));
  }
}

void t_read() {
  ssize_t len1 = 0, len2 = 0;
  char buff1[12], buff2[12];
  int32_t fd1[4], fd2[4];

  fd1[0] = open("./public/read1.txt", O_RDONLY);
  fd1[1] = open("./public/read2.txt", O_RDONLY);
  fd1[2] = open("./public/read3.txt", O_RDONLY);
  fd1[3] = 0;

  fd2[0] = open("./public/read1.txt", O_RDONLY);
  fd2[1] = open("./public/read2.txt", O_RDONLY);
  fd2[2] = open("./public/read3.txt", O_RDONLY);
  fd2[3] = 0;

  for (int32_t i = 0; fd1[i] != 0; i++) {
    len2 = read(fd1[i], buff1, 10);
    buff1[len2] = '\0';

    len1 = ft_read(fd2[i], buff2, 10);
    buff2[len1] = '\0';

    if (len1 != len2) {
      printf("Length mismatch with ft_read\n");
      exit(1);
    } else if (strcmp(buff1, buff2) != 0) {
      printf("Content mismatch with ft_read\n");
      exit(1);
    }

    close(fd1[i]);
    close(fd2[i]);
  }

  printf("\n-- READ ERRORS --\n\n");

  len1 = ft_read(-1, buff1, 10);
  printf("Return value: %zd with errno %d\n", len1, errno);
  if (len1 != -1) {
    printf("Expected -1 but got %zd with ft_read, errno: %s\n", len1,
           strerror(errno));
  }

  printf("\n\n---\n\n");

  len2 = write(-1, buff2, 10);
  printf("Return value: %zd with errno %d\n", len2, errno);
  if (len2 != -1) {
    printf("Expected -1 but got %zd with write, errno: %s\n", len2,
           strerror(errno));
  }
}

void t_strcmp() {
  char tulip[7][2][12] = {{"Hello World", "Hello World"},
                          {"HelloWorl", "Hello World"},
                          {"Hello World", "Hello Worl"},
                          {"", ""},
                          {"      ", "      "},
                          {"aaaa", "aaaaa"},
                          {"1", ""}};

  for (int32_t i = 0; i < 7; i++) {
    printf("Comparing %s - %s\n", tulip[i][0], tulip[i][1]);
    int32_t ret1 = ft_strcmp(tulip[i][0], tulip[i][1]);
    int32_t ret2 = strcmp(tulip[i][0], tulip[i][1]);

    printf("%d - %d\n", ret1, ret2);
    if (ret1 != ret2) {
      printf("Something wrong with ft_strcmp\n");
      exit(1);
    }
  }
}

int32_t main() {
  t_strlen();
  t_write();
  t_read();
  t_strcmp();
  return 0;
}
