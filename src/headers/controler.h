#ifndef CONTROLER_H_
#define CONTROLER_H_

#include "model.h"

namespace s21 {

class Controler {
 public:
  double Calculus(std::string input, double x) {
    return model.Calculate(input, x);
  }

  std::string Credit(double sum, int month, double percent, bool annuity) {
    return model.Credit(sum, month, percent, annuity);
  }

 private:
  Model model;
};

}  // namespace s21

#endif  // CONTROLER_H_
