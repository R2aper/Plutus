#pragma once

#include <string>
#include <vector>

#include "category.hpp"
#include "utils.hpp"

namespace Plutus {

enum TRANSACTION_TYPE { INCOME, EXPENSE };

/// @brief struct for storing Transaction's data
struct Transaction {
  // Currency curr;
  int64 id;
  std::string date;
  std::string note;
  double amount;
  TRANSACTION_TYPE type;
  Category category;

  Transaction();

  Transaction(int64 _id, const std::string &_date, const std::string &_note, double _amount,
              const Category &ct);

  /// @brief return string representation of Transaction
  std::vector<std::string> ToColumn() const;

  friend std::ostream &operator<<(std::ostream &os, const Transaction &tr);
  friend std::istream &operator>>(std::istream &is, Transaction &tr);
};

using Transactions = std::vector<Transaction>;

}; // namespace Plutus