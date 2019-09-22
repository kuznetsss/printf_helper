#include <iostream>

#include "printf_helper/printf_helper.h"

int main() {
  constexpr auto s = printf_helper::PrintfFormatting("abc",  1, 2.f, 3., 2l,
      3u);
  std::cout << s.str << std::endl;
  printf(s.str, "abc",  1, 2.f, 3., 2l, 3u);
  return 0;
}
