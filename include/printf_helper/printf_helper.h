#ifndef PRINTF_HELPER_H_
#define PRINTF_HELPER_H_

namespace printf_helper {

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
constexpr auto operator+(StaticString<N1> lhs, StaticString<N2> rhs) {
  char result[N1 + N2 - 1] = {0};
  for (std::size_t i = 0; i < N1 - 1; ++i)
    result[i] = lhs.str[i];
  std::size_t j = 0;
  for (std::size_t i = N1 - 1; i < N1 + N2 - 2; ++i, ++j)
    result[i] = rhs.str[j];
  return CreateStaticString(result);
}

template <class T> struct RemoveConstFromPointer { using type = T; };
template <class T> struct RemoveConstFromPointer<const T *> {
  using type = T *;
};

template <class T> constexpr auto TypeOf() { CreateStaticString("unknown"); }

// template <> constexpr auto TypeOf<wint_t>(wint_t) {
//  return CreateStaticString("%lc");
//}
template <> constexpr auto TypeOf<char *>() { return CreateStaticString("%s"); }
// template <> constexpr auto TypeOf<wchar_t*>(wchar_t*) { return "%ls"); }
template <> constexpr auto TypeOf<char>() { return CreateStaticString("%c"); }
template <> constexpr auto TypeOf<short>() { return CreateStaticString("%hd"); }
template <> constexpr auto TypeOf<int>() { return CreateStaticString("%d"); }
template <> constexpr auto TypeOf<long>() { return CreateStaticString("%ld"); }
template <> constexpr auto TypeOf<long long>() {
  return CreateStaticString("%lld");
}
// template <> constexpr auto TypeOf<intmax_t>(intmax_t) {
//  return CreateStaticString("%jd");
//}
template <> constexpr auto TypeOf<unsigned short>() {
  return CreateStaticString("%hu");
}
template <> constexpr auto TypeOf<unsigned int>() {
  return CreateStaticString("%u");
}
template <> constexpr auto TypeOf<unsigned long>() {
  return CreateStaticString("%lu");
}
template <> constexpr auto TypeOf<unsigned long long>() {
  return CreateStaticString("%llu");
}
template <> constexpr auto TypeOf<float>() { return CreateStaticString("%f"); }
template <> constexpr auto TypeOf<double>() { return CreateStaticString("%f"); }
template <> constexpr auto TypeOf<long double>() {
  return CreateStaticString("%Lf");
}

template <class T> constexpr auto TypeOfCool() {
  if constexpr (std::is_pointer<T>::value)
    return TypeOf<typename RemoveConstFromPointer<T>::type>();
  else
    return TypeOf<T>();
}

template <class... Args> constexpr auto PrintfFormatting(Args... args) {
  return (... + TypeOfCool<Args>());
}

} // namespace printf_helper

#endif // PRINTF_HELPER_H_
