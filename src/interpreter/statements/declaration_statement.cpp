#include "interpreter/statements/declaration_statement.hpp"

DeclarationStatement::DeclarationStatement(FunctionDeclaration *declarationNode, std::shared_ptr<Storage> storage)
    : declarationNode(declarationNode), storage(std::move(storage)) {}

DeclarationStatement::DeclarationStatement(VarDeclaration *declarationNode, std::shared_ptr<Storage> storage)
    : declarationNode(declarationNode), storage(std::move(storage)) {}

void DeclarationStatement::execute() {
    if (std::holds_alternative<VarDeclaration*>(declarationNode)) {
        auto varDeclaration = std::get<VarDeclaration*>(declarationNode);
        for (const auto &declaration : varDeclaration->declarations) {
            if (declaration.second) {
                if (auto expr = dynamic_cast<IntegerLiteral*>(declaration.second.get())) {
                    storage->setValue(declaration.first.value, Storage::StorageType::VARIABLE, Storage::DataType::INTEGER, expr->value);
                } else if (auto expr = dynamic_cast<DoubleLiteral*>(declaration.second.get())) {
                    storage->setValue(declaration.first.value, Storage::StorageType::VARIABLE, Storage::DataType::DOUBLE, expr->value);
                } else if (auto expr = dynamic_cast<BooleanLiteral*>(declaration.second.get())) {
                    storage->setValue(declaration.first.value, Storage::StorageType::VARIABLE, Storage::DataType::BOOLEAN, expr->value);
                } else if (auto expr = dynamic_cast<CharLiteral*>(declaration.second.get())) {
                    storage->setValue(declaration.first.value, Storage::StorageType::VARIABLE, Storage::DataType::CHAR, expr->value);
                } else if (auto expr = dynamic_cast<StringLiteral*>(declaration.second.get())) {
                    storage->setValue(declaration.first.value, Storage::StorageType::VARIABLE, Storage::DataType::STRING, new std::string(expr->value));
                } else if (auto expr = dynamic_cast<HexCodeLiteral*>(declaration.second.get())) {
                    storage->setValue(declaration.first.value, Storage::StorageType::VARIABLE, Storage::DataType::HEXCODE, new std::string(expr->value));
                } else {
                    throw std::invalid_argument("Unknown literal type!");
                }
            }
        }
    } else if (std::holds_alternative<FunctionDeclaration*>(declarationNode)) {
        auto functionDeclaration = std::get<FunctionDeclaration*>(declarationNode);
        std::shared_ptr<FunctionDeclaration> funcPtr = std::shared_ptr<FunctionDeclaration>(functionDeclaration);
        storage->storeFunction(funcPtr->name.value, funcPtr);
    }
}

