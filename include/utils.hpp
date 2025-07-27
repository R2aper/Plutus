#pragma once

#include <string>

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

  friend std::ostream &operator<<(std::ostream &os, const Category &ct) {
    os << "Id: " << ct.id << std::endl
       << "Name: " << ct.name << std::endl
       << "Excpected ammount: " << ct.expected_amount << std::endl
       << "Available amount: " << ct.available_amount << std::endl
       << "Spent amount: " << ct.spent_amount;
    return os;
  }
};

/// @brief struct for storing Transaction's data
struct Transaction {
  int64 id;
  std::string date;
  std::string note;
  double amount;
  int64 category_id;
  std::string category;

  friend std::ostream &operator<<(std::ostream &os, const Transaction &tr) {
    os << "Id: " << tr.id << std::endl
       << "Date: " << tr.date << std::endl
       << "Note: " << tr.note << std::endl
       << "Amount: " << tr.amount << std::endl
       << "Category id: " << tr.category_id << std::endl
       << "Category name: " << tr.category;
    return os;
  }
};

}; // namespace Plutus
