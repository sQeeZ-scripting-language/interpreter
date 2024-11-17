#include "interpreter/utils.hpp"

bool checkTrueishness(const std::unique_ptr<Expr> &expr, std::shared_ptr<Storage> storage) {
  Storage::DataWrapper datawrapper = Expression(expr.get(), storage).execute();
  switch (datawrapper.dataType) {
    case Storage::DataType::BOOLEAN:
        return datawrapper.data._bool;
    case Storage::DataType::INTEGER:
        return datawrapper.data._int != 0;
    case Storage::DataType::DOUBLE:
        return datawrapper.data._double != 0.0;
    case Storage::DataType::STRING:
        return !datawrapper.data._string->empty();
    case Storage::DataType::CHAR:
        return datawrapper.data._char != '\0';
    case Storage::DataType::_NULL:
    default:
        return false;
    }
}