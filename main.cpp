#include <iostream>
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

//template <> constexpr auto TypeOf<wint_t>(wint_t) {
//  return CreateStaticString("%lc");
//}
template <> constexpr auto TypeOf<char *>(char *) {
  return CreateStaticString("%s");
}
// template <> constexpr auto TypeOf<wchar_t*>(wchar_t*) { return "%ls"); }
template <> constexpr auto TypeOf<char>(char) {
  return CreateStaticString("%c");
}
template <> constexpr auto TypeOf<short>(short) {
  return CreateStaticString("%hd");
}
template <> constexpr auto TypeOf<int>(int) { return CreateStaticString("%d"); }
template <> constexpr auto TypeOf<long>(long) {
  return CreateStaticString("%ld");
}
template <> constexpr auto TypeOf<long long>(long long) {
  return CreateStaticString("%lld");
}
//template <> constexpr auto TypeOf<intmax_t>(intmax_t) {
//  return CreateStaticString("%jd");
//}
template <> constexpr auto TypeOf<unsigned short>(unsigned short) {
  return CreateStaticString("%hu");
}
template <> constexpr auto TypeOf<unsigned int>(unsigned int) {
  return CreateStaticString("%u");
}
template <> constexpr auto TypeOf<unsigned long>(unsigned long) {
  return CreateStaticString("%lu");
}
template <> constexpr auto TypeOf<unsigned long long>(unsigned long long) {
  return CreateStaticString("%llu");
}
template <> constexpr auto TypeOf<float>(float) {
  return CreateStaticString("%f");
}
template <> constexpr auto TypeOf<double>(double) {
  return CreateStaticString("%f");
}
template <> constexpr auto TypeOf<long double>(long double) {
  return CreateStaticString("%Lf");
}

template <class T, class... Args>
constexpr auto TypeOf(const T &t, const Args &... args) {
  const auto s1 = TypeOf(t);
  const auto s2 = TypeOf(args...);
  const auto r = Concat(s1, s2);
  return r;
}

template <class... Args> constexpr auto PrintfFormating(Args... args) {
  return TypeOf(args...);
}

int main() {
  constexpr auto s = PrintfFormating("abc", 1, 2.f, 3., 2l, 3u);
  std::cout << s.str << std::endl;
  return 0;
}
