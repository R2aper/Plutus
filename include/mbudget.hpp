#pragma once

#include "category.hpp"
#include "utils.hpp"

namespace Plutus {

struct MonthlyBudget {
  int64 id;
  Category category;
  int year;
  int month;
  double expected_amount;
  double available_amount;
  double spent_amount;

  /// @brief return string representation of MonthlyBudget
  std::vector<std::string> ToColumn() const;

  friend std::ostream &operator<<(std::ostream &os, const MonthlyBudget &mb);
  friend std::istream &operator>>(std::istream &is, MonthlyBudget &mb);
};

}; // namespace Plutus
