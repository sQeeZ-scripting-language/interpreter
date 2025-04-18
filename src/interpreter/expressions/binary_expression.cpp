#include "interpreter/expressions/binary_expression.hpp"

BinaryExpression::BinaryExpression(
    BinaryExpr *expressionNode, std::vector<std::shared_ptr<Storage>> storage,
    std::shared_ptr<Logs> logs)
    : expressionNode(expressionNode), storage(std::move(storage)), logs(logs) {}

Storage::DataWrapper BinaryExpression::execute() {
  if (expressionNode->operator_.tag == Token::TypeTag::OPERATOR) {
    switch (expressionNode->operator_.type.operatorToken) {
    case OperatorToken::ADDITION:
      return addition(
          Expression(expressionNode->left.get(), storage, logs).execute(),
          Expression(expressionNode->right.get(), storage, logs).execute());
    case OperatorToken::SUBTRACTION:
      return subtraction(
          Expression(expressionNode->left.get(), storage, logs).execute(),
          Expression(expressionNode->right.get(), storage, logs).execute());
    case OperatorToken::MULTIPLICATION:
      return multiplication(
          Expression(expressionNode->left.get(), storage, logs).execute(),
          Expression(expressionNode->right.get(), storage, logs).execute());
    case OperatorToken::DIVISION:
      return division(
          Expression(expressionNode->left.get(), storage, logs).execute(),
          Expression(expressionNode->right.get(), storage, logs).execute());
    case OperatorToken::MODULUS:
      return modulus(
          Expression(expressionNode->left.get(), storage, logs).execute(),
          Expression(expressionNode->right.get(), storage, logs).execute());
    case OperatorToken::POTENTIATION:
      return potentiation(
          Expression(expressionNode->left.get(), storage, logs).execute(),
          Expression(expressionNode->right.get(), storage, logs).execute());

    default:
      throw std::runtime_error("Unsupported binary operator.");
    }
  } else if (expressionNode->operator_.tag == Token::TypeTag::LOGICAL) {
    switch (expressionNode->operator_.type.logicalToken) {
    case LogicalToken::EQUAL:
      return _boolean(checkEquality(
          Expression(expressionNode->left.get(), storage, logs).execute(),
          Expression(expressionNode->right.get(), storage, logs).execute(),
          true));
    case LogicalToken::NOT_EQUAL:
      return _boolean(checkEquality(
          Expression(expressionNode->left.get(), storage, logs).execute(),
          Expression(expressionNode->right.get(), storage, logs).execute(),
          false));
    case LogicalToken::GREATER:
      return _boolean(checkGreater(
          Expression(expressionNode->left.get(), storage, logs).execute(),
          Expression(expressionNode->right.get(), storage, logs).execute()));
    case LogicalToken::GREATER_EQUAL:
      return _boolean(
          checkGreater(
              Expression(expressionNode->left.get(), storage, logs).execute(),
              Expression(expressionNode->right.get(), storage, logs)
                  .execute()) ||
          checkEquality(
              Expression(expressionNode->left.get(), storage, logs).execute(),
              Expression(expressionNode->right.get(), storage, logs).execute(),
              true));
    case LogicalToken::LESS:
      return _boolean(
          !checkGreater(
              Expression(expressionNode->left.get(), storage, logs).execute(),
              Expression(expressionNode->right.get(), storage, logs)
                  .execute()) &&
          !checkEquality(
              Expression(expressionNode->left.get(), storage, logs).execute(),
              Expression(expressionNode->right.get(), storage, logs).execute(),
              true));
    case LogicalToken::LESS_EQUAL:
      return _boolean(
          !checkGreater(
              Expression(expressionNode->left.get(), storage, logs).execute(),
              Expression(expressionNode->right.get(), storage, logs)
                  .execute()) ||
          checkEquality(
              Expression(expressionNode->left.get(), storage, logs).execute(),
              Expression(expressionNode->right.get(), storage, logs).execute(),
              true));
    case LogicalToken::AND:
      return _boolean(
          checkTrueishnessOfExpression(expressionNode->left, storage, logs) &&
          checkTrueishnessOfExpression(expressionNode->right, storage, logs));
    case LogicalToken::OR:
      return _boolean(
          checkTrueishnessOfExpression(expressionNode->left, storage, logs) ||
          checkTrueishnessOfExpression(expressionNode->right, storage, logs));
    default:
      throw std::runtime_error("Unsupported logical operator.");
    }
  } else {
    throw std::runtime_error("Unsupported binary expression.");
  }
}

Storage::DataWrapper BinaryExpression::addition(Storage::DataWrapper left,
                                                Storage::DataWrapper right) {
  switch (left.dataType) {
  case Storage::DataType::INTEGER:
    switch (right.dataType) {
    case Storage::DataType::INTEGER:
      return _integer(left.data._int + right.data._int);
    case Storage::DataType::DOUBLE:
      return _double(left.data._int + right.data._double);
    case Storage::DataType::CHAR:
      return _integer(left.data._int + right.data._char);
    case Storage::DataType::STRING:
      return stringAddition(std::to_string(left.data._int),
                            *right.data._string);
    default:
      throw std::invalid_argument("Invalid addition expression!");
    }
  case Storage::DataType::DOUBLE:
    switch (right.dataType) {
    case Storage::DataType::INTEGER:
      return _double(left.data._double + right.data._int);
    case Storage::DataType::DOUBLE:
      return _double(left.data._double + right.data._double);
    case Storage::DataType::CHAR:
      return _double(left.data._double + right.data._char);
    case Storage::DataType::STRING:
      return stringAddition(std::to_string(left.data._double),
                            *right.data._string);
    default:
      throw std::invalid_argument("Invalid addition expression!");
    }
  case Storage::DataType::CHAR:
    switch (right.dataType) {
    case Storage::DataType::INTEGER:
      return _integer(left.data._char + right.data._int);
    case Storage::DataType::DOUBLE:
      return _double(left.data._char + right.data._double);
    case Storage::DataType::CHAR:
      return _integer(left.data._char + right.data._char);
    case Storage::DataType::STRING:
      return stringAddition(std::string(1, left.data._char),
                            *right.data._string);
    default:
      throw std::invalid_argument("Invalid addition expression!");
    }
  case Storage::DataType::STRING:
    switch (right.dataType) {
    case Storage::DataType::INTEGER:
      return stringAddition(*left.data._string,
                            std::to_string(right.data._int));
    case Storage::DataType::DOUBLE:
      return stringAddition(*left.data._string,
                            std::to_string(right.data._double));
    case Storage::DataType::CHAR:
      return stringAddition(*left.data._string,
                            std::string(1, right.data._char));
    case Storage::DataType::STRING:
      return stringAddition(*left.data._string, *right.data._string);
    default:
      throw std::invalid_argument("Invalid addition expression!");
    }
    break;
  default:
    throw std::invalid_argument("Invalid addition expression!");
  }
}

Storage::DataWrapper BinaryExpression::subtraction(Storage::DataWrapper left,
                                                   Storage::DataWrapper right) {
  switch (left.dataType) {
  case Storage::DataType::INTEGER:
    switch (right.dataType) {
    case Storage::DataType::INTEGER:
      return _integer(left.data._int - right.data._int);
    case Storage::DataType::DOUBLE:
      return _double(left.data._int - right.data._double);
    case Storage::DataType::CHAR:
      return _integer(left.data._int - right.data._char);
    default:
      throw std::invalid_argument("Invalid subtraction expression!");
    }
  case Storage::DataType::DOUBLE:
    switch (right.dataType) {
    case Storage::DataType::INTEGER:
      return _double(left.data._double - right.data._int);
    case Storage::DataType::DOUBLE:
      return _double(left.data._double - right.data._double);
    case Storage::DataType::CHAR:
      return _double(left.data._double - right.data._char);
    default:
      throw std::invalid_argument("Invalid subtraction expression!");
    }
  case Storage::DataType::CHAR:
    switch (right.dataType) {
    case Storage::DataType::INTEGER:
      return _integer(left.data._char - right.data._int);
    case Storage::DataType::DOUBLE:
      return _double(left.data._char - right.data._double);
    case Storage::DataType::CHAR:
      return _integer(left.data._char - right.data._char);
    default:
      throw std::invalid_argument("Invalid subtraction expression!");
    }
  default:
    throw std::invalid_argument("Invalid subtraction expression!");
  }
}

Storage::DataWrapper
BinaryExpression::multiplication(Storage::DataWrapper left,
                                 Storage::DataWrapper right) {
  switch (left.dataType) {
  case Storage::DataType::INTEGER:
    switch (right.dataType) {
    case Storage::DataType::INTEGER:
      return _integer(left.data._int * right.data._int);
    case Storage::DataType::DOUBLE:
      return _double(left.data._int * right.data._double);
    case Storage::DataType::CHAR:
      return _integer(left.data._int * right.data._char);
    case Storage::DataType::STRING:
      return stringMultiplication(*right.data._string, left.data._int);
    default:
      throw std::invalid_argument("Invalid multiplication expression!");
    }
  case Storage::DataType::DOUBLE:
    switch (right.dataType) {
    case Storage::DataType::INTEGER:
      return _double(left.data._double * right.data._int);
    case Storage::DataType::DOUBLE:
      return _double(left.data._double * right.data._double);
    case Storage::DataType::CHAR:
      return _double(left.data._double * right.data._char);
    default:
      throw std::invalid_argument("Invalid multiplication expression!");
    }
  case Storage::DataType::CHAR:
    switch (right.dataType) {
    case Storage::DataType::INTEGER:
      return _integer(left.data._char * right.data._int);
    case Storage::DataType::DOUBLE:
      return _double(left.data._char * right.data._double);
    case Storage::DataType::CHAR:
      return _integer(left.data._char * right.data._char);
    default:
      throw std::invalid_argument("Invalid multiplication expression!");
    }
  case Storage::DataType::STRING:
    switch (right.dataType) {
    case Storage::DataType::INTEGER:
      return stringMultiplication(*left.data._string, right.data._int);
    default:
      throw std::invalid_argument("Invalid multiplication expression!");
    }
  default:
    throw std::invalid_argument("Invalid multiplication expression!");
  }
}

Storage::DataWrapper BinaryExpression::division(Storage::DataWrapper left,
                                                Storage::DataWrapper right) {
  switch (left.dataType) {
  case Storage::DataType::INTEGER:
    switch (right.dataType) {
    case Storage::DataType::INTEGER:
      return _integer(left.data._int / right.data._int);
    case Storage::DataType::DOUBLE:
      return _double(left.data._int / right.data._double);
    case Storage::DataType::CHAR:
      return _integer(left.data._int / right.data._char);
    default:
      throw std::invalid_argument("Invalid division expression!");
    }
  case Storage::DataType::DOUBLE:
    switch (right.dataType) {
    case Storage::DataType::INTEGER:
      return _double(left.data._double / right.data._int);
    case Storage::DataType::DOUBLE:
      return _double(left.data._double / right.data._double);
    case Storage::DataType::CHAR:
      return _double(left.data._double / right.data._char);
    default:
      throw std::invalid_argument("Invalid division expression!");
    }
  case Storage::DataType::CHAR:
    switch (right.dataType) {
    case Storage::DataType::INTEGER:
      return _integer(left.data._char / right.data._int);
    case Storage::DataType::DOUBLE:
      return _double(left.data._char / right.data._double);
    case Storage::DataType::CHAR:
      return _integer(left.data._char / right.data._char);
    default:
      throw std::invalid_argument("Invalid division expression!");
    }
  default:
    throw std::invalid_argument("Invalid division expression!");
  }
}

Storage::DataWrapper BinaryExpression::modulus(Storage::DataWrapper left,
                                               Storage::DataWrapper right) {
  switch (left.dataType) {
  case Storage::DataType::INTEGER:
    switch (right.dataType) {
    case Storage::DataType::INTEGER:
      return _integer(left.data._int % right.data._int);
    case Storage::DataType::DOUBLE:
      return _double(std::fmod(left.data._int, right.data._double));
    case Storage::DataType::CHAR:
      return _integer(left.data._int % right.data._char);
    default:
      throw std::invalid_argument("Invalid modulus expression!");
    }
  case Storage::DataType::DOUBLE:
    switch (right.dataType) {
    case Storage::DataType::INTEGER:
      return _double(std::fmod(left.data._double, right.data._int));
    case Storage::DataType::DOUBLE:
      return _double(std::fmod(left.data._double, right.data._double));
    case Storage::DataType::CHAR:
      return _double(std::fmod(left.data._double, right.data._char));
    default:
      throw std::invalid_argument("Invalid modulus expression!");
    }
  case Storage::DataType::CHAR:
    switch (right.dataType) {
    case Storage::DataType::INTEGER:
      return _integer(left.data._char % right.data._int);
    case Storage::DataType::DOUBLE:
      return _double(std::fmod(left.data._char, right.data._double));
    case Storage::DataType::CHAR:
      return _integer(left.data._char % right.data._char);
    default:
      throw std::invalid_argument("Invalid modulus expression!");
    }
  default:
    throw std::invalid_argument("Invalid modulus expression!");
  }
}

Storage::DataWrapper
BinaryExpression::potentiation(Storage::DataWrapper left,
                               Storage::DataWrapper right) {
  switch (left.dataType) {
  case Storage::DataType::INTEGER:
    switch (right.dataType) {
    case Storage::DataType::INTEGER:
      return _integer(std::pow(left.data._int, right.data._int));
    case Storage::DataType::DOUBLE:
      return _double(std::pow(left.data._int, right.data._double));
    case Storage::DataType::CHAR:
      return _integer(std::pow(left.data._int, right.data._char));
    default:
      throw std::invalid_argument("Invalid potentiation expression!");
    }
  case Storage::DataType::DOUBLE:
    switch (right.dataType) {
    case Storage::DataType::INTEGER:
      return _double(std::pow(left.data._double, right.data._int));
    case Storage::DataType::DOUBLE:
      return _double(std::pow(left.data._double, right.data._double));
    case Storage::DataType::CHAR:
      return _double(std::pow(left.data._double, right.data._char));
    default:
      throw std::invalid_argument("Invalid potentiation expression!");
    }
  case Storage::DataType::CHAR:
    switch (right.dataType) {
    case Storage::DataType::INTEGER:
      return _integer(std::pow(left.data._char, right.data._int));
    case Storage::DataType::DOUBLE:
      return _double(std::pow(left.data._char, right.data._double));
    case Storage::DataType::CHAR:
      return _integer(std::pow(left.data._char, right.data._char));
    default:
      throw std::invalid_argument("Invalid potentiation expression!");
    }
  default:
    throw std::invalid_argument("Invalid potentiation expression!");
  }
}

Storage::DataWrapper BinaryExpression::stringAddition(std::string left,
                                                      std::string right) {
  return Storage::DataWrapper(Storage::WrapperType::VALUE,
                              Storage::DataType::STRING,
                              new std::string(left + right));
}

Storage::DataWrapper BinaryExpression::stringMultiplication(std::string value,
                                                            int multiplier) {
  std::string result = "";
  for (int i = 0; i < multiplier; ++i) {
    result += value;
  }
  return Storage::DataWrapper(Storage::WrapperType::VALUE,
                              Storage::DataType::STRING,
                              new std::string(result));
}
