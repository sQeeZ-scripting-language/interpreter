#ifndef NODE_PARSER_HPP
#define NODE_PARSER_HPP

#include <napi.h>

#include "interpreter/interpreter.hpp"

Napi::Object logToJSObject(const Napi::Env &env, const Log &log);
Napi::Array logsToJSArray(const Napi::Env &env,
                          const std::shared_ptr<Logs> &logs);

#endif // NODE_PARSER_HPP