# Printf_helper library


[![Build Status](https://travis-ci.com/kuznetsss/printf_helper.svg?branch=master)](https://travis-ci.com/kuznetsss/printf_helper)

Printf_helper is simple header-only C++ library for deducing format
 string for printf at compile time.
 
 Example:
 ```c++
  int i = 0;
  const double d = 2.;
  const char* c_str = "abc";
  const auto format_string = printf_helper::GetPrintfFormat(i, d, c_str);
  printf(format_string + "\n", i, d, c_str);
```

The function `printf_helper::GetPrintfFormat()` is not constexpr from the
 outside, but inside it just returns constexpr variable.
 
The returned type is a special class `ConstexprString`. It can be implicitly
converted to `const char *`. Also `ConstexprString` has constexpr `operator+`
for `const char *` or another `ConstexprString`.

## Compiling

- C++ 17 is required to use the library. 
- Gtest library is used for tests. Conan will upload gtest
  automatically.
- You can disable compiling tests by setting cmake variable
  `ENABLE_TESTS` to `FALSE`.