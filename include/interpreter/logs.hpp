#ifndef LOGS_HPP
#define LOGS_HPP

#include <string>
#include <vector>

enum LogType { LOG, WARN, ERROR, COLORED };

class Log {
public:
  std::string value;
  LogType type;
  std::string color;

  Log(const std::string &val, LogType t, const std::string &col = "")
      : value(val), type(t), color(col) {}

  std::string getTypeString() const {
    switch (type) {
    case LOG:
      return "LOG";
    case WARN:
      return "WARN";
    case ERROR:
      return "ERROR";
    case COLORED:
      return "COLORED";
    default:
      return "UNKNOWN";
    }
  }
};

class Logs {
public:
  std::vector<Log> logs;

  void add(const std::string &value, LogType type,
           const std::string &color = "") {
    logs.emplace_back(value, type, color);
  }
};

#endif // LOGS_HPP
