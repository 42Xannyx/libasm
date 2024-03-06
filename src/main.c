#include <errno.h>
#include <fcntl.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <sys/fcntl.h>
#include <unistd.h>

#include "libasm.h"

// Should segfault
// void t_seg_strlen() {
//   int64_t len = 0;
//
//   printf("-- FT_STRLEN --\n");
//   len = ft_strlen(NULL);
//   printf("%d. len: %ld\n", 3 + 1, len);
//
//   printf("-- STRLEN --\n");
//   len = strlen(NULL);
//   printf("%d. len: %ld\n", 3 + 1, len);
// }
//
// void t_strlen() {
//   int64_t len = 0;
//   const char *strings[] = {"Hello world", "", "a", NULL};
//
//   for (int32_t i = 0; strings[i]; i++) {
//     if (strlen(strings[i]) != ft_strlen(strings[i])) {
//       printf("Something wrong with ft_strlen");
//     }
//   }
//   printf("Did checks for ft_strlen\n");
//
//   // t_seg_strlen();
// }

// void t_seg_write() {
//   int64_t len = 0;
//
//   printf("-- FT_WRITE --\n");
//   len = ft_write(STDOUT_FILENO, NULL, 1);
//   printf("%d. len: %lld\n", 4, len);
//
//   printf("-- WRITE --\n");
//   len = write(STDOUT_FILENO, NULL, 1);
//   printf("%d. len: %lld\n", 4, len);
// }

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
    }
  }

  ssize_t ret = ft_write(-1, strings[0], strlen(strings[0]));
  printf("Return value: %lu with errno %d\n", ret, errno);
  if (ret != (ssize_t)strlen(strings[0])) {
    printf("Something wrong with ft_write\n");
    printf("Oh dear, something went wrong with ft_write()! %s\n",
           strerror(errno));
  }

  printf("\n\n---\n\n");

  ret = write(-1, strings[0], strlen(strings[0]));
  printf("Return value: %lu with errno %d\n", ret, errno);
  if (ret != (ssize_t)strlen(strings[0])) {
    printf("Something wrong with write\n");
    printf("Oh dear, something went wrong with write()! %s\n", strerror(errno));
  }

  // t_seg_write();
}

void t_read() {
  ssize_t len1 = 0, len2 = 0;
  char buff1[12], buff2[12];
  int32_t fd1[4], fd2[4]; // Adjusted type to int

  // Initialize file descriptors
  fd1[0] = open("./public/read1.txt", O_RDONLY);
  fd1[1] = open("./public/read2.txt", O_RDONLY);
  fd1[2] = open("./public/read3.txt", O_RDONLY);
  fd1[3] = 0; // Mark the end

  fd2[0] = open("./public/read1.txt", O_RDONLY);
  fd2[1] = open("./public/read2.txt", O_RDONLY);
  fd2[2] = open("./public/read3.txt", O_RDONLY);
  fd2[3] = 0; // Corrected

  for (int32_t i = 0; fd1[i] != 0; i++) {
    len2 = read(fd1[i], buff1, 10);
    buff1[len2] = '\0';

    len1 = ft_read(fd2[i], buff2, 10);
    buff2[len1] = '\0';

    if (len1 != len2) {
      printf("Length mismatch with ft_read\n");
    } else if (strcmp(buff1, buff2) != 0) {
      printf("Content mismatch with ft_read\n");
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

int32_t main() {
  // t_strlen();
  t_write();
  t_read();
  return 0;
}
