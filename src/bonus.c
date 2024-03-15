#include <stdint.h>
#include <stdio.h>
#include <assert.h>

#include "libasm.h"

void test_atoi() {
  // Test 1: Basic conversion.
  printf("%d\n", ft_atoi_base("42", 16));
  printf("%d\n", atoi("42"));
  assert(ft_atoi_base("42", 10) == 42);
  assert(ft_atoi_base("0", 10) == 0);

  // Test 2: Leading whitespaces.
  assert(ft_atoi_base("   42", 10) == 42);

  // Test 3: Sign handling.
  assert(ft_atoi_base("-42", 10) == -42);
  assert(ft_atoi_base("+42", 10) == 42);

  // Test 4: Non-numeric characters.
  assert(ft_atoi_base("42abc", 10) == 42);

  // Test 5: Overflow and underflow (if applicable; behavior may be undefined).
  // Skipping as behavior is undefined - use strtol for well-defined behavior.

  // Test 6: Empty string.
  assert(ft_atoi_base("", 10) == 0);

  // Test 7: Only non-numeric characters.
  assert(ft_atoi_base("abc", 10) == 0);

  printf("All ft_atoi_base tests passed.\n");
}

int32_t main() {
  test_atoi();
  return EXIT_SUCCESS;
}
