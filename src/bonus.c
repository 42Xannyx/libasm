#include <assert.h>
#include <stdint.h>
#include <stdio.h>

#include "libasm.h"

void test_atoi_base() {
  // Test 1: Basic conversion with base 10

  assert(ft_atoi_base("42", "0123456789") == 42);
  assert(ft_atoi_base("0", "0123456789") == 0);
  assert(ft_atoi_base("3", "  0123456789") == -1);
  assert(ft_atoi_base("3", "01234  56789") == -1);

  // // Test 2: Leading whitespaces with base 10
  assert(ft_atoi_base("   42", "0123456789") == 42);

  // // Test 3: Sign handling with base 10
  // assert(ft_atoi_base("-42", "0123456789") == -42);
  // assert(ft_atoi_base("+42", "0123456789") == 42);
  //
  // // Test 4: Non-numeric characters with base 10
  // assert(ft_atoi_base("42abc", "0123456789") == 42);
  //
  // // Test 5: Empty string with base 10
  // assert(ft_atoi_base("", "0123456789") == 0);
  //
  // // Test 6: Only non-numeric characters with base 10
  // assert(ft_atoi_base("abc", "0123456789") == 0);
  //
  // // Test 7: Conversion with a custom base
  // assert(ft_atoi_base("vn", "poneyvif") == 42);
  // assert(ft_atoi_base("vn36", "poneyvif") ==
  //        3350); // Example for a larger number in custom base
  // assert(ft_atoi_base("offffffffff", "poneyvif") ==
  //        2147483647); // Maximum positive int32 value in custom base
  // assert(ft_atoi_base("-npppppppppp", "poneyvif") ==
  //        -2147483648); // Minimum negative int32 value in custom base

  printf("All ft_atoi_base tests passed.\n");
}

int32_t main() {
  test_atoi_base();

  return EXIT_SUCCESS;
}
