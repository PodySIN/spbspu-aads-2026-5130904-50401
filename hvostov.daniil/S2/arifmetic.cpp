#include "arifmetic.hpp"

bool hvostov::isSupportedOperand(const std::string& operand)
{
  std::string supportedOperands[] = {"<<", "+", "-", "%", "*", "/", "(", ")"};
  for (size_t i = 0; i < 8; i++) {
    if (operand == supportedOperands[i]) {
      return true;
    }
  }
  return false;
}

hvostov::Queue< std::string > hvostov::getInfix(const std::string& expression)
{
  Queue< std::string > infix;
  std::string element;
  for (size_t i = 0; i < expression.length(); i++) {
    if (expression[i] == ' ') {
      infix.push(element);
      element.clear();
    } else {
      element.push_back(expression[i]);
    }
  }
  if (element != "") {
    infix.push(element);
  }
  return infix;
}

size_t hvostov::getPriority(const std::string& operation)
{
  if (operation == "<<") {
    return 3;
  } else if (operation == "*" || operation == "/") {
    return 2;
  } else if (operation == "+" || operation == "-" || operation == "%") {
    return 1;
  }
  return 0;
}

hvostov::Queue< std::string > hvostov::getPostfix(Queue< std::string >& infix)
{
  Stack< std::string > operations;
  Queue< std::string > posfix;
  while (!infix.empty()) {
    std::string curr = infix.drop();
    if (isdigit(curr[0])) {
      posfix.push(curr);
    } else if (isSupportedOperand(curr)) {
      size_t priority = getPriority(curr);
      if (priority > 0) {
        while (!operations.empty() &&
            operations.top() != "(" &&
            (getPriority(operations.top()) >= priority)) {
          posfix.push(operations.drop());
        }
      } else if (curr == "(") {
        operations.push(curr);
      } else if (curr == ")") {
        while (!operations.empty() && operations.top() != "(") {
          posfix.push(operations.drop());
        }
        if (!operations.empty() && operations.top() == "(") {
          operations.drop();
        } else {
          throw std::logic_error("Mismatched parentheses!");
        }
      } 
    } else {
      throw std::logic_error("Wrong input!");
    }
  }
  while (!operations.empty()) {
    posfix.push(operations.drop());
  }
  return posfix;
}

int hvostov::evaluatePostfix(Queue< std::string >& postfix)
{
}

void hvostov::printResult(std::istream& in)
{

}
