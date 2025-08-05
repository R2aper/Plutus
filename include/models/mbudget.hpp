#pragma once

#include "category.hpp"
#include "utils.hpp"

namespace Plutus {

struct MonthlyBudget {
  int64 id;
  Category category;
  int year;
  int month;
  double budget_amount;
  double actual_amount;
  double difference_amount;

  MonthlyBudget();

  MonthlyBudget(int64 _id, const Category &ct, int _year, int _month, double _budget_amount,
                double _actual_amount, double _difference_amount);

  /// @brief return string representation of MonthlyBudget
  std::vector<std::string> ToColumn() const;

  friend std::ostream &operator<<(std::ostream &os, const MonthlyBudget &mb);
  friend std::istream &operator>>(std::istream &is, MonthlyBudget &mb);
};

}; // namespace Plutus
