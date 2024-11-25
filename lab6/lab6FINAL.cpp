#include <cmath>
#include <iomanip>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <vector>

class Expression {
 public:
  virtual ~Expression() = default;
  Expression() = default;
  Expression(const Expression& other) = default;
  Expression& operator=(const Expression& other) = default;
  Expression(Expression&& other) = default;
  Expression& operator=(Expression&& other) = default;
  virtual double eval() const = 0;
  virtual void add_operand(std::shared_ptr<Expression> expr) {}
};

class Number : public Expression {
 private:
  double value;

 public:
  explicit Number(double value) : value(value) {}
  double eval() const override { return value; }
};

class Add : public Expression {
 private:
  std::vector<std::shared_ptr<Expression>> operands;

 public:
  void add_operand(std::shared_ptr<Expression> expr) override {
    operands.push_back(expr);
  }

  double eval() const override {
    double result = 0.0;
    for (const auto& operand : operands) {
      result += operand->eval();
    }
    return result;
  }
};

class Sub : public Expression {
 private:
  std::vector<std::shared_ptr<Expression>> operands;

 public:
  void add_operand(std::shared_ptr<Expression> expr) override {
    operands.push_back(expr);
  }

  double eval() const override {
    if (operands.empty())
      return 0.0;
    double result = operands[0]->eval();
    for (size_t i = 1; i < operands.size(); ++i) {
      result -= operands[i]->eval();
    }
    return result;
  }
};

class Mul : public Expression {
 private:
  std::vector<std::shared_ptr<Expression>> operands;

 public:
  void add_operand(std::shared_ptr<Expression> expr) override {
    operands.push_back(expr);
  }

  double eval() const override {
    double result = 1.0;
    for (const auto& operand : operands) {
      result *= operand->eval();
    }
    return result;
  }
};

class Div : public Expression {
 private:
  std::vector<std::shared_ptr<Expression>> operands;

 public:
  void add_operand(std::shared_ptr<Expression> expr) override {
    operands.push_back(expr);
  }

  double eval() const override {
    if (operands.empty())
      return 1.0;
    double result = operands[0]->eval();
    for (size_t i = 1; i < operands.size(); ++i) {
      const double divisor = operands[i]->eval();
      if (divisor == 0) {
        return std::nan("");
      }
      result /= divisor;
    }
    return result;
  }
};

class Invalid : public Expression {
 public:
  double eval() const override { return std::nan(""); }
};

std::shared_ptr<Expression> parse_expression(std::istringstream& stream) {
  char c;
  stream >> c;

  if (c == '(') {
    char op;
    stream >> op;
    std::shared_ptr<Expression> expr;

    if (op == '+') {
      expr = std::make_shared<Add>();
    } else if (op == '-') {
      expr = std::make_shared<Sub>();
    } else if (op == '*') {
      expr = std::make_shared<Mul>();
    } else if (op == '/') {
      expr = std::make_shared<Div>();
    } else {
      return std::make_shared<Invalid>();
    }

    while (stream.peek() != ')' && !stream.eof()) {
      if (std::isdigit(stream.peek()) ||
          (stream.peek() == '-' &&
           (stream.peek() != '-' || std::isdigit(stream.peek() + 1)))) {
        double value;
        stream >> value;
        expr->add_operand(std::make_shared<Number>(value));
      } else {
        auto nested_expr = parse_expression(stream);
        if (dynamic_cast<Invalid*>(nested_expr.get())) {
          return nested_expr;
        }
        expr->add_operand(nested_expr);
      }
    }
    stream >> c;
    return expr;
  } else if (std::isdigit(c) || (c == '-' && std::isdigit(stream.peek()))) {
    stream.putback(c);
    double value;
    stream >> value;
    return std::make_shared<Number>(value);
  }
  return std::make_shared<Invalid>();
}

void interpret(const std::string& expression) {
  std::istringstream stream(expression);
  auto result = parse_expression(stream);
  if (dynamic_cast<Invalid*>(result.get())) {
    std::cout << "nan" << '\n';
  } else {
    std::cout << std::fixed << std::setprecision(4) << result->eval() << '\n';
  }
}
int main() {
  std::string line;
  while (std::getline(std::cin, line)) {
    interpret(line);
  }
  return 0;
}