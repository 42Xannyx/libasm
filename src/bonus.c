#include <assert.h>
#include <complex.h>
#include <stdint.h>
#include <stdio.h>

#include "libasm.h"

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

  printf("All ft_atoi_base tests passed.\n");
}

int32_t main() {
  test_atoi_base();

  return EXIT_SUCCESS;
}
