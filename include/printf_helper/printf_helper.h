#ifndef PRINTF_HELPER_H_
#define PRINTF_HELPER_H_

namespace printf_helper {

namespace impl {

template <std::size_t N> class ConstexprString {
public:
  constexpr explicit ConstexprString(const char (&s)[N]) : str_{0} {
    for (std::size_t i = 0; i < N; ++i)
      str_[i] = s[i];
  }

  constexpr operator const char *() const { return str_; } // NOLINT

  template <std::size_t N1, std::size_t N2>
  friend constexpr auto operator+(ConstexprString<N1> lhs,
                                  const char (&rhs)[N2]);

  template <std::size_t N1, std::size_t N2>
  friend constexpr auto operator+(ConstexprString<N1> lhs,
                                  ConstexprString<N2> rhs);

private:
  char str_[N];
};

template <std::size_t N>
constexpr ConstexprString<N> CreateConstexprString(const char (&s)[N]) {
  return ConstexprString<N>(s);
}

template <std::size_t N1, std::size_t N2>
constexpr auto operator+(ConstexprString<N1> lhs, const char (&rhs)[N2]) {
  char result[N1 + N2 - 1] = {0};
  for (std::size_t i = 0; i < N1 - 1; ++i)
    result[i] = lhs.str_[i];
  std::size_t j = 0;
  for (std::size_t i = N1 - 1; i < N1 + N2 - 2; ++i, ++j)
    result[i] = rhs[j];
  return CreateConstexprString(result);
}

template <std::size_t N1, std::size_t N2>
constexpr auto operator+(ConstexprString<N1> lhs, ConstexprString<N2> rhs) {
  return lhs + rhs.str_;
}

template <class T> struct RemoveConstFromPointer { using type = T; };
template <class T> struct RemoveConstFromPointer<const T *> {
  using type = T *;
};

template <class T> constexpr auto TypeOfPointer() {
  return CreateConstexprString("%p");
}

template <> constexpr auto TypeOfPointer<char *>() {
  return CreateConstexprString("%s");
}

template <class T> constexpr auto TypeOf() {
  static_assert(std::is_pointer<T>::value || std::is_reference<T>::value,
                "Unknown type for printf_helper");
  if constexpr (std::is_pointer<T>::value)
    return TypeOfPointer<typename RemoveConstFromPointer<T>::type>();

  // T is a reference
  return TypeOf<
      typename std::remove_cv<typename std::remove_reference<T>::type>::type>();
}

// template <> constexpr auto TypeOf<wint_t>(wint_t) {
//  return CreateConstexprString("%lc");
//}
// template <> constexpr auto TypeOf<wchar_t*>(wchar_t*) { return "%ls"); }
template <> constexpr auto TypeOf<char>() {
  return CreateConstexprString("%c");
}
template <> constexpr auto TypeOf<short>() {
  return CreateConstexprString("%hd");
}
template <> constexpr auto TypeOf<int>() { return CreateConstexprString("%d"); }
template <> constexpr auto TypeOf<long>() {
  return CreateConstexprString("%ld");
}
template <> constexpr auto TypeOf<long long>() {
  return CreateConstexprString("%lld");
}
// template <> constexpr auto TypeOf<intmax_t>(intmax_t) {
//  return CreateConstexprString("%jd");
//}

template <> constexpr auto TypeOf<unsigned char>() {
  return CreateConstexprString("%hhu");
}
template <> constexpr auto TypeOf<unsigned short>() {
  return CreateConstexprString("%hu");
}
template <> constexpr auto TypeOf<unsigned int>() {
  return CreateConstexprString("%u");
}
template <> constexpr auto TypeOf<unsigned long>() {
  return CreateConstexprString("%lu");
}
template <> constexpr auto TypeOf<unsigned long long>() {
  return CreateConstexprString("%llu");
}
template <> constexpr auto TypeOf<float>() {
  return CreateConstexprString("%f");
}
template <> constexpr auto TypeOf<double>() {
  return CreateConstexprString("%f");
}
template <> constexpr auto TypeOf<long double>() {
  return CreateConstexprString("%Lf");
}

} // namespace impl

template <class... Args> constexpr auto GetPrintfFormat(Args... args) {
  return (... + impl::TypeOf<Args>());
}

} // namespace printf_helper

#endif // PRINTF_HELPER_H_
