#include "interpreter/expressions/binary_expression.hpp"

BinaryExpression::BinaryExpression(BinaryExpr *expressionNode,
                                   std::shared_ptr<Storage> storage)
    : expressionNode(expressionNode), storage(std::move(storage)) {}

Storage::DataWrapper BinaryExpression::execute() {
    if (expressionNode->operator_.tag == Token::TypeTag::OPERATOR) {
        switch (expressionNode->operator_.type.operatorToken) {
        case OperatorToken::ADDITION:
            return addition(Expression(expressionNode->left.get(), storage).execute(), Expression(expressionNode->right.get(), storage).execute());
        case OperatorToken::SUBTRACTION:
            return subtraction(Expression(expressionNode->left.get(), storage).execute(), Expression(expressionNode->right.get(), storage).execute());
        case OperatorToken::MULTIPLICATION:
            return multiplication(Expression(expressionNode->left.get(), storage).execute(), Expression(expressionNode->right.get(), storage).execute());
        case OperatorToken::DIVISION:
            return division(Expression(expressionNode->left.get(), storage).execute(), Expression(expressionNode->right.get(), storage).execute());
        case OperatorToken::MODULUS:
            return modulus(Expression(expressionNode->left.get(), storage).execute(), Expression(expressionNode->right.get(), storage).execute());
        
        default:
            throw std::runtime_error("Unsupported binary operator.");
        }
    } else {
        throw std::runtime_error("Unsupported binary expression.");
    }
}

Storage::DataWrapper BinaryExpression::addition(Storage::DataWrapper left, Storage::DataWrapper right) {
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
                    return stringAddition(std::to_string(left.data._int), *right.data._string);
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
                    return stringAddition(std::to_string(left.data._double), *right.data._string);
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
                    return stringAddition(std::string(1, left.data._char), *right.data._string);
                default:
                    throw std::invalid_argument("Invalid addition expression!");
            }
        case Storage::DataType::STRING:
            switch (right.dataType) {
                case Storage::DataType::INTEGER:
                    return stringAddition(*left.data._string, std::to_string(right.data._int));
                case Storage::DataType::DOUBLE:
                    return stringAddition(*left.data._string, std::to_string(right.data._double));
                case Storage::DataType::CHAR:
                    return stringAddition(*left.data._string, std::string(1, right.data._char));
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

Storage::DataWrapper BinaryExpression::subtraction(Storage::DataWrapper left, Storage::DataWrapper right) {
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

Storage::DataWrapper BinaryExpression::multiplication(Storage::DataWrapper left, Storage::DataWrapper right) {
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

Storage::DataWrapper BinaryExpression::division(Storage::DataWrapper left, Storage::DataWrapper right) {
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

Storage::DataWrapper BinaryExpression::modulus(Storage::DataWrapper left, Storage::DataWrapper right) {
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

Storage::DataWrapper BinaryExpression::_integer(int value) {
    return Storage::DataWrapper(Storage::WrapperType::VALUE, Storage::DataType::INTEGER, value);
}

Storage::DataWrapper BinaryExpression::_double(double value) {
    return Storage::DataWrapper(Storage::WrapperType::VALUE, Storage::DataType::DOUBLE, value);
}

Storage::DataWrapper BinaryExpression::stringAddition(std::string left, std::string right) {
    return Storage::DataWrapper(Storage::WrapperType::VALUE, Storage::DataType::STRING, new std::string(left + right));
}

Storage::DataWrapper BinaryExpression::stringMultiplication(std::string value, int multiplier) {
    std::string result = "";
    for (int i = 0; i < multiplier; i++) {
        result += value;
    }
    return Storage::DataWrapper(Storage::WrapperType::VALUE, Storage::DataType::STRING, new std::string(result));
}
