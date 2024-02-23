#include <fcntl.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <sys/fcntl.h>
#include <unistd.h>

extern int64_t ft_strlen(const char *);
extern ssize_t ft_write(int fildes, const void *buf, size_t nbyte);
extern ssize_t ft_read(int fildes, void *buf, size_t nbyte);

// Should segfault
void t_seg_strlen() {
  int64_t len = 0;

  printf("-- FT_STRLEN --\n");
  len = ft_strlen(NULL);
  printf("%d. len: %ld\n", 3 + 1, len);

  printf("-- STRLEN --\n");
  len = strlen(NULL);
  printf("%d. len: %ld\n", 3 + 1, len);
}

void t_strlen() {
  int64_t len = 0;
  const char *strings[] = {"Hello world", "", "a", NULL};

  for (int32_t i = 0; strings[i]; i++) {
    if (strlen(strings[i]) != ft_strlen(strings[i])) {
      printf("Something wrong with ft_strlen");
    }
  }
  printf("Did checks for ft_strlen\n");

  // t_seg_strlen();
}

void t_seg_write() {
  int64_t len = 0;

  printf("-- FT_WRITE --\n");
  len = ft_write(STDOUT_FILENO, NULL, 1);
  printf("%d. len: %ld\n", 4, len);

  printf("-- WRITE --\n");
  len = write(STDOUT_FILENO, NULL, 1);
  printf("%d. len: %ld\n", 4, len);
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
      printf("Something wrong with ft_write");
    }
  }

  // t_seg_write();
}

void t_read() {
  ssize_t len1 = 0;
  ssize_t len2 = 0;
  int32_t fd[3];
  fd[0] = open("./public/read1.txt", O_RDONLY);
  fd[1] = open("./public/read2.txt", O_RDONLY);
  fd[2] = open("./public/read3.txt", O_RDONLY);
  fd[3] = NULL;

  for (int32_t i = 0; strings[i]; i++) {
    printf("-- FT_READ --\n");
    len1 = ft_read(STDOUT_FILENO, strings[i], strlen(strings[i]));

    printf("-- READ --\n");
    len2 = read(STDOUT_FILENO, strings[i], strlen(strings[i]));

    if (len1 != len2) {
      printf("Something wrong with ft_write");
    }
  }

  // t_seg_read();
}

int32_t main() {
  t_strlen();
  t_write();
  t_read();
  return 0;
}
