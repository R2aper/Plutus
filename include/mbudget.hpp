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

  MonthlyBudget();

  MonthlyBudget(int64 _id, const Category &ct, int _year, int _month, double _expected_amount,
                double _available_amount, double _spent_amount);

  /// @brief return string representation of MonthlyBudget
  std::vector<std::string> ToColumn() const;

  friend std::ostream &operator<<(std::ostream &os, const MonthlyBudget &mb);
  friend std::istream &operator>>(std::istream &is, MonthlyBudget &mb);
};

}; // namespace Plutus
