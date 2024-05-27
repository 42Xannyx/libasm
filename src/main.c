#include <assert.h>
#include <errno.h>
#include <fcntl.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "libasm.h"

int32_t compare_files(const char *file1, const char *file2) {
  FILE *fp1 = fopen(file1, "r");
  FILE *fp2 = fopen(file2, "r");

  if (!fp1 || !fp2) {
    if (fp1)
      fclose(fp1);
    if (fp2)
      fclose(fp2);
    return 0;
  }

  char ch1, ch2;
  do {
    ch1 = fgetc(fp1);
    ch2 = fgetc(fp2);
    if (ch1 != ch2) {
      fclose(fp1);
      fclose(fp2);
      return 0;
    }
  } while (ch1 != EOF && ch2 != EOF);

  fclose(fp1);
  fclose(fp2);
  return 1;
}

void test_strlen() {
  const char *strings[] = {"Hello world", "", "a", "12839\0asdas", NULL};

  for (int32_t i = 0; strings[i]; i++) {
    assert(strlen(strings[i]) == ft_strlen(strings[i]));
  }
  printf("All tests passed of ft_strlen.\n");
}

void test_write() {
  ssize_t len1 = 0;
  const char *strings[] = {"Hello world\n", "", "a\n", NULL};
  int32_t fd_ft_write =
      open("./public/output_ft_write.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
  int32_t fd_write =
      open("./public/output_write.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);

  if (fd_ft_write == -1 || fd_write == -1) {
    perror("Failed to open temporary files for writing");
    close(fd_ft_write);
    close(fd_write);
    return;
  }

  for (int i = 0; strings[i]; i++) {
    errno = 0;
    len1 = ft_write(fd_ft_write, strings[i], strlen(strings[i]));
    assert(len1 == (ssize_t)strlen(strings[i]));

    len1 = write(fd_write, strings[i], strlen(strings[i]));
    assert(len1 == (ssize_t)strlen(strings[i]));
  }

  close(fd_ft_write);
  close(fd_write);

  assert(compare_files("./public/output_ft_write.txt",
                       "./public/output_write.txt") == 1);

  // Test error handling with an invalid file descriptor
  errno = 0;
  len1 = ft_write(-1, "test", 4);
  assert(len1 == -1);
  assert(errno == EBADF);

  printf("All tests passed of ft_strlen.\n");
}

void test_read() {
  ssize_t len1 = 0, len2 = 0;
  char buff1[12], buff2[12];
  int32_t fd1[4], fd2[4];
  const char *paths[] = {"./public/read1.txt", "./public/read2.txt",
                         "./public/read3.txt", NULL};

  for (int32_t i = 0; paths[i] != NULL; i++) {
    errno = 0;
    fd1[i] = open(paths[i], O_RDONLY);
    fd2[i] = open(paths[i], O_RDONLY);

    if (fd1[i] == -1 || fd2[i] == -1) {
      perror("Failed to open file");
      close(fd1[i]);
      close(fd2[i]);
      continue;
    }

    len1 = read(fd1[i], buff1, 10);
    buff1[len1] = '\0';

    errno = 0;
    len2 = ft_read(fd2[i], buff2, 10);
    buff2[len2] = '\0';

    assert(len1 == len2);
    assert(strcmp(buff1, buff2) == 0);

    close(fd1[i]);
    close(fd2[i]);
  }

  // Test with a bad file descriptor
  errno = 0;
  len1 = ft_read(-1, buff1, 10);
  assert(len1 == -1);
  assert(errno == EBADF);

  errno = 0;
  len2 = read(-1, buff2, 10);
  assert(len2 == -1);
  assert(errno == EBADF);

  char *buff = NULL;
  ssize_t len;

  // Set up a valid file descriptor for reading.
  int32_t fd = open("./public/read1.txt", O_RDONLY);
  if (fd == -1) {
    return;
  }

  errno = 0;
  len = ft_read(fd, buff, 10);
  assert(len == -1);
  assert(errno == EFAULT);

  close(fd);
  printf("All tests passed of ft_read.\n");
}

void test_strcmp() {
  char tulip[15][2][50] = {{"Hello World", "Hello World"},
                           {"HelloWorl", "Hello World"},
                           {"Hello World", "Hello Worl"},
                           {"", ""},
                           {"      ", "      "},
                           {"aaaa", "aaaaa"},
                           {"1", ""},
                           {"\0", "\0"},
                           {"Hello\200", "Hello\300"},
                           {"Hello\nWorld", "Hello\nWorld"},
                           {"hello", "Hello"},
                           {"  leading space", "  leading space"},
                           {"trailing space ", "trailing space "},
                           {"🌍 unicode 🌎", "🌍 unicode 🌎"},
                           {"ABC\0DEF", "ABC\0DEG"}};

  for (int32_t i = 0; i < 7; i++) {
    int32_t ret1 = ft_strcmp(tulip[i][0], tulip[i][1]);
    int32_t ret2 = strcmp(tulip[i][0], tulip[i][1]);

    assert(ret1 == ret2);
  }
  printf("All tests passed of ft_strcmp.\n");
}

void test_strdup() {
  // Test 1: Check empty string.
  char *result = strdup("");
  // assert(result != NULL && result[0] == '\0');
  free(result);

  // Test 2: Check normal string duplication.
  char *str = "Hello, World!";
  result = ft_strdup(str);

  assert(result != NULL && strcmp(result, str) == 0);
  free(result);

  // // Test 3: Check that the duplicate is a separate copy.
  // if (result != NULL) {
  //   result[0] = 'J';
  //   assert(str[0] != result[0]);
  //   free(result);
  // }

  // Test 4: Check normal string duplication.
  // result = ft_strdup("!");
  //
  // assert(result != NULL && strcmp(result, "!") == 0);
  // free(result);

  printf("All tests passed of ft_strdup.\n");
}

void test_strcpy() {
  char dest[100];

  // Test 1: Copy a standard string.
  char *result = ft_strcpy(dest, "Hello, World!");
  assert(strcmp(dest, "Hello, World!") == 0);
  assert(result == dest);

  // Test 2: Copy an empty string.
  ft_strcpy(dest, "");
  assert(dest[0] == '\0');

  // Test 3: Copy a string with whitespaces.
  ft_strcpy(dest, "   ");
  assert(strcmp(dest, "   ") == 0);
  assert(dest[3] == '\0');

  // FIX
  // Test 4: Overlapping source and destination (if your implementation supports
  // it).
  // ft_strcpy(dest, "Overlap");
  // ft_strcpy(dest + 2, dest);
  // assert(strcmp(dest, "OvOvererp") == 0);

  printf("All tests passed of ft_strcpy.\n");
}

int32_t main() {
  test_strlen();
  test_write();
  test_read();
  test_strcmp();
  test_strdup();
  test_strcpy();

  return 0;
}
