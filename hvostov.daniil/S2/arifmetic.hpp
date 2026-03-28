#ifndef ARIFMETIC_HPP
#define ARIFMETIC_HPP

#include <cstddef>
#include <string>
#include <istream>
#include "stack.hpp"
#include "queue.hpp"

namespace hvostov {
  Queue< std::string > getInfix(const std::string& expression);
  bool isSupportedOperand(const std::string& operand);
  size_t getPriority(const std::string& operation);
  Queue< std::string > getPostfix(Queue< std::string >& infix);
  int evaluatePostfix(Queue< std::string >& postfix);
  void printResult(std::istream& in);
}

#endif
