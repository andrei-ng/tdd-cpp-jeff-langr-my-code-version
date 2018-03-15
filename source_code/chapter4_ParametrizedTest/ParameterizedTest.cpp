#include "gmock/gmock.h"

using namespace ::testing;

struct SumCase {
  int a, b, expected;
  SumCase(int a_val, int b_val, int expected_val) : a(a_val), b(b_val), expected(expected_val) {}
};

class AnAdder : public TestWithParam<SumCase> {};

class Adder {
 public:
  static int Sum(int a, int b) { return a + b; }
};

TEST(AnAdder, GeneratesASumFromTwoNumbers) { ASSERT_THAT(Adder::Sum(1, 1), Eq(2)); }

TEST_P(AnAdder, GeneratesLotsOfSumsFromTwoNumbers) {
  SumCase input = GetParam();
  ASSERT_THAT(Adder::Sum(input.a, input.b), Eq(input.expected));
}

SumCase sums[] = {SumCase(1, 1, 2), SumCase(1, 2, 3), SumCase(2, 2, 4), SumCase(10, 2, 4)};

INSTANTIATE_TEST_CASE_P(BulkParameterizedTest, AnAdder, ValuesIn(sums));
