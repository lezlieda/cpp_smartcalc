#include <gtest/gtest.h>

#include "../headers/controler.h"

TEST(Model, Test1) {
  std::string input = "(2+(2+-3)/(sin((9-2)*2^3)-6/-7)*-sin(3^4))^-2.72";
  s21::Controler controler;
  double x = 1;
  double result = controler.Calculus(input, x);
  EXPECT_NEAR(result, 298.5007615384, 1e-7);
}

TEST(Model, Test2) {
  std::string input =
      "+cos(e^ln(34.56))+sqrt(atan(0.8)+pi)-log(tan(pi/3)+-1--2)";
  s21::Controler controler;
  double x = 1;
  double result = controler.Calculus(input, x);
  EXPECT_NEAR(result, 0.51705816122572, 1e-7);
}

TEST(Model, Test3) {
  std::string input = "asin(0.123456) Mod acos(.165165)";
  s21::Controler controler;
  double x = 1;
  double result = controler.Calculus(input, x);
  EXPECT_NEAR(result, 0.123771777, 1e-7);
}

TEST(Model, Test4) {
  std::string input = "1.380650424e-24 * 6.02214129e23";
  s21::Controler controler;
  double x = 1;
  double result = controler.Calculus(input, x);
  EXPECT_NEAR(result, 0.83144719254264, 1e-7);
}

TEST(Model, Invalid_Input) {
  std::string input = "ee";
  s21::Controler controler;
  double x = 1;
  EXPECT_ANY_THROW(controler.Calculus(input, x));
  input = "e^";
  EXPECT_ANY_THROW(controler.Calculus(input, x));
  input = "sinus(x)-cos(x)";
  EXPECT_ANY_THROW(controler.Calculus(input, x));
  input = "***";
  EXPECT_ANY_THROW(controler.Calculus(input, x));
  input = "";
  EXPECT_ANY_THROW(controler.Calculus(input, x));
  input = "sin";
  EXPECT_ANY_THROW(controler.Calculus(input, x));
  input = "sin(x";
  EXPECT_ANY_THROW(controler.Calculus(input, x));
  input = "2(2+2)";
  EXPECT_ANY_THROW(controler.Calculus(input, x));
  input = "(3-4)5";
  EXPECT_ANY_THROW(controler.Calculus(input, x));
}

TEST(Model, Credit_Annuity) {
  s21::Controler controler;
  double sum = 250000;
  int months = 10;
  double rate = 18.99;
  std::string res = controler.Credit(sum, months, rate, true);
  std::string expected =
      "Monthly payment: 27227.16;\nInterest charges: 22271.60;\n"
      "Debt + interest: 272271.60;\nPayment schedule:\n"
      " №      Amount of       Principal      Interest        Balance\n"
      " №:       payment:        payment:      payment:          owed:\n"
      "  1       27227.16        23270.91       3956.25      226729.09\n"
      "  2       27227.16        23639.17       3587.99      203089.92\n"
      "  3       27227.16        24013.26       3213.90      179076.66\n"
      "  4       27227.16        24393.27       2833.89      154683.39\n"
      "  5       27227.16        24779.30       2447.86      129904.09\n"
      "  6       27227.16        25171.43       2055.73      104732.66\n"
      "  7       27227.16        25569.77       1657.39       79162.89\n"
      "  8       27227.16        25974.41       1252.75       53188.48\n"
      "  9       27227.16        26385.45        841.71       26803.03\n"
      " 10       27227.19        26803.03        424.16           0.00\n";
  EXPECT_EQ(res, expected);
}

TEST(Model, Credit_Differentated) {
  s21::Controler controler;
  double sum = 250000;
  int months = 10;
  double rate = 18.99;
  std::string res = controler.Credit(sum, months, rate, false);
  std::string expected =
      "First payment: 28956.25;\nLast payment: 25395.62;\n"
      "Interest charges: 21759.38;\nDebt + interest: 271759.38;\n"
      "Payment schedule:\n"
      " №      Amount of       Principal      Interest        Balance\n"
      " №:       payment:        payment:      payment:          owed:\n"
      "  1       28956.25        25000.00       3956.25      225000.00\n"
      "  2       28560.62        25000.00       3560.62      200000.00\n"
      "  3       28165.00        25000.00       3165.00      175000.00\n"
      "  4       27769.38        25000.00       2769.37      150000.00\n"
      "  5       27373.75        25000.00       2373.75      125000.00\n"
      "  6       26978.12        25000.00       1978.12      100000.00\n"
      "  7       26582.50        25000.00       1582.50       75000.00\n"
      "  8       26186.88        25000.00       1186.87       50000.00\n"
      "  9       25791.25        25000.00        791.25       25000.00\n"
      " 10       25395.62        25000.00        395.62           0.00\n";
  EXPECT_EQ(res, expected);
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
