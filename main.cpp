#include <algorithm>
#include <array>
#include <iostream>
#include <string>
#include <vector>

template <std::size_t N> class StaticString {
public:
  constexpr StaticString(const char (&s)[N]) : str{0} {
    for (std::size_t i = 0; i < N; ++i)
      str[i] = s[i];
  }

  char str[N];
};

template <std::size_t N>
constexpr StaticString<N> CreateStaticString(const char (&s)[N]) {
  return StaticString<N>(s);
}

/*
template <std::size_t N>
constexpr StaticString<N>
CreateStaticStringFromArray(const std::array<char, N> &array) {
  char tmp[N];
  for (std::size_t i = 0; i < N; ++i)
    tmp[i] = array[i];
  return CreateStaticString(tmp);
}
*/

template <std::size_t N1, std::size_t N2>
constexpr auto Concat(const StaticString<N1> &s1, const StaticString<N2> &s2) {
  char result[N1 + N2 - 1] = {0};
  for (std::size_t i = 0; i < N1 - 1; ++i)
    result[i] = s1.str[i];
  std::size_t j = 0;
  for (std::size_t i = N1 - 1; i < N1 + N2 - 2; ++i, ++j)
    result[i] = s2.str[j];
  return CreateStaticString(result);
}

template <class T> constexpr auto TypeOf(T) {
  return CreateStaticString("unknown");
}

template <> constexpr auto TypeOf<int>(int) { return CreateStaticString("%d"); }
// template <> constexpr auto TypeOf<char>(char) { return "%c"; }
// template <> constexpr auto TypeOf<char*>(char*) { return "%s"; }
// template <> constexpr auto TypeOf<float>(float) { return "%f"; }

template <class T, class... Args>
constexpr auto TypeOf(const T &t, const Args &... args) {
  constexpr auto s1 = TypeOf(t);
  constexpr auto s2 = TypeOf(args...);
  constexpr auto r = Concat(s1, s2);
  return r;
}

template <class... Args> constexpr auto PrintfFormating(Args... args) {
  return TypeOf(args...).str;
}

int main() {
  constexpr int t = 3;
  constexpr auto result = TypeOf(t, 2.);
  std::cout << result.str << std::endl;
  return 0;
}
