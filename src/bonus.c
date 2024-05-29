#include <assert.h>
#include <complex.h>
#include <stdint.h>
#include <stdio.h>

#include "libasm.h"

int cmp_int(void *a, void *b) { return *(int *)a - *(int *)b; }

void test_atoi_base() {
  // Test 1: Basic conversion with base 10
  assert(ft_atoi_base("42", "0123456789") == 42);
  assert(ft_atoi_base("0", "0123456789") == 0);

  // Test 2: Leading whitespaces with base 10
  assert(ft_atoi_base("   42", "0123456789") == 42);

  // Test 3: Sign handling with base 10
  assert(ft_atoi_base("-42", "0123456789") == -42);
  assert(ft_atoi_base("+42", "0123456789") == 42);
  assert(ft_atoi_base("+     42", "0123456789") == 0);
  assert(ft_atoi_base("----42", "0123456789") == 0);
  assert(ft_atoi_base("++++++42", "0123456789") == 0);

  // Test 4: Non-numeric characters with base 10
  assert(ft_atoi_base("42abc", "0123456789") == 42);

  // Test 5: Empty string with base 10
  assert(ft_atoi_base("", "0123456789") == 0);

  // Test 6: Only non-numeric characters with base 10
  assert(ft_atoi_base("abc", "0123456789") == 0);

  // Test 7: Conversion with a custom base
  assert(ft_atoi_base("vn", "poneyvif") == 42);
  assert(ft_atoi_base("vn36", "poneyvif") == 42);
  assert(ft_atoi_base("offffffffff", "poneyvif") == 2147483647);
  assert(ft_atoi_base("-npppppppppp", "poneyvif") == -2147483648);

  // Test 8: Invalid base (duplicates & whitespaces)
  assert(ft_atoi_base("3", "  0123456789") == 0);
  assert(ft_atoi_base("3", "01234  56789") == 0);
  assert(ft_atoi_base("3", "-1234556789") == 0);
  assert(ft_atoi_base("3", "+0") == 0);
  assert(ft_atoi_base("3", "0") == 0);
  assert(ft_atoi_base("3", "01234567859") == 0);
  assert(ft_atoi_base("3", "00") == 0);

  // Test 9: Edge cases with maximum and minimum integers
  assert(ft_atoi_base("2147483647", "0123456789") == 2147483647);
  assert(ft_atoi_base("-2147483648", "0123456789") == -2147483648);

  // Test 10: Mixed valid and invalid characters
  assert(ft_atoi_base("123xyz", "0123456789") == 123);
  assert(ft_atoi_base("abc123", "0123456789") == 0);

  // Test 11: Multiple leading whitespaces and signs
  assert(ft_atoi_base("   +123", "0123456789") == 123);
  assert(ft_atoi_base("   -123", "0123456789") == -123);
  assert(ft_atoi_base(" + 123", "0123456789") == 0);
  assert(ft_atoi_base(" - 123", "0123456789") == 0);

  // Test 12: Different bases
  assert(ft_atoi_base("1010", "01") == 10);            // Binary to decimal
  assert(ft_atoi_base("A", "0123456789ABCDEF") == 10); // Hexadecimal to decimal
  assert(ft_atoi_base("Z", "ABCDEFGHIJKLMNOPQRSTUVWXYZ") == 25); // Base 26

  // Tests of another tester
  // PoneyVif
  assert(ft_atoi_base("vn", "poneyvif") == 42);
  assert(ft_atoi_base("vn36", "poneyvif") == 42);
  assert(ft_atoi_base("offffffffff", "poneyvif") == 2147483647);
  assert(ft_atoi_base("-npppppppppp", "poneyvif") == -2147483648);

  // Binary
  assert(ft_atoi_base("101010", "01") == 42);
  assert(ft_atoi_base("101010ABCD", "01") == 42);
  assert(ft_atoi_base("1010+10ABCD", "01") == 10);
  assert(ft_atoi_base("-1010+10ABCD", "01") == -10);
  assert(ft_atoi_base("01111111111111111111111111111111", "01") == 2147483647);
  assert(ft_atoi_base("10000000000000000000000000000000", "01") == -2147483648);

  // Hexadecimal
  assert(ft_atoi_base("2A", "0123456789ABCDEF") == 42);
  assert(ft_atoi_base("+2Aabcdef", "0123456789ABCDEF") == 42);
  assert(ft_atoi_base("-2Aabcdef", "0123456789ABCDEF") == -42);
  assert(ft_atoi_base("-10abcdef", "0123456789ABCDEF") == -16);
  assert(ft_atoi_base("10abcdef", "0123456789ABCDEF") == 16);

  // Decimal
  assert(ft_atoi_base("42", "0123456789") == 42);

  assert(ft_atoi_base(" \t \n \v \f \r 42", "0123456789") == 42);
  assert(ft_atoi_base(" \t \n \v \f \r 42+38", "0123456789") == 42);
  assert(ft_atoi_base("-42abcdef", "0123456789") == -42);
  assert(ft_atoi_base("28abcdef", "0123456789") == 28);
  assert(ft_atoi_base("2147483647abcdef", "0123456789") == 2147483647);
  assert(ft_atoi_base("-2147483648", "0123456789") == -2147483648);

  // Wrong cases
  // Base length is 0 or 1
  assert(ft_atoi_base("-42abcdef", "") == 0);
  assert(ft_atoi_base("-42abcdef", "H") == 0);

  // Base contains +, -, or whitespace
  assert(ft_atoi_base("-42abcdef", "HEY-") == 0);
  assert(ft_atoi_base("-42abcdef", "HE+Y") == 0);
  assert(ft_atoi_base("-42abcdef", "H EY") == 0);
  assert(ft_atoi_base("-42abcdef", "HEY ") == 0);
  assert(ft_atoi_base("-42abcdef", " HEY") == 0);
  assert(ft_atoi_base("-42abcdef", "H\tEY") == 0);
  assert(ft_atoi_base("-42abcdef", "H\nEY") == 0);
  assert(ft_atoi_base("-42abcdef", "H\vEY") == 0);
  assert(ft_atoi_base("-42abcdef", "H\fEY") == 0);
  assert(ft_atoi_base("-42abcdef", "H\rEY") == 0);

  // Base contains the same character twice
  assert(ft_atoi_base("-42abcdef", "HHEY") == 0);
  assert(ft_atoi_base("-42abcdef", "HEYY") == 0);
  assert(ft_atoi_base("-42abcdef", "HEYYO") == 0);
  assert(ft_atoi_base("-42abcdef", "ABC011234") == 0);
  assert(ft_atoi_base("-42abcdef", "ABC012344") == 0);

  // Several {+/-}
  assert(ft_atoi_base("-+42abcdef", "0123456789") == 0);
  assert(ft_atoi_base("-+-42abcdef", "0123456789") == 0);
  assert(ft_atoi_base("-+-++-+-+--+42abcdef", "0123456789") == 0);

  printf("All ft_atoi_base tests passed.\n");
}

void test_list_size() {
  // Test 1: Empty list
  t_list *empty_list = NULL;
  assert(ft_list_size(empty_list) == 0);

  // Test 2: Single element list
  t_list *single_element_list = malloc(sizeof(t_list));

  single_element_list->data = NULL;
  single_element_list->next = NULL;
  assert(ft_list_size(single_element_list) == 1);
  free(single_element_list);

  // Test 3: Multiple elements list
  t_list *multiple_elements_list = malloc(sizeof(t_list));

  multiple_elements_list->data = NULL;
  multiple_elements_list->next = malloc(sizeof(t_list));
  multiple_elements_list->next->data = NULL;
  multiple_elements_list->next->next = malloc(sizeof(t_list));
  multiple_elements_list->next->next->data = NULL;
  multiple_elements_list->next->next->next = NULL;
  assert(ft_list_size(multiple_elements_list) == 3);
  free(multiple_elements_list->next->next);
  free(multiple_elements_list->next);
  free(multiple_elements_list);

  // Test 4: Large list
  int32_t large_size = 1000;
  t_list *large_list = malloc(sizeof(t_list));
  if (!large_list) {
    exit(EXIT_FAILURE);
  }

  t_list *current = large_list;
  t_list *next;

  large_list->data = NULL;
  for (int i = 1; i < large_size; i++) {
    current->next = malloc(sizeof(t_list));
    if (!current->next) {
      exit(EXIT_FAILURE);
    }

    current = current->next;
    current->data = NULL;
  }
  current->next = NULL;
  assert(ft_list_size(large_list) == large_size);
  current = large_list;

  while (current) {
    next = current->next;
    free(current);
    current = next;
  }

  printf("All ft_list_size tests passed.\n");
}

int32_t main() {
  test_atoi_base();
  test_list_size();

  return EXIT_SUCCESS;
}
