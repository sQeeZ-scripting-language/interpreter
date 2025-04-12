#include "interpreter/node/node_parser.hpp"

Napi::Object logToJSObject(const Napi::Env &env, const Log &log) {
  Napi::Object obj = Napi::Object::New(env);
  obj.Set("value", log.value);
  obj.Set("type", log.getTypeString());
  if (log.type == COLORED) {
    obj.Set("color", log.color);
  }
  return obj;
}

Napi::Array logsToJSArray(const Napi::Env &env,
                          const std::shared_ptr<Logs> &logs) {
  Napi::Array arr = Napi::Array::New(env, logs->logs.size());
  for (size_t i = 0; i < logs->logs.size(); ++i) {
    arr.Set(i, logToJSObject(env, logs->logs[i]));
  }
  return arr;
}