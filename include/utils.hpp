#pragma once

#include <iostream>
#include <string>
#include <vector>

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

namespace Plutus {

/// @brief struct for storing Category's data
struct Category {
  int64 id;
  std::string name;
  double expected_amount;
  double available_amount;
  double spent_amount;

  /// @brief return string representation of Category
  std::vector<std::string> ToColumn() const;

  friend std::ostream &operator<<(std::ostream &os, const Category &ct);
};

/// @brief struct for storing Transaction's data
struct Transaction {
  // Currency curr;
  int64 id;
  std::string date;
  std::string note;
  double amount;
  int64 category_id;
  std::string category;

  /// @brief return string representation of Transaction
  std::vector<std::string> ToColumn() const;

  friend std::ostream &operator<<(std::ostream &os, const Transaction &tr);
};

using Categories = std::vector<Category>;
using Transactions = std::vector<Transaction>;
using Table = std::vector<std::vector<std::string>>;

}; // namespace Plutus
