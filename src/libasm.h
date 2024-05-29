#ifndef LIBASM_H
#define LIBASM_H

#include <fcntl.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#ifndef BONUS
#define BONUS false
#endif

// Size is 16 bytes
// sizeof(void *) + sizeof(struct s_list *) = 8 bytes + 8 bytes = 16 bytes
typedef struct s_list {
  void *data;
  struct s_list *next;
} t_list;

/*
** prototype base
*/

size_t ft_strlen(const char *str);
char *ft_strcpy(char *dst, const char *src);
int32_t ft_strcmp(const char *s1, const char *s2);
ssize_t ft_write(int32_t fd, const void *buff, size_t nbyte);
ssize_t ft_read(int32_t fd, void *buff, size_t nbyte);
char *ft_strdup(const char *s);

/*
** prototype bonus
*/

int32_t ft_list_size(t_list *list);
// void ft_list_push_front(t_list **begin_list, void *data);
int32_t ft_atoi_base(char const *str, char *base);
void ft_list_sort(t_list **begin_list, int (*cmp)());
void ft_list_remove_if(t_list **begin_list, void *data_ref, int (*cmp)());

#endif
