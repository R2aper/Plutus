#pragma once

#include "controllers/abstract.hpp"

#include "models/category.hpp"
#include "utils.hpp"

namespace Plutus {

struct Category;

class CategoryController : public AbstractController {
public:
  explicit CategoryController(std::shared_ptr<Table> table, std::shared_ptr<sql::Database> db);

  /// @brief Insert Category into 'categoreis' table of database
  /// @param ct New category
  /// @return Result struct with boolean indicator of succes and std::string of error message
  Result Insert(Category &ct);

  /// @brief Remove Category from database by id
  /// @param id Id of category to remove
  /// @return Result struct with boolean indicator of succes and std::string of error message
  Result Remove(int64 id);

  /// @brief Update existing Category in database by id
  /// @param id Id of category to update
  /// @param new_name New name of Category
  /// @return Result struct with boolean indicator of succes and std::string of error message
  Result Update(int64 id, const std::string &new_name);

  /// @brief Fetch table with database
  void UpdateTable() override;
};

} // namespace Plutus
