#ifndef MODEL_H_
#define MODEL_H_

#include <cctype>
#include <cmath>
#include <cstring>
#include <map>
#include <stack>
#include <string>
#include <vector>

#ifndef M_E
#define M_E 2.71828182845904523536028747135266250
#endif
#ifndef M_PI
#define M_PI 3.14159265358979323846264338327950288
#endif

namespace s21 {
class Model {
 private:
  struct Token;

 public:
  Model() {
    priority['+'] = 3;
    priority['-'] = 3;
    priority['*'] = 4;
    priority['/'] = 4;
    priority['\%'] = 4;
    priority['^'] = 5;
    priority['~'] = 6;
  }
  ~Model() {}

  double Calculate(const std::string input, double x) {
    std::vector<Model::Token> rpn = Tokenize(input);
    rpn = ConvertToRPN(rpn);
    std::stack<double> stack;
    double a = 0;
    double b = 0;
    for (auto it : rpn) {
      if (it.type == Token::OPERAND) {
        if (it.str == "e") {
          stack.push(M_E);
        } else if (it.str == "pi") {
          stack.push(M_PI);
        } else if (it.str == "x") {
          stack.push(x);
        } else {
          stack.push((double)std::stod(it.str));
        }
      } else if (it.type == Token::OPERATOR) {
        if (stack.empty()) {
          throw "Input error";
        }
        b = stack.top();
        stack.pop();
        if (it.str == "~") {
          stack.push(-b);
        } else {
          if (stack.empty()) {
            throw "Input error";
          }
          a = stack.top();
          stack.pop();
          if (it.str == "+") {
            stack.push(a + b);
          } else if (it.str == "-") {
            stack.push(a - b);
          } else if (it.str == "*") {
            stack.push(a * b);
          } else if (it.str == "/") {
            stack.push(a / b);
          } else if (it.str == "^") {
            stack.push(std::pow(a, b));
          } else if (it.str == "\%") {
            stack.push(std::fmod(a, b));
          }
        }
      } else if (it.type == Token::FUNCTION) {
        if (stack.empty()) {
          throw "Input error";
        }
        a = stack.top();
        stack.pop();
        if (it.str == "sin") {
          stack.push(std::sin(a));
        } else if (it.str == "cos") {
          stack.push(std::cos(a));
        } else if (it.str == "tan") {
          stack.push(std::tan(a));
        } else if (it.str == "sqrt") {
          stack.push(std::sqrt(a));
        } else if (it.str == "asin") {
          stack.push(std::asin(a));
        } else if (it.str == "ln") {
          stack.push(std::log(a));
        } else if (it.str == "log") {
          stack.push(std::log10(a));
        } else if (it.str == "acos") {
          stack.push(std::acos(a));
        } else if (it.str == "atan") {
          stack.push(std::atan(a));
        }
      } else {
        throw "Input error";
      }
    }
    if (stack.empty()) {
      throw "Input error";
    }

    return stack.top();
  }

  std::string Credit(double sum, int month, double percent, bool annuity) {
    if (annuity) {
      return CreditAnnuity(sum, month, percent);
    } else {
      return CreditDifferentiated(sum, month, percent);
    }
  }

 private:
  struct Token {
    enum Type { OPERAND, OPERATOR, FUNCTION, LEFT_BRACKET, RIGHT_BRACKET };
    Type type;
    enum Associativity { NONE, RIGHT, LEFT };
    Associativity associativity;
    std::string str;
    int prior;
    Token(std::string str, int prior) : str(str), prior(prior) {}
    Token() {}
  };

  std::map<char, int> priority;
  std::vector<std::string> functions = {"sin", "cos", "tan",  "sqrt", "asin",
                                        "ln",  "log", "acos", "atan"};

  double BankRound(double num, int exp) {
    double res = num * pow(10, exp);
    if (fabs(res - trunc(res)) == 0.5) {
      if (!fmod(round(res), 2)) {
        res = round(res);
      } else {
        res = round(res) - 1;
      }
    } else {
      res = round(res);
    }
    return res / pow(10, exp);
  }

  bool isOperator(char c) { return priority.find(c) != priority.end(); }

  bool isFunction(std::string str) {
    return std::find(functions.begin(), functions.end(), str) !=
           functions.end();
  }

  int is_delim(char c, const char *delim) {
    int res = 0;
    while (*delim != '\0') {
      if (c == *delim) {
        res = 1;
      }
      delim++;
    }
    return res;
  }

  std::string InputPrepare(const std::string &src) {
    std::string input(src);
    input.erase(std::remove_if(input.begin(), input.end(), isspace),
                input.end());  // Удаляем пробелы
    size_t i = 0;
    while (i = input.find("Mod", i), i != std::string::npos) {
      input.replace(i, 3, "\%");
    }
    i = 0;
    while (i < input.length()) {
      if (input[i] == '+' && (i == 0 || is_delim(input[i - 1], "+-*/^\%("))) {
        input.replace(i, 1, "");
      }
      i++;
    }
    return input;
  }

  std::vector<Model::Token> Tokenize(const std::string &input) {
    std::vector<Model::Token> tokens;
    std::string str;
    Token token;
    std::string src(input);
    src = InputPrepare(src);
    size_t i = 0;
    if (src.empty()) throw "Input error";
    while (i < src.length()) {
      int dotCount = 0;
      if (std::isdigit(src[i]) || src[i] == '.') {
        if (src[i] == '.') ++dotCount;
        str += src[i];
        i++;
        while (std::isdigit(src[i]) || src[i] == '.') {
          if (src[i] == '.') ++dotCount;
          str += src[i];
          i++;
        }
        if (src[i] == 'e') {
          str += src[i++];
          if (src[i] == '-' || src[i] == '+') {
            str += src[i++];
          }
          while (std::isdigit(src[i])) {
            str += src[i++];
          }
        }
        token.str = str;
        if (dotCount > 1) throw "Input error";
        token.prior = 1;
        token.type = Token::OPERAND;
        token.associativity = Token::NONE;
        tokens.push_back(token);
        str.clear();
      } else if (src[i] == 'e' || src[i] == 'x') {
        str += src[i];
        i++;
        token.str = str;
        token.prior = 1;
        token.type = Token::OPERAND;
        token.associativity = Token::NONE;
        tokens.push_back(token);
        str.clear();
      } else if (src[i] == 'p' && src[i + 1] == 'i') {
        str += src[i];
        str += src[i + 1];
        i += 2;
        token.str = str;
        token.prior = 1;
        token.type = Token::OPERAND;
        token.associativity = Token::NONE;
        tokens.push_back(token);
        str.clear();
      } else if (isOperator(src[i])) {
        str += src[i];
        token.str = str;
        token.prior = priority[src[i]];
        token.type = Token::OPERATOR;
        token.associativity = Token::LEFT;
        if (src[i] == '^') {
          token.associativity = Token::RIGHT;
        } else if (src[i] == '-' &&
                   (i == 0 || is_delim(src[i - 1], "+-*/^\%("))) {
          token.str = "~";
          token.prior = 6;
          token.type = Token::OPERATOR;
          token.associativity = Token::RIGHT;
        }
        tokens.push_back(token);
        str.clear();
        i++;
      } else if (src[i] == '(') {
        if (i != 0 &&
            (std::isdigit(src[i - 1]) || src[i - 1] == 'e' ||
             src[i - 1] == 'x' || src[i - 1] == 'i' || src[i - 1] == '.')) {
          throw "Input error";
        }
        str += src[i];
        token.str = str;
        token.prior = 2;
        token.type = Token::LEFT_BRACKET;
        token.associativity = Token::NONE;
        tokens.push_back(token);
        str.clear();
        i++;
      } else if (src[i] == ')') {
        if (i != src.length() - 1 &&
            (std::isdigit(src[i + 1]) || src[i + 1] == 'e' ||
             src[i + 1] == 'x' || src[i + 1] == 'i' || src[i + 1] == '.')) {
          throw "Input error";
        }
        str += src[i];
        token.str = str;
        token.prior = 2;
        token.type = Token::RIGHT_BRACKET;
        token.associativity = Token::NONE;
        tokens.push_back(token);
        str.clear();
        i++;
      } else if (is_delim(src[i], "sctal")) {
        while (std::isalpha(src[i])) {
          str += src[i];
          i++;
        }
        token.str = str;
        if (isFunction(str)) {
          token.prior = 0;
          token.type = Token::FUNCTION;
          token.associativity = Token::NONE;
        } else {
          throw "Input error";
        }
        tokens.push_back(token);
        str.clear();
      } else {
        throw "Input error";
      }
    }
    auto it = tokens.begin();
    ++it;
    for (; it != tokens.end(); ++it) {
      if (it->type == Token::OPERAND && (it - 1)->type == Token::OPERAND) {
        throw "Input error";
      }
    }
    return tokens;
  }

  std::vector<Model::Token> ConvertToRPN(const std::vector<Model::Token> &src) {
    std::vector<Model::Token> rpn;
    std::stack<Model::Token> stack;
    for (auto it : src) {
      if (it.type == Token::OPERAND) {
        rpn.push_back(it);
      } else if (it.type == Token::FUNCTION) {
        stack.push(it);
      } else if (it.type == Token::OPERATOR) {
        while (!stack.empty() && stack.top().type == Token::OPERATOR &&
               ((it.associativity == Token::LEFT &&
                 it.prior <= stack.top().prior) ||
                (it.associativity == Token::RIGHT &&
                 it.prior < stack.top().prior))) {
          rpn.push_back(stack.top());
          stack.pop();
        }
        stack.push(it);
      } else if (it.type == Token::LEFT_BRACKET) {
        stack.push(it);
      } else if (it.type == Token::RIGHT_BRACKET) {
        while (!stack.empty() && stack.top().type != Token::LEFT_BRACKET) {
          rpn.push_back(stack.top());
          stack.pop();
        }
        if (stack.empty()) {
          throw "Input error";
        }
        stack.pop();
        if (!stack.empty() && stack.top().type == Token::FUNCTION) {
          rpn.push_back(stack.top());
          stack.pop();
        }
      }
    }
    while (!stack.empty()) {
      rpn.push_back(stack.top());
      stack.pop();
    }
    // for (auto it : rpn) {
    //   std::cout << it.str << " ";
    // }
    return rpn;
  }

  std::string CreditAnnuity(double sum, int month, double percent) {
    char *res;

    res = (char *)calloc(90 * (4 + month), sizeof(char));

    double payment = BankRound(
        sum * (percent / 100 / 12 +
               percent / 100 / 12 / (pow(1 + percent / 100 / 12, month) - 1)),
        2);
    double overpayment = payment * month - sum;
    double total = payment * month;

    sprintf(res,
            "Monthly payment: %.2f;\nInterest charges: %.2f;\nDebt + "
            "interest: %.2f;\n",
            payment, overpayment, total);

    double remaining = sum;

    strncat(res, "Payment schedule:\n", 90);
    strncat(res,
            " №      Amount of       Principal      Interest        Balance\n",
            90);
    strncat(res,
            " №:       payment:        payment:      payment:          owed:\n",
            90);

    for (int i = 1; i <= month; i++) {
      char *tmp = (char *)calloc(90, sizeof(char));
      double interest = BankRound(remaining * percent / 100 / 12, 2);
      double principal = payment - interest;
      remaining -= principal;
      if (i == month && remaining != 0) {
        payment += remaining;
        principal += remaining;
        remaining = 0;
      }
      sprintf(tmp, "%3d %14.2f %15.2f %13.2f %14.2f\n", i, payment, principal,
              interest, remaining);
      strncat(res, tmp, 90);
      free(tmp);
    }
    std::string out(res);
    free(res);
    return out;
  }

  std::string CreditDifferentiated(double sum, int month, double percent) {
    char *res, *schedule;

    res = (char *)calloc(90 * (3 + month), sizeof(char));
    schedule = (char *)calloc(90 * (2 + month), sizeof(char));

    double firstPayment =
        BankRound(sum / month + percent / 100 / 12 * (sum), 4);
    double lastPayment = BankRound(
        sum / month + percent / 100 / 12 * (sum - (sum * (month - 1)) / month),
        4);
    double interest = 0;
    sprintf(res, "First payment: %.2f;\nLast payment: %.2f;\n", firstPayment,
            lastPayment);

    double principal = BankRound(sum / month, 4);
    double remaining = sum;
    for (int i = 1; i <= month; i++) {
      double payment = BankRound(
          sum / month + percent / 100 / 12 * (sum - (sum * (i - 1)) / month),
          4);
      char *tmp = (char *)calloc(90, sizeof(char));
      double overpayment = (sum - principal * (i - 1)) * percent / 100 / 12;
      interest = BankRound(interest + overpayment, 4);
      remaining = BankRound(remaining - principal, 4);
      if (i == month && remaining != 0) {
        payment += remaining;
        principal += remaining;
        remaining = 0;
      }
      sprintf(tmp, "%3d %14.2f %15.2f %13.2f %14.2f\n", i, payment, principal,
              overpayment, remaining);
      strcat(schedule, tmp);
      free(tmp);
    }
    char *tmp = (char *)calloc(90, sizeof(char));
    sprintf(tmp, "Interest charges: %.2f;\nDebt + interest: %.2f;\n", interest,
            sum + interest);
    strncat(res, tmp, 90);
    free(tmp);

    strncat(res, "Payment schedule:\n", 90);
    strncat(res,
            " №      Amount of       Principal      Interest        Balance\n",
            90);
    strncat(res,
            " №:       payment:        payment:      payment:          owed:\n",
            90);
    strncat(res, schedule, 90 * (4 + month));
    free(schedule);
    std::string out(res);
    free(res);
    return out;
  }
};

}  // namespace s21

#endif  // MODEL_H_
