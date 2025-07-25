#pragma once

#include <string>

#ifdef _WIN32
#define PATH fs::path(std::string("homedir") + std::string("\\Documents\\ft\\"))
#else
#define PATH fs::path(std::string(getenv("HOME")) + std::string("/Documents/ft/"))
#endif

using uint64 = unsigned long long;
using int64 = long long;
using int32 = int;
using uint32 = unsigned int;
using uint8 = unsigned char;
using int8 = char;
using int16 = short;
using uint16 = unsigned short;

namespace Plutus {

struct Category {
  uint64 id;
  std::wstring name;
  double expected_amount;
  double available_amount;
  double spent_amount;
};

struct Transaction {
  uint64 id;
  std::wstring date;
  std::wstring note;
  double amount;
  uint64 category_id;
};

}; // namespace Plutus
