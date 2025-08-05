#pragma once

#include <SQLiteCpp/SQLiteCpp.h>
#include <string>
#include <vector>

namespace sql = SQLite;

#ifdef _WIN32
#define PATH fs::path(std::string("homedir") + std::string("\\Documents\\ft\\"))
#else
#define PATH fs::path(std::string(getenv("HOME")) + std::string("/Documents/ft/"))
#endif

using uint64 = unsigned long;
using int64 = signed long;
using int32 = int;
using uint32 = unsigned int;
using int16 = short;
using uint16 = unsigned short;

using Table = std::vector<std::vector<std::string>>;

namespace Plutus {
struct Result {
  bool is_success;
  std::string error_msg;

  friend bool operator!(const Result &r) { return r.is_success != true; }
};

}; // namespace Plutus
