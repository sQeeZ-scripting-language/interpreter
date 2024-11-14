#include "interpreter/expressions/binary_expression.hpp"

BinaryExpression::BinaryExpression(BinaryExpr *expressionNode,
                                   std::shared_ptr<Storage> storage)
    : expressionNode(expressionNode), storage(std::move(storage)) {}

Storage::DataWrapper BinaryExpression::execute() {
    if (expressionNode->operator_.tag == Token::TypeTag::OPERATOR) {
        switch (expressionNode->operator_.type.operatorToken) {
        case OperatorToken::ADDITION:
            return addition(Expression(expressionNode->left.get(), storage).execute(), Expression(expressionNode->right.get(), storage).execute());
            break;
        case OperatorToken::SUBTRACTION:
            break;
        case OperatorToken::MULTIPLICATION:
            break;
        case OperatorToken::DIVISION:
            break;
        case OperatorToken::MODULUS:
            break;
        
        default:
            throw std::runtime_error("Unsupported binary operator.");
        }
    } else {
        throw std::runtime_error("Unsupported binary expression.");
    }
}

Storage::DataWrapper BinaryExpression::addition(Storage::DataWrapper left, Storage::DataWrapper right) {
    if (left.dataType == Storage::DataType::INTEGER && right.dataType == Storage::DataType::INTEGER) {
        std::cout << "Adding " << left.data._int << " and " << right.data._int << std::endl;
        return Storage::DataWrapper(Storage::WrapperType::VALUE, Storage::DataType::INTEGER, left.data._int + right.data._int);
    } else {
        throw std::runtime_error("Unsupported addition operation.");
    }
}