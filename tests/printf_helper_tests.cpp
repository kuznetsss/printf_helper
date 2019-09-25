#include "printf_helper/printf_helper.h"

#include <gtest/gtest.h>

#include <string>

class PrintfHelperTests : public ::testing::Test {
 protected:
  template <class T>
  std::string GetFormatString(T t) {
    return std::string(printf_helper::GetPrintfFormat(t));
  };
};

TEST_F(PrintfHelperTests, SimpleTypes) {
  EXPECT_EQ(GetFormatString(char()), "%c");
  EXPECT_EQ(GetFormatString("const char*"), "%s");
  EXPECT_EQ(GetFormatString(short()), "%hd");
  EXPECT_EQ(GetFormatString(int()), "%d");
  EXPECT_EQ(GetFormatString(long()), "%ld");
  long long ll = 0ll;
  EXPECT_EQ(GetFormatString(ll), "%lld");
  unsigned char uc = 1;
  EXPECT_EQ(GetFormatString(uc), "%hhu");
  unsigned short us = 1;
  EXPECT_EQ(GetFormatString(us), "%hu");
  unsigned int ui = 1;
  EXPECT_EQ(GetFormatString(ui), "%u");
  unsigned long ul = 1;
  EXPECT_EQ(GetFormatString(ul), "%lu");
  unsigned long long ull = 1;
  EXPECT_EQ(GetFormatString(ull), "%llu");
  EXPECT_EQ(GetFormatString(float(0.f)), "%f");
  EXPECT_EQ(GetFormatString(double(0.)), "%f");
  long double ld = 0.;
  EXPECT_EQ(GetFormatString(ld), "%Lf");
  // This will cause static_assert fail
  // struct Foo {};
  // GetFormatString(Foo());
}

TEST_F(PrintfHelperTests, Pointers) {
  int i = 0;
  EXPECT_EQ(GetFormatString(&i), "%p");
  void *v = nullptr;
  EXPECT_EQ(GetFormatString(v), "%p");
  std::string str = "abc";
  EXPECT_EQ(GetFormatString(str.c_str()), "%s");
}

TEST_F(PrintfHelperTests, References) {
  int i = 0;
  int &i_ref = i;
  EXPECT_EQ(GetFormatString(i_ref), "%d");
}

TEST_F(PrintfHelperTests, OperatorPlus) {
  const auto format = printf_helper::GetPrintfFormat(int()) + "\n";
  EXPECT_EQ(std::string(format), "%d\n");
}

TEST_F(PrintfHelperTests, MultipleTypes) {
  int i = 0;
  int &i_ref = i;
  const int &i_const_ref = i;
  const auto format = printf_helper::GetPrintfFormat(
      int(), float(), double(), &i, i_ref, i_const_ref, "abc");
  EXPECT_EQ(std::string(format), "%d%f%f%p%d%d%s");
}

int main(int argc, char *argv[]) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
