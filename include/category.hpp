#pragma once

#include "utils.hpp"

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
  friend std::istream &operator>>(std::istream &is, Category &ct);
};

using Categories = std::vector<Category>;

} // namespace Plutus